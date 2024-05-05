#define CATCH_CONFIG_MAIN
#include <iostream>
#include "../../catch.hpp"
#include "../lw1/lw1.h"

TEST_CASE("Test with N = 10")
{
	std::vector<std::vector<size_t>> graph = 
	{
		{0, 1, 252, 442, 37, 237, 292, 195, 1, 315},
		{1, 0, 401, 177, 119, 30, 22, 470, 40, 1},
		{252, 401, 0, 1, 1, 477, 200, 175, 215, 239},
		{442, 177, 1, 0, 463, 200, 1, 294, 309, 313},
		{37, 119, 1, 463, 0, 1, 90, 140, 42, 477},
		{237, 30, 477, 200, 1, 0, 387, 1, 205, 480},
		{292, 22, 200, 1, 90, 387, 0, 120, 1, 349},
		{195, 470, 175, 294, 140, 1, 120, 0, 166, 1},
		{1, 40, 215, 309, 42, 205, 1, 166, 0, 491},
		{315, 1, 239, 313, 477, 480, 349, 1, 491, 0},
	};

	std::vector<size_t> minCycle = MinGamiltonCycle(graph);
	std::vector<size_t> expectedCycle = { 1, 2, 10, 8, 6, 5, 3, 4, 7, 9 };
	REQUIRE(minCycle == expectedCycle);
}

TEST_CASE("Empty graph")
{
	std::vector<std::vector<size_t>> graph = 
	{
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 }
	};

	std::vector<size_t> minCycle = MinGamiltonCycle(graph);
	std::vector<size_t> expectedCycle = { 1, 2, 3, 4 };
	REQUIRE(minCycle == expectedCycle);
}

TEST_CASE("Average graph 4")
{
	std::vector<std::vector<size_t>> graph = 
	{
		{0, 12, 7, 3},
		{12, 0, 5, 1},
		{7, 5, 0, 4},
		{3, 1, 4, 0}
	};
	
	std::vector<size_t> minCycle = MinGamiltonCycle(graph);
	std::vector<size_t> expectedCycle = { 1, 3, 2, 4 };
	REQUIRE(minCycle == expectedCycle);
}

TEST_CASE("Average graph 5")
{
	std::vector<std::vector<size_t>> graph = 
	{
		{0, 289, 297, 260, 439},
		{289, 0, 399, 444, 30},
		{297, 399, 0, 73, 443},
		{260, 444, 73, 0, 66},
		{439, 30, 443, 66, 0},
	};

	std::vector<size_t> minCycle = MinGamiltonCycle(graph);
	std::vector<size_t> expectedCycle = { 1, 2, 5, 4, 3 };
	REQUIRE(minCycle == expectedCycle);
}