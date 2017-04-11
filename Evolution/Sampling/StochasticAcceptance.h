/*
 * StochasticAcceptance.h
 *
 *  Created on: Feb 21, 2017
 *      Author: tim
 */

#ifndef EVOLUTION_GENETICS_SAMPLING_STOCHASTICACCEPTANCE_H_
#define EVOLUTION_GENETICS_SAMPLING_STOCHASTICACCEPTANCE_H_


#include <vector>

#include "../Evolvable.h"
#include "../../RandomNumbers.h"

/**
 * SamplingPolicy implementing Stochastic Acceptance.
 *
 * see: https://en.wikipedia.org/wiki/Fitness_proportionate_selection
 *
 * @author Timothy Van Slyke
 */
template <class E>
class StochasticAcceptance
{
private:
	/** Vector of pointers to Evolvables. */
	std::vector<E *> pop_;
	/** vector of fitnesses/ */
	std::vector<double> fits_;
	/** RNG for selecting random indices. */
	rng::UniformRNG<size_t> indexer_;
	/** RNG for generating a cutoff value to determine whether a selected fitness
	 * is good enough to be accepted.
	 */
	rng::UniformRNG<double> accepter_;

public:
	/**
	 * Build the internal sample.
	 * @param begin - iterator to the first element in the population.
	 * @param end - iterator to the first invalid element in the population.
	 */
	template <typename It>
	void buildSample(It begin, It end)
	{
		clear();
		auto maxFit = std::numeric_limits<double>::min();
		size_t size = size_t(0);
		for(auto iter = begin; iter != end; ++iter)
		{
			pop_.push_back(static_cast<E*>(&(*iter)));
			fits_.push_back(pop_.back()->getFitness());
			if(maxFit < fits_.back())
			{
				maxFit = fits_.back();
			}
			++size;
		}
		indexer_ = rng::UniformRNG<size_t>(0, size - 1);
		accepter_ = rng::UniformRNG<double>(0, maxFit);
	}

	/**
	 * Generate an entire sample at once.
	 * @param begin - beginning of the input population.
	 * @param end - end of the input population
	 * @param destBegin - beginning of the output population
	 * @param destEnd - end of the output population.
	 */
	template <typename It>
	void sample(It begin, It end, It destBegin, It destEnd)
	{
		buildSample(begin, end);
		for(auto index = indexer_();destBegin != destEnd;index = indexer_())
		{
			while(fits_[index] < accepter_())
			{
				index = indexer_();
			}
			*destBegin = pop_[index];
			++destBegin;
		}
	}

	/**
	 * Lazily select the next evolvable.
	 * @return a pointer to the next evolvable.
	 */
	E* next()
	{
		auto index = indexer_();
		while(fits_[index] < accepter_())
		{
			index = indexer_();
		}
		return pop_[index];
	}
	/**
	 * Clear the internal storage structures of the sampling policy.
	 */
	void clear()
	{
		pop_.clear();
		fits_.clear();
	}



};


#endif /* EVOLUTION_GENETICS_SAMPLING_STOCHASTICACCEPTANCE_H_ */
