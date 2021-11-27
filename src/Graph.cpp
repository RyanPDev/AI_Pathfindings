#include "Graph.h"

Graph::Graph()
{
}

Graph::Graph(std::vector<std::vector<int>> terrain)
{
	std::vector<Node*> aux;
	for (int i = 0; i < terrain.size(); i++)
	{
		for (int j = 0; j < terrain[i].size(); j++)
		{
			Node* n = new Node({ (float)j, (float)i }, terrain[i][j]);
			aux.push_back(n);
		}
		nodes.push_back(aux);
		aux.clear();
	}
	AddAllNeighbours();
}

void Graph::AddAllNeighbours()
{
	for (int i = 0; i < nodes.size(); i++)
		for (int j = 0; j < nodes[i].size(); j++)
		{
			if (nodes[i][j]->isValid) // the node is not wall
			{
				// 8 directions
				if ((j - 1) >= 0 && nodes[i][j - 1]->isValid) // left neighbour
				{
					nodes[i][j]->neighbours.push_back(nodes[i][j - 1]);
				}

				if ((j + 1) < nodes[0].size() && nodes[i][j + 1]->isValid) // right neighbour
				{
					nodes[i][j]->neighbours.push_back(nodes[i][j + 1]);
				}
				if ((i - 1) >= 0 && nodes[i - 1][j]->isValid) // up neighbour
				{
					nodes[i][j]->neighbours.push_back(nodes[i - 1][j]);
					if ((j - 1) >= 0 && nodes[i - 1][j - 1]->isValid) // up left neighbour
					{
						nodes[i][j]->neighbours.push_back(nodes[i - 1][j - 1]);
					}

					if ((j + 1) < nodes[0].size() && nodes[i - 1][j + 1]->isValid) // up right neighbour
					{
						nodes[i][j]->neighbours.push_back(nodes[i - 1][j + 1]);
					}
				}

				if ((i + 1) < nodes.size() && nodes[i + 1][j]->isValid) // down neighbour
				{
					nodes[i][j]->neighbours.push_back(nodes[i + 1][j]);
					if ((j - 1) >= 0 && nodes[i + 1][j - 1]->isValid) // down left neighbour
					{
						nodes[i][j]->neighbours.push_back(nodes[i + 1][j - 1]);
					}

					if ((j + 1) < nodes[0].size() && nodes[i + 1][j + 1]->isValid) // down right neighbour
					{
						nodes[i][j]->neighbours.push_back(nodes[i + 1][j + 1]);
					}
				}

			}
		}
}

//void Graph::DrawGraph()
//{
//	for (int i = 0; i < nodes.size(); i++)
//	{
//		for (int j = 0; j < nodes[0].size(); j++)
//		{
//			if (nodes[i][j]->isValid)
//				std::cout << " ";
//			else
//				std::cout << char(254);
//		}
//		std::cout << std::endl;
//	}
//}