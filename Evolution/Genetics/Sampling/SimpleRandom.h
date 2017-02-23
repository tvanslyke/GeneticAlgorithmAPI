/*
 * SimpleRandom.h
 *
 *  Created on: Feb 22, 2017
 *      Author: tim
 */

#ifndef EVOLUTION_GENETICS_SAMPLING_SIMPLERANDOM_H_
#define EVOLUTION_GENETICS_SAMPLING_SIMPLERANDOM_H_

#include "SamplingPolicy.h"



class SimpleRandom: public SamplingPolicy<SimpleRandom> {
private:
	std::vector<std::shared_ptr<Evolvable>> pop_;
	rng::UniformRNG<size_t> indexer;
public:
	template <typename It>
	void buildSample(const It & begin, const It & end, std::input_iterator_tag)
	{
		pop_.assign(begin, end);
		indexer = rng::UniformRNG<size_t>(0, pop_.size() - 1);
	}
	template <typename It>
	void sample(const It & begin, const It & end, It destBegin, It destEnd, std::input_iterator_tag)
	{
		pop_.assign(begin, end);
		indexer = rng::UniformRNG<size_t>(0, pop_.size() - 1);
		while(destBegin < destEnd)
		{
			*destBegin = next<typename It::value_type>();
		}
	}
	template <typename T>
	T next()
	{
		return pop_[indexer()];
	}


};


#endif /* EVOLUTION_GENETICS_SAMPLING_SIMPLERANDOM_H_ */
