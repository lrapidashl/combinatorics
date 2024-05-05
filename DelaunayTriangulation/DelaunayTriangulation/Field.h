#pragma once
#include "Node.h"
#include <vector>
#include <memory>

class Field
{
public:
	const double EPSILON = 0.000001;

	Field(double x1, double y1, double x2, double y2);

	explicit Field(const std::vector<Node>& nodes);

	Node GetUpperLeftCorner() const;

	Node GetBottomRightCorner() const;

	double GetWidth() const;

	double GetHeight() const;

	std::vector<std::shared_ptr<Node>> GetNodes() const;

	int GetCount() const;
private:
	Node m_upperLeftCorner;
	Node m_bottomRightCorner;
	std::vector<std::shared_ptr<Node>> m_nodes;
};

