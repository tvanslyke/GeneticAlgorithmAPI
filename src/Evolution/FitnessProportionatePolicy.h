/*
 * FitnessProportionatePolicy.h
 *
 *  Created on: Jan 13, 2017
 *      Author: tim
 */

#ifndef EVOLUTION_FITNESSPROPORTIONATEPOLICY_H_
#define EVOLUTION_FITNESSPROPORTIONATEPOLICY_H_

#include "../Evolution/EvolutionPolicy.h"

class FitnessProportionatePolicy: public EvolutionPolicy {
public:
	FitnessProportionatePolicy(string name, size_t pop_size);
	virtual ~FitnessProportionatePolicy();
	vector<Evolvable *> Sample(vector<Evolvable *> pop);
	void MakeNextGeneration(vector<Evolvable *> & pop);
};

#endif /* EVOLUTION_FITNESSPROPORTIONATEPOLICY_H_ */
