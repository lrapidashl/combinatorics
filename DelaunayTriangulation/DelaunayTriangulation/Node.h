#pragma once
#include <iostream>
#include <vector>
class Node
{
public:
	Node();

	Node(double x, double y);

	bool operator==(const Node& node);

	Node operator-(const Node& node);

	double operator^(const Node& node);

	std::ostream& operator<<(std::ostream& os);

	double GetX() const;

	void SetX(double x);

	double GetY() const;

	void SetY(double y);

	std::vector<std::shared_ptr<Node>> GetNodes();

	void AddNodeConnection(const std::shared_ptr<Node>& node);

	void DeleteNodeConnection(const std::shared_ptr<Node>& node);
private:
	double m_x = 0;
	double m_y = 0;
	std::vector<std::shared_ptr<Node>> m_nodes;
};

