/*
 * sampling.h
 *
 *  Created on: Jan 12, 2017
 *      Author: tim
 */

#ifndef SAMPLING_SAMPLING_H_
#define SAMPLING_SAMPLING_H_

#include "../Evolvables/Evolvable.h"
#include <cstdlib>
double total_fitness(const vector<Evolvable *> &);
vector<Evolvable *> stochastic_acceptance(vector<Evolvable *>, const size_t &);
vector<Evolvable *> stochastic_universal(vector<Evolvable *>, const size_t &);
vector<Evolvable *> fitness_proportionate(vector<Evolvable *>, const size_t &);


#endif /* SAMPLING_SAMPLING_H_ */
