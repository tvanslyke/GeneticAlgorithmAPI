/*
 * RelRandIncrMutator.h
 *
 *  Created on: Jan 15, 2017
 *      Author: tim
 */

#ifndef MUTATION_MUTATORS_RELRANDINCRMUTATOR_H_
#define MUTATION_MUTATORS_RELRANDINCRMUTATOR_H_

#include "RandIncrMutator.h"
#include "RelIncrMutator.h"

template <typename T, typename FPType = double>
class RelRandIncrMutator:   public virtual RelIncrMutator<T, FPType>,
							public virtual RandIncrMutator<T>
{
protected:
	virtual void SetBounds(T lb, T ub)
	{
		this->RandIncrMutator<T>::SetBounds(lb, ub);
	}
public:
	RelRandIncrMutator(FPType prop = .5):
		RelIncrMutator<T, FPType>::RelIncrMutator(prop),
		RandIncrMutator<T>::RandIncrMutator(0, 0)
	{
		;
	}
	virtual ~RelRandIncrMutator()
	{
		;
	}
	virtual void SetProportion(FPType prop)
	{
		this->RelIncrMutator<T, FPType>::SetProportion(prop);
	}
	virtual void MutateData(T & data)
	{
		if(rand() & 1)
			data += (T)abs(rng_range<FPType>(0, RelIncrMutator<T, FPType>::prop *  data));
		else
			data -= (T)abs(rng_range<FPType>(0, RelIncrMutator<T, FPType>::prop *  data));
	}
};

#endif /* MUTATION_MUTATORS_RELRANDINCRMUTATOR_H_ */
