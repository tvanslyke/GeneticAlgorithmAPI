/*
 * UniformRandomCrossover.h
 *
 *  Created on: Feb 13, 2017
 *      Author: tim
 */

#ifndef GENETICS_CROSOVERPOLICIES_UNIFORMRANDOMCROSSOVER_H_
#define GENETICS_CROSOVERPOLICIES_UNIFORMRANDOMCROSSOVER_H_
#include "../../../Evolvable.h"
#include "../../../../Random/BaseRNG.h"
#include "../../../../Random/RandomBitsAndBools.h"
class UniformRandomCrossover {
protected:
	unsigned int cutoff_;
public:
	UniformRandomCrossover(double prob);
	virtual ~UniformRandomCrossover();
	template <typename It>
	void cross(It & begin1, It & end1, It & begin2)
	{
		uint_fast64_t rand = 0;
		It start1, start2, stop1, stop2;
		start1 = begin1;
		start2 = begin2;
		stop1 = begin1;
		bool polarity = rng::RandomBitsAndBools::get();
		rand = rng::BaseRNG::getRandomNumber();
		while(start1 < end1)
		{
			start1 = stop1;
			start2 = stop2;
			while((rand < cutoff_) and (start1 < end1))
			{
				++stop1;
				++stop2;
				rand = rng::BaseRNG::getRandomNumber();
			}
			std::swap_ranges(start1, stop1, start2);
		}
	}
};

#endif /* GENETICS_CROSOVERPOLICIES_UNIFORMRANDOMCROSSOVER_H_ */