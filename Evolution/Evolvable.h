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
	friend class CrossoverPolicy;
private:

protected:
	Evolvable();
	std::shared_ptr<Chromosome> chromosome;

public:
	virtual ~Evolvable();
	void mutate();
	double getFitness() const;


};

#endif /* EVOLVABLE_H_ */
