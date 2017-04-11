/*
 * RandIncrMutator.h
 *
 *  Created on: Feb 5, 2017
 *      Author: tim
 */

#ifndef MUTATION_MUTATORS_RANDINCRMUTATOR_H_
#define MUTATION_MUTATORS_RANDINCRMUTATOR_H_

#include "../../../../Random/UniformRNG.h"
#include "MutatorBase.h"
#include <type_traits>
#include <boost/any.hpp>
/**
 * Mutator that mutates data by adding incrementing or decrementing
 * provided data by some amount within a specified range.
 *
 * @author Timothy Van Slyke
 */
template <typename T, bool B = std::is_integral<T>::value>
class RandIncrMutator;
/**
 * Specialization for integral types.
 */
template <typename T>
class RandIncrMutator<T, true>:
   public MutatorBase<RandIncrMutator<T, true>>
{
private:
	// make-signed to allow negative lower-bounds on unsigned types.
	using S = typename std::make_signed<T>::type;
protected:
	/** Random number generator to generate values to add/subtract to/from data. */
	rng::UniformRNG<S> rng_;
public:
	/** Default ctor. */
	RandIncrMutator() = default;
	/** Construct from a lower-bound and upper-bound. */
	RandIncrMutator(S lowerBound, S upperBound):
		rng_(lowerBound, upperBound)
	{

	}
	/**
	 * Mutate the data held by the boost::any reference.
	 * @param data - The boost::any reference to mutate.
	 */
	void mutate(boost::any & data)
	{
		T dat = boost::any_cast<T>(data);
		data = dat + rng_();
	}
};
/**
 * Specialization for non-integral types.
 */
template <typename T>
class RandIncrMutator<T, false>: public MutatorBase<RandIncrMutator<T, false>>
{
protected:
	rng::UniformRNG<T> rng_;
public:
	/** Default ctor. */
	RandIncrMutator() = default;
	/** Construct from a lower-bound and upper-bound. */
	RandIncrMutator(T lowerBound, T upperBound):
		rng_(lowerBound, upperBound)
	{

	}
	/**
	 * Mutate the data held by the boost::any reference.
	 * @param data - The boost::any reference to mutate.
	 */
	void mutate(boost::any & data)
	{
		boost::any_cast<T&>(data) += rng_();
	}
};
#endif /* MUTATION_MUTATORS_RANDINCRMUTATOR_H_ */
