/*
 * UniformRandomCrossover.h
 *
 *  Created on: Feb 13, 2017
 *      Author: tim
 */

#ifndef GENETICS_CROSOVERPOLICIES_UNIFORMRANDOMCROSSOVER_H_
#define GENETICS_CROSOVERPOLICIES_UNIFORMRANDOMCROSSOVER_H_


#include "CrossoverPolicy.h"
#include "../../../Random/BaseRNG.h"
#include "../../../Random/RandomBitsAndBools.h"




class UniformRandomCrossover: public CrossoverPolicy<UniformRandomCrossover>
{

private:
	//using It = CrossoverPolicy<UniformRandomCrossover>::iterator_type;
	uint_fast64_t cutoff_;
protected:

public:
	UniformRandomCrossover(double prob);
	virtual ~UniformRandomCrossover();



	template <typename It>
	void operator()(It begin1, It end1, It begin2, std::forward_iterator_tag)
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
	void operator()(It begin1, It end1, It begin2, It dest, std::forward_iterator_tag)
	{
		bool polarity = rng::RandomBitsAndBools::get();
		It end2 = begin2;
		It destend = dest;

		while(begin1 < end1)
		{
			begin1 = end1;
			begin2 = end2;
			while(((rng::BaseRNG::getRandomNumber() < cutoff_) < cutoff_) and (begin1 < end1))
			{
				++end1;
				++end2;
				++destend;
			}
			if(polarity)
				std::copy(begin1, end1, dest);
			polarity = not polarity;
		}
	}

	template <typename It>
	void operator()(It begin1, It end1, It begin2, std::random_access_iterator_tag)
	{
		bool polarity = rng::RandomBitsAndBools::get();
		size_t count = 0;
		size_t stop = std::distance(begin1, end1);//end1 - begin1;
		const uint_fast64_t & cut = cutoff_;
		while(stop > 0)
		{
			count = 0;
			while((++count < stop) and (rng::BaseRNG::getRandomNumber() < cutoff_)){}
			if(polarity)
			{
				std::swap_ranges(begin1, begin1 + count, begin2);
			}
			stop -= count;
			begin1 += count;
			begin2 += count;
			polarity = not polarity;
		}
	}

	template <typename It>
	void operator()(It begin1, It end1, It begin2, It dest, std::random_access_iterator_tag)
	{
		bool polarity = rng::RandomBitsAndBools::get();
		//uint_fast64_t rand = rng::BaseRNG::getRandomNumber();
		size_t count = 0;
		size_t stop = end1 - begin1;
		while(stop > 0)
		{
			count = 0;
			while((++count < stop) and (rng::BaseRNG::getRandomNumber() < cutoff_)){}
			if(polarity)
				std::copy(begin1, begin1 + count, dest);
			else
				std::copy(begin2, begin2 + count, dest);
			stop -= count;
			begin1 += count;
			begin2 += count;
			dest += count;
			polarity = not polarity;
		}
	}
};

#endif /* GENETICS_CROSOVERPOLICIES_UNIFORMRANDOMCROSSOVER_H_ */
