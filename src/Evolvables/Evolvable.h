/*
 * Evolvable.h
 *
 *  Created on: Jan 10, 2017
 *      Author: tim
 */

#ifndef EVOLVABLES_EVOLVABLE_H_
#define EVOLVABLES_EVOLVABLE_H_
#include "../Chromosome.h"

class Evolvable {
	friend class Population;
	friend bool fit_compare(Evolvable *&, Evolvable *&);
private:
	Chromosome genome;
	double fitness;
	size_t rank;
	void LoadNewGenome(Chromosome & newGenome);
	void Update();
	Chromosome & GetGenomeReference();
	Chromosome GetGenome();
};

#endif /* EVOLVABLES_EVOLVABLE_H_ */
