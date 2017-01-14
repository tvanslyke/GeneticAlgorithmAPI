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
	void LoadNewGenome(Chromosome & newGenome);
	Chromosome & GetGenomeReference();
public:
	void Update();
	double GetFitness();
	bool operator<(const Evolvable & other) const;
	bool operator<=(const Evolvable & other) const;
	bool operator>(const Evolvable & other) const;
	bool operator>=(const Evolvable & other) const;
	Chromosome GetGenome();
};

#endif /* EVOLVABLES_EVOLVABLE_H_ */
