/*
 * FitnessProportionatePolicy.cpp
 *
 *  Created on: Jan 13, 2017
 *      Author: tim
 */

#include "../Evolution/FitnessProportionatePolicy.h"

#include "../Evolution/sampling.h"


FitnessProportionatePolicy::FitnessProportionatePolicy(string name, size_t pop_size): EvolutionPolicy(name, false, false, pop_size, pop_size)
{

}

FitnessProportionatePolicy::~FitnessProportionatePolicy() {
	// TODO Auto-generated destructor stub
}

vector<Evolvable *> FitnessProportionatePolicy::Sample(vector<Evolvable *> pop)
{
	vector<Evolvable *> ret_vec = fitness_proportionate(pop, this->EvolutionPolicy::pop_bounds[0], true);
	return ret_vec;
}
void FitnessProportionatePolicy::MakeNextGeneration(vector<Evolvable *> & pop)
{
	pop = this->Sample(pop);
}
