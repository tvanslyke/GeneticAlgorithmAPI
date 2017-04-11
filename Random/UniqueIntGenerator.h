/*
 * UniqueIntGenerator.h
 *
 *  Created on: Feb 19, 2017
 *      Author: tim
 */

#ifndef RANDOM_UNIQUEINTGENERATOR_H_
#define RANDOM_UNIQUEINTGENERATOR_H_
#include "UniformRNG.h"
#include <set>
#include <vector>

#include <algorithm>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <limits>

namespace rng {

/**
 * Type used to indicate the type of sorting used when calling the sorted()
 * method of the UniqueIntGenerator class.
 */
enum SortingType
{
	DESCENDING = -1,
	NONE = 0,
	ASCENDING = 1
};
/**
 * A class for generating sequences of unique integers within a particular range.
 *
 * @author Timothy Van Slyke
 */
template <typename T>
class UniqueIntGenerator
{
private:

	/**
	 * Generator function to be used when generating an unsorted sequence of unique integers using
	 * the Fisher-Yates algorithm.
	 * @param rng - a reference to the instance's random number generator.
	 * @param storage - a reference to the instance's storage set.
	 * @param seq - a reference to the instance's storage vector.
	 * @return The next unique random integer.
	 */
	static T unsortedFisherYates(UniformRNG<T>& rng, std::set<T> & storage, std::vector<T> & seq)
	{
		auto num = seq.back();
		seq.pop_back();
		return num;
	}

	/**
	 * Generator function to be used when generating an unsorted sequence of unique integers using
	 * the brute force  algorithm.
	 * @param rng - a reference to the instance's random number generator.
	 * @param storage - a reference to the instance's storage set.
	 * @param seq - a reference to the instance's storage vector.
	 * @return The next unique random integer.
	 */
	static T unsortedNoFisherYates(UniformRNG<T>& rng, std::set<T> & storage, std::vector<T> & seq)
	{
		auto pair = storage.insert(rng());
		while(not pair.second)
		{
			pair = storage.insert(rng());
		}
		return *(pair.first);
	}

	/**
	 * Generator function to use when
	 * @param rng - a reference to the instance's random number generator.
	 * @param storage - a reference to the instance's storage set.
	 * @param seq - a reference to the instance's storage vector.
	 * @return The next unique random integer.
	 */
	static T sortedAscending(UniformRNG<T>& rng, std::set<T> & storage, std::vector<T> & seq)
	{
		auto num = *(storage.begin());
		storage.erase(storage.begin());
		return num;
	}

	/**
	 *
	 * @param rng - a reference to the instance's random number generator.
	 * @param storage - a reference to the instance's storage set.
	 * @param seq - a reference to the instance's storage vector.
	 * @return The next unique random integer.
	 */
	static T sortedDescending(UniformRNG<T>& rng, std::set<T> & storage, std::vector<T> & seq)
	{
		auto num = *(--(storage.end()));
		storage.erase(--(storage.end()));
		return num;
	}
	static_assert(std::is_integral<T>::value, "UniqueIntGenerator must be templated with an integral type.");
	/** The random number generator to use. */
	rng::UniformRNG<T> rng_;
	/** The current sorting type. */
	SortingType sorting;
	/** The number of elements to generate. */
	size_t len;
	/**
	 * A set of random numbers.
	 * Depending on the current sorting type, this may hold already-generated
	 * numbers (to avoid repetition), or it may contain a sequence of sorted random
	 * numbers to output.
	 */
	std::set<T> storage;

	/**
	 * A sequential vector of numbers used to store random numbers
	 */
	std::vector<T> seq;
	std::function<T (UniformRNG<T>&, std::set<T> &, std::vector<T> &)> gen;
	T num;
	/** Build a sequence of random numbers using  the fisher-yates algorithm. */
	void buildSeq()
	{
		auto diff = rng_.max() - rng_.min();
		seq.resize(diff);
		std::iota(seq.begin(), seq.end(), rng_.min());
		std::shuffle(seq.begin(), seq.end(), rng::BaseRNG::twister_);
		seq.resize(len);
	}

