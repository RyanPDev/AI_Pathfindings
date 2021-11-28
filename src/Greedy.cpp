#include "Greedy.h"

Greedy::Greedy()
{
}

Greedy::~Greedy()
{
}

void Greedy::CalculatePath(Graph graph, Path& path, Vector2D start, Vector2D goal)
{
	count = 1;
	start = pix2cell(start);
	while(graph.nodes[start.y][start.x] == nullptr)
	{
		Vector2D aux = goal - start;
		aux.Normalize();

		start += aux;
	}
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
			if (next->cameFrom == nullptr)
			{
				count++;
				next->heuristic = Heuristic(pix2cell(next->position), goal);
				next->cameFrom = current;
				frontier.push(next);
			}
		}
	}
	std::cout << "Numero de nodes explorats: " << count << std::endl;
}

void Greedy::Clear(std::priority_queue<Graph::Node*, std::vector<Graph::Node*>, CompareHeuristic>& q, Graph graph)
{
	for (int i = 0; i < graph.nodes.size(); i++)
		for (int j = 0; j < graph.nodes[i].size(); j++)
		{
			graph.nodes[i][j]->cameFrom = nullptr;
			graph.nodes[i][j]->heuristic = 0;
		}

	std::priority_queue < Graph::Node*, std::vector<Graph::Node*>, CompareHeuristic > empty;
	std::swap(q, empty);
}