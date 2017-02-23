/*
 * GenericKey.h
 *
 *  Created on: Feb 13, 2017
 *      Author: tim
 */

#ifndef UTILITIES_GENERICHASHING_GENERICWEAKKEY_H_
#define UTILITIES_GENERICHASHING_GENERICWEAKKEY_H_
#include <boost/functional/hash.hpp>
#include <stack>
class GenericWeakKey {
protected:
	void * mem_;
	const size_t nbytes_;
	const size_t hashcode_;
	template <typename T, typename ... Types>
	static void buildGenericKeyParams(size_t & hashcode, size_t & totalbytes, std::stack<std::pair<size_t, void *>> & pending, T & arg, Types & ... args)
	{
		totalbytes += sizeof(T);
		boost::hash_combine(hashcode, arg);
		pending.push(std::pair<T, void*>(sizeof(T), (void *)(&arg)));
		buildGenericKeyParams(hashcode, totalbytes, pending, args...);
	}
	template <typename T>
	static void buildGenericKeyParams(size_t & hashcode, size_t & totalbytes, std::stack<std::pair<size_t, void *>> & pending, T & arg)
	{
		totalbytes += sizeof(T);
		boost::hash_combine(hashcode, arg);
		pending.push(std::pair<T, void*>(sizeof(T), (void *)(&arg)));
	}
	GenericWeakKey(size_t & bytecount, size_t & hashcode, std::stack<std::pair<size_t, void*>> & pending);
	GenericWeakKey(const GenericWeakKey & other);
	GenericWeakKey(GenericWeakKey && other);
public:

	virtual ~GenericWeakKey();
	template <typename ... Types>
	static GenericWeakKey makeGenericKey(Types ... args)
	{
		std::stack<std::pair<size_t, void *>> pending = std::stack<std::pair<size_t, void *>>();
		size_t bytecount = 0;
		size_t hashcode = 0;
		buildGenericKeyParams<Types...>(hashcode, bytecount, pending, args...);
		return GenericWeakKey(bytecount, hashcode, pending);
	}
	size_t getHash() const;
	bool operator==(GenericWeakKey && other) const;
	bool operator==(const GenericWeakKey & other) const;
};
namespace std
{
	template <>
	struct hash<GenericWeakKey>
	{
		size_t operator()(const GenericWeakKey & gwk) const
		{
			return gwk.getHash();
		}
		size_t operator()(GenericWeakKey && gwk) const
		{
			return gwk.getHash();
		}
	};
}

#endif /* UTILITIES_GENERICHASHING_GENERICWEAKKEY_H_ */
