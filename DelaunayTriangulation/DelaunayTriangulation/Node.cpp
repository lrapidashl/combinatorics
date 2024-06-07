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
	return Node(m_x - node.GetX(), m_y - node.GetY());
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

void Node::SetX(double x)
{
	m_x = x;
}

double Node::GetY() const
{
	return m_y;
}

void Node::SetY(double y)
{
	m_y = y;
}

std::vector<std::shared_ptr<Node>> Node::GetNodes()
{
	return m_nodes;
}

void Node::AddNodeConnection(const std::shared_ptr<Node>& node)
{
	m_nodes.push_back(node);
}

void Node::DeleteNodeConnection(const std::shared_ptr<Node>& node)
{
	auto it = std::find(m_nodes.begin(), m_nodes.end(), node);
	if (it != m_nodes.end())
	{
		m_nodes.erase(it);
	}
}
