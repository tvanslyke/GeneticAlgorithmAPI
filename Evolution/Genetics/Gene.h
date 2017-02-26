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
#include "Mutation/Mutators/Mutators.h"

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
 */
class Gene {
private:
	template <template<typename = Gene> class Container = std::vector>
	friend class Chromosome;
	static MutatorManager mutatorMaker_;
	boost::any data_;
	std::shared_ptr<Mutator> mutator_;


	Gene(std::shared_ptr<Mutator> mutator, boost::any data);

public:

	template <typename T, template <typename U = T> class MutatorType, typename ... ArgTypes>
	static Gene makeGene(T data, ArgTypes ... args)
	{
		std::shared_ptr<Mutator> mutator = mutatorMaker_.getMutator<MutatorType<T>, ArgTypes ...>(args...);
		return Gene(mutator, boost::any(data));
	}

	virtual ~Gene();
	void mutate();

	template <typename T>
	explicit operator T() const
	{
		return boost::any_cast<T>(data_);
	}
	template <typename T>
	T getValue() const
	{
		return this->mutator_->getValue(data_);
	}
};

#endif /* GENE_H_ */
