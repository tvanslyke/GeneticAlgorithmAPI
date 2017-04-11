/*
 * MutatorKey.h
 *
 *  Created on: Feb 4, 2017
 *      Author: tim
 */

#ifndef MUTATION_MUTATORKEY_H_
#define MUTATION_MUTATORKEY_H_
#include "Mutators/Mutator.h"
#include <boost/functional/hash.hpp>
#include "../../../Utilities/GenericWeakKey.h"
#include "../../../Utilities/TypeNum.h"

/**
 * Key used for looking up mutators in a hashtable.
 * Derives from GenericWeaKey to delay calling the constructor.
 *
 * @author Timothy Van Slyke
 */
class MutatorKey: public GenericWeakKey {
protected:
	/**
	 * Only constructor is private
	 * @param id - Unique number assigned to the requested mutator type.
	 */
	MutatorKey(size_t id);
public:
	/**
	 * Hash function to use when hashing MutatorKey objects.
	 */
	class Hash
	{
	public:
		/**
		 * Hash a MutatorKey.
		 * @param key - the key to hash.
		 * @return the hash of the key.
		 */
		size_t operator()(const MutatorKey & key) const;
	};
	/**
	 * Factory method for creating MutatorKeys.
	 * @param args - Arguments to pass to the constructor for mutator type M.
	 * @return the MutatorKey instance.
	 */
	template <typename M, typename ... T>
	static MutatorKey makeMutatorKey(const T & ... args)
	{
		// initialize the key.
		auto mk = MutatorKey(TypeNum::getNum<M>());
		// finalize the state of the MutatorKey
		mk.buildGenericKey(0, args ...);
		return mk;
	}
	/** Default destructor. */
	virtual ~MutatorKey() = default;

	/**
	 * Equality testing for hashtable lookup.
	 * @param other - the other MutatorKey.
	 * @return true if keys are equivalent.
	 */
	bool operator==(const MutatorKey & other) const;

	/**
	 * Unique number automatically assigned to mutators of type M.
	 * (different for each mutator type)
	 */
	const size_t id_;
};



#endif /* MUTATION_MUTATORKEY_H_ */
