#include "AlgorithmsScene.h"
using namespace std;

AlgorithmsScene::AlgorithmsScene()
{
	draw_grid = false;
	maze = new Grid("../res/maze.csv");

	graph = Graph(maze->terrain);

	loadTextures("../res/maze.png", "../res/coin.png");
	
	// We don't do that here
	// srand((unsigned int)time(NULL));

	Agent* agent = new Agent(graph, false);
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agent->setBehavior(new PathFollowing);
	agent->setTarget(Vector2D(-20, -20));
	agents.push_back(agent);

	// set agent position coords to the center of a random cell
	Vector2D rand_cell(-1, -1);
	while (!maze->isValidCell(rand_cell))
		rand_cell = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));

	// set the coin in a random cell (but at least 3 cells far from the agent)
	ReplaceCoinPosition();

	for (Agent* a : agents)
	{
		std::cout << "Instancia " << count << ":" << std::endl;
		count++;
		a->setPosition(cell2pix(rand_cell));
		a->clearPath();
		a->pathfinding->CalculatePath(a->graph, a->path, a->getPosition(), coinPosition);

	}
}

AlgorithmsScene::~AlgorithmsScene()
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

void AlgorithmsScene::update(float dtime, SDL_Event* event)
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

	for (Agent* a : agents)
	{
		a->update(dtime, event);
		// if we have arrived to the coin, replace it in a random cell!
		if ((pix2cell(a->getPosition()) == coinPosition))
		{
			std::cout << "Instancia " << count << ":" << std::endl;
			count++;
			ReplaceCoinPosition();
			a->clearPath();
			a->pathfinding->CalculatePath(a->graph, a->path, a->getPosition(), coinPosition);

		}
	}
}

void AlgorithmsScene::ReplaceCoinPosition()
{
	coinPosition = Vector2D(-1, -1);
	// Gets a random VALID position in the maze
	while ((!maze->isValidCell(coinPosition)) || (Vector2D::Distance(coinPosition, pix2cell(agents[0]->getPosition())) < 3))
		coinPosition = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
}

void AlgorithmsScene::draw()
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
		a->draw(drawPaths);
	}
}

const char* AlgorithmsScene::getTitle()
{
	return "SDL Path Finding :: PathFinding Mouse Demo";
}

void AlgorithmsScene::drawMaze()
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
	//Alternative: render a backgroud texture:
	//SDL_RenderCopy(TheApp::Instance()->getRenderer(), background_texture, NULL, NULL );
}

void AlgorithmsScene::drawCoin()
{
	Vector2D coin_coords = cell2pix(coinPosition);
	int offset = CELL_SIZE / 2;
	SDL_Rect dstrect = { (int)coin_coords.x - offset, (int)coin_coords.y - offset, CELL_SIZE, CELL_SIZE };
	SDL_RenderCopy(TheApp::Instance()->getRenderer(), coin_texture, NULL, &dstrect);
}

bool AlgorithmsScene::loadTextures(char* filename_bg, char* filename_coin)
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
