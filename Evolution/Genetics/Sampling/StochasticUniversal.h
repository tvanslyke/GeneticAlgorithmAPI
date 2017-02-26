/*
 * StochastivUniversal.h
 *
 *  Created on: Feb 21, 2017
 *      Author: tim
 */

#ifndef EVOLUTION_GENETICS_SAMPLING_STOCHASTICUNIVERSAL_H_
#define EVOLUTION_GENETICS_SAMPLING_STOCHASTICUNIVERSAL_H_

#include "SamplingPolicy.h"
#include <vector>
#include <set>

/**
 * SamplingPolicy implementing stochastic acceptance selection.
 *
 * see: https://en.wikipedia.org/wiki/Stochastic_universal_sampling
 */

class StochasticUniversal:public SamplingPolicy<StochasticUniversal>
{
private:

public:
	StochasticUniversal();
	virtual ~StochasticUniversal();
	template <typename It>
	void sample(It begin, It end, It & destBegin, It & destEnd, std::input_iterator_tag)
	{

	}
};

#endif /* EVOLUTION_GENETICS_SAMPLING_STOCHASTICUNIVERSAL_H_ */
