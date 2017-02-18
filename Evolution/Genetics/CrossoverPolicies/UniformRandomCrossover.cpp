/*
 * UniformRandomCrossover.cpp
 *
 *  Created on: Feb 13, 2017
 *      Author: tim
 */

#include "UniformRandomCrossover.h"
#include "../../../Random/BaseRNG.h"
#include <cassert>
using rng::BaseRNG;
UniformRandomCrossover::UniformRandomCrossover(double prob)
{

	// TODO Auto-generated constructor stub
	assert(1 >= prob and prob >= 0);
	this->cutoff_ = BaseRNG::minm + (uint_fast64_t)((BaseRNG::maxm - BaseRNG::minm) * prob);
}

UniformRandomCrossover::~UniformRandomCrossover()
{
	// TODO Auto-generated destructor stub
}



