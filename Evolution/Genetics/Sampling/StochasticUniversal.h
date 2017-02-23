/*
 * StochastivUniversal.h
 *
 *  Created on: Feb 21, 2017
 *      Author: tim
 */

#ifndef EVOLUTION_GENETICS_SAMPLING_STOCHASTICUNIVERSAL_H_
#define EVOLUTION_GENETICS_SAMPLING_STOCHASTICUNIVERSAL_H_

#include "SamplingPolicy.h"

class StochasticUniversal:public SamplingPolicy<StochasticUniversal>
{
private:
	//std::vector<>
public:
	StochasticUniversal();
	virtual ~StochasticUniversal();
	virtual void buildSample();
};

#endif /* EVOLUTION_GENETICS_SAMPLING_STOCHASTICUNIVERSAL_H_ */
