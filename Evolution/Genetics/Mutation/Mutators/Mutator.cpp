/*
 * Mutator.cpp
 *
 *  Created on: Feb 11, 2017
 *      Author: tim
 */

#include "Mutator.h"
#include "../../../../Utilities/TypeNum.h"



const size_t Mutator::getID() const
{
	return TypeNum::getNum<Mutator>();
}
void Mutator::mutate(boost::any & data)
{

}

