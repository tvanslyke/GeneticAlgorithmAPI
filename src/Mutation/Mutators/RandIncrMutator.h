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
	RandIncrMutator(T incr_max):
		IncrMutator<T>((T)0)
	{

	}
	virtual ~RandIncrMutator()
	{

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
