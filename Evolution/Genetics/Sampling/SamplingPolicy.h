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

/**
 * The SamplingPolicy family of classes are responsible for fitness-based selection in the scope of this API.
 * They can be extended by users to implement their own method of population sampling (although some are provided with the API).
 * SamplingPolicy usage can be seen in the Population implementation.
 *
 * NOTE:  This class uses static polymorphism (CRTP).  To implement a custom policy, your class
 * 		  definition should take this form:
 *
 * 		  class MyPolicy: public SamplingPolicy<MyPolicy>;
 */
template <typename  PolicyType>
class SamplingPolicy {
public:
	SamplingPolicy()
	{
	}
	virtual ~SamplingPolicy()
	{

	}
	/**
	 * Initializes internal state of the sampling policy to allow indefinite calls to SamplingPolicy::next().
	 * This method of sampling allows for flexibility when the size of the new sample can only be determined on the fly.
	 *
	 * @param begin - random access iterator to the beginning of the population.
	 * @param end - random access iterator to the end of the population.
	 */
	template <typename It>
	typename std::enable_if<std::is_base_of<Evolvable, typename It::value_type>::value, void>::type
	buildSample(It begin, It end)
	{
		(*static_cast<PolicyType*>(this)).
				buildSample<It>(begin, end, typename std::iterator_traits<It>::iterator_category());
	}
	/**
	 * Constructs a new sample from an existing population.
	 *
	 * @param begin 	- iterator to the beginning of the current population.
	 * @param end   	- iterator to the end of the current population.
	 * @param destBegin - iterator to the beginning of the new sample.
	 * @param destEnd	- iterator to the end of the new sample.
	 *
	 */
	template <typename It>
	typename std::enable_if<std::is_base_of<Evolvable, typename It::value_type>::value, void>::type
	sample(It begin, It end, It & destBegin, It & destEnd)
	{
		(*static_cast<PolicyType*>(this)).buildSample(begin, end, destBegin, destEnd);
	}
	/**
	 * Obtain the next element from the sample.
	 * @return a pointer to an Evolvable object in the current population.
	 */
	Evolvable * next()
	{
		return (*static_cast<PolicyType*>(this)).next();
	}
	/**
	 * Clear any containers within the SamplingPolicy. (not all implementations necessarily require this method)
	 * @return a pointer to an Evolvable object in the current population.
	 */
	void clear()
	{
		(*static_cast<PolicyType*>(this)).clear();
	}
};

#endif /* EVOLUTION_GENETICS_SAMPLING_SAMPLINGPOLICY_H_ */
