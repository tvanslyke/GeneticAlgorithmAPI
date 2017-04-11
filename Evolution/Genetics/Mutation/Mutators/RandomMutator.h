/*
 * RandIncrMutator.h
 *
 *  Created on: Feb 5, 2017
 *      Author: tim
 */

#ifndef MUTATION_MUTATORS_RANDOMMUTATOR_H_
#define MUTATION_MUTATORS_RANDOMMUTATOR_H_
#include "../../../../RandomNumbers.h"
#include "MutatorBase.h"
#include <type_traits>
#include <limits>
#include <boost/any.hpp>

/**
 * Mutator that mutates data by setting its value equal to a randomly
 * selected value between some lower bound and upper bound (both inclusive).
 *
 * Primarily intended to be inherited from so as to make use of the 'rng_' and
 * 'rand_' fields, as well as the 'update()' methods.
 *
 * @author Timothy Van Slyke
 */
template <typename T>
class RandomMutator: public MutatorBase<RandomMutator<T>>
{

protected:
	rng::UniformRNG<T> rng_;
public:
	/** Construct from a lower-bound and upper-bound. */
	RandomMutator(T lower_bound, T upper_bound): rng_(lower_bound, upper_bound)
	{

	}
	/**
	 * Mutate the data held by the boost::any reference.
	 * @param data - The boost::any reference to mutate.
	 */
	virtual void mutate(boost::any & data)
	{
		boost::any_cast<T&>(data) = rng_();
	}
};







#endif /* MUTATION_MUTATORS_RANDOMMUTATOR_H_ */
