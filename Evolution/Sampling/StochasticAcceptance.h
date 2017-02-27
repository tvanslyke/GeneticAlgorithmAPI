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
#include "../../Random/RandomNumbers.h"

/**
 * SamplingPolicy implementing simple random selection. (kind of useless)
 *
 * see: https://en.wikipedia.org/wiki/Fitness_proportionate_selection
 */
class StochasticAcceptance
{
private:
	std::vector<Evolvable *> pop;
	std::vector<double> fits;
	rng::UniformRNG<size_t> indexer;
	rng::UniformRNG<double> accepter;
	void resize(size_t index)
	{
		pop.resize(index);
		fits.resize(index);
	}
public:
	StochasticAcceptance() {
		// TODO Auto-generated constructor stub
		pop = std::vector<Evolvable*>();
		fits = std::vector<double>();
		indexer = rng::UniformRNG<size_t>();
		accepter = rng::UniformRNG<double>();
	}
	~StochasticAcceptance() {
		// TODO Auto-generated destructor stub
	}


	Evolvable* next()
	{
		auto index = indexer();
		cout << index << endl;
		while(fits[index] < accepter())
		{
			index = indexer();
		}
		return pop[index];
	}
	void clear()
	{
		pop.clear();
		fits.clear();
	}

	template <typename It>
	void buildSample(It begin, It end)
	{
		clear();
		auto maxFit = std::numeric_limits<double>::min();
		size_t size = size_t(0);
		for(auto iter = begin; iter != end; ++iter)
		{
			pop.push_back(static_cast<Evolvable*>(&(*iter)));
			fits.push_back(pop.back()->getFitness());
			if(maxFit < fits.back())
			{
				maxFit = fits.back();
			}
			++size;
		}
		indexer = rng::UniformRNG<size_t>(0, size - 1);
		accepter = rng::UniformRNG<double>(0, maxFit);
	}
	template <typename It>
	void sample(It begin, It end, It destBegin, It destEnd)
	{
		buildSample(begin, end);
		for(auto index = indexer();destBegin != destEnd;index = indexer())
		{
			while(fits[index] < accepter())
			{
				index = indexer();
			}
			*destBegin = pop[index];
			++destBegin;
		}
	}
};


#endif /* EVOLUTION_GENETICS_SAMPLING_STOCHASTICACCEPTANCE_H_ */
