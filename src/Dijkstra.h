#pragma once
#include "Pathfinding.h"
#include <queue>
class Dijkstra :
	public Pathfinding
{
private:
	struct CompareWeight {
		bool operator() (Graph::Node* n1, Graph::Node* n2)
		{
			return n1->costSoFar > n2->costSoFar;
		}
	};
	std::priority_queue < Graph::Node*, std::vector<Graph::Node*>, CompareWeight > frontier;

public:
	Dijkstra();
	~Dijkstra();
	void CalculatePath(Graph, Path&, Vector2D, Vector2D);
	void Clear(std::priority_queue < Graph::Node*, std::vector<Graph::Node*>, CompareWeight >& q, Graph graph);
};