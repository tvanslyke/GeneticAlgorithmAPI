/*
 * MutatableFloatingPoint.h
 *
 *  Created on: Jan 15, 2017
 *      Author: tim
 */

#ifndef MUTATION_MUTATABLES_MUTATABLEFLOATINGPOINT_H_
#define MUTATION_MUTATABLES_MUTATABLEFLOATINGPOINT_H_

#include "Mutatable.h"
#include "../Mutators/MutatorFactory.h"
#include <algorithm>





template <typename T, typename FPType = double>
class MutatableFloatingPoint: public Mutatable {
protected:
	T data;
	Mutator<T, FPType> * mutator;
public:
	MutatableFloatingPoint()
	{
		data = 0;
		mutator = NULL;
	}
	MutatableFloatingPoint(T data, size_t mutator_select = MUT_REL_RAND_INCR, T lb = 0, T ub = 0, FPType prop = .5)
	{
		this->mutator = MutatorFactory<T, FPType>::GetMutator(mutator_select, lb, ub, prop);
		this->data = data;
	}
	virtual ~MutatableFloatingPoint()
	{
		MutatorFactory<T, FPType>::NotifyDeletion(mutator);
	}
	virtual void Mutate()
	{
		this->mutator->Mutate(data);
	}
	virtual MutatableFloatingPoint * Copy()
	{
		MutatableFloatingPoint * cpy = new MutatableFloatingPoint<T, FPType>();
		cpy->data = this->data;
		cpy->mutator = MutatorFactory<T, FPType>::NotitfyAddition(this->mutator);
		return cpy;
	}
};

#endif /* MUTATION_MUTATABLES_MUTATABLEFLOATINGPOINT_H_ */
