/*
 * Evolvable.h
 *
 *  Created on: Feb 5, 2017
 *      Author: tim
 */

#ifndef EVOLVABLE_H_
#define EVOLVABLE_H_

#include <memory>

#include "Genetics/DynamicChromosome.h"
#include "Genetics/StaticChromosome.h"
#include "../MutationPolicies.h"

/**
 * A class template interface that end-users should inherit from in to
 * guarantee compatibility with other structures within the library.
 *
 * The purpose of this class is to provide a bridge between library structures
 * and external algorithms that are to be optimized through the use of
 * evolutionary algorithms.
 *
 * This class template takes two parameters, a mutation policy for handling which
 * genes will be mutated when the Evolvable instance has it's mutate() method
 * called, and a chromosome (of which, two types are provided by the library) which
 * houses the mutable state for the instance.
 *
 * @author Timothy Van Slyke
 */
template <class M, class C = DynamicChromosome>
class Evolvable;


template <class M, class C>
class Evolvable
{

protected:
	/** Default constructor. */
	Evolvable() = default;
	/** Construct from an already-existing chromosome. */
	Evolvable(C && chromosome): chromosome_(std::forward(chromosome)), mutationPolicy_()
	{

	}
	/** Construct from an already-existing chromosome of a different type. */
	template <class D>
	Evolvable(const D & chromosome): chromosome_(chromosome), mutationPolicy_()
	{

	}
	/** Construct from an already-existing chromosome and an already-existing mutation policy. */
	Evolvable(C && chromosome, const M & mp): chromosome_(std::move(chromosome)), mutationPolicy_(mp)
	{

	}
	/**
	 * Construct from an already-existing chromosome of a different type and
	 * an already-existing mutation policy.
	 */
	template <class D>
	Evolvable(const D & chromosome, const M & mp): chromosome_(chromosome), mutationPolicy_(mp)
	{

	}
	/**
	 * Construct from an already-existing chromosome of a different type and
	 * a parameter pack of arguments to forward to the mutation policy constructor.
	 */
	template <class D, typename ... T>
	Evolvable(const D & chromosome, T && ... args): chromosome_(chromosome), mutationPolicy_(std::forward<T>(args) ...)
	{

	}
	/** The mutation policy. */
	M mutationPolicy_;
	/** The chromosome. */
	C chromosome_;
	/** Default virtual constructor. */
	virtual ~Evolvable() = default;
public:
	// type alias to the chromosome type
	using ChromosomeType = C;
	// type alias to the mutation policy type.
	using MutationPolicyType = M;
	/**
	 * Apply the mutation policy to the internal chromosome.
	 */
	virtual void mutate()
	{
		mutationPolicy_.mutate(chromosome_.begin(), chromosome_.end());
	}
	/**
	 * Virtual method for obtaining the fitness of this instance.
	 * All provided sampling policies use this method, however it is not mad
	 * purely virtual to allow use with non-fitness based selection algorithms
	 * @return the fitness of this Evolvable.
	 */
	virtual double getFitness()
	{
		return 0;
	}
	/**
	 * Set this instances chromosome.
	 * @param the new chromosome.
	 */
	virtual void setChromosome(const C & chrom)
	{
		chromosome_ = chrom;
	}
	/**
	 * Loads the the information from the internally-stored chromosome
	 * into the the instances state/fields.
	 * This pure virtual method MUST be implemented in order properly interact
	 * with other library components.
	 */
	virtual void loadFromChromosome() = 0;
	/**
	 * Provides a const reference to the internally held chromosome.
	 * This allows inspection of the chromosome without copying.
	 * @return a const reference to the internal chromosome.
	 */
	const C & viewChromosome() const
	{
		return chromosome_;
	}
};


#endif /* EVOLVABLE_H_ */
