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
#include "Evolvables/Evolvable.h"
using std::vector;

class Population {

private:
	vector<Evolvable *> pop;


	vector<Evolvable *> SampleStochastic(size_t new_pop_size);
	vector<Evolvable *> SampleRoulleteWheel(size_t new_pop_size);


public:
	Population(size_t count);
	virtual ~Population();
	bool NextGeneration();


};

#endif /* POPULATION_H_ */
