#define CATCH_CONFIG_MAIN
#include "../DelaunayTriangulation/Triangulation.h"
#include "../../../catch.hpp"
#include <vector>

TEST_CASE("Triangle")
{
    std::vector<Node> nodes = {
        {1, 3},
        {2, 3},
        {1, 2},
    };
    Triangulation triangulation(nodes);
    triangulation.Delonay();
}

