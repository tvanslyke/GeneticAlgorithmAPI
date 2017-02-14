/*
 * UniformBitMutator.h
 *
 *  Created on: Feb 10, 2017
 *      Author: tim
 */

#ifndef MUTATION_MUTATORS_BITFLIPMUTATORS_UNIFORMBITFLIPMUTATOR_H_
#define MUTATION_MUTATORS_BITFLIPMUTATORS_UNIFORMBITFLIPMUTATOR_H_
#include <limits>
#include "BitflipMutator.h"
#include "../../../../../Random/BaseRNG.h"
template <typename T>
class UniformBitflipMutator:public BitflipMutator<T> {

private:
	const uint_fast64_t cutoff_;
public:

	UniformBitflipMutator(uint_fast64_t cutoff):BitflipMutator<T>(),cutoff_(cutoff)
	{

	}
	UniformBitflipMutator(double probability):
		UniformBitflipMutator(BaseRNG::minm + ((uint_fast64_t)((BaseRNG::maxm - BaseRNG::minm) * probability)))
	{
		assert((0.0 <= probability) and (probability <= 1.0));
	}
	virtual ~UniformBitflipMutator()
	{
		;
	}
	void mutate(boost::any & dat)
	{
		T data = boost::any_cast<T>(dat);
		if(cutoff_)
		{

			size_t bits = CHAR_BIT * sizeof(T);
			for(size_t i = 0; i < bits; ++i)
			{
				while(cutoff_ < BaseRNG::getRandomNumber())
				{
					++i;
				}
				data ^= (T(1) << i);
			}
			dat = boost::any(data);
		}
		else
		{
			dat = boost::any(~data);
		}
	}
	virtual size_t getID() const
	{
		return UniformBitflipMutator<T>::mutatorID;
	}
	static const size_t mutatorID;
};
template <typename T>
const size_t UniformBitflipMutator<T>::mutatorID = MutatorDiagnostics::assignID();

#endif /* MUTATION_MUTATORS_BITFLIPMUTATORS_UNIFORMBITFLIPMUTATOR_H_ */
