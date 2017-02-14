/*
 * FitnessProportionate.h
 *
 *  Created on: Feb 14, 2017
 *      Author: tim
 */

#ifndef EVOLUTION_GENETICS_SAMPLING_FITNESSPROPORTIONATE_H_
#define EVOLUTION_GENETICS_SAMPLING_FITNESSPROPORTIONATE_H_
#include <cstdint>
#include <functional>
#include <vector>
#include "SamplingPolicy.h"

class FitnessProportionate: public SamplingPolicy {
protected:
	std::vector<uint_fast64_t> cumfits_;
	std::vector<std::shared_ptr<Evolvable> > pop_;
	virtual void buildSample();
public:
	FitnessProportionate(const std::vector<std::shared_ptr<Evolvable> > & pop);
	virtual ~FitnessProportionate();
	virtual std::shared_ptr<Evolvable> next();
};

#endif /* EVOLUTION_GENETICS_SAMPLING_FITNESSPROPORTIONATE_H_ */
