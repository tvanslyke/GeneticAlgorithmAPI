/*
 * MutatorManager.h
 *
 *  Created on: Feb 4, 2017
 *      Author: tim
 */

#ifndef MUTATORMANAGER_H_
#define MUTATORMANAGER_H_
#include "../../../Utilities/SharedUtilityManager.h"
#include "Mutators/Mutator.h"
#include "MutatorKey.h"

class MutatorManager: public SharedUtilityManager<MutatorKey, Mutator> {
public:
	using SharedUtilityManager<MutatorKey, Mutator>::SharedUtilityManager;

	template <typename MutatorType, typename... Types>
	std::shared_ptr<Mutator> getMutator(Types ... args)
	{
		MutatorKey key = MutatorKey::makeMutatorKey<MutatorType, Types...>(args...);
		if(this->has(key))
		{
			return this->utilities_[key].lock();
		}
		else
		{
			std::shared_ptr<Mutator> value = std::shared_ptr<MutatorType>(new MutatorType(args...), makeDeleter(key));
			this->utilities_[key] = std::weak_ptr<Mutator>(value);
			return value;
		}
	}
};

#endif /* MUTATORMANAGER_H_ */
