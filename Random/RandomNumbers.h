/*
 * RandomNumbers.h
 *
 *  Created on: Feb 5, 2017
 *      Author: tim
 */

#ifndef RANDOM_RANDOMNUMBERS_H_
#define RANDOM_RANDOMNUMBERS_H_

#include <type_traits>
#include <limits>
#include "UniformRNG.h"
#include <functional>
#include <vector>
#include <unordered_set>
#include <numeric>
#include <iterator>
#include <iostream>
using std::cout;
using std::endl;
namespace rng{



template <typename T>
class RandomNumbers {
private:
	static UniformRNG<T> rng_;
	static std::pair<T, T> lims_;
	static bool init_;
	static SharedUtilityManager<std::pair<T, T>, UniformRNG<T>> rngmap_;

public:
	static void Initialize() noexcept
	{
		UniformRNG<T>::Reset();
	}
	static void Reset() noexcept
	{
		UniformRNG<T>::Reset();
	}
	RandomNumbers()
	{

	}
	virtual ~RandomNumbers()
	{
		;
	}
	static void replace(const T & lb, const T & ub)
	{
		if(not init_)
			Initialize();
		if(lims_.first != lb)
		{
			lims_.first = lb;
			lims_.second = ub;
			rng_ = UniformRNG<T>(lims_);

		}
		else if(lims_.second != ub)
		{
			lims_.first = lb;
			lims_.second = ub;
			rng_ = UniformRNG<T>(lims_);
		}
	}
	static void replace(T && lb, T && ub)
	{
		if(not init_)
			Initialize();
		if(lims_.first != lb)
		{
			lims_.first = lb;
			lims_.second = ub;
			rng_ = UniformRNG<T>(lims_);

		}
		else if(lims_.second != ub)
		{
			lims_.first = lb;
			lims_.second = ub;
			rng_ = UniformRNG<T>(lims_);
		}
	}

	static void replace(const T & lb, T && ub)
	{
		if(not init_)
			Initialize();
		if(lims_.first != lb)
		{
			lims_.first = lb;
			lims_.second = ub;
			rng_ = UniformRNG<T>(lims_);

		}
		else if(lims_.second != ub)
		{
			lims_.first = lb;
			lims_.second = ub;
			rng_ = UniformRNG<T>(lims_);
		}
	}
	static void replace(T && lb, const T & ub)
	{
		if(not init_)
			Initialize();
		if(lims_.first != lb)
		{
			lims_.first = lb;
			lims_.second = ub;
			rng_ = UniformRNG<T>(lims_);

		}
		else if(lims_.second != ub)
		{
			lims_.first = lb;
			lims_.second = ub;
			rng_ = UniformRNG<T>(lims_);
		}
	}
	static T randomNumber(T lb = std::numeric_limits<T>::min(),
			      	  	  T ub = std::numeric_limits<T>::max())
	{
		replace(lb, ub);
		return rng_();
	}

	std::shared_ptr<UniformRNG<T>> getUniformRNG(T lb, T ub)
	{
		return this->rngmap_.get(lb, ub);
	}

	std::shared_ptr<UniformRNG<T>> getUniformRNG(std::pair<T, T> lims)
	{
		return this->rngmap_.get(lims.first, lims.second);
	}
	template <typename It>
	static void fill(It begin, It end, T lb, T ub)
	{

		size_t len = end - begin;
		if(len > 0)
		{
			replace(lb, ub);
		}
		else
		{
			return;
		}
		for(size_t i = 0; i < len; ++i)
		{
			begin[i] = rng_();
		}
	}

	static std::function<T ()> generator(T lb, T ub)
	{
		replace(lb, ub);
		auto gen = [lb, ub]()->T
		{
			static UniformRNG<T> rng = UniformRNG<T>(lb, ub);
			return rng();
		};
		return gen;
	}

	static std::vector<T> sampleRange(size_t count, T lb, T ub)
	{
		replace(lb, ub);
		std::vector<T> samples = std::vector<T>(count);
		for(size_t i = 0; i < count; ++i)
		{
			samples[i] = rng_();
		}
		return samples;
	}


	template <typename It1>
	static It1 choose(const It1 & begin, const It1 & end)
	{
		replace(0, (end - begin) - 1);
		return (begin + rng_());
	}
	template <typename It1>
	static It1 choose(It1 && begin, const It1 & end)
	{
		replace(0, (end - begin) - 1);
		return (begin + rng_());
	}
	template <typename It1>
	static It1 choose(const It1 & begin, It1 && end)
	{
		replace(0, (end - begin) - 1);
		return (begin + rng_());
	}
	template <typename It1>
	static It1 choose(It1 && begin, It1 && end)
	{
		replace(0, (end - begin) - 1);
		return (begin + rng_());
	}
	template <typename It>
	static void uniqueIntegers(It begin, It end, T lb, T ub)
	{

		replace(lb, ub);
		ptrdiff_t count = std::distance(begin, end);
		if(ub - lb < 2 * count)
		{
			// kinda-sorta fisher-yates
			std::vector<T> full_range = std::vector<T>((size_t)((ub - lb) + 1));
			std::iota(full_range.begin(), full_range.end(), lb);
			std::shuffle(full_range.begin(), full_range.end(), BaseRNG::twister_);
			std::copy(full_range.begin(), full_range.begin() + count,  begin);
		}
		else
		{
			// heuristic rejection
			std::unordered_set<T> selected = std::unordered_set<T>();
			selected.reserve(count);
			T num;
			for(ptrdiff_t i = 0; i < count; ++i)
			{
				num = rng_();
				while(selected.count(num) > 0)
				{
					num = rng_();
				}
				selected.insert(num);
				*begin = num;
				++begin;
			}
		}
	}

	template <typename It>
	static void uniqueFloats(It begin, It end, T lb, T ub)
	{

		replace(lb, ub);
		// heuristic rejection
		size_t count = end - begin;
		std::unordered_set<T> selected = std::unordered_set<T>();
		selected.reserve(count);
		T num;
		for(size_t i = 0; i < count; ++i)
		{
			num = rng_();
			while(selected.count(num) > 0)
			{
				num = rng_();
			}
			selected.insert(num);

			*begin = num;
			++begin;
		}
	}


};

template <typename T>
UniformRNG<T> RandomNumbers<T>::rng_;// = UniformRNG<T>(0, 1);

template <typename T>
std::pair<T, T> RandomNumbers<T>::lims_;// = std::pair<T, T>(0, 1);

template <typename T>
bool RandomNumbers<T>::init_ = false;// = std::pair<T, T>(0, 1);

} /* End namespace rng */
#endif /* RANDOM_RANDOMNUMBERS_H_ */
