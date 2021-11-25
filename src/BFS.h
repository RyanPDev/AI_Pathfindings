#pragma once
#include "Pathfinding.h"
#include <queue>

class BFS : public Pathfinding
{
private:
	std::queue<Graph::Node*> frontier;
public:
	BFS();
	~BFS();
	void CalculatePath(Graph, Path&, Vector2D, Vector2D);
	void clear(std::queue<Graph::Node*>& q, Graph graph);
};