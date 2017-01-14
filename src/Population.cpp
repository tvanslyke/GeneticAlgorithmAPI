/*
 * Population.cpp
 *
 *  Created on: Jan 10, 2017
 *      Author: tim
 */

#include "Population.h"
#include <unordered_map>

using std::vector;

bool fit_compare(Evolvable * &a, Evolvable * &b)
{
	return (a->fitness) < (b->fitness);
}

Population::Population(SamplingPolicy * policy) {
	// TODO Auto-generated constructor stub
	this->policy = policy;
}

Population::~Population() {
	// TODO Auto-generated destructor stub
}

bool Population::IsExtant()
{
	return (bool)pop.size();
}
bool Population::NextGeneration()
{
	return true;
}



