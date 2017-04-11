/*
 * MakeMutator.h
 *
 *  Created on: Apr 5, 2017
 *      Author: tim
 */

#ifndef EVOLUTION_GENETICS_MUTATION_MAKEMUTATOR_H_
#define EVOLUTION_GENETICS_MUTATION_MAKEMUTATOR_H_
#include "../Gene.h"
/**
 * Class for allowing the process of creating shared Mutator instances to be
 * more readable (hopefully).
 *
 * Uses the format of standard library functions like std::make_tuple.
 * @author Timothy Van Slyke
 */
template <typename M, typename ... T>
class MakeMutator
{
private:
	/** Shared pointer to Mutator. */
	std::shared_ptr<Mutator> mutator_;

public:
	/**
	 * Constructor that initializes an internal pointer to a mutator.
	 * @param args - Forwarding references to pass to Gene::makeMutator.
	 */
	MakeMutator(T && ... args): mutator_(Gene::makeMutator<M, T...>(std::forward<T>(args)...))
	{

	}
	/** Discourage lvalue instantiation of objects of this type */
	MakeMutator(const MakeMutator &) = delete;

	/** Cast to a shared_ptr<Mutator> */
	operator std::shared_ptr<Mutator>()
	{
		return mutator_;
	}
	/** Downcast the internal mutator and return. */
	operator M()
	{
		return static_cast<M>(*mutator_);
	}
};
template <typename M, typename ... T>
class MakeMutator<M, std::tuple<T...>>
{
private:
	/** Shared pointer to Mutator. */
	std::shared_ptr<Mutator> mutator_;
	/**
	 * Unpack a tuple into an parameter pack for Gene::makeMutator and store the
	 * result internally.
	 * @param args
	 * @param
	 */
	template <size_t ... I>
	void unpackTuple(const std::tuple<T...> & args, std::index_sequence<I...>)
	{
		mutator_ = Gene::makeMutator<M>(std::get<I>(args)...);
	}
public:
	/** Construct from a tuple of arguments to pass to Gene::makeMutator. */
	MakeMutator(const std::tuple<T...> & argTup)
	{
		unpackTuple(argTup, std::make_index_sequence<sizeof...(T)>{});
	}

	/** Discourage lvalue instantiation of objects of this type */
	MakeMutator(const MakeMutator &) = delete;

	/** Cast to a shared_ptr<Mutator> */
	operator std::shared_ptr<Mutator>()
	{
		return mutator_;
	}
	/** Downcast the internal mutator and return. */
	operator M()
	{
		return static_cast<M>(*mutator_);
	}
};
#endif /* EVOLUTION_GENETICS_MUTATION_MAKEMUTATOR_H_ */
