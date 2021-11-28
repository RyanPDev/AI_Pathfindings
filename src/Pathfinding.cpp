#include "Pathfinding.h"

Pathfinding::Pathfinding() { count = 1; }
Pathfinding::~Pathfinding() {}

float Pathfinding::Heuristic(Vector2D node, Vector2D goal)
{
	float dx = abs(node.x - goal.x);
	float dy = abs(node.y - goal.y);
	return D * (dx + dy) + (D2 - 2 * D) * std::min(dx, dy);
}

bool operator<(const Graph::Node& node1, Graph::Node& node2)
{
	return node1.weight > node2.weight;
}

void Pathfinding::GetPath(Path& path, Vector2D start, Graph::Node* goal)
{
	Graph::Node* current = goal;
	path.points.push_back(current->position);

	while (pix2cell(current->position) != start)
	{
		current = current->cameFrom;
		path.points.push_back(current->position);
	}
	std::reverse(path.points.begin(), path.points.end());
}