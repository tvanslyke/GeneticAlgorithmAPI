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

Population::Population(size_t count) {
	// TODO Auto-generated constructor stub
	pop = vector<Evolvable *>(count);
}

Population::~Population() {
	// TODO Auto-generated destructor stub
}


bool Population::NextGeneration()
{
	return true;
}

vector<Evolvable * > Population::SampleStochastic(size_t new_pop_size)
{
	vector<Evolvable *> new_pop = vector<Evolvable *>(new_pop_size);

	return vector<Evolvable *>();
}
vector<Evolvable *> Population::SampleRoulleteWheel(size_t new_pop_size)
{
	return vector<Evolvable *>();
}

