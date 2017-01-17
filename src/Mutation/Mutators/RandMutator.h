/*
 * RandMutator.h
 *
 *  Created on: Jan 14, 2017
 *      Author: tim
 */

#ifndef MUTATION_MUTATORS_RANDMUTATOR_H_
#define MUTATION_MUTATORS_RANDMUTATOR_H_

#include "Mutator.h"
#include <limits>

template <typename T, typename FPType = double>
class RandMutator : public virtual Mutator<T, FPType>
{
protected:
	T lower_bound;
	T upper_bound;
public:
	RandMutator()
	{
		this->lower_bound = std::numeric_limits<T>::min();
		this->upper_bound = std::numeric_limits<T>::max();
	}
	RandMutator(T lower_bound, T upper_bound)
	{
		assert(lower_bound <= upper_bound);
		this->lower_bound = lower_bound;
		this->upper_bound = upper_bound;
	}
	virtual ~RandMutator()
	{
		;
	}
	virtual void SetBounds(T lb, T ub)
	{
		lower_bound = lb;
		upper_bound = ub;
	}
	void MutateData(T & data)
	{
		data = rng_range<T>(lower_bound, upper_bound);
	}
	void MutateData(T * data)
	{
		*data = rng_range<T>(lower_bound, upper_bound);
	}
};

#endif
