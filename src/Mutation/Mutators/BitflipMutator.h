/*
 * BitflipMutator.h
 *
 *  Created on: Jan 14, 2017
 *      Author: tim
 */

#ifndef MUTATION_MUTATORS_BITFLIPMUTATOR_H_
#define MUTATION_MUTATORS_BITFLIPMUTATOR_H_

#include "Mutator.h"
#include <type_traits>
#include <iostream>
#include "../../Random/random_numbers.h"
using std::cout;
using std::endl;

template <typename T, typename FPType = double>
class BitflipMutator: public Mutator<T>
{
private:
	size_t nbits = std::numeric_limits<T>::digits;
public:
	BitflipMutator()
	{
		static_assert(std::is_integral<T>::value,
				      "BitflipMutator is only valid for integral (non-floating point) types!\n");
	}
	virtual ~BitflipMutator()
	{

	}
	void MutateData(T & data)
	{
		data ^= 1 << rng_range<size_t>(0, nbits);
	}
	void MutateData(T * data)
	{
		(*data) ^= 1 << rng_range<size_t>(0, nbits);
	}
	void DebugPrint()
	{
		cout << "Number of bits: " << nbits << endl;
	}
};

#endif /* MUTATION_MUTATORS_BITFLIPMUTATOR_H_ */
