#pragma once

#include <iostream>
#include <cstdlib> 
#include <queue>
#include <list>
#include <climits>

class BGraph
{
public:
    const int NIL = 0;
    const int INF = INT_MAX;

    BGraph(int m, int n);

    void AddEdge(int u, int v);

    bool Bfs();

    bool Dfs(int u);

    int HopcroftKarpAlgorithm();
private:
    int m, n;
    std::list<int>* adj;
    int* pair_u, * pair_v, * dist;
};