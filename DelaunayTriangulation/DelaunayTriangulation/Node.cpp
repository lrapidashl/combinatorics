#include "Node.h"

Node::Node()
{
}

Node::Node(double x, double y) :
	m_x(x),
	m_y(y)
{
}

bool Node::operator==(const Node& node)
{
	return m_x == node.GetX() && m_y == node.GetY();
}

Node Node::operator-(const Node& node)
{
	return Node(m_x - node.GetX(), m_y - GetY());
}

double Node::operator^(const Node& node)
{
	return m_x * node.GetY() - m_y * node.GetX();
}

std::ostream& Node::operator<<(std::ostream& os)
{
	return os << "( " << m_x << ", " << m_y << " )";
}

double Node::GetX() const
{
	return m_x;
}

double Node::GetY() const
{
	return m_y;
}