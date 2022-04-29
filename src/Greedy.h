#pragma once
#include "Pathfinding.h"
#include <queue>
class Greedy :
    public Pathfinding
{
	private:
		struct CompareHeuristic {
			bool operator() (Graph::Node* n1, Graph::Node* n2)
			{
				return n1->heuristic > n2->heuristic;
			}
		};
		std::priority_queue < Graph::Node*, std::vector<Graph::Node*>, CompareHeuristic > frontier;
	public:
		Greedy();
		~Greedy();
		void CalculatePath(Graph, Path&, Vector2D, Vector2D);
		
		void Clear(std::priority_queue < Graph::Node*, std::vector<Graph::Node*>, CompareHeuristic >&q, Graph graph);
};


