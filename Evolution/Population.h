/*
 * Population.h
 *
 *  Created on: Feb 13, 2017
 *      Author: tim
 */

#ifndef GENETICSTRUCTURES_POPULATION_H_
#define GENETICSTRUCTURES_POPULATION_H_

#include <memory>
#include <vector>
//#include "Genetics/CrossoverPolicies/CrossoverPolicy.h"
//#include "Evolvable.h"

class Population {
protected:
	Population();
	//std::vector<std::shared_ptr<Evolvable>> pop;
	//std::shared_ptr<CrossoverPolicy> crossoverPolicy;
public:
	virtual ~Population();
	virtual void nextGeneration();
};

#endif /* GENETICSTRUCTURES_POPULATION_H_ */
