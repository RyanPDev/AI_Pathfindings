#include "Astar.h"

Astar::Astar()
{
}

Astar::~Astar()
{
}

void Astar::CalculatePath(Graph graph, Path& path, Vector2D start, Vector2D goal)
{
	float newCost = 0;
	count = 1;
	start = pix2cell(start);
	graph.nodes[start.y][start.x]->cameFrom = graph.nodes[start.y][start.x];
	frontier.push(graph.nodes[start.y][start.x]);
	Graph::Node* current = nullptr;
	while (!frontier.empty()) // while frontier is not empty
	{
		current = frontier.top();
		frontier.pop(); // take node out of frontier

		if (pix2cell(current->position) == goal) //early exit
		{
			GetPath(path, start, current);
			Clear(frontier, graph);
			break;
		}

		for (Graph::Node* next : current->neighbours)
		{
			newCost = current->costSoFar + next->weight;
			if (next->cameFrom == nullptr || newCost < next->costSoFar)
			{
				count++;
				next->costSoFar = newCost;
				if (next->heuristic == 0)
					next->heuristic = Heuristic(pix2cell(next->position), goal);

				next->priority = newCost + next->heuristic;
				next->cameFrom = current;
				frontier.push(next);
			}
		}
	}
	std::cout << "Numero de nodes afegits a la frontera: " << count << std::endl;
}

void Astar::Clear(std::priority_queue<Graph::Node*, std::vector<Graph::Node*>, ComparePriority>& q, Graph graph)
{
	for (int i = 0; i < graph.nodes.size(); i++)
		for (int j = 0; j < graph.nodes[i].size(); j++)
		{
			//Reset Node
			graph.nodes[i][j]->cameFrom = nullptr;
			graph.nodes[i][j]->costSoFar = 0;
			graph.nodes[i][j]->heuristic = 0;
			graph.nodes[i][j]->priority = 0;

		}

	std::priority_queue < Graph::Node*, std::vector<Graph::Node*>, ComparePriority > empty;
	std::swap(q, empty);
}
