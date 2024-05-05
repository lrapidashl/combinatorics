#define BOOST_TIMER_ENABLE_DEPRECATED

#include <iostream>
#include <vector>
#include <boost/timer.hpp>
#include "lw1.h"

int main()
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
	boost::timer t;
	t.restart();

	std::vector<size_t> minCycle = MinGamiltonCycle(graph);
	copy(minCycle.begin(), minCycle.end(), std::ostream_iterator<size_t>(std::cout, " "));

	double duration = t.elapsed();

	std::cout << std::endl << duration << std::endl;
}