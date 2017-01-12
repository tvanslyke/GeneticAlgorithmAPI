/*
 * Mutatable.h
 *
 *  Created on: Jan 10, 2017
 *      Author: tim
 */

#ifndef INTERFACES_MUTATABLE_H_
#define INTERFACES_MUTATABLE_H_

#include <type_traits>
#include <iostream>
using std::cout;
using std::endl;

class Mutatable {
	friend class Gene;

public:
	Mutatable(){};
	virtual ~Mutatable(){};
	virtual void Mutate(){};
	virtual Mutatable * Copy(){return (Mutatable *)NULL;};
};

#endif /* INTERFACES_MUTATABLE_H_ */
