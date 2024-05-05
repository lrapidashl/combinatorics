#pragma once
#include <iostream>
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

	double GetY() const;
private:
	double m_x = 0;
	double m_y = 0;
};

