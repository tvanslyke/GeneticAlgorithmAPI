/*
 * NonuniformBitflipMutator.h
 *
 *  Created on: Feb 12, 2017
 *      Author: tim
 */

#ifndef MUTATION_MUTATORS_BITFLIPMUTATORS_NONUNIFORMBITFLIPMUTATOR_H_
#define MUTATION_MUTATORS_BITFLIPMUTATORS_NONUNIFORMBITFLIPMUTATOR_H_
#include <climits>
#include "BitflipMutator.h"
using rng::BaseRNG;

template <typename T>
class NonuniformBitflipMutator: public BitflipMutator<T> {
private:

	std::vector<uint_fast64_t> cutoffs_;
	size_t nbits;
public:
	static std::vector<uint_fast64_t> vectorize(std::function<double (size_t)> func)
	{
		size_t nbits = sizeof(T) * CHAR_BIT;
		double sum = 0;
		std::vector<double> nums;
		nums.reserve(nbits);
		for(size_t i = 0; i < nbits; ++i)
		{
			nums.push_back(func(i));
			sum += nums[i];
		}
		uint_fast64_t fullrange = BaseRNG::maxm - BaseRNG::minm;
		std::vector<uint_fast64_t> cutoffs;
		cutoffs.reserve(nbits);
		for(size_t i = 0; i < nbits; ++i)
		{
			cutoffs.push_back(BaseRNG::minm + (uint_fast64_t)(fullrange * (nums[i]/sum)));
		}
		return cutoffs;
	}
	NonuniformBitflipMutator(const std::vector<uint_fast64_t> & dist_values)
	{
		nbits = sizeof(T) * CHAR_BIT;
		assert(dist_values.size() == nbits);
		cutoffs_ = dist_values;
	}
	NonuniformBitflipMutator(std::vector<uint_fast64_t> && dist_values)
	{
		nbits = sizeof(T) * CHAR_BIT;
		assert(dist_values.size() == nbits);
		cutoffs_ = dist_values;
	}
	virtual ~NonuniformBitflipMutator()
	{

	}
	void mutate(boost::any & data)
	{
		T temp = boost::any_cast<T>(data);
		uint_fast64_t prob = 0;
		for(size_t i = 0; i < nbits; ++i)
		{
			prob = BaseRNG::getRandomNumber();
			if(cutoffs_[i] > prob)
			{
				temp ^= (1 << i);
			}
		}
		data = boost::any(temp);
	}
	virtual size_t getID() const
	{
		return NonuniformBitflipMutator<T>::mutatorID;
	}
	static const size_t mutatorID;
};
template <typename T>
const size_t NonuniformBitflipMutator<T>::mutatorID = MutatorDiagnostics::assignID();
#endif /* MUTATION_MUTATORS_BITFLIPMUTATORS_NONUNIFORMBITFLIPMUTATOR_H_ */
