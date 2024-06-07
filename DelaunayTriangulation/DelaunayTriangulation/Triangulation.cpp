#include "Triangulation.h"
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <algorithm>

Triangulation::Triangulation(const std::vector<Node>& nodes) :
	m_field(std::make_shared<Field>(Field(nodes)))
{
}

void Triangulation::Delonay()
{
	DivideAndConquerAlgorithm(m_field);
	MakeDelonay();
	for (const auto& edge : m_edges)
	{
		std::cout << "<ConnectionLine dot1={{x: " << edge->first->GetX() << ", y: " << edge->first->GetY() << "}} dot2={{x: " << edge->second->GetX() << ", y: " << edge->second->GetY() << "}} color={'linear-gradient(90deg, rgba(255,167,50,1) 0%, rgba(255,167,50,0.303046218487395) 14%, rgba(255,167,50,0.3) 89%, rgba(255,167,50,1) 100%)'}></ConnectionLine>" << '\n';
	}
}

void Triangulation::DivideAndConquerAlgorithm(const std::shared_ptr<Field>& field)
{
	auto nodes = field->GetNodes();
	if (nodes.size() == 3)
	{
		std::shared_ptr<Triangle> trianglePtr = std::make_shared<Triangle>(Triangle(*nodes[0], *nodes[1], *nodes[2]));
		ConnectNodes(nodes[0], nodes[1]);
		ConnectNodes(nodes[0], nodes[2]);
		ConnectNodes(nodes[1], nodes[2]);
	}
	else if (nodes.size() == 4)
	{
		std::shared_ptr<Triangle> trianglePtr = std::make_shared<Triangle>(Triangle(*nodes[0], *nodes[1], *nodes[2]));
		ConnectNodes(nodes[0], nodes[1]);
		ConnectNodes(nodes[0], nodes[2]);
		ConnectNodes(nodes[1], nodes[2]);
		ConnectNodeWithTriangle(nodes[3], nodes[0], nodes[1], nodes[2]);
	}
	else if (nodes.size() == 8)
	{
		auto newFields = DivideField(field, 4);
		DivideAndConquerAlgorithm(newFields.first);
		DivideAndConquerAlgorithm(newFields.second);
		MergeFields(newFields.first, newFields.second);
	}
	else if (nodes.size() < 12)
	{
		auto newFields = DivideField(field, 3);
		DivideAndConquerAlgorithm(newFields.first);
		DivideAndConquerAlgorithm(newFields.second);
		MergeFields(newFields.first, newFields.second);
	}
	else
	{
		auto newFields = DivideField(field, (int)std::ceil(nodes.size() / 2));
		DivideAndConquerAlgorithm(newFields.first);
		DivideAndConquerAlgorithm(newFields.second);
		MergeFields(newFields.first, newFields.second);
	}
}

void Triangulation::MakeDelonay()
{
	bool isDelonay = false;
	for (size_t k = 0; k < 1002; k++)
	{
		isDelonay = true;
		std::vector<std::shared_ptr<Edge>> tempEdges = m_edges;
		for (std::shared_ptr<Edge>& edge : tempEdges)
		{
			if (std::find(m_edges.begin(), m_edges.end(), edge) != m_edges.end())
			{
				auto commonNodes = GetNodesIntersection(edge->first->GetNodes(), edge->second->GetNodes());
				if (commonNodes.size() < 2)
				{
					continue;
				}
				bool isFlip = false;
				for (size_t i = 0; i < commonNodes.size() - 1; i++)
				{
					for (size_t j = i + 1; j < commonNodes.size(); j++)
					{
						if (!IsDelonay(edge, commonNodes[i], commonNodes[j])
							&& IsIntersect(*commonNodes[i], *commonNodes[j], *edge->first, *edge->second))
						{
							Flip(edge, commonNodes[i], commonNodes[j]);
							isFlip = true;
							isDelonay = false;
							break;
						}
					}
					if (isFlip)
					{
						break;
					}
				}
			}
		}
	}
}

std::pair<std::shared_ptr<Field>, std::shared_ptr<Field>> Triangulation::DivideField(const std::shared_ptr<Field>& field, int count)
{
	if (count >= field->GetCount() || count <= 0)
	{
		throw std::invalid_argument("can`t divide by a given node count");
	}
	auto nodes = field->GetNodes();
	std::sort(nodes.begin(), nodes.end(), [](const std::shared_ptr<Node>& a, const std::shared_ptr<Node>& b)
		{
			return (a->GetX() == b->GetX()) ? (a->GetY() < b->GetY()) : (a->GetX() < b->GetX());
		});

	std::vector<Node> nearNodes;
	std::vector<Node> farNodes;
	for (size_t i = 0; i < nodes.size(); i++)
	{
		if (i < count)
		{
			nearNodes.push_back(*nodes[i]);
		}
		else
		{
			farNodes.push_back(*nodes[i]);
		}
	}
	return std::make_pair(std::make_shared<Field>(Field(nearNodes)), std::make_shared<Field>(Field(farNodes)));
}

