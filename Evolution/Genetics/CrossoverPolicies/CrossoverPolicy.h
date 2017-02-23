/*
 * CrossoverPolicy.h
 *
 *  Created on: Feb 13, 2017
 *      Author: tim
 */

#ifndef GENETICSTRUCTURES_CROSOVERPOLICIES_CROSSOVERPOLICY_H_
#define GENETICSTRUCTURES_CROSOVERPOLICIES_CROSSOVERPOLICY_H_


#include <iterator>
#include <iostream>
template <class PolicyType>
class CrossoverPolicy {
private:

public:
	//typedef It iterator_type;
	CrossoverPolicy()
	{

	}

	virtual ~CrossoverPolicy()
	{

	}
	template <typename It>
	void operator()(It start1, It end1, It start2)
	{
		(*(static_cast<PolicyType*>(this)))(start1, end1, start2, typename std::iterator_traits<It>::iterator_category());
	}
	template <typename It>
	void operator()(It start1, It end1, It start2, size_t count)
	{
		(*(static_cast<PolicyType*>(this)))(start1, end1, start2, count, typename std::iterator_traits<It>::iterator_category());
	}
	template <typename It>
	void operator()(It start1, It end1, It start2, It dest)
	{
		(*(static_cast<PolicyType*>(this)))(start1, end1, start2, dest, typename std::iterator_traits<It>::iterator_category());
	}
	template <typename It>
	void operator()(It start1, It end1, It start2, It dest, size_t count)
	{
		(*(static_cast<PolicyType*>(this)))(start1, end1, start2, dest, typename std::iterator_traits<It>::iterator_category());
	}
	template <typename ... ArgTypes>
	void operator()(ArgTypes... args)
	{
		(*(static_cast<PolicyType*>(this)))(args...);
	}
};



#endif /* GENETICSTRUCTURES_CROSOVERPOLICIES_CROSSOVERPOLICY_H_ */
