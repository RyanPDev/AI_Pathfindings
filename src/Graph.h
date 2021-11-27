#pragma once
#include <vector>
#include "Vector2D.h"
#include "SDL_SimpleApp.h"

class Graph
{
public:
	Graph();
	Graph(std::vector<std::vector<int>>);
	void AddAllNeighbours();

	void DrawGraph();

	struct Node {
		Vector2D position;
		float weight, heuristic, priority;
		std::vector<Node*> neighbours;
		Node* cameFrom; //parent node
		int costSoFar; // cost so far for each node
		bool isValid;
		Node(Vector2D cellPos, float _weight) : weight(_weight)
		{
			position = cell2pix(cellPos);
			isValid = weight != 0;
			cameFrom = nullptr;
			costSoFar = 0;
			heuristic = priority = 0;
		}

		Vector2D cell2pix(Vector2D cell)
		{
			int offset = CELL_SIZE / 2;
			return Vector2D(cell.x * CELL_SIZE + offset, cell.y * CELL_SIZE + offset);
		}		
	};
	std::vector<std::vector<Node*>> nodes;	
};