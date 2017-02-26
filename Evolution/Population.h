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
#include "Genetics/Sampling/SamplingPolicy.h"
//#include "Genetics/CrossoverPolicies/CrossoverPolicy.h"
//#include "Evolvable.h"
//class EvolvableImpl =
template <
class EvolvableImpl,
class SP,
class CP,
class = typename std::enable_if<std::is_base_of<Evolvable, EvolvableImpl>::value, EvolvableImpl>::type>
class Population;

template <class EvolvableImpl,class SP,class CP>
class Population<EvolvableImpl, SP, CP>
{
protected:
	Population();
	std::vector<EvolvableImpl> pop;
	SamplingPolicy<SP> sampler;
	//std::shared_ptr<CrossoverPolicy> crossoverPolicy;
public:
	virtual ~Population();
	virtual void nextGeneration();
};

#endif /* GENETICSTRUCTURES_POPULATION_H_ */
