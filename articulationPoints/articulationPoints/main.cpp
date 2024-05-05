#define BOOST_TIMER_ENABLE_DEPRECATED

#include <iostream>
#include <vector>
#include <set>
#include "articulationPoints.h"

int main()
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
	copy(articulationPoints.begin(), articulationPoints.end(), std::ostream_iterator<size_t>(std::cout, " "));
	std::cout << std::endl;
}