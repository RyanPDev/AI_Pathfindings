#include "Pathfinding.h"

Pathfinding::Pathfinding() { count = 1; }
Pathfinding::~Pathfinding() {}

//Heuristic calculated that we use --> Diagonal Octile (8 ways)
float Pathfinding::Heuristic(Vector2D node, Vector2D goal)
{
	float dx = abs(node.x - goal.x);
	float dy = abs(node.y - goal.y);
	return D * (dx + dy) + (D2 - 2 * D) * std::min(dx, dy);
}

//Once the algorithm has found the goal, we check the "camefrom" variable for each node from the goal to start and then reverse it on the path
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