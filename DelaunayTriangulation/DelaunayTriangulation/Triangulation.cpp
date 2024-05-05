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
	for (const auto& triangle : m_triangles)
	{
		auto nodes = triangle->GetNodes();
		std::cout << "( " << nodes[0]->GetX() << ", " << nodes[0]->GetY() << " )" << "   "
			<< "( " << nodes[1]->GetX() << ", " << nodes[1]->GetY() << " )" << "   "
			<< "( " << nodes[2]->GetX() << ", " << nodes[2]->GetY() << " )" << std::endl;
	}
}

void Triangulation::DivideAndConquerAlgorithm(const std::shared_ptr<Field>& field)
{
	auto nodes = field->GetNodes();
	if (nodes.size() == 3)
	{
		std::shared_ptr<Triangle> trianglePtr = std::make_shared<Triangle>(Triangle(*nodes[0], *nodes[1], *nodes[2]));
		m_triangles.push_back(trianglePtr);
	}
	else if (nodes.size() == 4)
	{
		std::shared_ptr<Triangle> trianglePtr = std::make_shared<Triangle>(Triangle(*nodes[0], *nodes[1], *nodes[2]));
		m_triangles.push_back(trianglePtr);
		ConnectNodeWithTriangle(nodes[3], trianglePtr);
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

}

std::pair<Triangulation::Edge, Triangulation::Edge> Triangulation::GetTangents(const std::shared_ptr<Field>& leftField, const std::shared_ptr<Field>& rightField)
{
	auto leftFieldNodes = leftField->GetNodes();
	auto rightFieldNodes = rightField->GetNodes();
	std::vector<std::shared_ptr<Node>> allNodes;
	allNodes.insert(allNodes.end(), leftFieldNodes.begin(), leftFieldNodes.end());
	allNodes.insert(allNodes.end(), rightFieldNodes.begin(), rightFieldNodes.end());
	std::sort(leftFieldNodes.begin(), leftFieldNodes.end(), [](const std::shared_ptr<Node>& a, const std::shared_ptr<Node>& b)
		{
			return (a->GetY() == b->GetY()) ? (a->GetX() < b->GetX()) : (a->GetY() < b->GetY());
		});
	std::sort(rightFieldNodes.begin(), rightFieldNodes.end(), [](const std::shared_ptr<Node>& a, const std::shared_ptr<Node>& b)
		{
			return (a->GetY() == b->GetY()) ? (a->GetX() > b->GetX()) : (a->GetY() < b->GetY());
		});
	Edge topTangent = std::make_pair(leftFieldNodes[leftFieldNodes.size() - 1], rightFieldNodes[leftFieldNodes.size() - 1]);
	Edge bottomTangent = std::make_pair(leftFieldNodes[0], rightFieldNodes[0]);
	auto rightFieldUpperEnvelop = GetUpperEnvelope(rightFieldNodes);
	auto leftFieldUpperEnvelop = GetUpperEnvelope(leftFieldNodes);
	while (GetAllNodesOrientation(topTangent, allNodes) == 0 && false) // здесь пока цикл обхожу, чтобы не зависала программа
	{
		if (GetAllNodesOrientation(topTangent, leftFieldNodes) <= 0)
		{
			//topTangent.first = 
		}
		else
		{

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
			return (a->GetX() == b->GetX()) ? (a->GetY() < b->GetY()) : (a->GetX() < b->GetX());
		});
	envelop.push_back(tempNodes[0]);
	for (const auto& node : tempNodes)
	{
		while (envelop.size() >= 2 && (((*node - *envelop.back()) ^ (*envelop[envelop.size() - 2] - *envelop.back())) <= 0))
		{
			envelop[envelop.size() - 2] = envelop[envelop.size() - 1];
			envelop.pop_back();
		}
		envelop.push_back(node);
	}
	return envelop;
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
		auto orientation = GetOrientation(*edge.first, *edge.second, *node);
		if (firstOrientation == 0)
		{
			firstOrientation = orientation;
		}
		if (firstOrientation > 0 && orientation <= 0 || firstOrientation < 0 && orientation >= 0)
		{
			return 0;
		}
	}
	return firstOrientation > 0 ? 1 : -1;
}

void Triangulation::ConnectNodeWithTriangle(const std::shared_ptr<Node>& node, std::shared_ptr<Triangle>& triangle)
{
	std::vector<std::shared_ptr<Node>> nodes = triangle->GetNodes();
	bool isFirstNodeCanConect = !IsIntersect(*node, *nodes[0], *nodes[1], *nodes[2]);
	bool isSecondNodeCanConect = !IsIntersect(*node, *nodes[1], *nodes[0], *nodes[2]);
	bool isThridNodeCanConect = !IsIntersect(*node, *nodes[2], *nodes[1], *nodes[0]);
	if (isFirstNodeCanConect && isSecondNodeCanConect)
	{
		Triangle newTriangle(*node, *nodes[0], *nodes[1]);
		triangle->AddAdjactionTriangle(std::make_shared<Triangle>(newTriangle), 2);
		newTriangle.AddAdjactionTriangle(triangle, 0);
		m_triangles.push_back(std::make_shared<Triangle>(newTriangle));
	}
	if (isFirstNodeCanConect && isThridNodeCanConect)
	{
		Triangle newTriangle(*node, *nodes[0], *nodes[2]);
		triangle->AddAdjactionTriangle(std::make_shared<Triangle>(newTriangle), 1);
		newTriangle.AddAdjactionTriangle(triangle, 0);
		m_triangles.push_back(std::make_shared<Triangle>(newTriangle));
	}
	if (isSecondNodeCanConect && isThridNodeCanConect)
	{
		Triangle newTriangle(*node, *nodes[1], *nodes[2]);
		triangle->AddAdjactionTriangle(std::make_shared<Triangle>(newTriangle), 0);
		newTriangle.AddAdjactionTriangle(triangle, 0);
		m_triangles.push_back(std::make_shared<Triangle>(newTriangle));
	}
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
