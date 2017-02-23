/*
 * RandomNumbers.h
 *
 *  Created on: Feb 5, 2017
 *      Author: tim
 */

#ifndef RANDOM_RANDOMNUMBERS_H_
#define RANDOM_RANDOMNUMBERS_H_

#include "RandomDistributions.h"
#include "UniformRNG.h"
#include <type_traits>
#include <limits>
#include <functional>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <iostream>
using std::cout;
using std::endl;
namespace rng{




template <typename T>
class RandomNumbers {
private:

	RandomNumbers()
	{

	}
public:



	static void Initialize()
	{
		UniformRNG<T>::Reset();
	}
	static void Reset()
	{
		UniformRNG<T>::Reset();
	}

	virtual ~RandomNumbers()
	{
		;
	}


	template <typename It>
	static void fill(It begin, It end, T lb, T ub)
	{

		auto len = end - begin;
		if(len > 0)
		{
		}
		else
		{
			return;
		}
		auto rng = UniformRNG<T>(lb, ub);
		for(size_t i = 0; i < len; ++i)
		{
			begin[i] = rng();
		}
	}

	static std::function<T ()> generator(T lb, T ub)
	{
		replace(lb, ub);
		auto gen = [lb, ub]()->T
		{
			static UniformRNG<T> rng = UniformRNG<T>(lb, ub);
			return rng();
		};
		return gen;
	}

	static std::vector<T> sampleRange(size_t count, T lb, T ub)
	{
		auto rng = UniformRNG<T>(lb, ub);
		auto samples = std::vector<T>(count);
		for(size_t i = 0; i < count; ++i)
		{
			samples[i] = rng();
		}
		return samples;
	}
};

} /* End namespace rng */
#endif /* RANDOM_RANDOMNUMBERS_H_ */
