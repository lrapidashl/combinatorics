#define BOOST_TIMER_ENABLE_DEPRECATED

#include <iostream>
#include <vector>
#include <set>
#include <boost/timer.hpp>
#include "appointments.h"

int main()
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

	boost::timer t;
	t.restart();

	std::vector<std::set<size_t>> minGroup = GetMinGroup(skills, group);
	if (minGroup.empty())
	{
		std::cout << "Задачу не решить" << std::endl;
	}
	else
	{
		for (const auto& skills : minGroup)
		{
			copy(skills.begin(), skills.end(), std::ostream_iterator<size_t>(std::cout, " "));
			std::cout << std::endl;
		}
	}

	double duration = t.elapsed();

	std::cout << std::endl << duration << std::endl;
}