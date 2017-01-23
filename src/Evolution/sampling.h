/*
 * sampling.h
 *
 *  Created on: Jan 12, 2017
 *      Author: tim
 */

#ifndef EVOLUTION_SAMPLING_H_
#define EVOLUTION_SAMPLING_H_

#include "../Evolvables/Evolvable.h"
#include <cstdlib>
double total_fitness(const vector<Evolvable *> &);
vector<Evolvable *> stochastic_acceptance(vector<Evolvable *>, const size_t &);
vector<Evolvable *> stochastic_universal(vector<Evolvable *>, const size_t &);
vector<Evolvable *> fitness_proportionate(vector<Evolvable *>, const size_t &, bool delete_unsampled = false);


#endif /* EVOLUTION_SAMPLING_H_ */
