/*
 * StochasticAcceptance.h
 *
 *  Created on: Feb 21, 2017
 *      Author: tim
 */

#ifndef EVOLUTION_GENETICS_SAMPLING_STOCHASTICACCEPTANCE_H_
#define EVOLUTION_GENETICS_SAMPLING_STOCHASTICACCEPTANCE_H_

#include "SamplingPolicy.h"
#include <vector>




class StochasticAcceptance: public SamplingPolicy<StochasticAcceptance>
{
private:
	std::vector<std::shared_ptr<Evolvable>> pop;
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
		pop = std::vector<std::shared_ptr<Evolvable>>();
		fits = std::vector<double>();
		indexer = rng::UniformRNG<size_t>();
		accepter = rng::UniformRNG<double>();
	}

	~StochasticAcceptance() {
		// TODO Auto-generated destructor stub
	}


	std::shared_ptr<Evolvable> next()
	{
		auto index = indexer();
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
	void buildSample(const It & begin, const It & end, std::input_iterator_tag)
	{
		clear();
		auto maxFit = std::numeric_limits<double>::min();
		auto i = 0;
		for(; begin != end; ++i, ++begin)
		{
			pop.push_back(*begin);
			fits.push_back(pop[i]->getFitness());
			if(maxFit < fits.back())
			{
				maxFit = fits.back();
			}
		}
		indexer = rng::UniformRNG<size_t>(0, i - 1);
		accepter = rng::UniformRNG<double>(0, maxFit);
	}
	template <typename It>
	void sample(const It & begin, const It & end, It & destBegin, It & destEnd, std::input_iterator_tag)
	{
		buildSample(begin, end, std::forward_iterator_tag());
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
	template <typename It>
	void buildSample(const It & begin, const It & end, std::random_access_iterator_tag)
	{
		auto ind = 0ul;
		auto len = std::distance(begin, end);
		auto maxFit = std::numeric_limits<double>::min();
		fits.resize(len);
		pop.resize(len);
		static auto transfer = [this, &ind, &maxFit](const std::shared_ptr<Evolvable> & item)
		{
			this->fits[ind] = item->getFitness();
			if(maxFit < fits[ind])
			++ind;
			return item;
		};
		std::transform(begin, end, pop.begin(), transfer);
		indexer = rng::UniformRNG<size_t>(0, ind - 1);
		accepter = rng::UniformRNG<double>(0, maxFit);
	}
	template <typename It>
	void sample(const It & begin, const It & end, It & destBegin, It & destEnd, std::random_access_iterator_tag)
	{
		auto len = end - begin;
		auto maxFit = std::numeric_limits<double>::min();
		fits.resize(len);
		auto ind = 0ul;
		for(;begin != end; ++begin, ++ind)
		{
			fits[ind] = begin->getFitness();
			if(fits[ind] > maxFit)
			{
				maxFit = fits[ind];
			}
		}
		indexer = rng::UniformRNG<size_t>(0, ind - 1);
		accepter = rng::UniformRNG<double>(0, maxFit);
		for(ind = indexer();destBegin != destEnd;ind = indexer())
		{
			while(fits[ind] < accepter())
			{
				ind = indexer();
			}
			*destBegin = begin[index];
			++destBegin;
		}
	}


};


#endif /* EVOLUTION_GENETICS_SAMPLING_STOCHASTICACCEPTANCE_H_ */
