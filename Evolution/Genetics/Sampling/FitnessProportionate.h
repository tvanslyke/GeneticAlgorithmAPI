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
#include "SamplingPolicy.h"
#include "../../../Random/RandomNumbers.h"





class FitnessProportionate: public SamplingPolicy<FitnessProportionate> {
	using FitPair = std::pair<std::shared_ptr<Evolvable>,double>;
	using BaseRNG = rng::BaseRNG;
	class FitPairGreater
	{
		using FitPair = std::pair<std::shared_ptr<Evolvable>,double>;
	public:
		bool operator()(const FitPair & a, const FitPair & b) const
		{
			return a.second > b.second;
		}
		bool operator()(FitPair && a, FitPair && b) const
		{
			return a.second > b.second;
		}
	};
protected:
	std::vector<uint_fast64_t> cumfits_;
	std::vector<std::shared_ptr<Evolvable>> pop_;

public:
	//virtual ~FitnessProportionate();
	template <typename It>
	void buildSample(const It & begin, const It & end, std::input_iterator_tag)
	{
		double totalFit = 0.0;
		std::multiset<FitPair,FitPairGreater> sortedPop;
		auto ins = sortedPop.begin();
		for(auto iter = begin; iter != end; ++iter)
		{
			ins = sortedPop.insert(std::make_pair(*iter, (*iter)->getFitness()));
			totalFit += ins->second;
		}
		cumfits_.resize(0);
		pop_.resize(0);
		ins = sortedPop.begin();
		auto scaleToInt = [&totalFit](const double & num)->uint_fast64_t{return uint_fast64_t(BaseRNG::range * (num / totalFit) + BaseRNG::minm);};
		cumfits_.push_back(scaleToInt(ins->second));
		pop_.push_back(ins->first);
		ins = sortedPop.erase(ins);
		while(not sortedPop.empty())
		{
			cumfits_.push_back(scaleToInt(ins->second) + cumfits_.back());
			pop_.push_back(ins->first);
			ins = sortedPop.erase(ins);
		}
		for(auto & e:pop_)
		{
			cout << e->getFitness() << "\t";
		}
		cout << endl;
	}
	template <typename It>
	void sample(const It & begin, const It & end, It destBegin, It destEnd, std::input_iterator_tag)
	{
		buildSample(begin, end, std::forward_iterator_tag());
		while(destBegin != destEnd)
		{
			*destBegin = next();
			++destBegin;
		}
	}
	std::shared_ptr<Evolvable> next()
	{
		// generate random 64bit uint
		cout << "a ";
		uint_fast64_t rnum = rng::BaseRNG::getRandomNumber();
		auto start = cumfits_.begin();

		auto stop = cumfits_.end();
		// find rnum
		std::tie(start, stop) =  std::equal_range(start, stop, rnum);
		// if the number i repeated, find an upper bound and select an element randomly
		// from within that range
		cout << "b ";
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
			cout << "c " << endl;
			auto ind = (rng::UniformRNG<size_t>(start - cumfits_.begin(), (stop - cumfits_.begin())))();
			cout << ind << endl;
			return pop_[ind];
		}
	}
	void clear()
	{
		pop_.clear();
		cumfits_.clear();
	}
};

#endif /* EVOLUTION_GENETICS_SAMPLING_FITNESSPROPORTIONATE_H_ */
