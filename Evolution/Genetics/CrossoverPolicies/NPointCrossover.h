/*
 * NPointCrossover.h
 *
 *  Created on: Feb 18, 2017
 *      Author: tim
 */

#ifndef EVOLUTION_GENETICS_CROSSOVERPOLICIES_NPOINTCROSSOVER_H_
#define EVOLUTION_GENETICS_CROSSOVERPOLICIES_NPOINTCROSSOVER_H_

#include "CrossoverPolicy.h"
#include "../../../Random/RandomBitsAndBools.h"
#include "../../../Random/UniqueIntGenerator.h"

class NPointCrossover: public CrossoverPolicy<NPointCrossover> {

private:
	rng::UniqueIntGenerator<size_t> generator;
	const size_t nPoints;
public:
	NPointCrossover(size_t n);
	virtual ~NPointCrossover();
	template <typename It>
	void operator()(It begin1, It end1, It begin2, std::forward_iterator_tag)
	{
		(*this)(begin1, end1, begin2, std::distance(begin1, end1), std::forward_iterator_tag());
	}

	template <typename It>
	void operator()(It begin1, It end1, It begin2, It dest, std::forward_iterator_tag)
	{
		(*this)(begin1, end1, begin2, std::distance(begin1, end1), std::forward_iterator_tag());
	}

	template <typename It>
	void operator()(const It & begin1, const It & end1, const It & begin2, std::random_access_iterator_tag)
	{
		(*this)(begin1, end1, begin2, std::distance(begin1, end1), std::random_access_iterator_tag());
	}

	template <typename It>
	void operator()(const It & begin1, const It & end1, const It & begin2, It dest, std::random_access_iterator_tag)
	{
		(*this)(begin1, end1, begin2, std::distance(begin1, end1), std::random_access_iterator_tag());
	}
	template <typename It>
	void operator()(It begin1, It end1, It begin2, size_t count, std::forward_iterator_tag)
	{

		generator.limits(0, count)
				 .sorted(rng::ASCENDING);
		generator.lock();
		size_t dist = generator();
		auto temp = dist;
		bool polarity = rng::RandomBitsAndBools::get();
		auto stop = begin1;
		std::advance(stop, dist);
		if(polarity)
			std::swap_ranges(begin1, stop, begin2);
		std::advance(begin2, dist);
		begin1 = stop;
		for(auto ignr = 1; ignr < nPoints; ++ignr)
		{
			polarity = not polarity;
			dist = generator() - temp;
			temp += dist;
			std::advance(stop, dist);
			if(polarity)
				std::swap_ranges(begin1, stop, begin2);
			std::advance(begin2, dist);
			begin1 = stop;
		}
	}

	template <typename It>
	void operator()(It begin1, It end1, It begin2, It dest, size_t count, std::forward_iterator_tag)
	{

		generator.limits(0, count)
				 .sorted(rng::ASCENDING);
		generator.lock();
		size_t dist = generator();
		auto temp = dist;
		bool polarity = rng::RandomBitsAndBools::get();
		auto stop = It();
		auto advance_all = [&polarity, &begin1, &begin2, &dist, &stop, &dest]()
		{
			if(polarity)
			{
				stop = begin1;
				std::advance(stop, dist);
				std::copy(begin1, stop, dest);
				std::advance(begin2, dist);
			}
			else
			{
				stop = begin2;
				std::advance(stop, dist);
				std::copy(begin2, stop, dest);
				std::advance(begin1, dist);
			}
			std::advance(dest, dist);
		};
		advance_all();
		begin1 = stop;
		for(auto ignr = 1; ignr < nPoints; ++ignr)
		{
			polarity = not polarity;
			dist = generator() - temp;
			temp += dist;
			advance_all();
		}
		if(polarity)
		{
			std::copy(begin1, end1, dest);
		}
		else
		{
			auto end2 = end1;
			std::advance(end2, std::distance(begin1, end1));
			std::copy(begin2, end2, dest);
		}
	}


	template <typename It>
	void operator()(It begin1, It end1, It begin2, size_t count, std::random_access_iterator_tag)
	{

		generator.limits(0u, count)
				 .sorted(rng::ASCENDING);
		generator.lock();
		auto dist = generator();
		auto temp = dist;
		bool polarity = rng::RandomBitsAndBools::get();
		if(polarity)
			std::swap_ranges(begin1, begin1 + dist, begin2);
		begin1 += dist;
		begin2 += dist;

		for(auto ignr = 1u; ignr < nPoints; ++ignr)
		{
			polarity = not polarity;
			dist = generator() - temp;
			temp += dist;
			if(polarity)
				std::swap_ranges(begin1, begin1 + dist, begin2);
			begin2 += dist;
			begin1 += dist;
		}
		if(polarity)
			std::swap_ranges(begin1, end1, begin2);
	}
	template <typename It>
	void operator()(It begin1, It end1, It begin2, It dest, size_t count, std::random_access_iterator_tag)
	{
		generator.limits(0, count)
				 .sorted(rng::ASCENDING);
		generator.lock();
		size_t dist = generator();
		auto temp = dist;
		bool polarity = rng::RandomBitsAndBools::get();
		if(polarity)
			std::copy(begin1, begin1 + dist, dest);
		else
			std::copy(begin2, begin2 + dist, dest);
		begin1 += dist;
		begin2 += dist;
		for(auto ignr = 1; ignr < nPoints; ++ignr)
		{
			polarity = not polarity;
			dist = generator() - temp;
			temp += dist;
			if(polarity)
				std::copy(begin1, begin1 + dist, dest);
			else
				std::copy(begin2, begin2 + dist, dest);
			begin2 += dist;
			begin1 += dist;
		}
		if(polarity)
			std::copy(begin1, end1, dest);
		else
			std::copy(begin1, begin2 + end1 - begin1, dest);
	}

};

#endif /* EVOLUTION_GENETICS_CROSSOVERPOLICIES_NPOINTCROSSOVER_H_ */
