/*
 * GuaranteedMutation.cpp
 *
 *  Created on: Feb 27, 2017
 *      Author: tim
 */

#include "GuaranteedMutation.h"


GuaranteedMutation::GuaranteedMutation(size_t minm, size_t maxm) {
	// TODO Auto-generated constructor stub
	counter_ = rng::UniformRNG<size_t>(minm, maxm);
	indexer_ = rng::UniqueIntGenerator<size_t>();
}
