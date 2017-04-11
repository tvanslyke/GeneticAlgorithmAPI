/*
 * MakeGene.h
 *
 *  Created on: Apr 4, 2017
 *      Author: tim
 */

#ifndef EVOLUTION_GENETICS_MAKEGENE_H_
#define EVOLUTION_GENETICS_MAKEGENE_H_
#include "Gene.h"
#include "Mutation/MakeMutator.h"
#include <utility>
#include "../../Mutators.h"

/**
 * Class to be used similarly to standard library functions like std::make_shared,
 * std::make_tuple, etc.  The implementation is naive due to time constraints, but
 * makes Gene construction more readable.
 *
 * @author Timothy Van Slyke
 */
template <typename T,		// Type held by Gene.
		  typename M,		// Mutator.
		  typename ... U>	// Mutator constructor argument types.
class MakeGene
{

private:
	/** Temporary Gene instance*/
	Gene geneTemp_;
public:
	/** Construct from a parameter pack. */
	MakeGene(const T & data, U && ... args):
		geneTemp_((std::shared_ptr<Mutator>)(MakeMutator<M, U...>(std::forward<U>(args)...)), data){}
	/** Construct from a data parameter and a tuple of arguments to pass to MakeMutator */
	MakeGene(const T & data, const std::tuple<U ...> & args):
		geneTemp_((std::shared_ptr<Mutator>)(MakeMutator<M, std::tuple<U...>>(args)), data)
	{

	}

	/** Implicitly cast to Gene. */
	operator Gene()
	{
		return geneTemp_;
	}

	/** Allow class Gene to directly access the internals of this class */
	friend class Gene;
};

#endif /* EVOLUTION_GENETICS_MAKEGENE_H_ */
