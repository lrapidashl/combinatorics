#include "BGraph.h"

int BGraph::HopcroftKarpAlgorithm()
{
    pair_u = new int[m + 1];
    pair_v = new int[n + 1];
    dist = new int[m + 1];
    for (int u = 0; u <= m; u++)
    {
        pair_u[u] = NIL;
    }
    for (int v = 0; v <= n; v++)
    {
        pair_v[v] = NIL;
    }

    int result = 0;

    while (Bfs())
    {
        for (int u = 1; u <= m; u++)
        {
            if (pair_u[u] == NIL && Dfs(u))
            {
                result++;
            }
        }
    }
    return result;
}

bool BGraph::Bfs()
{
    std::queue<int> q;

    for (int u = 1; u <= m; u++)
    {
        if (pair_u[u] == NIL)
        {
            dist[u] = 0;
            q.push(u);
        }
        else
        {
            dist[u] = INF;
        }
    }
    dist[NIL] = INF;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        if (dist[u] < dist[NIL])
        {
            std::list<int>::iterator it;
            for (it = adj[u].begin(); it != adj[u].end(); ++it)
            {
                int v = *it;
                if (dist[pair_v[v]] == INF)
                {
                    dist[pair_v[v]] = dist[u] + 1;
                    q.push(pair_v[v]);
                }
            }
        }
    }
    return (dist[NIL] != INF);
}

bool BGraph::Dfs(int u)
{
    if (u != NIL)
    {
        std::list<int>::iterator it;
        for (it = adj[u].begin(); it != adj[u].end(); ++it)
        {
            int v = *it;

            if (dist[pair_v[v]] == dist[u] + 1)
            {
                if (Dfs(pair_v[v]) == true)
                { 
                    pair_v[v] = u;
                    pair_u[u] = v;
                    return true;
                }
            }
        }

        dist[u] = INF;
        return false;
    }
    return true;
}

BGraph::BGraph(int m, int n)
{
    this->m = m;
    this->n = n;
    adj = new std::list<int>[m + 1];
}

void BGraph::AddEdge(int u, int v)
{
    adj[u].push_back(v); 
}