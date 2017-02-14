/*
 * Mutator.h
 *
 *  Created on: Feb 4, 2017
 *      Author: tim
 */

#ifndef MUTATOR_H_
#define MUTATOR_H_
#include "Mutator.h"
#include <boost/any.hpp>
#include "../MutatorDiagnostics.h"
class Mutator
{
protected:
	static size_t assignID();
	Mutator();

public:
	virtual ~Mutator();
	virtual size_t getID() const;
	virtual void mutate(boost::any & data);
	int getValue(boost::any);
	static const size_t mutatorID;
};

#endif /* MUTATOR_H_ */
