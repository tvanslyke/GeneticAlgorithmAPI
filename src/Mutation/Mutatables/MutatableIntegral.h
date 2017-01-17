/*
 * MutatableIntegral.h
 *
 *  Created on: Jan 14, 2017
 *      Author: tim
 */

#ifndef MUTATION_MUTATABLES_MUTATABLEINTEGRAL_H_
#define MUTATION_MUTATABLES_MUTATABLEINTEGRAL_H_

#include "Mutatable.h"
#include "MutatorFactory.h"
#include <iostream>

#define MUT_BITFLIP         0  // no constructor args
#define MUT_RAND            1  // lower and upper bound args of type T
#define MUT_INCR            2  // incr arg of type T
#define MUT_RAND_INCR       3  // lower and upper bound args of type T
#define MUT_REL_INCR        4  // proportion argument of type FPType
#define MUT_REL_RAND_INCR   5  // proportion argument of type FPType


template <typename T, typename FPType = double>
class MutatableIntegral: public Mutatable {
private:
	T data;
	Mutator<T> * mutator;
public:
	MutatableIntegral(T data, size_t mutator_select = 0, T lb = 0, T ub = 0, FPType prop = .5)
	{
		this->data = data;
		mutator = MutatorFactory<T, FPType>::GetMutator(mutator_select, lb, ub, prop);

	}
	virtual ~MutatableIntegral()
	{
		delete mutator;
	}
	void Mutate()
	{
		this->mutator->MutateData(data);
	}
};

#endif /* MUTATION_MUTATABLES_MUTATABLEINTEGRAL_H_ */
