/*
 * RelIncrMutator.h
 *
 *  Created on: Jan 15, 2017
 *      Author: tim
 */

#ifndef MUTATION_MUTATORS_RELINCRMUTATOR_H_
#define MUTATION_MUTATORS_RELINCRMUTATOR_H_

#include "Mutator.h"
template <typename T, typename FPType = double>
class RelIncrMutator: public virtual Mutator<T>
{
	static_assert(std::is_floating_point<FPType>::value,
			      "[RelIncrMutator] FPType must be either a float, double, or long double.\n");
protected:
	// proportion or percent of |data| to randomly add or remove
	FPType prop;
public:
	RelIncrMutator(FPType prop = .5)
	{
		this->prop = prop;
	}
	virtual ~RelIncrMutator()
	{
		;
	}
	virtual void SetProportion(FPType prop)
	{
		this->prop = prop;
	}
	void MutateData(T & data)
	{
		if(rand() & 1)
			data += prop * data;
		else
			data -= prop * data;
	}
};








#endif /* MUTATION_MUTATORS_RELINCRMUTATOR_H_ */
