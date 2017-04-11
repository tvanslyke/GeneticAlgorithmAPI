/*
 * RandomBitsAndBools.h
 *
 *  Created on: Feb 13, 2017
 *      Author: tim
 */

#ifndef RANDOM_RANDOMBITSANDBOOLS_H_
#define RANDOM_RANDOMBITSANDBOOLS_H_
#include <cstdlib>
#include "stdint.h"

namespace rng{

/**
 * Class for generating random bits and boolean values
 *
 * @author Timothy Van Slyke
 */
class RandomBitsAndBools {
private:
	static uint_fast64_t bits;
	static size_t pos;
	RandomBitsAndBools();
public:
	virtual ~RandomBitsAndBools();

	static bool get();
};


}
#endif /* RANDOM_RANDOMBITSANDBOOLS_H_ */
