/*
 * searching.h
 *
 *  Created on: Jan 13, 2017
 *      Author: tim
 */

#ifndef ALGORITHMS_SEARCHING_H_
#define ALGORITHMS_SEARCHING_H_


template <typename It, typename T>
It binary_search_asc(It first, It last, T val)
{
	It mid = first + ((last - first) / 2);
	while(last - first > 1)
	{
		if(*mid > val)
		{
			last = mid;
			mid -= (mid - first) / 2;
		}
		else
		{
			first = mid;
			mid += (last - mid) / 2;
		}
	}
	if(*first > val) return first;
	if(*mid > val)   return mid;
	else             return last;
}



#endif /* ALGORITHMS_SEARCHING_H_ */
