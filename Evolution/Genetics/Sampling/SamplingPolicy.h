/*
 * SamplingPolicy.h
 *
 *  Created on: Feb 14, 2017
 *      Author: tim
 */

#ifndef EVOLUTION_GENETICS_SAMPLING_SAMPLINGPOLICY_H_
#define EVOLUTION_GENETICS_SAMPLING_SAMPLINGPOLICY_H_
#include "../../Evolvable.h"
class SamplingPolicy {
public:
	SamplingPolicy();
	virtual ~SamplingPolicy();
	virtual void buildSample();
	virtual std::shared_ptr<Evolvable> next();
};

#endif /* EVOLUTION_GENETICS_SAMPLING_SAMPLINGPOLICY_H_ */
