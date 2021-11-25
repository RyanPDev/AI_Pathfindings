#pragma once
#include "Vector2D.h"
#include "Graph.h"
#include "Path.h"
#include <algorithm>


class Pathfinding
{
protected:
	void GetPath(Path&, Vector2D, Graph::Node*);

public:
	Pathfinding();
	~Pathfinding();

	virtual void CalculatePath(Graph, Path&, Vector2D, Vector2D) = 0;
	Vector2D pix2cell(Vector2D pix)
	{
		return Vector2D((float)((int)pix.x / CELL_SIZE), (float)((int)pix.y / CELL_SIZE));
	}
};