void Triangulation::MergeFields(const std::shared_ptr<Field>& leftField, const std::shared_ptr<Field>& rightField)
{
	auto tangents = GetTangents(leftField, rightField);
	Edge topTangent = tangents.first;
	ConnectNodes(topTangent.first, topTangent.second);
	Edge bottomTangent = tangents.second;
	ConnectNodes(bottomTangent.first, bottomTangent.second);
	auto leftFieldConvexHull = GetConvexHull(leftField->GetNodes());
	auto rightFieldConvexHull = GetConvexHull(rightField->GetNodes());
	std::shared_ptr<Node> nextLeft = topTangent.first;
	std::shared_ptr<Node> nextRight = topTangent.second;
	bool isLeftNodeOfTangentsSame = topTangent.first == bottomTangent.first;
	bool isRightNodeOfTangentsSame = topTangent.second == bottomTangent.second;
	while (!((topTangent.first == bottomTangent.first && nextRight == bottomTangent.second)
		|| (topTangent.second == bottomTangent.second && nextLeft == bottomTangent.first)))
	{
		nextLeft = leftFieldConvexHull[GetNodeIndex(leftFieldConvexHull, topTangent.first) == 0 ? leftFieldConvexHull.size() - 1 : GetNodeIndex(leftFieldConvexHull, topTangent.first) - 1];
		nextRight = rightFieldConvexHull[(GetNodeIndex(rightFieldConvexHull, topTangent.second) + 1) % rightFieldConvexHull.size()];
		if (GetOrientation(*topTangent.second, *topTangent.first, *nextRight) < 0
			&& (GetOrientation(*topTangent.first, *nextRight, *nextLeft) > 0
				|| GetOrientation(*topTangent.first, *topTangent.second, *nextLeft) < 0)
			&& (topTangent.second != bottomTangent.second || isRightNodeOfTangentsSame)
			&& (nextRight->GetY() >= nextLeft->GetY()
				|| GetOrientation(*topTangent.first, *topTangent.second, *nextLeft) < 0
				|| GetOrientation(*topTangent.second, *nextLeft, *nextRight) >= 0)
			|| (topTangent.first == bottomTangent.first && !isLeftNodeOfTangentsSame))
		{
			ConnectNodes(topTangent.first, nextRight);
			topTangent.second = nextRight;
			isRightNodeOfTangentsSame = false;
		}
		else
		{
			ConnectNodes(topTangent.second, nextLeft);
			topTangent.first = nextLeft;
			isLeftNodeOfTangentsSame = false;
		}
	}
}

std::pair<Triangulation::Edge, Triangulation::Edge> Triangulation::GetTangents(const std::shared_ptr<Field>& leftField, const std::shared_ptr<Field>& rightField)
{
	auto leftFieldNodes = leftField->GetNodes();
	auto rightFieldNodes = rightField->GetNodes();
	std::vector<std::shared_ptr<Node>> allNodes;
	allNodes.insert(allNodes.end(), leftFieldNodes.begin(), leftFieldNodes.end());
	allNodes.insert(allNodes.end(), rightFieldNodes.begin(), rightFieldNodes.end());
	auto rightFieldUpperEnvelop = GetUpperEnvelope(rightFieldNodes);
	auto leftFieldUpperEnvelop = GetUpperEnvelope(leftFieldNodes);
	Edge topTangent = std::make_pair(leftFieldUpperEnvelop[0], rightFieldUpperEnvelop.back());
	while (GetAllNodesOrientation(topTangent, allNodes) <= 0)
	{
		if (GetAllNodesOrientation(topTangent, leftFieldNodes) <= 0)
		{
			topTangent.first = leftFieldUpperEnvelop[(GetNodeIndex(leftFieldUpperEnvelop, topTangent.first) + 1) % leftFieldUpperEnvelop.size()];
		}
		else
		{
			topTangent.second = rightFieldUpperEnvelop[GetNodeIndex(rightFieldUpperEnvelop, topTangent.second) == 0 ? rightFieldUpperEnvelop.size() - 1 : GetNodeIndex(rightFieldUpperEnvelop, topTangent.second) - 1];
		}
	}
	auto rightFieldLowerEnvelop = GetLowerEnvelope(rightFieldNodes);
	auto leftFieldLowerEnvelop = GetLowerEnvelope(leftFieldNodes);
	Edge bottomTangent = std::make_pair(leftFieldLowerEnvelop.back(), rightFieldLowerEnvelop[0]);
	while (GetAllNodesOrientation(bottomTangent, allNodes) >= 0)
	{
		if (GetAllNodesOrientation(bottomTangent, leftFieldNodes) >= 0)
		{
			bottomTangent.first = leftFieldLowerEnvelop[GetNodeIndex(leftFieldLowerEnvelop, bottomTangent.first) == 0 ? leftFieldLowerEnvelop.size() - 1 : GetNodeIndex(leftFieldLowerEnvelop, bottomTangent.first) - 1];
		}
		else
		{
			bottomTangent.second = rightFieldLowerEnvelop[(GetNodeIndex(rightFieldLowerEnvelop, bottomTangent.second) + 1) % rightFieldLowerEnvelop.size()];
		}
	}
	return std::make_pair(topTangent, bottomTangent);
}

