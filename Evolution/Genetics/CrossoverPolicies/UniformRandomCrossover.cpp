/*
 * UniformRandomCrossover.cpp
 *
 *  Created on: Feb 13, 2017
 *      Author: tim
 */


#include "UniformRandomCrossover.h"
#include <cassert>
UniformRandomCrossover::UniformRandomCrossover(double prob):
cutoff_((uint_fast64_t)(rng::BaseRNG::minm + (uint_fast64_t)((rng::BaseRNG::maxm - rng::BaseRNG::minm) * prob)))
{

	// TODO Auto-generated constructor stub
	assert(1 >= prob and prob >= 0);

}
UniformRandomCrossover::~UniformRandomCrossover()
{

}
