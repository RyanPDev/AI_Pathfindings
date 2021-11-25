#include "BFS.h"

BFS::BFS() {}
BFS::~BFS() {}

void BFS::CalculatePath(Graph graph, Path& path, Vector2D start, Vector2D goal)
{
	int count = 0;
	start = pix2cell(start);

	graph.nodes[start.y][start.x]->cameFrom = graph.nodes[start.y][start.x];
	frontier.push(graph.nodes[start.y][start.x]);
	Graph::Node* current = nullptr;
	while (!frontier.empty())
	{
		current = frontier.front();
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
				count++;
				next->cameFrom = current;
			}
		}
	}
	std::cout << "Numero de nodes afegits a la frontera: " << count << std::endl;
}

void BFS::clear(std::queue<Graph::Node*>& q, Graph graph)
{
	for (int i = 0; i < graph.nodes.size(); i++)
		for (int j = 0; j < graph.nodes[i].size(); j++)
			graph.nodes[i][j]->cameFrom = nullptr;

	std::queue<Graph::Node*> empty;
	std::swap(q, empty);
}