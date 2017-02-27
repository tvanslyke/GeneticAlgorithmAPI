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

/**
 * Policy for handling crossover between two chromosomes.  Implementations of the CrossoverPolicy interface
 * must inherit from CrossoverPolicy via the CRTP format:
 *
 * 		MyPolicy:public CrossoverPolicy<MyPolicy>
 *
 * CrossoverPolicy dispatches to the proper overload of operator() in PolicyType.  All CrossoverPolicy
 * implementations only need to implement one of the below signatures of operator(), provided that the
 * NextGenerationPolicy caller invokes the corresponding signature in Population.
 */
template <class PolicyType>
class CrossoverPolicy {
private:

public:

	CrossoverPolicy()
	{

	}

	virtual ~CrossoverPolicy()
	{

	}

	/**
	 * Crosses two chromosomes in-place.
	 *
	 * @param start1 - iterator to the start of the first chromosome.
	 * @param end1	 - iterator to the end of the first chromosome.
	 * @param start2 - iterator to the start of the second chromosome.
	 */
	template <typename It>
	void operator()(It start1, It end1, It start2)
	{
		(*(static_cast<PolicyType*>(this)))(start1, end1, start2, typename std::iterator_traits<It>::iterator_category());
	}

	/**
	 * Crosses two chromosomes in-place, but provides a parameter for the length of the chromosome.
	 * This is useful for cases where std::distance(begin1, end1) has linear time complexity, but the distance is known to the caller.
	 *
	 * @param start1 - iterator to the start of the first chromosome.
	 * @param end1	 - iterator to the end of the first chromosome.
	 * @param start2 - iterator to the start of the second chromosome.
	 * @param count  - distance between start1 and end1.
	 */
	template <typename It>
	void operator()(It start1, It end1, It start2, size_t count)
	{
		(*(static_cast<PolicyType*>(this)))(start1, end1, start2, count, typename std::iterator_traits<It>::iterator_category());
	}

	/**
	 * Crossover on two chromosomes that does not modify the parents.  The result of the crossover is read into the 'dest' iterator.
	 *
	 * @param start1 - iterator to the start of the first chromosome.
	 * @param end1	 - iterator to the end of the first chromosome.
	 * @param start2 - iterator to the start of the second chromosome.
	 */
	template <typename It>
	void operator()(It start1, It end1, It start2, It dest)
	{
		(*(static_cast<PolicyType*>(this)))(start1, end1, start2, dest, typename std::iterator_traits<It>::iterator_category());
	}

	/**
	 * Crossover on two chromosomes that does not modify the parents.  The result of the crossover is read into the 'dest' iterator.
	 * This is useful for cases where std::distance(begin1, end1) has linear time complexity, but the distance is known to the caller.
	 *
	 * @param start1 - iterator to the start of the first chromosome.
	 * @param end1	 - iterator to the end of the first chromosome.
	 * @param start2 - iterator to the start of the second chromosome.
 	 * @param count  - distance between start1 and end1.
	 */
	template <typename It>
	void operator()(It start1, It end1, It start2, It dest, size_t count)
	{
		(*(static_cast<PolicyType*>(this)))(start1, end1, start2, dest, typename std::iterator_traits<It>::iterator_category());
	}
};



#endif /* GENETICSTRUCTURES_CROSOVERPOLICIES_CROSSOVERPOLICY_H_ */
