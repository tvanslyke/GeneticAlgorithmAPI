/*
 * RandomBitsAndBools.cpp
 *
 *  Created on: Feb 13, 2017
 *      Author: tim
 */

#include "RandomBitsAndBools.h"
#include "BaseRNG.h"
namespace rng{
RandomBitsAndBools::RandomBitsAndBools() {
	// TODO Auto-generated constructor stub

}

RandomBitsAndBools::~RandomBitsAndBools() {
	// TODO Auto-generated destructor stub
}

bool RandomBitsAndBools::get()
{
	if( ((pos) &= (~(1 << 6))) )
	{
		bits = BaseRNG::getRandomNumber();
	}
	return bool(bits & (1 << (pos++)));
}

size_t RandomBitsAndBools::pos = (size_t)(0);
uint_fast64_t RandomBitsAndBools::bits = BaseRNG::getRandomNumber();

}
