/*
 * crossover.h
 *
 *  Created on: Jan 11, 2017
 *      Author: tim
 */

#ifndef CROSSOVER_H_
#define CROSSOVER_H_

#include "Chromosome.h"
#include <climits>
#include <cstdlib>

#define UNIFORM           0
#define SINGLE_POINT      1
#define DOUBLE_POINT      2



void n_point_in_place(Chromosome & c1, Chromosome & c2, size_t n);

Chromosome n_point_new_child(Chromosome & c1, Chromosome & c2, size_t n);

void uniform_in_place(Chromosome & c1, Chromosome & c2, float prob = 0.5);

Chromosome uniform_new_child(Chromosome & c1, Chromosome & c2, float prob = 0.5);





#endif /* CROSSOVER_H_ */
