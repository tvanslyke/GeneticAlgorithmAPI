/*
 * GenericHashing.h
 *
 *  Created on: Feb 11, 2017
 *      Author: tim
 */

#ifndef UTILITIES_GENERICHASHING_H_
#define UTILITIES_GENERICHASHING_H_
#include <boost/functional/hash.hpp>
#include <typeinfo>

#include "GenericStrongKey.h"


class GenericHashing {
private:
	static size_t seed;
public:
	template <typename T, typename ... Types>
	static size_t auto_hash(T arg, const Types & ... args)
	{
		boost::hash_combine<T>(seed, arg);
		return weak_hash<Types...>(args...);
	}

	template <typename T>
	static size_t auto_hash(T arg)
	{
		boost::hash_combine<T>(seed, arg);
		size_t seed_cpy = seed;
		seed = 0;
		return seed_cpy;
	}
	template <typename ... Types>
	static GenericWeakKey weak_hash(Types ... args)
	{
		return GenericWeakKey::makeGenericKey<Types...>(args...);
	}
	template <typename ... Types>
	static GenericStrongKey strong_hash(Types ... args)
	{
		return GenericStrongKey::makeGenericKey<Types...>(args...);
	}



};

#endif /* UTILITIES_GENERICHASHING_H_ */
