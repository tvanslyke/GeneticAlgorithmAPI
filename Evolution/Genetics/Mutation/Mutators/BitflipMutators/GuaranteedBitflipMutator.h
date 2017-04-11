/*
 * GuaranteedBitflipMutator.h
 *
 *  Created on: Feb 11, 2017
 *      Author: tim
 */

#ifndef MUTATION_MUTATORS_BITFLIPMUTATORS_GUARANTEEDBITFLIPMUTATOR_H_
#define MUTATION_MUTATORS_BITFLIPMUTATORS_GUARANTEEDBITFLIPMUTATOR_H_
#include <memory>
#include "../../../../../Random/UniqueIntGenerator.h"

/**
 * Mutator that guarantees at least some number of bits will be flipped.
 * @author Timothy Van Slyke
 */
template <typename T>
class GuaranteedBitflipMutator:MutatorBase<GuaranteedBitflipMutator<T>> {
private:

	/** RNG for selecting which bit to flip */
	rng::UniformRNG<size_t> bitSelector_;
	/** Number of bits used to represent type T. */
	static const size_t typeBits_ = CHAR_BIT * sizeof(T);
public:
	/**
	 * Construct from a minimum and maximum
	 * @param nmin - minimum number of bits to flip.
	 * @param nmax - maximum number of bits to flip.
	 */
	GuaranteedBitflipMutator(size_t nmin, size_t nmax)
	{
		static_assert(std::is_integral<T>::value, "Bitflip Mutators may only operate on integral types.");
		bitSelector_ = rng::UniformRNG<T>(nmin, nmax);
	}
	/** Default virtual destructor. */
	virtual ~GuaranteedBitflipMutator() = default;
	/**
	 * Mutate the data held by the boost::any reference.
	 * @param data - The boost::any reference to mutate.
	 */
	void mutate(boost::any & dat)
	{
		// get the value of dat
		T data = boost::any_cast<T>(dat);

		size_t bitcount = bitSelector_();

		// generate indices to flip
		std::vector<size_t> locs = std::vector<size_t>(bitcount);
		auto generator = rng::UniqueIntGenerator<size_t>(0, typeBits_ - 1)
							.unsorted()
							.length(bitcount);
		generator.lock();
		// flip the bits
		for(size_t i = 0; i < bitcount; ++i)
		{
			data ^= (1 << generator());
		}
		// reassign mutated value to the provided boost::any reference
		dat = boost::any(data);
	}
};

#endif /* MUTATION_MUTATORS_BITFLIPMUTATORS_GUARANTEEDBITFLIPMUTATOR_H_ */
