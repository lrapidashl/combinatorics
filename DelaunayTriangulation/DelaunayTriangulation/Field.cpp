#include "Field.h"
#include <algorithm>
#include <stdexcept>

Field::Field(double x1, double y1, double x2, double y2) :
	m_upperLeftCorner(x1, y1),
	m_bottomRightCorner(x2, y2)
{
	if (x1 >= x2 || y1 >= y2)
	{
		throw std::invalid_argument("Неверные границы поля");
	}
}

Field::Field(const std::vector<Node>& nodes)
{
	std::vector<double> xCoords;
	std::vector<double> yCoords;
	for (const Node& node : nodes)
	{
		xCoords.push_back(node.GetX());
		yCoords.push_back(node.GetY());
		m_nodes.push_back(std::make_shared<Node>(node));
	}
	std::sort(xCoords.begin(), xCoords.end());
	std::sort(yCoords.begin(), yCoords.end());
	m_upperLeftCorner = Node(xCoords[0] - EPSILON, yCoords[yCoords.size() - 1] - EPSILON);
	m_bottomRightCorner = Node(xCoords[xCoords.size() - 1] + EPSILON, yCoords[0] + EPSILON);
}

Node Field::GetUpperLeftCorner() const
{
	return m_upperLeftCorner;
}

Node Field::GetBottomRightCorner() const
{
	return m_bottomRightCorner;
}

double Field::GetWidth() const
{
	return m_bottomRightCorner.GetX() - m_upperLeftCorner.GetX();
}

double Field::GetHeight() const
{
	return m_bottomRightCorner.GetY() - m_upperLeftCorner.GetY();
}

std::vector<std::shared_ptr<Node>> Field::GetNodes() const
{
	return m_nodes;
}

int Field::GetCount() const
{
	return (int)m_nodes.size();
}
