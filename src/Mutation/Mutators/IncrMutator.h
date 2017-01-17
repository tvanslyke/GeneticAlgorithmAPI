/*
 * IncrMutator.h
 *
 *  Created on: Jan 14, 2017
 *      Author: tim
 */

#ifndef MUTATION_MUTATORS_INCRMUTATOR_H_
#define MUTATION_MUTATORS_INCRMUTATOR_H_

#include "Mutator.h"
#include <cstdlib>
#include <limits>
#include <cmath>


template <typename T, typename FPType = double>
class IncrMutator : public virtual Mutator<T, FPType>
{
protected:
	T incr;
	T minm;
	T maxm;
public:
	IncrMutator(T incr = 0): Mutator<T>()
	{
		this->incr = abs(incr);
		minm = std::numeric_limits<T>::min() + incr;
		maxm = std::numeric_limits<T>::min() - incr;
	}
	virtual ~IncrMutator()
	{
		;
	}
	virtual void SetIncr(T new_incr)
	{
		this->incr = new_incr;
	}
	void MutateData(T & data)
	{
		T temp = rand() & 1 ? -incr : incr;
		if(temp > 0)
		{
			if(data > maxm)
				data -= incr;
			else
				data += incr;
		}
		else
		{
			if(data < minm)
				data -= incr;
			else
				data += incr;
		}
	}
	void MutateData(T * data)
	{
		T temp = rand() & 1 ? -incr : incr;
		if(temp > 0)
		{
			if(*data > maxm)
				*data -= incr;
			else
				*data += incr;
		}
		else
		{
			if(*data < minm)
				*data -= incr;
			else
				*data += incr;
		}
	}
};

#endif /* MUTATION_MUTATORS_INCRMUTATOR_H_ */
