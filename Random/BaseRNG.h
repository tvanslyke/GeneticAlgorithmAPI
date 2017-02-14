/*
 * RNGSeeder.h
 *
 *  Created on: Feb 5, 2017
 *      Author: tim
 */

#ifndef RANDOM_BASERNG_H_
#define RANDOM_BASERNG_H_

/**
 * Lightweight class to generate seeds for random distributions.
 * Because construction of std::random_device is expensive, a single
 * std::random_device instance is used for all random number generation.
 * The alternative would be to create a static member for each template
 * of class UniformRNG.
 */
#include <random>
namespace rng{

class BaseRNG
{

private:

	static std::random_device rd_;
	BaseRNG();
	virtual ~BaseRNG();
public:
	static std::mt19937_64 twister_;
	static uint_fast64_t getRandomNumber();
	static unsigned getVeryRandomNumber();
	static const uint_fast64_t minm;
	static const uint_fast64_t maxm;
	template <typename T>
	static void seedRNG(T & rng)
	{
		rng(rd_());
	}
};
}/* End namespace rng */
#endif /* RANDOM_BASERNG_H_ */
