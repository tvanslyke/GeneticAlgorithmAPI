/*
 * ConstantSize.h
 *
 *  Created on: Feb 27, 2017
 *      Author: tim
 */

#ifndef EVOLUTION_NEWGENERATIONPOLICIES_CONSTANTSIZE_H_
#define EVOLUTION_NEWGENERATIONPOLICIES_CONSTANTSIZE_H_

#include <vector>
#include "../Evolvable.h"
#include <memory>

template <typename SP, typename CP, typename MP>
class ConstantSize
{
private:
	SP samplingPolicy;
	std::unique_ptr<CrossoverPolicy<CP>> crossoverPolicy;
	MP mutationPolicy;
	size_t popSize;
public:
	ConstantSize()
	{
		samplingPolicy = SP();
		crossoverPolicy = std::unique_ptr<CrossoverPolicy<CP>>(new CrossoverPolicy<CP>());
		mutationPolicy = MP();
		popSize = size_t();
	}
	virtual ~ConstantSize()
	{
		;
	}
private:
	template <typename Ev>
	void nextGeneration(std::vector<Ev> & pop)
	{
		popSize = pop.size();
		std::vector<Ev> nextGen(popSize);
		nextGen.reserve(popSize);
		samplingPolicy.buildSample(pop.begin(), pop.end());
		Ev* parent1;
		Ev* parent2;
		for(auto i = 0; i < popSize; ++i)
		{
			parent1 = static_cast<Ev*>(samplingPolicy.next());
			parent2 = static_cast<Ev*>(samplingPolicy.next());
			crossoverPolicy(parent1->begin(), parent1->end(), parent2->begin(), nextGen[i].begin());
		}
	}
};

#endif /* EVOLUTION_NEWGENERATIONPOLICIES_CONSTANTSIZE_H_ */
