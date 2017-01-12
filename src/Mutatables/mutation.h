/*
 * mutatation.h
 *
 *  Created on: Jan 10, 2017
 *      Author: tim
 */

#ifndef MUTATION_H_
#define MUTATION_H_
#include <cstdlib>
#include <climits>
#include <unordered_map>
#include "../Random/random_numbers.h"


template <typename T>
void mutate_bitflip(T & data)
{
	size_t bit_select = rng_range<size_t>(0, sizeof(T) * CHAR_BIT);
	data ^= 1 << bit_select;
}

template <typename T>
class IncrMutator
{
private:
	T default_incr;
	T relative_incr;
public:
	IncrMutator(T default_incr, T relative_incr)
	{
		this->default_incr = default_incr;
		this->relative_incr = relative_incr;
	}
	void MutateRelativeIncr(T & gene)
	{
		gene += rng_range(0, 2) ? -relative_incr * gene : relative_incr *  gene;
	}
	void MutateFixedIncr(T & gene)
	{
		gene += rng_range(0, 2) ? -default_incr : default_incr;
	}
};

#endif /* MUTATION_H_ */





