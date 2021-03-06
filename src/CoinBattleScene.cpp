#include "CoinBattleScene.h"

using namespace std;

CoinBattleScene::CoinBattleScene()
{
	draw_grid = false;
	maze = new Grid("../res/maze.csv");

	graph = Graph(maze->terrain);

	loadTextures("../res/maze.png", "../res/coin.png");
	srand((unsigned int)time(NULL));

	for (int i = 0; i < NUM_AGENTS; i++)
	{
		Agent* agent = new Agent(graph, true);
		agent->loadSpriteTexture("../res/soldier.png", 4);
		agent->setBehavior(new PathFollowing);
		agent->setTarget(Vector2D(-20, -20));
		agents.push_back(agent);
	}

	for (int i = 0; i < MAX_COINS; i++)
	{
		Vector2D* c = new Vector2D;

		coinsPosition.push_back(c);
	}

	for (Vector2D* c : coinsPosition)
	{
		ReplaceCoinPosition(*c);
	}

	Vector2D rand_cell(-1, -1);
	for (Agent* a : agents)
	{
		rand_cell = (-1, -1);
		while (!maze->isValidCell(rand_cell))
			rand_cell = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));

		std::cout << "Instancia " << count << ":" << std::endl;
		count++;

		// set agent position coords to the center of a random cell
		a->setPosition(cell2pix(rand_cell));
		a->ChooseNewGoal(coinsPosition);
	}
}

CoinBattleScene::~CoinBattleScene()
{
	if (background_texture)
		SDL_DestroyTexture(background_texture);
	if (coin_texture)
		SDL_DestroyTexture(coin_texture);

	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void CoinBattleScene::update(float dtime, SDL_Event* event)
{
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_G)
			draw_grid = !draw_grid;
		if (event->key.keysym.scancode == SDL_SCANCODE_SPACE)
			drawPaths = !drawPaths;
		break;
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		break;
	default:
		break;
	}

	//Checks distance between agents. If they're close enough, start modifiying weights around them so they can evade each other
	if (CalculateDistance(agents[0]->getPosition(), agents[1]->getPosition()) < evasiveDistance)
	{
		agents[0]->graph.ResetAllWeights(maze->terrain);
		agents[0]->graph.ChangeWeights(agents[1]->getPosition(), 100000, 20000, 10000);
		agents[0]->ChooseNewGoal(coinsPosition);

		agents[1]->graph.ResetAllWeights(maze->terrain);
		agents[1]->graph.ChangeWeights(agents[0]->getPosition(), 100000, 20000, 10000);
		agents[1]->ChooseNewGoal(coinsPosition);
	}

	for (Agent* a : agents)
	{
		a->update(dtime, event);


		if (pix2cell(a->getPosition()) == *a->currentGoal)
		{
			std::cout << "Instancia " << count << ":" << std::endl;
			count++;
			for (Vector2D* c : coinsPosition)
			{
				if (a->currentGoal == c)
				{
					ReplaceCoinPosition(*c);
					break;
				}
			}
			for (Agent* a_ : agents)
			{
				a_->graph.ResetAllWeights(maze->terrain);
				a_->ChooseNewGoal(coinsPosition);
			}
		}
	}
}

void CoinBattleScene::ReplaceCoinPosition(Vector2D& coinPosition)
{
	coinPosition = Vector2D(-1, -1);
	// set the coin in a random cell (but at least 3 cells far from the agent)

	while ((!maze->isValidCell(coinPosition)) || (Vector2D::Distance(coinPosition, pix2cell(agents[0]->getPosition())) < 3))
	{
		coinPosition = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
	}
}

void CoinBattleScene::draw()
{
	drawMaze();
	drawCoin();

	if (draw_grid)
	{
		SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 255, 255, 255, 127);
		for (int i = 0; i < SRC_WIDTH; i += CELL_SIZE)
		{
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), i, 0, i, SRC_HEIGHT);
		}
		for (int j = 0; j < SRC_HEIGHT; j = j += CELL_SIZE)
		{
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), 0, j, SRC_WIDTH, j);
		}
	}

	for (Agent* a : agents)
	{
		a->draw(drawPaths); //We pass bool as a parameter to set visibility of paths to true or false with input from user
	}
}

const char* CoinBattleScene::getTitle()
{
	return "SDL Path Finding :: PathFinding Mouse Demo";
}

void CoinBattleScene::drawMaze()
{
	SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 0, 255, 255);
	SDL_Rect rect;
	Vector2D coords;
	for (int j = 0; j < maze->getNumCellY(); j++)
	{
		for (int i = 0; i < maze->getNumCellX(); i++)
		{
			if (!maze->isValidCell(Vector2D((float)i, (float)j)))
			{
				SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 0, 255, 255);
				coords = cell2pix(Vector2D((float)i, (float)j)) - Vector2D((float)CELL_SIZE / 2, (float)CELL_SIZE / 2);
				rect = { (int)coords.x, (int)coords.y, CELL_SIZE, CELL_SIZE };
				SDL_RenderFillRect(TheApp::Instance()->getRenderer(), &rect);
			}
			else {
				// Do not draw if it is not necessary (bg is already black)
			}
		}
	}
}

void CoinBattleScene::drawCoin()
{
	for (Vector2D* c : coinsPosition)
	{
		Vector2D coin_coords = cell2pix(*c);
		int offset = CELL_SIZE / 2;
		SDL_Rect dstrect = { (int)coin_coords.x - offset, (int)coin_coords.y - offset, CELL_SIZE, CELL_SIZE };
		SDL_RenderCopy(TheApp::Instance()->getRenderer(), coin_texture, NULL, &dstrect);
	}
}

bool CoinBattleScene::loadTextures(char* filename_bg, char* filename_coin)
{
	SDL_Surface* image = IMG_Load(filename_bg);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	background_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	if (image)
		SDL_FreeSurface(image);

	image = IMG_Load(filename_coin);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	coin_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	if (image)
		SDL_FreeSurface(image);

	return true;
}