std::vector<std::shared_ptr<Node>> Triangulation::GetUpperEnvelope(const std::vector<std::shared_ptr<Node>>& nodes)
{
	std::vector<std::shared_ptr<Node>> envelop;
	std::vector<std::shared_ptr<Node>> tempNodes = nodes;
	std::sort(tempNodes.begin(), tempNodes.end(), [](const std::shared_ptr<Node>& a, const std::shared_ptr<Node>& b)
		{
			return (a->GetX() == b->GetX()) ? (a->GetY() > b->GetY()) : (a->GetX() > b->GetX());
		});
	std::shared_ptr<Node> p0 = tempNodes[0];

	for (const auto& node : tempNodes)
	{
		while (envelop.size() >= 2 && (((*node - *envelop.back()) ^ (*envelop[envelop.size() - 2] - *envelop.back())) <= 0))
		{
			envelop.pop_back();
		}
		envelop.push_back(node);
	}
	return envelop;
}

std::vector<std::shared_ptr<Node>> Triangulation::GetLowerEnvelope(const std::vector<std::shared_ptr<Node>>& nodes)
{
	std::vector<std::shared_ptr<Node>> envelop;
	std::vector<std::shared_ptr<Node>> tempNodes = nodes;
	std::sort(tempNodes.begin(), tempNodes.end(), [](const std::shared_ptr<Node>& a, const std::shared_ptr<Node>& b)
		{
			return (a->GetX() == b->GetX()) ? (a->GetY() < b->GetY()) : (a->GetX() < b->GetX());
		});
	std::shared_ptr<Node> p0 = tempNodes[0];

	for (const auto& node : tempNodes)
	{
		while (envelop.size() >= 2 && (((*node - *envelop.back()) ^ (*envelop[envelop.size() - 2] - *envelop.back())) <= 0))
		{
			envelop.pop_back();
		}
		envelop.push_back(node);
	}
	return envelop;
}

std::vector<std::shared_ptr<Node>> Triangulation::GetConvexHull(const std::vector<std::shared_ptr<Node>>& nodes)
{
	auto convexHull = GetLowerEnvelope(nodes);
	convexHull.pop_back();
	auto upperEnvelop = GetUpperEnvelope(nodes);
	convexHull.insert(convexHull.end(), upperEnvelop.begin(), upperEnvelop.end());
	convexHull.pop_back();
	return convexHull;
}

bool Triangulation::IsDelonay(const std::shared_ptr<Edge>& edge, const std::shared_ptr<Node>& node1, const std::shared_ptr<Node>& node2)
{
	auto x0 = node1->GetX();
	auto y0 = node1->GetY();
	auto x1 = edge->first->GetX();
	auto y1 = edge->first->GetY();
	auto x2 = node2->GetX();
	auto y2 = node2->GetY();
	auto x3 = edge->second->GetX();
	auto y3 = edge->second->GetY();

	auto Sa = (x0 - x1) * (x0 - x3) + (y0 - y1) * (y0 - y3);
	auto Sb = (x2 - x1) * (x2 - x3) + (y2 - y1) * (y2 - y3);

	if (Sa < 0 && Sb < 0)
	{
		return false;
	}
	else if (Sa >= 0 && Sb >= 0)
	{
		return true;
	}

	return ((x0 - x1) * (y0 - y3) - (x0 - x3) * (y0 - y1)) * Sb
		+ Sa * ((x2 - x1) * (y2 - y3) - (x2 - x3) * (y2 - y1)) >= 0;
}

void Triangulation::Flip(std::shared_ptr<Edge>& oldEdge, std::shared_ptr<Node>& newNode1, std::shared_ptr<Node>& newNode2)
{
	DisconnectNodes(oldEdge);
	ConnectNodes(newNode1, newNode2);
}

void Triangulation::ConnectNodes(std::shared_ptr<Node>& a, std::shared_ptr<Node>& b)
{
	a->AddNodeConnection(b);
	b->AddNodeConnection(a);
	m_edges.push_back(std::make_shared<Edge>(std::make_pair(a, b)));
}

void Triangulation::DisconnectNodes(std::shared_ptr<Edge>& edge)
{
	std::erase(m_edges, edge);
	edge->first->DeleteNodeConnection(edge->second);
	edge->second->DeleteNodeConnection(edge->first);
}

