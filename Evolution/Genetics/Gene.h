/*
 * Gene.h
 *
 *  Created on: Feb 3, 2017
 *      Author: tim
 */

#ifndef GENE_H_
#define GENE_H_
#include <boost/any.hpp>
#include <functional>
#include <boost/optional.hpp>
#include <string>
#include <iostream>
#include <memory>
#include "Mutation/MutatorManager.h"


/** Forward declaration. */
template <class, class, class ...>
class MakeGene;

/**
 * Gene objects encapsulate the lowest level mutatable (in the genetic sense) object contained
 * within an implementation of the Evolvable interface.  Genes contain a mutator that mutate
 * their encapsulated data.
 * Mutators are provided by the API, but can be extended by users through inheritance and dynamic
 * polymorphism.
 *
 * Genes are the building block of Chromosome objects, from which any Evolvable implementation
 * must be constructible.
 *
 * @author Timothy Van Slyke
 */
class Gene {
private:
	/** Factory/manager for mutators. */
	static MutatorManager mutatorMaker_;
	/**
	 * Type-erased data to be mutated.
	 * Type-erasure is used to allow uniform storage of Gene instances in containers.
	 */
	boost::any data_;
	std::shared_ptr<Mutator> mutator_;



public:
	/** Default ctor. */
	Gene() = default;
	/** Construct from an existing mutator. */
	Gene(const std::shared_ptr<Mutator> & mutator);
	/** Construct from an existing mutator and a boost::any instance. */
	Gene(const std::shared_ptr<Mutator> & mutator, const boost::any & data);

	/** Construct from a MakeGene instance. */
	template <typename ... T>
	Gene(const MakeGene<T...> & makeGene)
	{
		data_ = makeGene.geneTemp_.data_;
		mutator_ = makeGene.geneTemp_.mutator_;
	}


	/**
	 * Copy assignment from a MakeGene instance.
	 * @param makeGene - Temporary object storing an internal Gene.
	 * @return
	 */
	template <typename ... T>
	Gene & operator=(const MakeGene<T...> & makeGene)
	{
		data_ = makeGene.geneTemp_.data_;
		mutator_ = makeGene.geneTemp_.mutator_;
		return *this;
	}
	/**
	 * Invokes mutator to mutate the internally stored data.
	 */
	void mutate();

	/**
	 * Explicit cast to type T.
	 * Throws boost::bad_any_cast.
	 */
	template <typename T>
	explicit operator T() const
	{
		return boost::any_cast<T>(data_);
	}

	/**
	 * Copy assignment operator that reassigns the internal data.
	 * @param updatedData - the new value to store in the boost::any instance.
	 * @return a reference to this Gene instance.
	 */
	template <typename T>
	Gene & operator=(const T & updatedData)
	{
		data_ = updatedData;
		return *this;
	}

	/**
	 * Interpret the internal, type-erased data as type T.
	 * @return the internal data represented as an object of type T.
	 */
	template <typename T>
	T getValue() const
	{
		return boost::any_cast<T>(data_);
	}
	/**
	 * Request a shared pointer-to-Mutator from the static MutatorManager instance
	 * @return std::shared_ptr<Mutator> to the requested mutator instance.
	 */
	template <class M, typename ... T>
	static std::shared_ptr<Mutator> makeMutator(T && ... args)
	{
		return mutatorMaker_.getMutator<M, T...>(std::forward<T>(args) ...);
	}
};

#endif /* GENE_H_ */
