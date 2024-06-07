#include <iostream>
#include "SpanningTree.h"

int main()
{
    SpanningTree::Matrix adjacencyMatrix(4);
    adjacencyMatrix.matrix = {
        { 0, 1, 1, 0 },
        { 1, 0, 1, 0 },
        { 1, 1, 0, 1 },
        { 0, 0, 1, 0 }
    };
    std::cout << SpanningTree::GetSpanningTreeCount(adjacencyMatrix) << std::endl;
}
