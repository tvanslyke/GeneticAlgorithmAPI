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
#include <iostream>
#include <tuple>


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



template <typename K, typename V, class H = std::hash<K>>
class SharedUtilityManager
{
protected:
	/** Deleter for shared_ptrs created by SharedUtilityManager<K, V, H> */
	class SharedUtilityDeleter
	{
		using HashTable = std::unordered_map<K, std::weak_ptr<V>, H>;
		/**
		 * Reference to the unordered_map in the SharedUtilityManager<K, V, H> instance
		 * from which the shared_ptr holding this Deleter was created.
		 */
		HashTable & hashTable_;
		/**
		 * The C++11 standard guarantees the validity of the key pointer for as long
		 * as the key is not erased from the table.  This class handles all deletion in the
		 * associated SharedUtilityManager<K, V, H> instance, so this key will remain valid for
		 * the lifetime of the Deleter instance.
		 */
		const K * key_;
	public:
		/**
		 * Construct the deleter from a hashtable reference.
		 */
		SharedUtilityDeleter(HashTable & htable): hashTable_(htable), key_(nullptr){}

		/**
		 * Delete the internal pointer within the shared_ptr instance and remove the corresponding
		 * weak_ptr from the unordered_map.
		 * @param value
		 */
		void operator()(V * value)
		{
			if(hashTable_.count(*key_) > 0)
			{
				hashTable_.erase(*key_);
			}
			delete value;
		}
		/**
		 * Set the key for the deleter.
		 * In order to hold a pointer to the key (we're assuming a pointer is lighter than an instance),
		 * we need to provide the deleter to the shared_ptr constructor first, then insert a weak_ptr into
		 * the hashtable, and THEN provide a pointer to the stored key to the deleter.  We would otherwise
		 * construct the deleter with the pointer already provided.
		 * @param key - the pointer to the key stored in the hashtable.
		 */
		void setKey(const K * key)
		{
			key_ = key;
		}
	};
	using Deleter = SharedUtilityDeleter;
	/**
	 * Hash table holding weak pointers to unique V instances.  The structure of K
	 * is left to the user, however this class is intended for key-value pairs such that the a
	 * mapping (in the mathematical sense) of keys to values is an injective/one-to-one relationship.
	 */
	std::unordered_map<K, std::weak_ptr<V>, H> utilities_;


	/**
	 * When a new instance of V is created in the hash table, a deleter is produced.
	 * This deleter is called when the last owner of a shared pointer to the V instance
	 * ceases to own the instance.  This deleter needs to be created only once, so long as the weak
	 * pointer is stored in the hash table is created from the FIRST shared pointer created for the
	 * particular instance.  All subsequent shared pointers that are created by calling weak_ptr::lock()
	 * will also hold this deleter.
	 */
	Deleter makeDeleter()
	{
		return Deleter(utilities_);
	}
public:

	/**
	 * Constructs a new SharedUtilityManager.
	 */
	SharedUtilityManager()
	{
		utilities_ = std::unordered_map<K, std::weak_ptr<V>, H>();
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
	bool has(const K & key) const
	{
		return utilities_.count(key) > 0;
	}

	/**
	 * Given a key of type K, this method will produce an object of
	 * type V that corresponds to the key.  In order for this method to
	 * work, V objects must be constructible from K objects.
	 */
	std::shared_ptr<V> get(const K & key)
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
			std::shared_ptr<V> value = std::shared_ptr<V>(new V(key), makeDeleter());
			typename std::unordered_map<K, std::weak_ptr<V>, H>::iterator kvp = utilities_.begin();
			std::tie(kvp, std::ignore) = utilities_.emplace(key, value);
			std::get_deleter(value)->setKey(&(kvp->first));
			return value;
		}
	}

	/**
	 * Given a finite sequence of arguments of arbitrary type, this method
	 * will produce an object of type V corresponding to the provided
	 * arguments.  Both K and V objects MUST be constructible
	 * from the provided arguments.  This method does NOT require that V
	 * objects be constructible from K objects, only that they both be
	 * constructible from the same parameter list.  That way, it isn't 100%
	 * necessary to write a V constructor that accepts a K.
	 */
	template <typename... T>
	std::shared_ptr<V> get(const T & ... args)
	{
		// construct a key from the parameter list.
		K key = K(args...);
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
			std::shared_ptr<V> value = std::shared_ptr<V>(new V(args...), makeDeleter());
			typename std::unordered_map<K, std::weak_ptr<V>, H>::iterator kvp = utilities_.begin();
			std::tie(kvp, std::ignore) = utilities_.emplace(key, value);
			std::get_deleter(value)->setKey(&(kvp->first));
			return value;
		}
	}
};




#endif /* UTILITIES_SHAREDUTILITYMANAGER_H_ */
