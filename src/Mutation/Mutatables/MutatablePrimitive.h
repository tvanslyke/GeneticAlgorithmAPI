/*
 * MutatablePrimitive.h
 *
 *  Created on: Jan 10, 2017
 *      Author: tim
 */

#ifndef MUTATABLES_MUTATABLEPRIMITIVE_H_
#define MUTATABLES_MUTATABLEPRIMITIVE_H_
#include "Mutatable.h"
#include <cstdlib>
#include "../Mutators/Mutator.h"

template <typename T>
class MutatablePrimitive: public Mutatable {
private:
	T data;
	Mutator<T> * mutator;
public:
	MutatablePrimitive(T data)
	{
		this->data = data;
	}
	MutatablePrimitive(Mutatable * other)
	{

	}
	virtual ~MutatablePrimitive()
	{
		;
	}

	virtual void operator =(T value)
	{
		this->data = value;
	}
	virtual void Mutate()
	{
		//mutate_bitflip<T>(this->data);
	}
	T GetValue()
	{
		return data;
	}
	MutatablePrimitive * Copy()
	{
		MutatablePrimitive * new_pm = new MutatablePrimitive<T>(data);
		return new_pm;
	}
};

#endif /* MUTATABLES_MUTATABLEPRIMITIVE_H_ */
