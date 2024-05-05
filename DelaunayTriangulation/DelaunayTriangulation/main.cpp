#include "Node.h"
#include "Triangulation.h"
#include <iostream>
#include <unordered_set>

auto GetPointsFromStdin() 
{
    double x, y;
    std::vector<Node> nodes;
    while ((std::cin >> x) && (std::cin >> y)) {
        nodes.emplace_back(x, y);
    }
    return nodes;
}

int main() 
{
    auto nodes = GetPointsFromStdin();
    Triangulation triangulation(nodes);
    triangulation.Delonay();
    return 0;
}
