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
	struct Table {
		Vector2D start;
		Vector2D goal;
	}table[20];

	int count = 0;

	std::vector<Agent*> agents;
	Vector2D coinPosition;
	void ReplaceCoinPosition();

	Grid* maze;
	bool draw_grid;
	Graph graph;

	void drawMaze();
	void drawCoin();
	SDL_Texture* background_texture;
	SDL_Texture* coin_texture;
	bool loadTextures(char* filename_bg, char* filename_coin);

};
