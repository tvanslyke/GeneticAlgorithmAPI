/*
 * BinarySearcher.h
 *
 *  Created on: Feb 10, 2017
 *      Author: tim
 */

#ifndef UTILITIES_BINARYSEARCHER_H_
#define UTILITIES_BINARYSEARCHER_H_

template <typename T>
class BinarySearcher {
private:
public:
	BinarySearcher();
	virtual ~BinarySearcher();

	/**
	 * Binary search that returns a valid position only when an exact match is found;
	 */
	template <typename It>
	static It searchExact(T value, It begin, It end)
	{
		const It npos = end;
		It mid;
		while(begin < end)
		{
			mid = begin + (end - begin) / 2;
			if(*mid > value)
			{
				end = mid;
			}
			else if(*mid < value)
			{
				begin = mid;
			}
			else
			{
				return mid;
			}
		}
		return npos;
	}
};

#endif /* UTILITIES_BINARYSEARCHER_H_ */
