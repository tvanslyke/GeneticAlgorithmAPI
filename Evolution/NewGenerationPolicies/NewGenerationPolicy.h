/*
 * NewGenerationPolicy.h
 *
 *  Created on: Feb 13, 2017
 *      Author: tim
 */

#ifndef EVOLUTION_NEWGENERATIONPOLICIES_NEWGENERATIONPOLICY_H_
#define EVOLUTION_NEWGENERATIONPOLICIES_NEWGENERATIONPOLICY_H_

#include <vector>
#include "../Evolvable.h"
#include <memory>
template <typename SP, typename CP>
class NewGenerationPolicy {
private:
	SP sampler;
	std::unique_ptr<CrossoverPolicy<CP>> crosser;
public:
	NewGenerationPolicy()
	{
		sampler = SP();
		crosser = std::unique_ptr<CrossoverPolicy<CP>>(new CrossoverPolicy<CP>());
	}
	virtual ~NewGenerationPolicy()
	{
		;
	}
private:
	template <typename Ev>
	void nextGeneration(std::vector<Ev> & pop)
	{
		;
	}
};

#endif /* EVOLUTION_NEWGENERATIONPOLICIES_NEWGENERATIONPOLICY_H_ */
