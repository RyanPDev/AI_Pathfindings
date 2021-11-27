#include "AStar.h"

AStar::AStar()
{
}

AStar::~AStar()
{
}

void AStar::CalculatePath(Graph graph, Path& path, Vector2D start, Vector2D goal)
{
	float newCost = 0;
	count = 1;
	start = pix2cell(start);

	graph.nodes[start.y][start.x]->cameFrom = graph.nodes[start.y][start.x];

	frontier.push(graph.nodes[start.y][start.x]);

	Graph::Node* current = nullptr;

	while (!frontier.empty())
	{
		current = frontier.top();
		frontier.pop();

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

void AStar::Clear(std::priority_queue<Graph::Node*, std::vector<Graph::Node*>, ComparePriority>& q, Graph graph)
{
	for (int i = 0; i < graph.nodes.size(); i++)
		for (int j = 0; j < graph.nodes[i].size(); j++)
		{
			graph.nodes[i][j]->cameFrom = nullptr;
			graph.nodes[i][j]->costSoFar = 0;
			graph.nodes[i][j]->heuristic = 0;
			graph.nodes[i][j]->priority = 0;

		}

	std::priority_queue < Graph::Node*, std::vector<Graph::Node*>, ComparePriority > empty;
	std::swap(q, empty);
}
float AStar::Heuristic(Vector2D node, Vector2D goal)
{
	float dx = abs(node.x - goal.x);
	float dy = abs(node.y - goal.y);
	return D * (dx + dy) + (D2 - 2 * D) * std::min(dx, dy);
}
