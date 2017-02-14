/*
 * Evolvable.h
 *
 *  Created on: Feb 5, 2017
 *      Author: tim
 */

#ifndef EVOLVABLE_H_
#define EVOLVABLE_H_

#include <memory>

#include "Genetics/ChromosomeTypes/Chromosome.h"
class Evolvable {

private:

protected:
	Evolvable();
	std::unique_ptr<Chromosome> chromosome;
public:
	virtual ~Evolvable();
	void mutate()
	{
		this->chromosome->mutate();
	}
};

#endif /* EVOLVABLE_H_ */
