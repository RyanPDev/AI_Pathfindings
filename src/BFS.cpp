#include "BFS.h"

BFS::BFS() {}
BFS::~BFS() {}

void BFS::CalculatePath(Graph graph, Path& path, Vector2D start, Vector2D goal)
{
	start = pix2cell(start);

	graph.nodes[start.y][start.x]->cameFrom = graph.nodes[start.y][start.x];
	frontier.push(graph.nodes[start.y][start.x]);

	while (!frontier.empty())
	{
		Graph::Node* current = frontier.front();
		frontier.pop();

		if (pix2cell(current->position) == goal) //early exit
		{
			GetPath(path, start, current);
			clear(frontier, graph);
			
			break;
		}

		for (Graph::Node* next : current->neighbours)
		{
			if (next->cameFrom == nullptr)
			{
				frontier.push(next);
				next->cameFrom = current;
			}
		}
	}
}
void BFS::clear(std::queue<Graph::Node*>& q, Graph graph)
{
	for (int i = 0; i < graph.nodes.size(); i++)
		for (int j = 0; j < graph.nodes[i].size(); j++)
			graph.nodes[i][j]->cameFrom = nullptr;

	std::queue<Graph::Node*> empty;
	std::swap(q, empty);
}