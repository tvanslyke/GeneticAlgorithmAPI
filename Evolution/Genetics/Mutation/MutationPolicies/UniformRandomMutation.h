/*
 * UniformRandomMutation.h
 *
 *  Created on: Feb 27, 2017
 *      Author: tim
 */

#ifndef EVOLUTION_GENETICS_MUTATION_MUTATIONPOLICIES_UNIFORMRANDOMMUTATION_H_
#define EVOLUTION_GENETICS_MUTATION_MUTATIONPOLICIES_UNIFORMRANDOMMUTATION_H_

#include "../../../../Random/Decisions.h"

/**
 * Mutation Policy for mutating items in an iterable with a given, uniform probaility for each item.
 * @author Timothy Van Slyke
 */
class UniformRandomMutation {

public:
	/** Default ctor. */
	UniformRandomMutation();
	/** Construct for prob/total probability of a particular item being mutated. */
	UniformRandomMutation(double prob, double total = 1.0);
	/**
	 * Mutate the items 'pointed' to by the provided iterators.
	 * @param begin - iterator to the first item.
	 * @param end - past-the-end iterator.
	 */
	template <typename It>
	void mutate(It begin, It end)
	{
		while(begin != end)
		{
			if(decider_.decide())
			{
				begin->mutate();
			}
			++begin;
		}
	}
private:
	rng::Decisions decider_;

};

#endif /* EVOLUTION_GENETICS_MUTATION_MUTATIONPOLICIES_UNIFORMRANDOMMUTATION_H_ */
