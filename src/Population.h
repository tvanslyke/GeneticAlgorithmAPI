/*
 * Population.h
 *
 *  Created on: Jan 10, 2017
 *      Author: tim
 */

#ifndef POPULATION_H_
#define POPULATION_H_
#include <unordered_map>
#include <vector>

#include "Evolution/EvolutionPolicy.h"
#include "Evolvables/Evolvable.h"
using std::vector;

class Population {
	friend class SamplingPolicy;
private:
	vector<Evolvable *> pop;
	EvolutionPolicy * evolution_policy;

public:
	Population(EvolutionPolicy * policy);
	virtual ~Population();

	// replaces 'pop' with it's next generation.
	// member 'SamplingPolicy * policy' handles selection of the next generation.
	bool NextGeneration();

	// indicates whether the population is extant (not extinct).
	// true if pop.size() > 0 else false
	bool IsExtant();
};

#endif /* POPULATION_H_ */
