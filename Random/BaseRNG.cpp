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

unsigned int BaseRNG::getRandomNumber()
{
	return twister_();
}


std::random_device BaseRNG::rd_;
std::mt19937_64 BaseRNG::twister_(BaseRNG::rd_());

const unsigned int BaseRNG::minm = rd_.min();
const unsigned int BaseRNG::maxm = rd_.max();
}
