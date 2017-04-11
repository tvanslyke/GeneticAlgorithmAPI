/*
 * Decisions.cpp
 *
 *  Created on: Feb 27, 2017
 *      Author: tim
 */

#include <cassert>
#include "BaseRNG.h"
#include "Decisions.h"
namespace rng {


Decisions::~Decisions()
{

}
Decisions::Decisions(double prob, double total)
{

	assert(prob > 0);
	prob_ = uint_fast64_t(prob * (maxm - minm) / total);
}
Decisions::Decisions():Decisions(0, 1.0)
{

}
bool Decisions::equalChanceDecision()
{
	return BaseRNG::getRandomNumber() & 1;
}

bool Decisions::next()
{
	return BaseRNG::getRandomNumber() < prob_;
}

bool Decisions::decide()
{
	return BaseRNG::getRandomNumber() < prob_;
}

void Decisions::setProbability(double prob, double total)
{
	prob_ = uint_fast64_t(prob * (maxm - minm) / total);
}

std::function<bool()> Decisions::generator()
{
	uint_fast64_t capture_prob = prob_;
	return [capture_prob](){return BaseRNG::getRandomNumber() < capture_prob;};
}

std::function<bool()> Decisions::generator(double prob, double total)
{
	uint_fast64_t capture_prob = uint_fast64_t(prob * (maxm - minm) / total);
	return [capture_prob](){return BaseRNG::getRandomNumber() < capture_prob;};
}

const uint_fast64_t & Decisions::maxm = BaseRNG::max();
const uint_fast64_t & Decisions::minm = BaseRNG::min();
} /* namespace rng */
