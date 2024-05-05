#pragma once
#include "Field.h"
#include "Triangle.h"

class Triangulation
{
public:
	Triangulation(const std::vector<Node>& nodes);

	void Delonay();

private:
	typedef std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>> Edge;
	static const int CLOCKWISE = 1;
	static const int COUNTERCLOCKWISE = -1;
	static const int COLLINEAR = 0;

	std::shared_ptr<Field> m_field;
	std::vector<std::shared_ptr<Triangle>> m_triangles;

	void DivideAndConquerAlgorithm(const std::shared_ptr<Field>& field);

	std::pair<std::shared_ptr<Field>, std::shared_ptr<Field>> DivideField(const std::shared_ptr<Field>& field, int count);

	void MergeFields(const std::shared_ptr<Field>& leftField, const std::shared_ptr<Field>& rightField);

	std::pair<Edge, Edge> GetTangents(const std::shared_ptr<Field>& leftField, const std::shared_ptr<Field>& rightField);

	std::vector<std::shared_ptr<Node>> GetUpperEnvelope(const std::vector<std::shared_ptr<Node>>& nodes);

	size_t GetNodeIndex(std::vector<std::shared_ptr<Node>> nodes, std::shared_ptr<Node> node);

	int GetAllNodesOrientation(const Edge& edge, const std::vector<std::shared_ptr<Node>>& nodes);

	void ConnectNodeWithTriangle(const std::shared_ptr<Node>& node, std::shared_ptr<Triangle>& triangle);

	int GetOrientation(const Node& p, const Node& q, const Node& r) const;

	bool IsOnSegment(const Node& p, const Node& q, const Node& r) const;

	bool IsIntersect(const Node& p1, const Node& q1, const Node& p2, const Node& q2);
};

