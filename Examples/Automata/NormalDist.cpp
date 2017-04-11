/*
 * NormalDist.cpp
 *
 *  Created on: Apr 5, 2017
 *      Author: tim
 */

#include "NormalDist.h"
#include <cmath>
#include <iostream>
NormalDist::NormalDist():twoSigmaSqrd_(1.0) {
	// TODO Auto-generated constructor stub

}
NormalDist::NormalDist(double sigma):twoSigmaSqrd_(2.0 * sigma * sigma) {
	// TODO Auto-generated constructor stub

}
double NormalDist::operator()(double dist) const
{
	return exp(-1 * dist * dist / twoSigmaSqrd_) / sqrt(M_PI * twoSigmaSqrd_);
}
void NormalDist::setSigma(double sigma) noexcept
{
	twoSigmaSqrd_ = 2 * sigma * sigma;
}
