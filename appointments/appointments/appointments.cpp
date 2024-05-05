#define BOOST_TIMER_ENABLE_DEPRECATED

#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <boost/timer.hpp>
#include "appointments.h"

std::vector<std::set<size_t>> GetMinGroup(const std::set<size_t>& skills, const std::vector<std::set<size_t>>& group)
{
	std::vector<std::set<size_t>> minGroup;
	
	for (size_t i = 0; i < std::pow(2, group.size()); i++)
	{
		std::vector<std::set<size_t>> tempGroup;
		std::set<size_t> tempSkills;
		for (size_t j = 0; j < group.size(); j++)
		{
			if (i & ((size_t)1 << j))
			{
				tempGroup.push_back(group[j]);
				tempSkills.insert(group[j].begin(), group[j].end());
			}
		}
		if (std::includes(tempSkills.begin(), tempSkills.end(), skills.begin(), skills.end())
			&& (minGroup.empty() || tempGroup.size() < minGroup.size()))
		{
			minGroup = tempGroup;
		}
	}

	return minGroup;
}