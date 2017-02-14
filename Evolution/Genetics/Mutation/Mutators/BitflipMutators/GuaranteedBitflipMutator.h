/*
 * GuaranteedBitflipMutator.h
 *
 *  Created on: Feb 11, 2017
 *      Author: tim
 */

#ifndef MUTATION_MUTATORS_BITFLIPMUTATORS_GUARANTEEDBITFLIPMUTATOR_H_
#define MUTATION_MUTATORS_BITFLIPMUTATORS_GUARANTEEDBITFLIPMUTATOR_H_
#include <memory>
#include "BitflipMutator.h"
template <typename T>
class GuaranteedBitflipMutator:BitflipMutator<T> {
private:
	size_t bitcount;
	std::shared_ptr<rng::UniformRNG<size_t>> bitselector;
	static size_t type_bits;
public:
	GuaranteedBitflipMutator(size_t nmin, size_t nmax):BitflipMutator<T>()
	{
		if(nmin == nmax)
		{
			bitselector = nullptr;
			bitcount = nmin;
		}
		else
		{
			bitselector = rng::RandomNumbers<size_t>::getUniformRNG(nmin, nmax);
			bitcount = 0;
		}

	}
	virtual ~GuaranteedBitflipMutator()
	{
		;
	}
	void mutate(boost::any & dat)
	{
		T & data = boost::any_cast<T>(data);

		if(bitselector != nullptr)
		{
			bitcount = bitselector();
		}
		std::vector<size_t> locs = std::vector<size_t>(bitcount);
		rng::RandomNumbers<size_t>::uniqueIntegers(locs.begin(), locs.end(), 0, type_bits);
		for(size_t i = 0; i < bitcount; ++i)
		{
			data ^= (1 << locs[i]);
		}
	}
	virtual size_t getID() const
	{
		return GuaranteedBitflipMutator<T>::mutatorID;
	}
	static const size_t mutatorID;
};

template <typename T>
size_t GuaranteedBitflipMutator<T>::type_bits = CHAR_BIT * sizeof(T) - 1;

template <typename T>
const size_t GuaranteedBitflipMutator<T>::mutatorID = MutatorDiagnostics::assignID();


#endif /* MUTATION_MUTATORS_BITFLIPMUTATORS_GUARANTEEDBITFLIPMUTATOR_H_ */
