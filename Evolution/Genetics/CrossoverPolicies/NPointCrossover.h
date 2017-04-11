/*
 * NPointCrossover.h
 *
 *  Created on: Apr 6, 2017
 *      Author: tim
 */

#ifndef EVOLUTION_GENETICS_CROSSOVERPOLICIES_NPOINTCROSSOVER_
#define EVOLUTION_GENETICS_CROSSOVERPOLICIES_NPOINTCROSSOVER_

#include "CrossoverPolicy.h"
#include <type_traits>
#include <stdexcept>
#include <cassert>
#include "../../../Random/RandomBitsAndBools.h"
#include "../../../Random/UniqueIntGenerator.h"
/**
 * CrossoverPolicy where there are N points along the chromosome that
 * mark a swaping points.  Every other point alternates between being
 * swapped and staying in its original chromosome.
 *
 * @author Timothy Van Slyke
 */
template <size_t N>
class NPointCrossover: public CrossoverPolicy<NPointCrossover<N>> {
private:
	/** Generates breakpoint indices. */
	rng::UniqueIntGenerator<size_t> generator_;
public:
	/** Default ctor. */
	NPointCrossover() = default;
	/** default virtual destructor. */
	virtual ~NPointCrossover() = default;;

	/**
	 * Two-parent one-child crossover.
	 * @param parent1 - The first parent.
	 * @param parent2 - The second parent.
	 * @param child - The child chromosome.
	 */
	template <class C>
    void crossover(const C & parent1, const C & parent2, C & child)
	{
		// initialize the generator.
		generator_.limits(0, parent1.size()).length(N).sorted(rng::ASCENDING);
		generator_.lock();
		// decide which parent the first segment will come from
		bool polarity = rng::RandomBitsAndBools::get();
		auto begin = child.begin();
		size_t start = 0;
		size_t stop = 0;
		// iterate over each breakpoint, switching the parent chromosome every other point.
		for(size_t i = 0; i < N; ++i)
		{
			stop = generator_();
			std::copy((polarity ? parent1 : parent2).cbegin() + start,
					 (polarity ? parent1 : parent2).cbegin() + stop,
					  begin + start);
			polarity = not polarity;
			start = stop;
		}
		// one last copy
		stop = std::distance(parent1.begin(), parent1.end());
		std::copy((polarity ? parent1 : parent2).cbegin() + start,
				  (polarity ? parent1 : parent2).cbegin() + stop,
				  begin + start);
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
		// initialize the generator.
		generator_.limits(0, parent1.size()).length(N).sorted(rng::ASCENDING);
		generator_.lock();
		auto begin1 = child1.begin();
		auto begin2 = child2.begin();
		size_t start = 0;
		size_t stop = 0;
		// iterate over each breakpoint
		for(size_t i = 0; i < N; ++i)
		{
			stop = generator_();
			// switch parents/children every other iteration
			if(i & 1)
			{
				std::copy(parent1.begin() + start, parent1.begin() + stop, begin1 + start);
				std::copy(parent2.begin() + start, parent2.begin() + stop, begin2 + start);
			}
			else
			{
				std::copy(parent1.begin() + start, parent1.begin() + stop, begin1 + start);
				std::copy(parent2.begin() + start, parent2.begin() + stop, begin2 + start);
			}
			start = stop;
		}
		// one last copy
		if(N & 1)
		{
			std::copy(parent1.begin() + start, parent1.end(), begin1 + start);
			std::copy(parent2.begin() + start, parent2.end(), begin2 + start);
		}
		else
		{
			std::copy(parent1.begin() + start, parent1.end(), begin1 + start);
			std::copy(parent2.begin() + start, parent2.end(), begin2 + start);
		}
	}

};
#endif /* EVOLUTION_GENETICS_CROSSOVERPOLICIES_NPOINTCROSSOVER_ */