	/** Fill the storage set with a sorted sequence of random numbers. */
	void fillStorage()
	{
		storage.clear();

		// dont use fisher-yates if the rng number range is greater than the length
		if(rng_.max() - rng_.min() > 2 * len)
		{
			while(storage.size() < len)
			{
				storage.insert(rng_());
			}
		}
		// use fisher-yates if the rng number range is less than than the length
		else
		{
			buildSeq();
			storage.insert(seq.begin(), seq.end());
		}
	}
public:
	/**
	 * Construce
	 * @param lb - inclusive lower bound of the range of numbers to generate.
	 * @param ub - inclusive upper bound of the range of numbers to generate.
	 * @param len - the number of integers to generate.
	 */
	UniqueIntGenerator(T lb = std::numeric_limits<T>::min(),
					   T ub = std::numeric_limits<T>::max(),
					   size_t length = size_t()):
		rng_(lb, ub), storage(), sorting(NONE), seq()
	{
		len = length;
		gen = [this](UniformRNG<T>& rng, std::set<T> & storage, std::vector<T> & seq)->T
		{
			return T();
		};
		sorting = NONE;
	}
	/**
	 * Get the next random integer.
	 * @return The next random integer.
	 */
	T operator()()
	{
		return gen(rng_, storage, seq);
	}

	/**
	 * Lock the internal state of the UniqueIntGenerator and set the internal generator function.
	 * Call this method after calls to sorted(), limits(), and/or length()/count()/size().
	 */
	void lock()
	{
		// ensure the range of valid numbers can accomodate the number of requested numbers.
		if((rng_.max() - rng_.min()) < len)
		{
			throw std::runtime_error("[UniqueIntGenerator] Requested " +
					std::to_string(len) +
					" unique integers from a range [" + std::to_string(rng_.min()) + ", " + std::to_string(rng_.max()) + "] containing only " +
					std::to_string(rng_.max() - rng_.min()) + " integers.");
		}
		// unsorted sequence of unique integers
		else if(sorting == NONE)
		{
			// dont use Fisher-Yates if the range of valid numbers is
			// twice the number of integers to generate.
			if((2 * len) < size_t(rng_.max() - rng_.min()))
			{
				clear();
				gen = UniqueIntGenerator<T>::unsortedNoFisherYates;
			}
			else
			{
				buildSeq();
				gen = UniqueIntGenerator<T>::unsortedFisherYates;
			}
		}
		// sorted sequence of unique integers.
		else
		{
			// fill storage with the sorted sequence.
			fillStorage();
			if(sorting == ASCENDING)
			{
				gen = UniqueIntGenerator<T>::sortedAscending;
			}
			else
			{
				gen = UniqueIntGenerator<T>::sortedDescending;
			}
		}
	}

	/**
	 * Set the generated sequence of unique integers to be unsorted.
	 * @return a reference to this instance (named parameter idiom chaining).
	 */
	UniqueIntGenerator<T> & unsorted()
	{
		return sorted(NONE);
	}

	/**
	 * Set the generated sequence of unique integers to be sorted with the
	 * specified SortingType (ASCENDING, NONE, or DESCENDING).
	 * @param sorting - The type of sorting to use.
	 * @return a reference to this instance (named parameter idiom chaining).
	 */
	UniqueIntGenerator<T> & sorted(SortingType sorting = ASCENDING)
	{
		this->sorting = sorting;
		return *this;
	}

	/**
	 *
	 * @param lb - inclusive lower bound of the range of numbers to generate.
	 * @param ub - inclusive upper bound of the range of numbers to generate.
	 * @return a reference to this instance (named parameter idiom chaining).
	 */
	UniqueIntGenerator<T> & limits(T lb, T ub)
	{
		this->rng_.setBounds(lb, ub);
		return *this;
	}
	/**
	 * Set the number of integers that will be generated.
	 * @param len - the number of integers to generate.
	 * @return a reference to this instance (named parameter idiom chaining).
	 */
	UniqueIntGenerator<T> & length(size_t len)
	{
		this->len = len;
		return *this;
	}
	/**
	 * Set the number of integers that will be generated.
	 * @param len - the number of integers to generate.
	 * @return a reference to this instance (named parameter idiom chaining).
	 */
	UniqueIntGenerator<T> & size(size_t len)
	{
		this->len = len;
		return *this;
	}
	/**
	 * Set the number of integers that will be generated.
	 * @param len - the number of integers to generate.
	 * @return a reference to this instance (named parameter idiom chaining).
	 */
	UniqueIntGenerator<T> & count(size_t len)
	{
		this->len = len;
		return *this;
	}
	/**
	 * Clear the internal storage set and vector.
	 */
	void clear()
	{
		storage.clear();
		seq.clear();
	}
	/**
	 * Get the lowest possible number that cab be generated.
	 * @return Lowest possible number that can be generated.
	 */
	T min()
	{
		return rng_.min();
	}
	/**
	 * Get the highest possible number that cab be generated.
	 * @return Highest possible number that can be generated.
	 */
	T max()
	{
		return rng_.max();
	}
};

} /* namespace rng */

#endif /* RANDOM_UNIQUEINTGENERATOR_H_ */
