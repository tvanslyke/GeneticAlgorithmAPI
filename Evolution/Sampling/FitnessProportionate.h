/*
 * FitnessProportionate.h
 *
 *  Created on: Feb 14, 2017
 *      Author: tim
 */

#ifndef EVOLUTION_GENETICS_SAMPLING_FITNESSPROPORTIONATE_H_
#define EVOLUTION_GENETICS_SAMPLING_FITNESSPROPORTIONATE_H_
#include <cstdint>
#include <functional>
#include <vector>
#include <algorithm>
#include "../Evolvable.h"
#include "../../RandomNumbers.h"



/**
 * SamplingPolicy implementing fitness proportionate selection.
 *
 * see: https://en.wikipedia.org/wiki/Fitness_proportionate_selection
 *
 * @author Timothy Van Slyke
 */

template <typename E>
class FitnessProportionate
{
	using FitPair = std::pair<E*, double>;
	using BaseRNG = rng::BaseRNG;
	/** Comparison functor to be used internally. */
	class FitPairGreater
	{
		using FitPair = std::pair<E*, double>;
	public:
		/**
		 * Compare two FitPairs.
		 * @param a - the first FitPair.
		 * @param b - the second FitPair.
		 * @return true if fitness(a) > fitness(B), else false.
		 */
		bool operator()(const FitPair & a, const FitPair & b) const
		{
			return a.second > b.second;
		}
	};
protected:
	/** Vector of cumulative Fitnesses. */
	std::vector<uint_fast64_t> cumfits_;
	/** Vector of pointers to Evolvables. */
	std::vector<E*> pop_;

public:
	/**
	 * Build the internal sample.
	 * @param begin - iterator to the first element in the population.
	 * @param end - iterator to the first invalid element in the population.
	 */
	template <typename It>
	void buildSample(const It & begin, const It & end)
	{
		// total fitness
		double totalFit = 0.0;
		// sorted population elements.
		std::multiset<FitPair,FitPairGreater> sortedPop;
		auto ins = sortedPop.begin();
		// fill the multiset.
		for(auto iter = begin; iter != end; ++iter)
		{
			ins = sortedPop.insert(FitPair(static_cast<E*>(&(*iter)), (*iter).getFitness()));
			totalFit += ins->second;
		}
		// clear the cumfits vector
		cumfits_.clear();
		// clear the vector of evolvable pointers.
		pop_.clear();

		ins = sortedPop.begin();
		// scales fitnesses to uint64s for faster comparisons.
		auto scaleToInt = [&totalFit](double num)->uint_fast64_t
		{
			return uint_fast64_t(BaseRNG::range() * (num / totalFit) + BaseRNG::min());
		};

		// sort the adjusted fitnesses and fill the local vector of evolvables.

		cumfits_.push_back(scaleToInt(ins->second));
		pop_.push_back(ins->first);
		ins = sortedPop.erase(ins);

		while(not sortedPop.empty())
		{
			cumfits_.push_back(scaleToInt(ins->second) + cumfits_.back());
			pop_.push_back(ins->first);
			ins = sortedPop.erase(ins);
		}
	}
	/**
	 * Generate an entire sample at once.
	 * @param begin - beginning of the input population.
	 * @param end - end of the input population
	 * @param destBegin - beginning of the output population
	 * @param destEnd - end of the output population.
	 */
	template <typename It>
	void sample(const It & begin, const It & end, It destBegin, It destEnd)
	{
		buildSample(begin, end);
		while(destBegin != destEnd)
		{
			*destBegin = next();
			++destBegin;
		}
	}
	/**
	 * Lazily select the next evolvable.
	 * @return a pointer to the next evolvable.
	 */
	E* next()
	{
		// generate random 64bit uint

		uint_fast64_t rnum = rng::BaseRNG::getRandomNumber();
		auto start = cumfits_.begin();

		auto stop = cumfits_.end();
		// find rnum
		std::tie(start, stop) =  std::equal_range(start, stop, rnum);
		// if the number i repeated, find an upper bound and select an element randomly
		// from within that range

		if(start == cumfits_.end())
		{
			return pop_.back();
		}
		else if(stop - start == 1)
		{
			return pop_[start - cumfits_.begin()];
		}
		// if not repeated, return immediately
		else
		{
			auto ind = (rng::UniformRNG<size_t>(start - cumfits_.begin(), (stop - cumfits_.begin())))();
			return pop_[ind];
		}
	}
	/**
	 * Clear the internal storage structures of the sampling policy.
	 */
	void clear()
	{
		pop_.clear();
		cumfits_.clear();
	}
};

#endif /* EVOLUTION_GENETICS_SAMPLING_FITNESSPROPORTIONATE_H_ */
