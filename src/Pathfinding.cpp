#include "Pathfinding.h"

Pathfinding::Pathfinding() {}
Pathfinding::~Pathfinding() {}

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