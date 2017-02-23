/*
 * SharedUtilityManager.h
 *
 *  Created on: Feb 9, 2017
 *      Author: tim
 */

#ifndef UTILITIES_SHAREDUTILITYMANAGER_H_
#define UTILITIES_SHAREDUTILITYMANAGER_H_

#include <unordered_map>
#include <memory>
#include <functional>
#include "GenericHashing/GenericHashing.h"
#include <iostream>


template <typename KeyType, typename ValueType>
class SharedUtilityDeleter
{
	using HashTable = std::unordered_map<KeyType, std::weak_ptr<ValueType>>;
	HashTable & hashTable_;
	const KeyType key_;
public:
	SharedUtilityDeleter(KeyType key, HashTable & htable): hashTable_(htable), key_(key)
	{
	}
	~SharedUtilityDeleter()
	{

	}
	void operator()(ValueType  * value)
	{
		assert(hashTable_.count(key_) > 0);
		hashTable_.erase(key_);
		delete value;
	}
};
/**
 * A class for managing instances of a class such that no redundant instances of that
 * class are allowed to exist (so long as instantiation occurs only through this interface).
 *
 * SharedUtilityManager doles out shared pointers to objects contained within an internal hash table
 * whenever some external entity makes a request through the get() method.  Instantiation
 * only occurs when an object is requested that is not contained within the hash table.
 *
 * This class doubles as a factory and an object lifetime manager (although in reality the
 * lifetime management is really done by shared pointers).  It should be used primarily
 * when large-scale shared ownership of a single type of resource is expected.
 */


template <typename KeyType, typename ValueType>
class SharedUtilityManager
{
protected:

	/**
	 * Hash table holding weak pointers to unique ValueType instances.  The structure of KeyType
	 * is left to the user, however this class is intended for key-value pairs such that the a
	 * mapping (in the mathematical sense) of keys to values is an injective/one-to-one relationship.
	 */
	std::unordered_map<KeyType, std::weak_ptr<ValueType>> utilities_;


	/**
	 * When a new instance of ValueType is created in the hash table, a deleter is produced.
	 * This deleter is called when the last owner of a shared pointer to the ValueType instance
	 * ceases to own the instance.  This deleter needs to be created only once, so long as the weak
	 * pointer is stored in the hash table is created from the FIRST shared pointer created for the
	 * particular instance.  All subsequent shared pointers that are created by calling weak_ptr::lock()
	 * will also hold this deleter.
	 */
	SharedUtilityDeleter<KeyType, ValueType> makeDeleter(KeyType key)
	{
		return SharedUtilityDeleter<KeyType, ValueType>(key, utilities_);
	}
public:
	/**
	 * Constructs a new SharedUtilityManager.
	 */
	SharedUtilityManager()
	{
		utilities_ = std::unordered_map<KeyType, std::weak_ptr<ValueType>>();
	}
	~SharedUtilityManager()
	{
		for(auto & kvp:utilities_)
		{
			if(kvp.second.use_count() > 0)
			{
				std::cout << "[SharedUtilityManager::~SharedUtilityManager()] Warning!  Destruction occurring before all managed elements destroyed!" << std::endl;
			}
		}
	}

	/**
	 * Returns whether or not a certain key is currently mapped to an object
	 * in the hashtable.
	 *
	 * This method is intended for internal use (as syntactic sugar because
	 * if(this->has(key)) reads quite nicely) but is entirely benign as a
	 * public method.
	 */
	bool has(const KeyType & key) const
	{
		return utilities_.count(key) > 0;
	}

	/**
	 * Given a key of type KeyType, this method will produce an object of
	 * type ValueType that corresponds to the key.  In order for this method to
	 * work, ValueType objects must be constructible from KeyType objects.
	 */
	std::shared_ptr<ValueType> get(const KeyType & key)
	{

		if(this->has(key))
		{
			// If the key is in the hash table, then return a shared pointer from the
			// weak pointer in the hash table.
			return utilities_[key].lock();
		}
		else
		{
			/* If the key is not in the hash table, then create a shared_ptr with a deleter
			 * to ensure that the last shared_ptr to die erases the entry in the hash table.
			 * Create a weak_ptr from the shared_ptr and return the shared_ptr.
			 */
			std::shared_ptr<ValueType> value = std::shared_ptr<ValueType>(new ValueType(key), makeDeleter(key));
			//utilities_[key] = std::weak_ptr<ValueType>(value);
			utilities_.emplace(key, value);
			return value;
		}
	}

	/**
	 * Given a finite sequence of arguments of arbitrary type, this method
	 * will produce an object of type ValueType corresponding to the provided
	 * arguments.  Both KeyType and ValueType objects MUST be constructible
	 * from the provided arguments.  This method does NOT require that ValueType
	 * objects be constructible from KeyType objects, only that they both be
	 * constructible from the same parameter list.  That way, it isn't 100%
	 * necessary to write a ValueType constructor that accepts a KeyType.
	 */
	template <typename... Types>
	std::shared_ptr<ValueType> get(const Types & ... args)
	{
		// construct a key from the parameter list.
		KeyType key = KeyType(args...);
		if(this->has(key))
		{
			// If the key is in the hash table, then return a shared pointer from the
			// weak pointer in the hash table.
			return utilities_[key].lock();
		}
		else
		{
			/* If the key is not in the hash table, then create a shared_ptr with a deleter
			 * to ensure that the last shared_ptr to die erases the entry in the hash table.
			 * Create a weak_ptr from the shared_ptr and return the shared_ptr.
			 *
			 */
			std::shared_ptr<ValueType> value = std::shared_ptr<ValueType>(new ValueType(args...), makeDeleter(key));
			utilities_[key] = std::weak_ptr<ValueType>(value);
			//utilities_.emplace(key, value);
			return value;
		}
	}
};



