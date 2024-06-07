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
	std::vector<std::shared_ptr<Edge>> m_edges;

	void DivideAndConquerAlgorithm(const std::shared_ptr<Field>& field);

	void MakeDelonay();

	std::pair<std::shared_ptr<Field>, std::shared_ptr<Field>> DivideField(const std::shared_ptr<Field>& field, int count);

	void MergeFields(const std::shared_ptr<Field>& leftField, const std::shared_ptr<Field>& rightField);

	std::pair<Edge, Edge> GetTangents(const std::shared_ptr<Field>& leftField, const std::shared_ptr<Field>& rightField);

	std::vector<std::shared_ptr<Node>> GetUpperEnvelope(const std::vector<std::shared_ptr<Node>>& nodes);

	std::vector<std::shared_ptr<Node>> GetLowerEnvelope(const std::vector<std::shared_ptr<Node>>& nodes);

	std::vector<std::shared_ptr<Node>> GetConvexHull(const std::vector<std::shared_ptr<Node>>& nodes);

	bool IsDelonay(const std::shared_ptr<Edge>& edge, const std::shared_ptr<Node>& node1, const std::shared_ptr<Node>& node2);

	void Flip(std::shared_ptr<Edge>& oldEdge, std::shared_ptr<Node>& newNode1, std::shared_ptr<Node>& newNode2);

	void ConnectNodes(std::shared_ptr<Node>& a, std::shared_ptr<Node>& b);

	void DisconnectNodes(std::shared_ptr<Edge>& edge);

	double GetAngle(std::shared_ptr<Node> a, std::shared_ptr<Node> b, std::shared_ptr<Node> c);

	size_t GetNodeIndex(std::vector<std::shared_ptr<Node>> nodes, std::shared_ptr<Node> node);

	int GetAllNodesOrientation(const Edge& edge, const std::vector<std::shared_ptr<Node>>& nodes);

	void ConnectNodeWithTriangle(std::shared_ptr<Node>& newNode, std::shared_ptr<Node>& node1, std::shared_ptr<Node>& node2, std::shared_ptr<Node>& node3);

	std::vector<std::shared_ptr<Node>> GetNodesIntersection(const std::vector<std::shared_ptr<Node>>& nodes1, const std::vector<std::shared_ptr<Node>>& nodes2);

	int GetOrientation(const Node& p, const Node& q, const Node& r) const;

	bool IsOnSegment(const Node& p, const Node& q, const Node& r) const;

	bool IsIntersect(const Node& p1, const Node& q1, const Node& p2, const Node& q2);
};

