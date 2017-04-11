/*
 * UniformBitMutator.h
 *
 *  Created on: Feb 10, 2017
 *      Author: tim
 */

#ifndef MUTATION_MUTATORS_BITFLIPMUTATORS_UNIFORMBITFLIPMUTATOR_H_
#define MUTATION_MUTATORS_BITFLIPMUTATORS_UNIFORMBITFLIPMUTATOR_H_
#include <limits>
#include "../../../../../Random/BaseRNG.h"
#include <type_traits>

using rng::BaseRNG;
/**
 * Class for mutating integral data by flipping bits.  Each bit in the datum has the same
 * probability of being selected for being flipped.
 * @author Timothy Van Slyke
 */
template <typename T>
class UniformBitflipMutator:public MutatorBase<UniformBitflipMutator<T>> {
private:
	/** Threshhold value for random-number generator. */
	const uint_fast64_t cutoff_;
public:
	/** Construct from a probability between 0 and 1. */
	UniformBitflipMutator(double probability):
		cutoff_(BaseRNG::min() + ((uint_fast64_t) (BaseRNG::range() * probability)))
	{
		static_assert(std::is_integral<T>::value, "Bitflip Mutators may only operate on integral types.");
		if(probability > 1.0 or probability < 0.0)
		{
			throw std::invalid_argument("[UniformBitflipMutator] Probability must be between 0.0 and 1.0.");
		}
	}
	/** Default destructor. */
	virtual ~UniformBitflipMutator() = default;
	/**
	 * Mutate the data held by the boost::any reference.
	 * @param data - The boost::any reference to mutate.
	 */
	void mutate(boost::any & dat)
	{
		// get the value stored by the reference
		T data = boost::any_cast<T>(dat);
		size_t bits = CHAR_BIT * sizeof(T);
		// randomly mutate bits
		for(size_t i = 0; i < bits; ++i)
		{
			while(cutoff_ < BaseRNG::getRandomNumber())
			{
				++i;
			}
			data ^= (T(1) << i);
		}
	}
};


#endif /* MUTATION_MUTATORS_BITFLIPMUTATORS_UNIFORMBITFLIPMUTATOR_H_ */
