/*
 * UniformRandomCrossover.h
 *
 *  Created on: Feb 13, 2017
 *      Author: tim
 */

#ifndef GENETICS_CROSOVERPOLICIES_UNIFORMRANDOMCROSSOVER_H_
#define GENETICS_CROSOVERPOLICIES_UNIFORMRANDOMCROSSOVER_H_
#include "../../Evolvable.h"
#include "../../../Random/BaseRNG.h"
#include "../../../Random/RandomBitsAndBools.h"
#include <iterator>
#include <iostream>
class UniformRandomCrossover {
protected:
	uint_fast64_t cutoff_;
public:
	UniformRandomCrossover(double prob);
	virtual ~UniformRandomCrossover();
	template <typename It>
	void cross(It begin1, It end1, It begin2)
	{
		cross(begin1, end1, begin2, typename std::iterator_traits<It>::iterator_category());
	}
	template <typename It>
	void cross(It begin1, It end1, It begin2, It dest)
	{
		cross(begin1, end1, begin2, std::iterator_traits<It>::iterator_tag());
	}
	template <typename It>
	void cross(It begin1, It end1, It begin2, std::random_access_iterator_tag)
	{
		bool polarity = rng::RandomBitsAndBools::get();
		It stop = It(begin1);
		while(begin1 < end1)
		{
			begin2 += stop - begin1;
			begin1 = stop;
			while((rng::BaseRNG::getRandomNumber() < cutoff_) and (stop < end1))
			{
				++stop;
			}
			if(polarity)
				std::swap_ranges(begin1, stop, begin2);
			polarity = not polarity;
		}
	}
	template <typename It>
	void cross(It begin1, It end1, It begin2, It dest, std::random_access_iterator_tag)
	{
		uint_fast64_t rand = 0;

		bool polarity = rng::RandomBitsAndBools::get();
		rand = rng::BaseRNG::getRandomNumber();
		It end2 = begin2;
		It destend = dest;

		while(begin1 < end1)
		{
			begin1 = end1;
			begin2 = end2;
			while((rand < cutoff_) and (begin1 < end1))
			{
				++end1;
				++end2;
				++destend;
				rand = rng::BaseRNG::getRandomNumber();
			}
			std::copy(begin1, end1, dest);
		}
	}
};

#endif /* GENETICS_CROSOVERPOLICIES_UNIFORMRANDOMCROSSOVER_H_ */
