/*
 * BaseRNG.cpp
 *
 *  Created on: Feb 5, 2017
 *      Author: tim
 */

#include "BaseRNG.h"
#include <random>

namespace rng{


BaseRNG::BaseRNG(){}
BaseRNG::~BaseRNG(){}

uint_fast64_t BaseRNG::getRandomNumber()
{
	return twister_();
}

unsigned int BaseRNG::getVeryRandomNumber()
{
	return rd_();
}
std::random_device BaseRNG::rd_;
std::mt19937_64 BaseRNG::twister_(BaseRNG::rd_());

const uint_fast64_t BaseRNG::minm = BaseRNG::twister_.min();
const uint_fast64_t BaseRNG::maxm = BaseRNG::twister_.max();
const uint_fast64_t BaseRNG::range = BaseRNG::twister_.max() - BaseRNG::twister_.min();
}
