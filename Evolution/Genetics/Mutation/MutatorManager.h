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
#include <memory>
/**
 * A factory/manager class for doling out pointers to objects derived from class Mutator.
 *
 * @author Timothy Van Slyke
 */
class MutatorManager: public SharedUtilityManager<MutatorKey, Mutator, MutatorKey::Hash> {
public:
	using SUM = SharedUtilityManager<MutatorKey, Mutator, MutatorKey::Hash>;
	using SUM::SharedUtilityManager;

	/**
	 * Get a shared_ptr<Mutator> pointing to a mutator of type M with the requested
	 * parameters.
	 * @param args - Arguments to pass to the constructor for mutators of type M.
	 * @return shared_ptr<Mutator> pointing to the mutator.
	 */
	template <typename M, typename... T>
	std::shared_ptr<Mutator> getMutator(T && ... args)
	{
		MutatorKey key = MutatorKey::makeMutatorKey<M, T...>(std::forward<T>(args)...);
		if(this->has(key))
		{
			return this->utilities_[key].lock();
		}
		else
		{
			auto value = std::shared_ptr<Mutator>(new M(args...), makeDeleter());
			typename decltype(utilities_)::iterator kvp = utilities_.begin();
			std::tie(kvp, std::ignore) = utilities_.emplace(key, value);
			std::get_deleter<SUM::Deleter>(value)->setKey(&(kvp->first));
			return value;
		}
	}
};

#endif /* MUTATORMANAGER_H_ */
