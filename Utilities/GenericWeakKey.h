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
#include <stdexcept>

/**
 * Class for providing a generic hash-table key from arbitrary argument lists.
 *
 * This class significantly slows down the speed of a hash-table lookup, so it should not
 * be used with the intention of obtaining optimal hashing speed.  This class's
 * intended use is to allow lookup of objects from only the argument list
 * of the constructor.  Therefore, GenericWeakKey should only be used when the
 * constructor for an object takes arguments that define it uniquely.
 *
 * The arguments passed to makeGenericKey() (static factory method) are type-erased
 * after construction of the key, so the keys are 'weak' (so to speak).
 */
class GenericWeakKey
{
protected:
	/** vector of bytes that represent the parameter pack. */
	std::vector<char> mem_;
	/** pre-calculated cumulative hash of the parameter pack. */
	size_t hashcode_;
	/**
	 * Recursive method that forwards it's arguments to boost::hash_combine and stores
	 * their type-erased values within mem_.
	 *
	 * @param totalbytes - cumulative count of the number of bytes needed to
	 *                     store the argument list.
	 * @param arg - the current argument.
	 * @param args - trailing arguments.
	 */
	template <typename T, typename ... U>
	void buildGenericKey(size_t totalbytes, const T & arg, const U & ... args)
	{
		// observe the bytes that this object consists of.
		// this reinterpret cast is safe (in a single threaded system) because we
		// are not modifying the state of the casted object; we are only observing.
		const char * memView = reinterpret_cast<const char *>(&arg);
		// hash this argument
		boost::hash_combine(hashcode_, arg);
		// recursively call on the next arg.
		buildGenericKey(totalbytes + sizeof(T), args...);
		// copy these bytes to the correct location within the vector
		std::copy(memView, memView + sizeof(T), mem_.begin() + totalbytes);
	}
	/**
	 * Base case of buildGenericKeyParams().  Sets the values of the class's hashcode and
	 * internal vector length.
	 * @param totalbytes - cumulative count of the number of bytes needed to
	 *                     store the argument list.
	 * @param arg - the final argument.
	 */
	template <typename T>
	void buildGenericKey(size_t totalbytes, const T & arg)
	{
		// observe the bytes that this object consists of.
		// this reinterpret cast is safe (in a single threaded system) because we
		// are not modifying the state of the casted object; we are only observing.
		const char * memView = reinterpret_cast<const char *>(&arg);
		// hash this argument, but do not forward because memView is holding a
		// pointer to the data making up 'arg'.
		boost::hash_combine(hashcode_, arg);
		// reserve the total memory needed to store all of the bytes.
		mem_.resize(totalbytes + sizeof(T));
		// copy these bytes to the correct location within the vector
		std::copy(memView, memView + sizeof(T), mem_.begin() + totalbytes);
	}
public:
	/** The Hash policy for a genericWeakKey. */
	class Hash
	{
	public:
		/**
		 *
		 * @param gwk - reference to the key to 'hash'.
		 * @return hashcode for the weak key.
		 */
		size_t operator()(const GenericWeakKey & gwk) const;
	};
	/** Default virtual destructor. */
	virtual ~GenericWeakKey() = default;

	/**
	 * Create a GenericWeakKey from the parameter pack.
	 * @param args - parameters to create the key from.
	 * @return the created key.
	 */
	template <typename ... U>
	static GenericWeakKey makeGenericKey(const U & ... args)
	{
		// default-construct the key.
		size_t bytecount = 0;
		auto key = GenericWeakKey();
		key.buildGenericKey<U...>(bytecount, std::forward<U>(args)...);
		return key;
	}
	/**
	 * Get the hash value of this argument list.
	 * @return the hash value of the argument list
	 */
	virtual size_t getHash() const;
	/**
	 * Equality between two GenericWeakKeys.  Checks byte-for-byte
	 * equivalence of the keys.
	 * @param other - the other key to check equality against.
	 * @return true if they are equal, false otherwise.
	 */
	bool operator==(const GenericWeakKey & other) const;
};


#endif /* UTILITIES_GENERICHASHING_GENERICWEAKKEY_H_ */
