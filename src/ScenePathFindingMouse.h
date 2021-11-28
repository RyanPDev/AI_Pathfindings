#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>
#include "Scene.h"
#include "Agent.h"
#include "Seek.h"
#include "PathFollowing.h"
#include "Grid.h"
#include "Graph.h"

class ScenePathFindingMouse :
	public Scene
{
public:
	ScenePathFindingMouse();
	~ScenePathFindingMouse();
	void update(float dtime, SDL_Event* event);
	void draw();
	const char* getTitle();

private:
	int count = 1;

	std::vector<Agent*> agents;
	const int NUM_AGENTS = 2;
	const int MAX_COINS = 5;
	std::vector<Vector2D*> coinsPosition;
	void ReplaceCoinPosition(Vector2D&);

	Grid* maze;
	bool draw_grid;
	Graph graph;

	void drawMaze();
	void drawCoin();
	SDL_Texture* background_texture;
	SDL_Texture* coin_texture;
	bool loadTextures(char* filename_bg, char* filename_coin);
};
