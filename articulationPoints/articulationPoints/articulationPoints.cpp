#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>
#include "articulationPoints.h"


void ArticulationPointsDFS(
    const std::vector<std::vector<size_t>>& graph,
    size_t vertex,
    std::set<size_t>& visitedVertices,
    std::vector<size_t>& minReachable,
    std::vector<size_t>& inTime,
    size_t& time,
    int parent,
    std::set<size_t>& articulationPoints
)
{
    size_t children = 0;
    visitedVertices.insert(vertex);
    inTime[vertex] = time;
    minReachable[vertex] = time;
    time++;
    for (size_t i = 0; i < graph.size(); i++)
    {
        if (graph[vertex][i] == 1)
        {
            if (!visitedVertices.contains(i))
            {
                ArticulationPointsDFS(graph, i, visitedVertices, minReachable, inTime, time, (int)vertex, articulationPoints);
                children++;
                minReachable[vertex] = std::min(minReachable[vertex], minReachable[i]);
                if (parent != -1 && minReachable[i] >= inTime[vertex])
                {
                    articulationPoints.insert(vertex + 1);
                }
            }
            else if (i != parent)
            {
                minReachable[vertex] = std::min(minReachable[vertex], inTime[i]);
            }
        }
    }
    if (parent == -1 && children > 1)
    {
        articulationPoints.insert(vertex + 1);
    }
}

std::set<size_t> GetArticulationPoints(const std::vector<std::vector<size_t>>& graph) 
{
    std::set<size_t> articulationPoints;
    std::set<size_t> visitedVertices;
    std::vector<size_t> inTime;
    std::vector<size_t> minReachable;
    for (size_t i = 0; i < graph.size(); i++)
    {
        inTime.push_back(0);
        minReachable.push_back(0);
    }
    int lastVisited = -1;
    size_t time = 1;

    for (size_t i = 0; i < graph.size(); i++)
    {
        if (!visitedVertices.contains(i))
        {
            ArticulationPointsDFS(graph, i, visitedVertices, minReachable, inTime, time, -1, articulationPoints);
        }
    }
    
	return articulationPoints;
}