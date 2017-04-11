/*
 * GuaranteedMutation.h
 *
 *  Created on: Feb 27, 2017
 *      Author: tim
 */

#ifndef EVOLUTION_GENETICS_MUTATION_MUTATIONPOLICIES_GUARANTEEDMUTATION_H_
#define EVOLUTION_GENETICS_MUTATION_MUTATIONPOLICIES_GUARANTEEDMUTATION_H_

#include "../../../../Random/UniqueIntGenerator.h"
#include <cstddef>
/**
 * Mutation policy that guarantees at least some minimum and no more than some
 * maximum number of Genes/Cromosomes will be mutated.
 *
 * @author Timothy Van Slyke
 */
class GuaranteedMutation {
public:
	/** Construct from a minimum and maximum number of items to mutate. */
	GuaranteedMutation(size_t minm, size_t maxm);
	virtual ~GuaranteedMutation() = default;
	/**
	 * Mutate the items 'pointed' to by the provided iterators.
	 * @param begin - iterator to the first item.
	 * @param end - past-the-end iterator.
	 */
	template <typename It>
	void mutate(It begin, It end)
	{
		indexer_ = rng::UniqueIntGenerator<size_t>().limits(0, std::distance(begin, end) - 1)
												   .unsorted()
												   .length(counter_.max());
		indexer_.lock();
		size_t count = counter_();
		ptrdiff_t index = 0;
		while(count)
		{
			index = indexer_() - index;
			std::advance(begin, index);
			begin->mutate();
			--count;
		}
	}
private:
	rng::UniqueIntGenerator<size_t> indexer_;
	rng::UniformRNG<size_t> counter_;

};
#endif /* EVOLUTION_GENETICS_MUTATION_MUTATIONPOLICIES_GUARANTEEDMUTATION_H_ */
