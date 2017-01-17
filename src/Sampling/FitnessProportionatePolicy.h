/*
 * FitnessProportionatePolicy.h
 *
 *  Created on: Jan 13, 2017
 *      Author: tim
 */

#ifndef SAMPLING_FITNESSPROPORTIONATEPOLICY_H_
#define SAMPLING_FITNESSPROPORTIONATEPOLICY_H_

#include "SamplingPolicy.h"

class FitnessProportionatePolicy: public SamplingPolicy {
public:
	FitnessProportionatePolicy(string name, size_t pop_size);
	virtual ~FitnessProportionatePolicy();
	vector<Evolvable *> Sample(vector<Evolvable *> pop);
};

#endif /* SAMPLING_FITNESSPROPORTIONATEPOLICY_H_ */
