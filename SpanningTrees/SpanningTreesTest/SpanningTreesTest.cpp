#define CATCH_CONFIG_MAIN
#include "../SpanningTrees/SpanningTree.h"
#include "../../../catch.hpp"
#include <vector>

TEST_CASE("Test with 4x4")
{
    SpanningTree::Matrix adjacencyMatrix(4);
     adjacencyMatrix.matrix = {
        { 0, 1, 1, 0 },
        { 1, 0, 1, 0 },
        { 1, 1, 0, 1 },
        { 0, 0, 1, 0 }
    };
    int result = SpanningTree::GetSpanningTreeCount(adjacencyMatrix);

    int expected = 3;

    REQUIRE(result == expected);
}

TEST_CASE("Test with hard 4x4")
{
    SpanningTree::Matrix adjacencyMatrix(4);
    adjacencyMatrix.matrix = {
        { 0, 1, 1, 0 },
        { 1, 0, 1, 1 },
        { 1, 1, 0, 1 },
        { 0, 1, 1, 0 }
    };
    int result = SpanningTree::GetSpanningTreeCount(adjacencyMatrix);

    int expected = 8;

    REQUIRE(result == expected);
}

TEST_CASE("Test with 5x5")
{
    SpanningTree::Matrix adjacencyMatrix(5);
    adjacencyMatrix.matrix = {
        { 0, 1, 1, 0, 1 },
        { 1, 0, 1, 1, 0 },
        { 1, 1, 0, 1, 1 },
        { 0, 1, 1, 0, 0 },
        { 1, 0, 1, 0, 0 }
    };
    int result = SpanningTree::GetSpanningTreeCount(adjacencyMatrix);

    int expected = 21;

    REQUIRE(result == expected);
}

TEST_CASE("Isolated vertex")
{
    SpanningTree::Matrix adjacencyMatrix(4);
    adjacencyMatrix.matrix = {
        { 0, 0, 0, 0 },
        { 0, 0, 1, 1 },
        { 0, 1, 0, 1 },
        { 0, 1, 1, 0 }
    };
    int result = SpanningTree::GetSpanningTreeCount(adjacencyMatrix);

    int expected = 0;

    REQUIRE(result == expected);
}

TEST_CASE("2 components")
{
    SpanningTree::Matrix adjacencyMatrix(4);
    adjacencyMatrix.matrix = {
        { 0, 1, 0, 0 },
        { 1, 0, 0, 0 },
        { 0, 0, 0, 1 },
        { 0, 0, 1, 0 }
    };
    int result = SpanningTree::GetSpanningTreeCount(adjacencyMatrix);

    int expected = 0;

    REQUIRE(result == expected);
}