double Triangulation::GetAngle(std::shared_ptr<Node> a, std::shared_ptr<Node> b, std::shared_ptr<Node> c)
{
	return std::acos(((a->GetX() - b->GetX()) * (c->GetX() - b->GetX()) + (a->GetY() - b->GetY()) * (c->GetY() - b->GetY()))
		/ (std::sqrt(std::pow(a->GetX() - b->GetX(), 2) + std::pow(a->GetX() - b->GetX(), 2)) * std::sqrt(std::pow(c->GetX() - b->GetX(), 2) + std::pow(c->GetX() - b->GetX(), 2))));
}

size_t Triangulation::GetNodeIndex(std::vector<std::shared_ptr<Node>> nodes, std::shared_ptr<Node> node)
{
	auto it = std::find(nodes.begin(), nodes.end(), node);

	if (it != nodes.end())
	{
		return it - nodes.begin();
	}
	else
	{
		return -1;
	}
}

int Triangulation::GetAllNodesOrientation(const Edge& edge, const std::vector<std::shared_ptr<Node>>& nodes)
{
	int firstOrientation = 0;
	for (const auto& node : nodes)
	{
		if (node == edge.first || node == edge.second)
		{
			continue;
		}
		auto orientation = GetOrientation(*edge.first, *edge.second, *node);
		if (firstOrientation == 0)
		{
			firstOrientation = orientation;
		}
		if (firstOrientation > 0 && orientation < 0 || firstOrientation < 0 && orientation > 0)
		{
			return 0;
		}
	}
	return firstOrientation > 0 ? 1 : -1;
}

void Triangulation::ConnectNodeWithTriangle(std::shared_ptr<Node>& newNode, std::shared_ptr<Node>& node1, std::shared_ptr<Node>& node2, std::shared_ptr<Node>& node3)
{
	bool isFirstNodeCanConect = !IsIntersect(*newNode, *node1, *node2, *node3);
	bool isSecondNodeCanConect = !IsIntersect(*newNode, *node2, *node1, *node3);
	bool isThridNodeCanConect = !IsIntersect(*newNode, *node3, *node2, *node1);
	if (isFirstNodeCanConect && isSecondNodeCanConect)
	{
		ConnectNodes(newNode, node1);
		ConnectNodes(newNode, node2);
	}
	if (isFirstNodeCanConect && isThridNodeCanConect)
	{
		ConnectNodes(newNode, node1);
		ConnectNodes(newNode, node3);
	}
	if (isSecondNodeCanConect && isThridNodeCanConect)
	{
		ConnectNodes(newNode, node2);
		ConnectNodes(newNode, node3);
	}
}

std::vector<std::shared_ptr<Node>> Triangulation::GetNodesIntersection(const std::vector<std::shared_ptr<Node>>& nodes1, const std::vector<std::shared_ptr<Node>>& nodes2)
{
	std::vector<std::shared_ptr<Node>> nodes3;

	for (const std::shared_ptr<Node>& node : nodes1)
	{
		auto it = std::find(nodes2.begin(), nodes2.end(), node);
		if (it != nodes2.end())
		{
			nodes3.push_back(node);
		}
	}

	return nodes3;
}

int Triangulation::GetOrientation(const Node& p, const Node& q, const Node& r) const
{
	int val = (int)((q.GetY() - p.GetY()) * (r.GetX() - q.GetX()) - (q.GetX() - p.GetX()) * (r.GetY() - q.GetY()));

	if (val == 0)
	{
		return COLLINEAR;
	}

	return (val > 0) ? CLOCKWISE : COUNTERCLOCKWISE;
}

bool Triangulation::IsOnSegment(const Node& p, const Node& q, const Node& r) const
{
	return (q.GetX() <= std::max(p.GetX(), r.GetX()) && q.GetX() >= std::min(p.GetX(), r.GetX()) &&
		q.GetY() <= std::max(p.GetY(), r.GetY()) && q.GetY() >= std::min(p.GetY(), r.GetY()))
		? true : false;
}

bool Triangulation::IsIntersect(const Node& p1, const Node& q1, const Node& p2, const Node& q2)
{
	int o1 = GetOrientation(p1, q1, p2);
	int o2 = GetOrientation(p1, q1, q2);
	int o3 = GetOrientation(p2, q2, p1);
	int o4 = GetOrientation(p2, q2, q1);

	return (
		o1 != o2 && o3 != o4
		|| o1 == 0 && IsOnSegment(p1, p2, q1)
		|| o2 == 0 && IsOnSegment(p1, q2, q1)
		|| o3 == 0 && IsOnSegment(p2, p1, q2)
		|| o4 == 0 && IsOnSegment(p2, q1, q2)
		) ? true : false;
}
