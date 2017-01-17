/*
 * FitnessProportionatePolicy.cpp
 *
 *  Created on: Jan 13, 2017
 *      Author: tim
 */

#include "FitnessProportionatePolicy.h"
#include "sampling.h"


FitnessProportionatePolicy::FitnessProportionatePolicy(string name, size_t pop_size): SamplingPolicy(name, false, false, pop_size, pop_size)
{

}

FitnessProportionatePolicy::~FitnessProportionatePolicy() {
	// TODO Auto-generated destructor stub
}

vector<Evolvable *> FitnessProportionatePolicy::Sample(vector<Evolvable *> pop)
{
	vector<Evolvable *> ret_vec = fitness_proportionate(pop, this->SamplingPolicy::pop_bounds[0]);
	return ret_vec;
}
