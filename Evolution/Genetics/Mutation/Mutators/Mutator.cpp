/*
 * Mutator.cpp
 *
 *  Created on: Feb 11, 2017
 *      Author: tim
 */

#include "Mutator.h"




Mutator::Mutator()
{
	
}


Mutator::~Mutator()
{

}
size_t Mutator::getID() const
{
	return Mutator::mutatorID;
}
void Mutator::mutate(boost::any & data)
{

}

int Mutator::getValue(boost::any)
{
	return 0;
}
const size_t Mutator::mutatorID = 0;
