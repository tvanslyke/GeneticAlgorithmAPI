/*
 * random_numbers.cpp
 *
 *  Created on: Jan 11, 2017
 *      Author: tim
 */
#include "random_numbers.h"

// implementation dependent way of preserving bits
union signed_to_unsigned
{
	signed int i;
	unsigned int u;
};

void rng_autoinit()
{
	timeval tv;
	gettimeofday(&tv, NULL);
	srand(tv.tv_usec);
}

void set_rand_bools(vector<bool> & vec, unsigned int & bits, size_t  &offset)
{
	for(size_t i = 0; i < BITS_PER_RAND; ++i)
	{
		vec[offset + i] = bits << i;
	}
	offset += BITS_PER_RAND;
}

vector<bool> rand_bool_vector(const size_t & n_bools)
{
	vector<bool> bools = vector<bool>(n_bools);
	union signed_to_unsigned converter;
	size_t offset = 0;
	size_t i;
	for(i = 0; i < n_bools / BITS_PER_RAND; ++i)
	{
		converter.i = rand();
		set_rand_bools(bools, converter.u, offset);
	}
	for(i = 0; i < n_bools - offset; ++i)
	{
		converter.i = rand();
		bools[offset + i] = converter.u << i;
	}
	return bools;
}