template <typename ValueType>
class SharedUtilityManager<void, ValueType>
{
protected:

	/**
	 * Hash table holding weak pointers to unique ValueType instances.  The structure of KeyType
	 * is left to the user, however this class is intended for key-value pairs such that the a
	 * mapping (in the mathematical sense) of keys to values is an injective/one-to-one relationship.
	 */
	std::unordered_map<GenericWeakKey, std::weak_ptr<ValueType>> utilities_;


	/**
	 * When a new instance of ValueType is created in the hash table, a deleter is produced.
	 * This deleter is called when the last owner of a shared pointer to the ValueType instance
	 * ceases to own the instance.  This deleter needs to be created only once, so long as the weak
	 * pointer is stored in the hash table is created from the FIRST shared pointer created for the
	 * particular instance.  All subsequent shared pointers that are created by calling weak_ptr::lock()
	 * will also hold this deleter.
	 */
	SharedUtilityDeleter<GenericWeakKey, ValueType> makeDeleter(GenericWeakKey key)
	{
		return SharedUtilityDeleter<GenericWeakKey, ValueType>(key, utilities_);
	}
public:
	/**
	 * Constructs a new SharedUtilityManager.
	 */
	SharedUtilityManager()
	{
		utilities_ = std::unordered_map<GenericWeakKey, std::weak_ptr<ValueType>>();
	}
	/**
	 * Destructor.  No managed memory.
	 */
	virtual ~SharedUtilityManager()
	{
		for(auto & kvp:utilities_)
		{
			if(kvp.second.use_count() > 0)
			{
				std::cout << "[SharedUtilityManager::~SharedUtilityManager()] Warning!  Destruction occurring before all managed elements destroyed!" << std::endl;
			}
		}
	}
	/**
	 * Returns whether or not a certain key is currently mapped to an object
	 * in the hashtable.
	 *
	 * This method is intended for internal use (as syntactic sugar because
	 * if(this->has(key)) reads quite nicely) but is entirely benign as a
	 * public method.
	 */
	bool has(const GenericWeakKey & key) const
	{
		return utilities_.count(key) > 0;
	}



	/**
	 * Given a finite sequence of arguments of arbitrary type, this method
	 * will produce an object of type ValueType corresponding to the provided
	 * arguments.  Both KeyType and ValueType objects MUST be constructible
	 * from the provided arguments.  This method does NOT require that ValueType
	 * objects be constructible from KeyType objects, only that they both be
	 * constructible from the same parameter list.  That way, it isn't 100%
	 * necessary to write a ValueType constructor that accepts a KeyType.
	 */
	template <typename... Types>
	std::shared_ptr<ValueType> get(Types ... args)
	{
		// construct a key from the parameter list.
		GenericStrongKey key = GenericHashing::strong_hash<Types...>(args...);
		if(this->has(key))
		{
			// If the key is in the hash table, then return a shared pointer from the
			// weak pointer in the hash table.
			return utilities_[key].lock();
		}
		else
		{
			// If the key is not in the hash table, then create a shared_ptr with a deleter
			// to ensure that the last shared_ptr to die erases the entry in the hash table.
			// Create a weak_ptr from the shared_ptr and return the shared_ptr.
			std::shared_ptr<ValueType> value = std::shared_ptr<ValueType>(new ValueType(args...), makeDeleter(key));
			utilities_[key] = std::weak_ptr<ValueType>(value);
			return value;
		}
	}
	/**
	 * Given a finite sequence of arguments of arbitrary type, this method
	 * will produce an object of type ValueType corresponding to the provided
	 * arguments.  Both KeyType and ValueType objects MUST be constructible
	 * from the provided arguments.  This method does NOT require that ValueType
	 * objects be constructible from KeyType objects, only that they both be
	 * constructible from the same parameter list.  That way, it isn't 100%
	 * necessary to write a ValueType constructor that accepts a KeyType.
	 */
	template <typename... Types>
	std::shared_ptr<ValueType> getWeak(Types ... args)
	{
		// construct a key from the parameter list.
		GenericWeakKey key = GenericHashing::weak_hash<Types...>(args...);
		if(this->has(key))
		{
			// If the key is in the hash table, then return a shared pointer from the
			// weak pointer in the hash table.
			return utilities_[key].lock();
		}
		else
		{
			// If the key is not in the hash table, then create a shared_ptr with a deleter
			// to ensure that the last shared_ptr to die erases the entry in the hash table.
			// Create a weak_ptr from the shared_ptr and return the shared_ptr.
			std::shared_ptr<ValueType> value = std::shared_ptr<ValueType>(new ValueType(args...), makeDeleter(key));
			utilities_[key] = std::weak_ptr<ValueType>(value);
			return value;
		}
	}
};
#endif /* UTILITIES_SHAREDUTILITYMANAGER_H_ */
