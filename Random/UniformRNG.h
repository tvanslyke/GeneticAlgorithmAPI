/*
 * RandomNumbers.h
 *
 *  Created on: Feb 5, 2017
 *      Author: tim
 */

#ifndef RANDOMNUMBERS_H_
#define RANDOMNUMBERS_H_
#include <unordered_map>
#include <type_traits>
#include <boost/functional/hash.hpp>
#include <random>
#include "BaseRNG.h"
#include <memory>
#include <iostream>
#include <stdexcept>
#include "../Utilities/SharedUtilityManager.h"
#include "RandomDistributions.h"



/*namespace std
{
	template <typename T>
	struct hash<std::pair<T, T>>
	{
		size_t operator()(const std::pair<T, T> & nums) const
		{
			size_t seed = 0;
			boost::hash_combine(seed, nums.first);
			boost::hash_combine(seed, nums.second);
			return seed;
		}
		size_t operator()(std::pair<T, T> && nums) const
		{
			size_t seed = 0;
			boost::hash_combine(seed, nums.first);
			boost::hash_combine(seed, nums.second);
			return seed;
		}
	};
}*/

namespace rng{

/**
 * Generic uniform random number generator.  This declaration is not implemented,
 * but is instead specialized below depending on std::is_integral<T>::value.  All
 * integral types get a std::uniform_int_distribution while all floating point
 * types get a std::uniform_real_distribution.
 */
template<typename T, typename U = T>
class UniformRNG{};


// aliases to avoid the long names std::shared_ptr<std::uniform_int_distribution<T>>
// and std::shared_ptr<std::uniform_real_distribution<T>>.
template <typename T>
using IntDistRef = std::shared_ptr<std::uniform_int_distribution<T>>;
template <typename T>
using FloatDistRef = std::shared_ptr<std::uniform_real_distribution<T>>;


// these random number generators are defined by their lower and upper bounds,
// as well as their types.  The overload to std::hash allows us to store rngs
// that are currently in use.  This way we can simply have UniformRNG<T>s that
// need the same exact behavior, without duplicating the actual generators or
// distributions.




/**
 * Random number generator for integral types. Each template contains a hashtable
 * that keeps track of all instantiated "std::uniform_int_distribution"s, and only
 * constructs a new instance when there does not already exist one that satisfies
 * the needed requirements.
 */

template<typename T>
class UniformRNG<T, typename std::enable_if<std::is_integral<T>::value, T>::type>
{
private:
	using ParamType = typename std::uniform_int_distribution<T>::param_type;
	IntDistRef<T> dist_;
public:
	UniformRNG():UniformRNG<T>(T(0), T(0)){}

	/**
	 * Create a new UniformRNG for an integral type.
	 */
	UniformRNG(T lb, T ub)
	{
		assert(lb <=ub);
		dist_ = RandomDistributions<T>::getDist(lb, ub);
	}
	/**
	 * Create a new UniformRNG for an integral type from a std::pair.
	 */
	UniformRNG(std::pair<T, T> lims)
	{
		assert(lims.first <= lims.second);
		dist_ = RandomDistributions<T>::getDist(lims.first, lims.second);
	}

	~UniformRNG()
	{
	}
	/**
	 * Create a new random integer.  Identical to operator().
	 */
	T getRandomNumber()
	{
		return (*(this->dist_))(BaseRNG::twister_);
	}
	static void Reset()
	{
		//dist_manager_ = SharedUtilityManager<std::pair<T, T>, std::uniform_int_distribution<T>>();
	}
	/**
	 * Create a new random integer.  Identical to getRandomNumber().
	 */
	T operator()()
	{
		return (*(this->dist_))(BaseRNG::twister_);
	}
	UniformRNG<T> & operator=(const UniformRNG<T> & other)
	{
		this->dist_ = IntDistRef<T>(other.dist_);
		return *this;
	}

	T max()
	{
		return dist_->max();
	}
	T min()
	{
		return dist_->min();
	}
};



template<typename T>
class UniformRNG<T, typename std::enable_if<not (std::is_integral<T>::value), T>::type>
{
private:
	using ParamType = typename std::uniform_real_distribution<T>::param_type;
	std::pair<T, T> lims_;
	FloatDistRef<T> dist_;
	static void Init()
	{
		static bool initialized = false;
		if(not initialized)
		{
			initialized = true;
			Reset();
		}
	}

public:
	UniformRNG():UniformRNG<T>(T(0), T(0)){}

	/**
	 * Create a new UniformRNG for an integral type.
	 */
	UniformRNG(T lb, T ub)
	{
		assert(lb <=ub);
		dist_ = RandomDistributions<T>::getDist(lb, ub);
	}
	/**
	 * Create a new UniformRNG for an integral type from a std::pair.
	 */
	UniformRNG(std::pair<T, T> lims)
	{
		assert(lims.first <= lims.second);
		dist_ = RandomDistributions<T>::getDist(lims.first, lims.second);
	}

	~UniformRNG()
	{
	}
	/**
	 * Create a new random integer.  Identical to operator().
	 */
	T getRandomNumber()
	{
		return (*(this->dist_))(BaseRNG::twister_);
	}

	static void Reset()
	{
		//dist_manager_ = SharedUtilityManager<std::pair<T, T>, std::uniform_real_distribution<T>>();
	}
	/**
	 * Create a new random integer.  Identical to getRandomNumber().
	 */
	T operator()()
	{
		return (*(this->dist_))(BaseRNG::twister_);
	}

	T max()
	{
		return dist_->max();
	}
	T min()
	{
		return dist_->min();
	}
};
/*
template <typename T>
using IntDistManagerType = SharedUtilityManager<std::pair<T, T>, std::uniform_int_distribution<T>>;
template <typename T>
IntDistManagerType<T> UniformRNG<T, typename std::enable_if<std::is_integral<T>::value, T>::type>::dist_manager_ = IntDistManagerType<T>();
template <typename T>
using RealDistManagerType = SharedUtilityManager<std::pair<T, T>, std::uniform_real_distribution<T>>;
template <typename T>
RealDistManagerType<T> UniformRNG<T, typename std::enable_if<!std::is_integral<T>::value, T>::type>::dist_manager_ = RealDistManagerType<T>();
*/
}

#endif /* RANDOMNUMBERS_H_ */
