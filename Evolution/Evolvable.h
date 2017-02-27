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
	//friend class CrossoverPolicy;
private:

protected:
	Evolvable();
	Chromosome * chromosome;

public:

	virtual ~Evolvable();
	virtual void mutate();
	virtual double getFitness() const;

};

#endif /* EVOLVABLE_H_ */
