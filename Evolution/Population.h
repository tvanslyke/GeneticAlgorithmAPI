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

#include "Genetics/CrossoverPolicies/CrossoverPolicy.h"
#include "Evolvable.h"
template <class Ev,class SP,class CP, class = typename std::enable_if<std::is_base_of<Evolvable, Ev>::value, Ev>::type>
class Population;

template <class Ev,class SP,class CP>
class Population<Ev, SP, CP>
{
protected:
	Population();
	std::vector<Ev> pop;
	std::unique_ptr<SamplingPolicy<SP>> sampler;
	std::unique_ptr<CrossoverPolicy<CP>> crosser;
public:
	virtual ~Population();
	virtual void nextGeneration();
};

#endif /* GENETICSTRUCTURES_POPULATION_H_ */
