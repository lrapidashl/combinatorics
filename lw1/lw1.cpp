#define BOOST_TIMER_ENABLE_DEPRECATED

#include <algorithm>
#include <iostream>
#include <vector>
#include <boost/timer.hpp>
#include "lw1.h"

std::vector<size_t> MinGamiltonCycle(const std::vector<std::vector<size_t>>& graph)
{
	std::vector<size_t> cycle;
	for (size_t i = 1; i <= graph.size(); i++)
	{
		cycle.push_back(i);
	}
	size_t minCycleLen = INT_MAX;
	std::vector<size_t> minCycle = cycle;
	do
	{
		size_t cycleLen = 0;
		for (size_t i = 0; i < cycle.size(); i++)
		{
			size_t len = graph[cycle[i] - 1][cycle[(i + 1) % cycle.size()] - 1];
			if (len > 0)
			{
				cycleLen += len;
			}
			else
			{
				cycleLen = INT_MAX;
				break;
			}
		}
		if (cycleLen < minCycleLen)
		{
			minCycle = cycle;
			minCycleLen = cycleLen;
		}
	} while (std::next_permutation(cycle.begin(), cycle.end()));

	return minCycle;
}