/*
 * SamplingPolicy.h
 *
 *  Created on: Feb 14, 2017
 *      Author: tim
 */

#ifndef EVOLUTION_GENETICS_SAMPLING_SAMPLINGPOLICY_H_
#define EVOLUTION_GENETICS_SAMPLING_SAMPLINGPOLICY_H_
#include "../../Evolvable.h"
#include "../../../Random/RandomNumbers.h"
#include <iterator>
#include <type_traits>
//https://en.wikipedia.org/wiki/Alias_method


template <typename  PolicyType>
class SamplingPolicy {
	//static_assert(std::is_same<U, T>::value, "");
private:

public:
	SamplingPolicy()
	{
	}
	virtual ~SamplingPolicy()
	{

	}
	template <typename It>
	typename std::enable_if<std::is_same<typename It::value_type, std::shared_ptr<Evolvable>>::value, void>::type
	buildSample(It begin, It end)
	{
		(*static_cast<PolicyType*>(this)).
				buildSample<It>(
						begin,
						end,
						typename std::iterator_traits<It>::iterator_category());
	}
	template <typename It>
	typename std::enable_if<std::is_same<typename It::value_type, std::shared_ptr<Evolvable>>::value, void>::type
	sample(It begin, It end, It & destBegin, It & destEnd)
	{
		(*static_cast<PolicyType*>(this)).buildSample(begin, end, destBegin, destEnd, typename std::iterator_traits<It>::iterator_category());
	}
	std::shared_ptr<Evolvable> next()
	{
		return (*static_cast<PolicyType*>(this)).next();
	}
	void clear()
	{
		(*static_cast<PolicyType*>(this)).clear();
	}
};

#endif /* EVOLUTION_GENETICS_SAMPLING_SAMPLINGPOLICY_H_ */
