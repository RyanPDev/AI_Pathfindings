#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>
#include "Agent.h"
#include "utils.h"


class Grid
{
public:
	Grid(char* filename);
	~Grid();

private:
	int num_cell_x;
	int num_cell_y;


public:
	
	std::vector< std::vector<int> > terrain;
	int getNumCellX();
	int getNumCellY();
	bool isValidCell(Vector2D cell);
};