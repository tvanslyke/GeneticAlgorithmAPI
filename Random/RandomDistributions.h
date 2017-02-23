/*
 * RandomDistributionManager.h
 *
 *  Created on: Feb 20, 2017
 *      Author: tim
 */

#ifndef RANDOM_RANDOMDISTRIBUTIONMANAGER_H_
#define RANDOM_RANDOMDISTRIBUTIONMANAGER_H_
#include <random>
#include "../Utilities/SharedUtilityManager.h"
#include <type_traits>
namespace std
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
}
namespace rng {


template <typename T>
using IntDistRef = std::shared_ptr<std::uniform_int_distribution<T>>;
template <typename T>
using FloatDistRef = std::shared_ptr<std::uniform_real_distribution<T>>;

template <typename T, typename U = T>
class RandomDistributions;
template <typename T>
class RandomDistributions<T, typename std::enable_if<std::is_integral<T>::value, T>::type>{
private:
	static SharedUtilityManager<std::pair<T, T>, std::uniform_int_distribution<T>> dist_manager_;
	RandomDistributions();
public:
	static IntDistRef<T> getDist(const std::pair<T, T> & lims)
	{
		return dist_manager_.get(lims.first, lims.second);
	}
	static IntDistRef<T> getDist(const T & lb, const T & ub)
	{
		return dist_manager_.get(lb, ub);
	}
public:
};

template <typename T>
class RandomDistributions<T, typename std::enable_if<std::is_floating_point<T>::value, T>::type>{
private:
	static SharedUtilityManager<std::pair<T, T>, std::uniform_real_distribution<T>> dist_manager_;
	RandomDistributions();
public:
	static FloatDistRef<T> getDist(const std::pair<T, T> & lims)
	{
		return dist_manager_.get(lims.first, lims.second);
	}
	static FloatDistRef<T> getDist(const T & lb, const T & ub)
	{
		return dist_manager_.get(lb, ub);
	}
};
template <typename T>
SharedUtilityManager<std::pair<T, T>, std::uniform_int_distribution<T>>
RandomDistributions<T, typename std::enable_if<std::is_integral<T>::value, T>::type>::dist_manager_ =
		SharedUtilityManager<std::pair<T, T>, std::uniform_int_distribution<T>>();
template <typename T>
SharedUtilityManager<std::pair<T, T>, std::uniform_real_distribution<T>>
RandomDistributions<T, typename std::enable_if<std::is_floating_point<T>::value, T>::type>::dist_manager_ =
		SharedUtilityManager<std::pair<T, T>, std::uniform_real_distribution<T>>();

} /* namespace rng */

#endif /* RANDOM_RANDOMDISTRIBUTIONMANAGER_H_ */
