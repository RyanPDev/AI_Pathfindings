#include "Dijkstra.h"

Dijkstra::Dijkstra()
{

}

Dijkstra::~Dijkstra()
{

}

void Dijkstra::CalculatePath(Graph graph, Path& path, Vector2D start, Vector2D goal)
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
			//std::cout << "Current: " << current->costSoFar << "Next: " << next->costSoFar << "NewCost: " << newCost << std::endl;
			if (next->cameFrom == nullptr || newCost < next->costSoFar)
			{
				if (next->cameFrom == nullptr)
				{
					count++;
				}
				next->costSoFar = current->costSoFar + next->weight;
				next->cameFrom = current;
				frontier.push(next);
				//std::cout << "SIZE: " << frontier.size() << std::endl;
			}
		}
	}
	std::cout << "Numero de nodes afegits a la frontera: " << count << std::endl;
}

void Dijkstra::Clear(std::priority_queue < Graph::Node*, std::vector<Graph::Node*>, CompareWeight >& q, Graph graph)
{
	for (int i = 0; i < graph.nodes.size(); i++)
		for (int j = 0; j < graph.nodes[i].size(); j++)
		{
			graph.nodes[i][j]->cameFrom = nullptr;
			graph.nodes[i][j]->costSoFar = 0;
		}

	std::priority_queue < Graph::Node*, std::vector<Graph::Node*>, CompareWeight > empty;
	std::swap(q, empty);
}