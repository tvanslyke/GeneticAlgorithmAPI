/*
 * UniqueIntGenerator.h
 *
 *  Created on: Feb 19, 2017
 *      Author: tim
 */

#ifndef RANDOM_UNIQUEINTGENERATOR_H_
#define RANDOM_UNIQUEINTGENERATOR_H_

#include <set>
#include <vector>
#include "UniformRNG.h"
#include <algorithm>
#include <functional>
#include <iostream>
namespace rng {
typedef enum
{
	DESCENDING = -1,
	NONE = 0,
	ASCENDING = 1
} SortingType;

template <typename T>
class UniqueIntGenerator {
private:
	UniformRNG<T> rng_;
	SortingType sorting;
	size_t len;
	std::set<T> storage;
	std::vector<T> seq;
	std::function<T (UniformRNG<T>&, std::set<T> &, std::vector<T> &)> gen;
	T num;
	void buildSeq()
	{
		auto diff = rng_.max() - rng_.min();
		seq.resize(diff);
		std::iota(seq.begin(), seq.end(), rng_.min());
		std::shuffle(seq.begin(), seq.end(),rng::BaseRNG::twister_);
		seq.resize(len);
	}
	void fillStorage()
	{
		storage.clear();
		if(rng_.max() - rng_.min() > 2 * len)
		{
			while(storage.size() < len)
			{
				storage.insert(rng_());
			}
		}
		else
		{
			buildSeq();
			for(auto & iter:seq)
			{
				storage.insert(iter);
			}
		}
	}
public:
	UniqueIntGenerator(T lb = T(), T ub = T(), size_t length = size_t()):rng_(lb, ub)
	{
		storage = std::set<T>();
		seq = std::vector<T>();
		len = length;
		gen = [this](UniformRNG<T>& rng, std::set<T> & storage, std::vector<T> & seq)->T
		{
			return T();
		};
		sorting = NONE;
	}
	virtual ~UniqueIntGenerator()
	{

	}
	T operator()()
	{

		return gen(rng_, storage, seq);
	}
	UniqueIntGenerator<T> & lock()
	{
		if(sorting == NONE)
		{
			if((2 * len) < size_t(rng_.max() - rng_.min()))
			{
				storage.clear();
				gen =[](UniformRNG<T>& rng, std::set<T> & storage, std::vector<T> & seq)
				{
					auto num = rng();
					while(not (storage.insert(num)).second)
					{
						num = rng();
					}
					return num;
				};
			}
			else
			{
				buildSeq();
				gen =[](UniformRNG<T>& rng, std::set<T> & storage, std::vector<T> & seq)
				{
					auto num = seq.back();
					seq.pop_back();
					return num;
				};
			}
		}
		else
		{
			storage.clear();
			fillStorage();
			if(sorting == ASCENDING)
			{
				gen =[](UniformRNG<T>& rng, std::set<T> & storage, std::vector<T> & seq)
				{
					auto num =*(storage.begin());
					storage.erase(storage.begin());
					return num;
				};
			}
			else
			{
				gen =[](UniformRNG<T>& rng, std::set<T> & storage, std::vector<T> & seq)
				{
					auto num = *(--(storage.end()));
					storage.erase(--(storage.end()));
					return num;
				};
			}
		}
		return *this;

	}
	UniqueIntGenerator & unsorted()
	{
		return sorted(NONE);
	}
	UniqueIntGenerator & sorted(SortingType sorting = ASCENDING)
	{
		this->sorting = sorting;
		return *this;
	}
	UniqueIntGenerator & limits(T lb, T ub)
	{
		this->rng_ = UniformRNG<T>(lb, ub);

		std::cout << rng_.min()<< " ";
		std::cout << rng_.max() << std::endl;
		return *this;
	}
	UniqueIntGenerator & length(size_t len)
	{
		this->len = len;
		return *this;
	}
	void clear()
	{
		storage.clear();
		seq.clear();
	}
	T min()
	{
		return rng_.min();
	}
	T max()
	{
		return rng_.max();
	}
};

} /* namespace rng */

#endif /* RANDOM_UNIQUEINTGENERATOR_H_ */
