/*
 * MutatablePrimitives.h
 *
 *  Created on: Jan 17, 2017
 *      Author: tim
 */

#ifndef MUTATION_MUTATABLES_MUTATABLEPRIMITIVES_H_
#define MUTATION_MUTATABLES_MUTATABLEPRIMITIVES_H_

#include "MutatableIntegral.h"
#include "MutatableFloatingPoint.h"


template <typename T>
Mutatable * MakeNewMutatablePrimitive(T data)
{
	if(std::is_integral<T>::value)
	{
		return new MutatableIntegral<T>(data);
	}
	else if(std::is_floating_point<T>::value)
	{
		return new MutatableFloatingPoint<T>(data);
	}
	else
	{
		throw new std::invalid_argument("[Gene::Gene()] Bad type in Gene constructor (must be primitive or inherit from Mutatable).\n");
		return NULL;
	}
}


#endif /* MUTATION_MUTATABLES_MUTATABLEPRIMITIVES_H_ */
