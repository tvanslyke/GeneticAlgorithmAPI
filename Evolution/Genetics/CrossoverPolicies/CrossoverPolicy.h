/*
 * CrossoverPolicy.h
 *
 *  Created on: Feb 13, 2017
 *      Author: tim
 */

#ifndef GENETICSTRUCTURES_CROSOVERPOLICIES_CROSSOVERPOLICY_H_
#define GENETICSTRUCTURES_CROSOVERPOLICIES_CROSSOVERPOLICY_H_


#include <iterator>
#include <iostream>
#include "../DynamicChromosome.h"
#include "../StaticChromosome.h"
#include <stdexcept>

/** Enumerations used for tag dispatching.*/
enum TwoChildren
{
	TWO_CHILDREN
};

enum OneChild
{
	ONE_CHILD
};

/**
 * Policy for handling crossover between two chromosomes.  Implementations of the CrossoverPolicy interface
 * must inherit from CrossoverPolicy via the CRTP format:
 *
 * 		MyPolicy:public CrossoverPolicy<MyPolicy>
 *
 * CrossoverPolicy uses tag dispatching to invoke the crossover() method implemented by it's component policy 'P'.
 * @author Timothy Van Slyke
 */
template <class P>
class CrossoverPolicy {
private:

public:
	/** Default constructor. */
	CrossoverPolicy() = default;
	/** Default destructor. */
	virtual ~CrossoverPolicy() = default;

	/**
	 * Performs a crossover procedure to produce one child StaticChromosome<N> from two parent StaticChromosome<N>.
	 *
	 * @param parent1 - The first parent chromosome.
	 * @param parent2 - The second parent chromosome.
	 * @param tag dispatched parameter.  Call with ONE_CHILD to invoke this overload.
	 * @return returns the new StaticChromosome<N>
	 */
	template <size_t N>
	StaticChromosome<N> cross(const StaticChromosome<N> & parent1, const StaticChromosome<N> & parent2, OneChild)
	{
		StaticChromosome<N> child;
		static_cast<P&>(*this).template crossover<StaticChromosome<N>>(parent1, parent2, child);
		return child;
	}
	/**
	 * Performs a crossover procedure to produce two children StaticChromosome<N>s from two parent chromosomes.
	 *
	 * @param parent1 - The first parent chromosome.
	 * @param parent2 - The second parent chromosome.
	 * @param tag dispatched parameter.  Call with TWO_CHILDREN to invoke this overload.
	 * @return returns two new StaticChromosome<N>s in a std::pair.
	 */
	template <size_t N>
	std::pair<StaticChromosome<N>, StaticChromosome<N>>
	cross(const StaticChromosome<N> & parent1, const StaticChromosome<N> & parent2, TwoChildren)
	{
		StaticChromosome<N> child1;
		StaticChromosome<N> child2;
		static_cast<P&>(*this).template crossover<StaticChromosome<N>>(parent1, parent2, child1, child2);
		return {child1, child2};
	}

	/**
	 * Performs a crossover procedure to produce one child DynamicChromosome from two parent DynamicChromosomes.
	 *
	 * @param parent1 - The first parent chromosome.
	 * @param parent2 - The second parent chromosome.
	 * @param tag dispatched parameter.  Call with ONE_CHILD to invoke this overload.
	 * @return returns the new DynamicChromosome
	 */
	DynamicChromosome cross(const DynamicChromosome & parent1, const DynamicChromosome & parent2, OneChild)
	{

		if(parent1.size() != parent2.size())
		{
			throw std::invalid_argument("Attempt to perform crossover on parent chromosomes of different sizes.");
		}
		DynamicChromosome child;
		child.resize(parent1.size());
		static_cast<P&>(*this).template crossover<DynamicChromosome>(parent1, parent2, child);
		return child;
	}


	/**
	 * Performs a crossover procedure to produce two children DynamicChromosomes from two parent DynamicChromosomes.
	 *
	 * @param parent1 - The first parent chromosome.
	 * @param parent2 - The second parent chromosome.
	 * @param tag dispatched parameter.  Call with TWO_CHILDREN to invoke this overload.
	 * @return returns two new DynamicChromosomes in a std::pair.
	 */
	std::pair<DynamicChromosome, DynamicChromosome>
	cross(const DynamicChromosome & parent1, const DynamicChromosome & parent2, TwoChildren)
	{

		if(parent1.size() != parent2.size())
		{
			throw std::invalid_argument("Attempt to perform crossover on parent chromosomes of different sizes.");
		}
		DynamicChromosome child1;
		DynamicChromosome child2;
		child1.resize(parent1.size());
		child2.resize(parent1.size());
		static_cast<P&>(*this).template crossover<DynamicChromosome>(parent1, parent2, child1, child2);
		return {child1, child2};
	}

};



#endif /* GENETICSTRUCTURES_CROSOVERPOLICIES_CROSSOVERPOLICY_H_ */
