#define CATCH_CONFIG_MAIN
#include <iostream>
#include "../../../catch.hpp"
#include "../articulationPoints/articulationPoints.h"

TEST_CASE("Empty")
{
	std::vector<std::vector<size_t>> graph =
	{
		{0}
	};

	std::set<size_t> articulationPoints = GetArticulationPoints(graph);
	std::set<size_t> expectedArticulationPoints = {};
	REQUIRE(articulationPoints == expectedArticulationPoints);
}

TEST_CASE("Average")
{
	std::vector<std::vector<size_t>> graph =
	{
		{ 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
		{ 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0 },
		{ 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
		{ 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 },
		{ 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	};

	std::set<size_t> articulationPoints = GetArticulationPoints(graph);
	std::set<size_t> expectedArticulationPoints = {1, 2, 3, 4, 7, 9};
	REQUIRE(articulationPoints == expectedArticulationPoints);
}

TEST_CASE("Worm")
{
	std::vector<std::vector<size_t>> graph =
	{
		{0, 1, 0, 0, 0},
		{1, 0, 1, 0, 0},
		{0, 1, 0, 1, 0},
		{0, 0, 1, 0, 1},
		{0, 0, 0, 1, 0}
	};

	std::set<size_t> articulationPoints = GetArticulationPoints(graph);
	std::set<size_t> expectedArticulationPoints = { 2, 3, 4 };
	REQUIRE(articulationPoints == expectedArticulationPoints);
}

TEST_CASE("2 vertex")
{
	std::vector<std::vector<size_t>> graph =
	{
		{0, 1},
		{1, 0}
	};

	std::set<size_t> articulationPoints = GetArticulationPoints(graph);
	std::set<size_t> expectedArticulationPoints = {};
	REQUIRE(articulationPoints == expectedArticulationPoints);
}

TEST_CASE("Full")
{
	std::vector<std::vector<size_t>> graph =
	{
		{0, 1, 1, 1, 1},
		{1, 0, 1, 1, 1},
		{1, 1, 0, 1, 1},
		{1, 1, 1, 0, 1},
		{1, 1, 1, 1, 0}
	};

	std::set<size_t> articulationPoints = GetArticulationPoints(graph);
	std::set<size_t> expectedArticulationPoints = { };
	REQUIRE(articulationPoints == expectedArticulationPoints);
}