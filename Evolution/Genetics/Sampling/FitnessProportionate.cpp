/*
 * FitnessProportionate.cpp
 *
 *  Created on: Feb 14, 2017
 *      Author: tim
 */

#include "FitnessProportionate.h"
#include <algorithm>
#include <unordered_map>
#include <memory>
#include "../../../Random/RandomNumbers.h"
#include <iterator>


FitnessProportionate::FitnessProportionate(const std::vector<std::shared_ptr<Evolvable>> & pop): pop_(pop)
{

}

FitnessProportionate::~FitnessProportionate() {
	// TODO Auto-generated destructor stub
}

void FitnessProportionate::buildSample()
{
	using FitPair = std::pair<double, std::shared_ptr<Evolvable> >;
	size_t len = pop_.size();
	double totalfit = 0.0;
	std::vector<FitPair> sortedFits;
	for(size_t i = 0; i < len; ++i)
	{
		sortedFits.push_back(FitPair(pop_[i]->getFitness(), pop_[i]));
		totalfit += sortedFits.back().first;
	}

	std::sort(sortedFits.rbegin(),
			  sortedFits.rend(),
			  [](const FitPair & a, const FitPair & b){return a.first < b.first;});
	cumfits_ = std::vector<uint_fast64_t>();
	cumfits_.reserve(len);
	double acc = 0.0;
	FitPair & thispair = sortedFits.front();
	pop_[0] = thispair.second;
	acc += thispair.first;
	cumfits_.push_back((uint_fast64_t)((acc/totalfit) * rng::BaseRNG::maxm));
	for(size_t i = 0; i < len; ++i)
	{
		thispair = sortedFits[i];
		pop_[0] = thispair.second;
		acc += thispair.first;
		cumfits_.push_back((uint_fast64_t)((acc/totalfit) * rng::BaseRNG::maxm));
	}
}
std::shared_ptr<Evolvable> FitnessProportionate::next()
{

	uint_fast64_t rnum = rng::BaseRNG::getRandomNumber();
	std::vector<uint_fast64_t>::iterator start = cumfits_.begin();
	std::vector<uint_fast64_t>::iterator stop = cumfits_.end();
	start = std::lower_bound(start, stop, rnum);
	if(*(start + 1) == *start)
	{
		stop = std::upper_bound(start, stop, *start);
	}
	else
	{
		return pop_[start - cumfits_.begin()];
	}
	size_t ind = rng::RandomNumbers<size_t>::randomNumber(start - cumfits_.begin(), stop - cumfits_.begin());
	return this->pop_[ind];
}








