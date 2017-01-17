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
#include <unordered_map>
using std::cout;
using std::endl;
using std::unordered_map;



class Mutatable {
	friend class Gene;
public:
	Mutatable(){};
	virtual ~Mutatable(){};
	virtual void Mutate(){};
	virtual Mutatable * Copy(){return (Mutatable *)NULL;};
};

#endif /* INTERFACES_MUTATABLE_H_ */
