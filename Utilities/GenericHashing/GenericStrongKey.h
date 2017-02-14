/*
 * GenericStrongKey.h
 *
 *  Created on: Feb 11, 2017
 *      Author: tim
 */

#ifndef UTILITIES_GENERICHASHING_GENERICSTRONGKEY_H_
#define UTILITIES_GENERICHASHING_GENERICSTRONGKEY_H_
#include <typeinfo>
#include <vector>
#include <cstdlib>
#include <boost/functional/hash.hpp>
#include "GenericWeakKey.h"
class GenericStrongKey: public GenericWeakKey {
protected:
	const std::vector<std::type_index> types_;

	template <typename T, typename ... Types>
	static void buildGenericKeyParams(size_t & hashcode,
									  size_t & totalbytes,
									  std::stack<std::pair<size_t, void *>> & pending,
									  std::vector<std::type_index> & types,
									  T & arg, Types & ... args)
	{
		totalbytes += sizeof(T);
		types.push_back(std::type_index(typeid(T)));
		boost::hash_combine(hashcode, arg);
		pending.push(std::pair<T, void*>(sizeof(T), (void *)(&arg)));
		buildGenericKeyParams(hashcode, totalbytes, pending, types, args...);
	}

	template <typename T>
	static void buildGenericKeyParams(size_t & hashcode,
									  size_t & totalbytes,
									  std::stack<std::pair<size_t, void *>> & pending,
									  std::vector<std::type_index> & types,
									  T & arg)
	{
		types.push_back(std::type_index(typeid(T)));
		totalbytes += sizeof(T);
		boost::hash_combine(hashcode, arg);
		boost::hash_combine(hashcode, types.back());
		pending.push(std::pair<T, void*>(sizeof(T), (void *)(&arg)));
	}

	GenericStrongKey(size_t & hashcode,
			  size_t & totalbytes,
			  std::stack<std::pair<size_t, void *>> & pending,
			  std::vector<std::type_index> & types);
public:

	template <typename ... Types>
	static GenericStrongKey makeGenericKey(Types ... args)
	{
		std::vector<std::type_index> types = std::vector<std::type_index>();
		types.reserve(sizeof...(Types));
		std::stack<std::pair<size_t, void *>> pending;
		size_t bytecount = 0;
		size_t hashcode = 0;
		buildGenericKeyParams<Types...>(hashcode, bytecount, pending, types, args...);
		return GenericStrongKey(bytecount, hashcode, pending, types);
	}
	virtual ~GenericStrongKey();
	bool operator==(const GenericStrongKey & other) const;
	bool operator==(GenericStrongKey && other) const;
	size_t getHash() const;
};

namespace std
{
	template <>
	struct hash<GenericStrongKey>
	{
		size_t operator()(const GenericStrongKey & gsk) const
		{
			return gsk.getHash();
		}
		size_t operator()(GenericStrongKey && gsk) const
		{
			return gsk.getHash();
		}
	};
}

#endif /* UTILITIES_GENERICHASHING_GENERICSTRONGKEY_H_ */
