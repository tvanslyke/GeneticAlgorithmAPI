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

#define MUTATE_BITFLIP

// ftp://vm1-dca.fee.unicamp.br/pub/docs/vonzuben/ia707_1s06/textos/00538609.pdf

template <typename T>
void mutate_bitflip(T & data)
{
	assert(std::is_integral<T>::value);
	size_t bit_select = rng_range<size_t>(0, sizeof(T) * CHAR_BIT);
	data ^= 1 << bit_select;
}



#endif /* MUTATION_H_ */





