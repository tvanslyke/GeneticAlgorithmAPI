/*
 * MutatorBase.h
 *
 *  Created on: Mar 8, 2017
 *      Author: tim
 */

#ifndef EVOLUTION_GENETICS_MUTATION_MUTATORS_BITFLIPMUTATORS_MUTATORBASE_H_
#define EVOLUTION_GENETICS_MUTATION_MUTATORS_BITFLIPMUTATORS_MUTATORBASE_H_

#include "Mutator.h"
#include "../../../../Utilities/TypeNum.h"
#include <type_traits>

/**
 * Sub-base class utilizing the Curiously Recurring Template Pattern to
 * achieve static polymorphism.  This pattern is used here to avoid long
 * chains of virtual calls and to free derived classes from needing to implement
 * the getID method.
 *
 * @author Timothy Van Slyke
 */
template <class M>
class MutatorBase: public Mutator
{
public:


	virtual ~MutatorBase() = default;
	/**
	 * Mutate the data held by the boost::any reference.
	 *
	 * @param data - The boost::any reference to mutate.
	 */
	void mutate(boost::any & data)
	{
		(static_cast<M&>(*this)).mutate(data);
	}
	/**
	 * Return the unique ID for this type of mutator.
	 * @return The id for this mutator type.
	 */
	const size_t getID() const
	{
		return TypeNum::getNum<M>();
	}

};

#endif /* EVOLUTION_GENETICS_MUTATION_MUTATORS_BITFLIPMUTATORS_MUTATORBASE_H_ */
