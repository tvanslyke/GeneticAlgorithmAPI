/*
 * vector_utils.h
 *
 *  Created on: Jan 14, 2017
 *      Author: tim
 */

#ifndef MISC_VECTOR_UTILS_H_
#define MISC_VECTOR_UTILS_H_

#include <vector>
#include <cstdlib>

using std::vector;





template <typename T>
T v_min(vector<T> vec)
{
	size_t len = vec.size();
	T minm = 0;
	if(len)
	{
		minm = vec[0];
		for(size_t i = 1; i < len; ++i)
		{
			if(vec[i] < minm)
			{
				minm = vec[i];
			}
		}
	}
	return minm;
}

template <typename T>
T v_max(vector<T> vec)
{
	size_t len = vec.size();
	T maxm = 0;
	if(len)
	{
		maxm = vec[0];
		for(size_t i = 1; i < len; ++i)
		{
			if(vec[i] > maxm)
			{
				maxm = vec[i];
			}
		}
	}
	return maxm;
}


#endif /* MISC_VECTOR_UTILS_H_ */
