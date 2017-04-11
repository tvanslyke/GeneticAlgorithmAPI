/*
 * UniformRandomCrossover.h
 *
 *  Created on: Feb 13, 2017
 *      Author: tim
 */

#ifndef GENETICS_CROSOVERPOLICIES_UNIFORMRANDOMCROSSOVER_H_
#define GENETICS_CROSOVERPOLICIES_UNIFORMRANDOMCROSSOVER_H_


#include "CrossoverPolicy.h"
#include "../../../Random/BaseRNG.h"
#include "../../../Random/RandomBitsAndBools.h"




class UniformRandomCrossover: public CrossoverPolicy<UniformRandomCrossover>
{

private:
	/** Cutoff threshold. */
	uint_fast64_t cutoff_;

public:
	/** Construct with given probability. */
	UniformRandomCrossover(double prob);
	/** default virtual destructor. */
	virtual ~UniformRandomCrossover() = default;

	/**
	 * Two-parent one-child crossover.
	 * @param parent1 - The first parent.
	 * @param parent2 - The second parent.
	 * @param child - The child chromosome.
	 */
	template <class C>
	void crossover(const C & parent1, const C & parent2, C & child)
	{
		bool polarity = rng::RandomBitsAndBools::get();
		size_t start = 0;
		size_t stop = 0;
		size_t len = parent1.size();
		while(stop < len)
		{
			start = stop;
			++stop;
			while((rng::BaseRNG::getRandomNumber() < cutoff_) and (stop < len))
			{
				++stop;
			}
			if(polarity)
			{
				std::copy(parent1.begin() + start, parent1.begin() + stop, child.begin() + start);
			}
			else
			{
				std::copy(parent2.begin() + start, parent2.begin() + stop, child.begin() + start);
			}
			polarity = not polarity;
		}
	}
	/**
	 * Two-parent two-child crossover.
	 * @param parent1 - The first parent.
	 * @param parent2 - The second parent.
	 * @param child1 - The first child chromosome.
	 * @param child2 - The second child chromosome.
	 */
	template <class C>
	void crossover(const C & parent1, const C & parent2, C & child1, C & child2)
	{
		bool polarity = rng::RandomBitsAndBools::get();
		size_t start = 0;
		size_t stop = 0;
		size_t len = parent1.size();
		while(stop < len)
		{
			start = stop;
			++stop;
			while((rng::BaseRNG::getRandomNumber() < cutoff_) and (stop < len))
			{
				++stop;

			}
			if(polarity)
			{
				std::copy(parent1.begin() + start, parent1.begin() + stop, child1.begin() + start);
				std::copy(parent2.begin() + start, parent2.begin() + stop, child2.begin() + start);
			}
			else
			{
				std::copy(parent1.begin() + start, parent1.begin() + stop, child2.begin() + start);
				std::copy(parent2.begin() + start, parent2.begin() + stop, child1.begin() + start);
			}
			polarity = not polarity;
		}
	}
};

#endif /* GENETICS_CROSOVERPOLICIES_UNIFORMRANDOMCROSSOVER_H_ */
