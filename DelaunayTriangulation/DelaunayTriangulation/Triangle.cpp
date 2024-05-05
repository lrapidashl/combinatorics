#include "Triangle.h"

Triangle::Triangle(const Node& node1, const Node& node2, const Node& node3)
{
	m_nodes.resize(VERTEX_NUMBER);
	m_triangles.resize(VERTEX_NUMBER);
	m_nodes[0] = std::make_shared<Node>(node1);
	m_nodes[1] = std::make_shared<Node>(node2);
	m_nodes[2] = std::make_shared<Node>(node3);
	m_triangles[0] = nullptr;
	m_triangles[1] = nullptr;
	m_triangles[2] = nullptr;
}

std::vector<std::shared_ptr<Node>> Triangle::GetNodes() const
{
	return m_nodes;
}

std::vector<std::shared_ptr<Triangle>> Triangle::GetTriangles() const
{
	return m_triangles;
}

void Triangle::AddAdjactionTriangle(std::shared_ptr<Triangle> triangle, int index)
{
	m_triangles[index] = triangle;
}
