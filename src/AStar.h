#pragma once
#include "Pathfinding.h"
#include <queue>
class AStar :
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
	//We use Octile diagonal distance
	const float D = 1;
	const float D2 = sqrt(2);
public:
	AStar();
	~AStar();
	void CalculatePath(Graph, Path&, Vector2D, Vector2D);
	void Clear(std::priority_queue < Graph::Node*, std::vector<Graph::Node*>, ComparePriority >& q, Graph graph);
	float Heuristic(Vector2D, Vector2D);
};

