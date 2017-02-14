/*
 * Endian.h
 *
 *  Created on: Feb 12, 2017
 *      Author: tim
 */

#ifndef UTILITIES_ENDIAN_H_
#define UTILITIES_ENDIAN_H_

#include <algorithm>
enum
{
	LITTLE,
	BIG
} Endianness;

class Endian {

protected:
	Endian();

	template <typename T>
	static void reverseBytes(T & value)
	{
		size_t nbytes = sizeof(T);
		if(nbytes == 1)
			return;
		char * bytes = (char*)&value;
		std::reverse(bytes, bytes + nbytes);
	}
public:
	virtual ~Endian();
	template <typename T>
	static void newByteOrder(T & value)
	{
		reverseBytes<T>(value);
	}
	template <typename T>
	static T getNewByteOrder(T value)
	{
		reverseBytes<T>(value);
		return value;
	}

};

#endif /* UTILITIES_ENDIAN_H_ */
