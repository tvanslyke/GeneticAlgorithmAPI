/*
 * SimpleRandom.h
 *
 *  Created on: Feb 22, 2017
 *      Author: tim
 */

#ifndef EVOLUTION_GENETICS_SAMPLING_SIMPLERANDOM_H_
#define EVOLUTION_GENETICS_SAMPLING_SIMPLERANDOM_H_

#include "SamplingPolicy.h"


/**
 * SamplingPolicy implementing simple random selection. (kind of useless)
 *
 * see: https://en.wikipedia.org/wiki/Simple_random_sample
 */
class SimpleRandom: public SamplingPolicy<SimpleRandom> {
private:
	std::vector<Evolvable*> pop_;
	rng::UniformRNG<size_t> indexer;
public:
	template <typename It>
	void buildSample(const It & begin, const It & end)
	{
		this->pop_.clear();
		for(It iter = begin; iter != end; ++iter)
		{
			pop_.push_back(&(*iter));
		}
		indexer = rng::UniformRNG<size_t>(0, pop_.size() - 1);
	}
	template <typename It>
	void sample(const It & begin, const It & end, It destBegin, It destEnd)
	{
		indexer = rng::UniformRNG<size_t>(0, std::distance(begin, end) - 1);
		while(destBegin < destEnd)
		{
			*destBegin = begin[indexer()];
		}
	}
	Evolvable* next()
	{
		return pop_[indexer()];
	}
};


#endif /* EVOLUTION_GENETICS_SAMPLING_SIMPLERANDOM_H_ */
