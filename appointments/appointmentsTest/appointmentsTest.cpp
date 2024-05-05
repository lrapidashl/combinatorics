#define CATCH_CONFIG_MAIN
#include <iostream>
#include "../../../catch.hpp"
#include "../appointments/appointments.h"

TEST_CASE("Bad case")
{
	std::set<size_t> skills = { 1, 2, 3, 4 };
	std::vector<std::set<size_t>> group =
	{
		{ 1, 2 },
		{ 1 },
		{ 2, 4 },
		{ 4 }
	};

	std::vector<std::set<size_t>> minGroup = GetMinGroup(skills, group);
	std::vector<std::set<size_t>> expectedGroup = {};
	REQUIRE(minGroup == expectedGroup);
}

TEST_CASE("Average")
{
	std::set<size_t> skills = { 1, 2, 3, 4 };
	std::vector<std::set<size_t>> group =
	{
		{ 1, 2 },
		{ 1 },
		{ 2, 4 },
		{ 3, 1 },
		{ 4 }
	};

	std::vector<std::set<size_t>> minGroup = GetMinGroup(skills, group);
	std::vector<std::set<size_t>> expectedGroup =
	{
		{2, 4},
		{3, 1}
	};
	REQUIRE(minGroup == expectedGroup);
}

TEST_CASE("One super person")
{
	std::set<size_t> skills = { 1, 2, 3, 4 };
	std::vector<std::set<size_t>> group =
	{
		{ 1, 2 },
		{ 1 },
		{ 2, 4 },
		{ 3, 1 },
		{ 4 },
		{1, 2, 3, 4}
	};

	std::vector<std::set<size_t>> minGroup = GetMinGroup(skills, group);
	std::vector<std::set<size_t>> expectedGroup =
	{
		{1, 2, 3, 4}
	};
	REQUIRE(minGroup == expectedGroup);
}

TEST_CASE("4 simple persons")
{
	std::set<size_t> skills = { 1, 2, 3, 4 };
	std::vector<std::set<size_t>> group =
	{
		{1},
		{2},
		{3},
		{4},
		{5},
	};

	std::vector<std::set<size_t>> minGroup = GetMinGroup(skills, group);
	std::vector<std::set<size_t>> expectedGroup =
	{
		{1},
		{2},
		{3},
		{4},
	};
	REQUIRE(minGroup == expectedGroup);
}

TEST_CASE("Oversupply")
{
	std::set<size_t> skills = { 1, 2, 3, 4 };
	std::vector<std::set<size_t>> group =
	{
		{ 1, 5, 6, 7 },
		{ 1 },
		{ 2, 4, 10, 11 },
		{ 3, 1, 4 },
		{ 4 }
	};

	std::vector<std::set<size_t>> minGroup = GetMinGroup(skills, group);
	std::vector<std::set<size_t>> expectedGroup =
	{
		{ 2, 4, 10, 11 },
		{ 3, 1, 4 }
	};
	REQUIRE(minGroup == expectedGroup);
}