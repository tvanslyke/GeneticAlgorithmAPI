/*
 * MutatableIntegral.h
 *
 *  Created on: Jan 14, 2017
 *      Author: tim
 */

#ifndef MUTATION_MUTATABLES_MUTATABLEINTEGRAL_H_
#define MUTATION_MUTATABLES_MUTATABLEINTEGRAL_H_

#include "Mutatable.h"
#include "../Mutators/MutatorFactory.h"
#include <iostream>
#include <type_traits>



template <typename T, typename FPType = double>
class MutatableIntegral: public Mutatable {
private:
	T data;
	Mutator<T> * mutator;
public:
	MutatableIntegral()
	{
		mutator = NULL;
		data = 0;
	}
	MutatableIntegral(T data, size_t mutator_select = 0, T lb = 0, T ub = 0, FPType prop = .5)
	{
		mutator = MutatorFactory<T, FPType>::GetMutator(mutator_select, lb, ub, prop);
		this->data = data;
	}
	virtual ~MutatableIntegral()
	{
		MutatorFactory<T, FPType>::NotifyDeletion(mutator);
	}
	void Mutate()
	{
		this->mutator->MutateData(data);
	}
	virtual MutatableIntegral<T, FPType> * Copy()
	{
		MutatableIntegral<T, FPType> * cpy = new MutatableIntegral<T, FPType>();
		cpy->data = this->data;
		cpy->mutator = MutatorFactory<T, FPType>::NotitfyAddition(this->mutator);
		return cpy;
	}
};

#endif /* MUTATION_MUTATABLES_MUTATABLEINTEGRAL_H_ */
