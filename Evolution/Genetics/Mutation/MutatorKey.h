/*
 * MutatorKey.h
 *
 *  Created on: Feb 4, 2017
 *      Author: tim
 */

#ifndef MUTATION_MUTATORKEY_H_
#define MUTATION_MUTATORKEY_H_
#include <cstdlib>
#include <typeinfo>
#include "Mutators/Mutator.h"
#include <boost/functional/hash.hpp>
#include "../../../Utilities/GenericHashing/GenericWeakKey.h"

class MutatorKey: public GenericWeakKey {
protected:

	MutatorKey(size_t & bytecount, size_t & hashcode, std::stack<std::pair<size_t, void*>> & pending, const size_t & id);
public:
	template <typename MutatorType, typename ... Types>
	static MutatorKey makeMutatorKey(Types ... args)
	{
		size_t bytecount = 0;
		size_t hashcode = 0;
		std::stack<std::pair<size_t, void*>>  pending = std::stack<std::pair<size_t, void*>>();
		GenericWeakKey::buildGenericKeyParams<Types...>(hashcode, bytecount, pending, args...);
		return MutatorKey(bytecount, hashcode, pending, MutatorType::mutatorID);
	}
	virtual ~MutatorKey();

	bool operator==(MutatorKey && other) const;
	bool operator==(const MutatorKey & other) const;

	const size_t id_;
};

namespace std
{
	template <>
	struct hash<MutatorKey>
	{
		size_t operator()(const MutatorKey & key) const
		{
			return key.getHash();
		}
		size_t operator()(MutatorKey && key) const
		{
			return key.getHash();
		}
	};
}



#endif /* MUTATION_MUTATORKEY_H_ */
