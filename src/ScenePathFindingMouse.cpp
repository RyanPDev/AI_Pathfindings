#include "ScenePathFindingMouse.h"

using namespace std;

ScenePathFindingMouse::ScenePathFindingMouse()
{
	draw_grid = false;
	maze = new Grid("../res/maze.csv");

	graph = Graph(maze->terrain);

	loadTextures("../res/maze.png", "../res/coin.png");
	srand((unsigned int)time(NULL));

	Agent* agent = new Agent(graph);
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
		a->setPosition(maze->cell2pix(rand_cell));
		a->clearPath();
		a->pathfinding->CalculatePath(a->graph, a->path, a->getPosition(), coinPosition);

	}
}

ScenePathFindingMouse::~ScenePathFindingMouse()
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

void ScenePathFindingMouse::update(float dtime, SDL_Event* event)
{
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_SPACE)
			draw_grid = !draw_grid;
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
		if ((maze->pix2cell(a->getPosition()) == coinPosition)) //
		{
			std::cout << "Instancia " << count << ":" << std::endl;
			count++;
			ReplaceCoinPosition();
			a->clearPath();
			a->pathfinding->CalculatePath(a->graph, a->path, a->getPosition(), coinPosition);
			
		}
	}
}

void ScenePathFindingMouse::ReplaceCoinPosition()
{
	coinPosition = Vector2D(-1, -1);
	while ((!maze->isValidCell(coinPosition)) || (Vector2D::Distance(coinPosition, maze->pix2cell(agents[0]->getPosition())) < 3))
		coinPosition = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
}

void ScenePathFindingMouse::draw()
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
		a->draw();
	}
}

const char* ScenePathFindingMouse::getTitle()
{
	return "SDL Path Finding :: PathFinding Mouse Demo";
}

void ScenePathFindingMouse::drawMaze()
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
				coords = maze->cell2pix(Vector2D((float)i, (float)j)) - Vector2D((float)CELL_SIZE / 2, (float)CELL_SIZE / 2);
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

void ScenePathFindingMouse::drawCoin()
{
	Vector2D coin_coords = maze->cell2pix(coinPosition);
	int offset = CELL_SIZE / 2;
	SDL_Rect dstrect = { (int)coin_coords.x - offset, (int)coin_coords.y - offset, CELL_SIZE, CELL_SIZE };
	SDL_RenderCopy(TheApp::Instance()->getRenderer(), coin_texture, NULL, &dstrect);
}

bool ScenePathFindingMouse::loadTextures(char* filename_bg, char* filename_coin)
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

//table[0].start = { 24, 13 };
//table[1].start  = { 11, 22 };
//table[2].start  = { 31, 2 };
//table[3].start  = { 25, 11 };
//table[4].start  = { 8, 7 };
//table[5].start  = { 9, 19 };
//table[6].start  = { 32, 18 };
//table[7].start  = { 26, 7 };
//table[8].start  = { 25, 21 };
//table[9].start  = { 15, 9 };
//table[10].start  = { 20, 1 };
//table[11].start  = { 21, 7 };
//table[12].start  = { 13, 2 };
//table[13].start  = { 3, 4 };
//table[14].start  = { 32, 6 };
//table[15].start  = { 16, 16 };
//table[16].start  = { 10, 17 };
//table[17].start  = { 13, 11 };
//table[18].start  = { 17, 20 };
//table[19].start  = { 20, 23 };