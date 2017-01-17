/*
 * MutatableFloatingPoint.h
 *
 *  Created on: Jan 15, 2017
 *      Author: tim
 */

#ifndef MUTATION_MUTATABLES_MUTATABLEFLOATINGPOINT_H_
#define MUTATION_MUTATABLES_MUTATABLEFLOATINGPOINT_H_

#include "Mutatable.h"

template <typename T>
class MutatableFloatingPoint: public Mutatable {
protected:
	T data;
public:
	MutatableFloatingPoint(T data, unsigned int mutator_select)
	{
		this->data = data;
	}
	virtual ~MutatableFloatingPoint()
	{

	}
	virtual void Mutate()
	{

	}
	virtual MutatableFloatingPoint * Copy()
	{
		return new MutatableFloatingPoint(this->data);
	}
};

#endif /* MUTATION_MUTATABLES_MUTATABLEFLOATINGPOINT_H_ */
