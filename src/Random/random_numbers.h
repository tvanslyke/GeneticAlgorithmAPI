/*
 * random_numbers.h
 *
 *  Created on: Jan 10, 2017
 *      Author: tim
 */

#ifndef RANDOM_RANDOM_NUMBERS_H_
#define RANDOM_RANDOM_NUMBERS_H_

#include <cstdlib>
#include <climits>
#include <cmath>
#include <vector>
#include "sys/time.h"
#include <unordered_set>
#include <type_traits>
#include <string>
#include <numeric>
#include <algorithm>
#include <cassert>
const unsigned BITS_PER_RAND = (unsigned int)(log(RAND_MAX) / log(2)) - 1;

using std::vector;
using std::unordered_set;
using std::is_integral;
using std::string;
using std::to_string;
using std::iota;

void rng_autoinit();

template <typename T>
vector<T> py_range(T start, T end)
{
	assert(std::is_integral<T>::value);
	vector<T> vec = vector<T>((size_t)end - (size_t)start);
	iota(vec.begin(), vec.end(), start);
	return vec;
}

template <typename T>
T rng_range(T lb, T ub)
{
	return (T)((T)rand() / ((T)(RAND_MAX / (ub - lb))) + lb);;
}
template <typename T>
vector<T> rng_range_vector(size_t len, T lb, T ub)
{
	assert(ub > lb);
}

// sample values in range [lb, ub) with repetition
template <typename T>
vector<T> rng_range_sample_rep(size_t len, const T & lb, const T & ub)
{
	vector<T> sample = vector<T>(len);
	while(len--)
	{
		sample[len] = rng_range(lb, ub);
	}
}
// sample values in range [lb, ub) without repetition
template <typename T>
vector<T> rng_range_sample_unq(size_t len, const T & lb, const T & ub)
{
	// if the following 'if' is triggered, the program would enter an infinite loop
	if(std::is_integral<T>::value)
	{
		if(len < ub - lb)
		{
			string err_msg = "[rng_range_sample_unq()] Invalid sample size " + to_string(len) + "with\n"
							 "integral type lower bound " + to_string(lb) + " and upper bound " + to_string(ub) + ".\n";
			throw new std::invalid_argument(err_msg);
		}
		else
		{

			if(len < (ub - lb) / 2)
		    // sample elements to include
			{
				unordered_set<T> used;
				vector<T> sample = vector<T>(len);
				T num = rng_range(lb, ub);
				while(len--)
				{
					while(used.count(num))
					{
						num = rng_range(lb, ub);
					}
					used.insert(num);
					sample[len] = num;
				}
				return sample;
			}
			else
			// sample elements to exclude
			{
				vector<T> sample = py_range<T>(lb, ub);
				unordered_set<T> used(sample.begin(), sample.end());
				size_t offset = lb;
				size_t count = ub - lb;
				T num;
				while(len > count)
				{
					num = rng_range(lb, ub);
					if(used.count(num))
					{
						std::swap(sample[num - offset], sample[--count]);
						used.erase(num);
					}
				}
				sample.resize(len);
				random_shuffle(sample.begin(), sample.end());
				return sample;
			}
		}
	}
	else
	{
		unordered_set<T> used;
		vector<T> sample = vector<T>(len);
		T num = rng_range(lb, ub);
		while(len--)
		{
			while(used.count(num))
			{
				num = rng_range(lb, ub);
			}
			used.insert(num);
			sample[len] = num;
		}
		return sample;
	}

}


vector<bool> rand_bool_vector(const size_t & n_bools);

vector<bool> rand_bool_vector(const size_t & n_bools, float prob);

#endif /* RANDOM_RANDOM_NUMBERS_H_ */
