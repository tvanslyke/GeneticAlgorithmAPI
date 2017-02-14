/*
 * RandIncrMutator.h
 *
 *  Created on: Feb 5, 2017
 *      Author: tim
 */

#ifndef MUTATION_MUTATORS_RANDOMMUTATOR_H_
#define MUTATION_MUTATORS_RANDOMMUTATOR_H_
#include "../../../../Random/UniformRNG.h"
#include "Mutator.h"
#include <type_traits>
#include <limits>
#include <boost/any.hpp>

/**
 * Mutator that mutates data by setting its value equal to a randomly
 * selected value between some lower bound and upper bound (both inclusive).
 *
 * Primarily intended to be inherited from so as to make use of the 'rng_' and
 * 'rand_' fields, as well as the 'update()' methods.
 */
template <typename T>
class RandomMutator: public Mutator
{

protected:
	rng::UniformRNG<T> rng_;
	T rand_;
	virtual void update()
	{
		rand_ = rng_();
	}
public:
	RandomMutator(T lower_bound, T upper_bound)
	{
		this->rng_ = rng::UniformRNG<T>(lower_bound, upper_bound);
		this->rand_ = T();
	}
	virtual ~RandomMutator()
	{

	}
	virtual T getValue(boost::any & data)
	{
		return boost::any_cast<T>(data);
	}
	virtual void mutate(boost::any & data)
	{
		update();
		boost::any_cast<T&>(data) = rand_;
	}
	virtual size_t getID() const
	{
		return RandomMutator<T>::mutatorID;
	}
	static const size_t mutatorID;
};

template <typename T>
const size_t RandomMutator<T>::mutatorID = MutatorDiagnostics::assignID();






#endif /* MUTATION_MUTATORS_RANDOMMUTATOR_H_ */
