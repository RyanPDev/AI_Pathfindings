#pragma once
#include "Pathfinding.h"
#include <queue>
class ModifiedAStar :
    public Pathfinding
{
private:
	struct ComparePriority {
		bool operator() (Graph::Node* n1, Graph::Node* n2)
		{
			return n1->priority > n2->priority;
		}
	};
	std::priority_queue < Graph::Node*, std::vector<Graph::Node*>, ComparePriority > frontier;

	const float alpha = 0.9;
	const float beta = 0.1;

public:
	ModifiedAStar();
	~ModifiedAStar();
	void CalculatePath(Graph, Path&, Vector2D, Vector2D);
	void Clear(std::priority_queue < Graph::Node*, std::vector<Graph::Node*>, ComparePriority >& q, Graph graph);
};

