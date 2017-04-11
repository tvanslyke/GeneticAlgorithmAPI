/*
 * Mutator.h
 *
 *  Created on: Feb 4, 2017
 *      Author: tim
 */

#ifndef MUTATOR_H_
#define MUTATOR_H_

#include <boost/any.hpp>

/**
 * Base mutator class.  Mutators mutate data contained within
 * Gene instances in a policy-like manor.
 *
 * @author Timothy Van Slyke
 */
class Mutator
{
public:

	/** Default virtual ctor. */
	virtual ~Mutator() = default;
	/**
	 * Return the unique ID for this type of mutator.
	 * @return The id for this mutator type.
	 */
	virtual const size_t getID() const;
	/**
	 * Mutate the data held by the boost::any reference.
	 * @param data - The boost::any reference to mutate.
	 */
	virtual void mutate(boost::any & data);
};

#endif /* MUTATOR_H_ */
