/*
 * NPointCrossover.cpp
 *
 *  Created on: Feb 27, 2017
 *      Author: tim
 */


#include "NPointCrossover.h"

NPointCrossover::NPointCrossover(size_t n):nPoints(n)
{
	generator = rng::UniqueIntGenerator<size_t>(0u, 0u, nPoints).sorted(rng::ASCENDING);
}
NPointCrossover::~NPointCrossover()
{

}
