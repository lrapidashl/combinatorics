#pragma once
#include "Node.h"
#include <vector>
#include <memory>

class Triangle
{
public:
	Triangle(const Node& node1, const Node& node2, const Node& node3);

	std::vector<std::shared_ptr<Node>> GetNodes() const;

	std::vector<std::shared_ptr<Triangle>> GetTriangles() const;

	void AddAdjactionTriangle(std::shared_ptr<Triangle> triangle, int index);
private:
	static const int VERTEX_NUMBER = 3;

	std::vector<std::shared_ptr<Node>> m_nodes;
	std::vector<std::shared_ptr<Triangle>> m_triangles;
};

