/*
 * RandIncrMutator.h
 *
 *  Created on: Jan 14, 2017
 *      Author: tim
 */

#ifndef MUTATION_MUTATORS_RANDINCRMUTATOR_H_
#define MUTATION_MUTATORS_RANDINCRMUTATOR_H_

#include "IncrMutator.h"
#include "RandMutator.h"
#include <limits>

template <typename T, typename FPType = double>
class RandIncrMutator: public virtual RandMutator<T, FPType>,
                       public virtual IncrMutator<T, FPType>
{
public:
	RandIncrMutator(T lower_bound, T upper_bound):
		RandMutator<T>(lower_bound, upper_bound),
		IncrMutator<T>((T)0)
	{
		IncrMutator<T>::minm = std::numeric_limits<T>::min();
		IncrMutator<T>::maxm = std::numeric_limits<T>::max();
	}
	virtual ~RandIncrMutator()
	{

	}
	virtual void SetBounds(T lb, T ub)
	{
		this->RandMutator<T>::SetBounds(lb, ub);
	}
	void MutateData(T & data)
	{
		this->IncrMutator<T>::incr = rng_range<T>(RandMutator<T>::lower_bound, RandMutator<T>::upper_bound);
		this->IncrMutator<T>::MutateData(data);
	}
	void MutateData(T * data)
	{
		this->IncrMutator<T>::incr = rng_range<T>(RandMutator<T>::lower_bound, RandMutator<T>::upper_bound);
		this->IncrMutator<T>::MutateData(data);
	}

};

#endif /* MUTATION_MUTATORS_RANDINCRMUTATOR_H_ */
