/*
 * HillClimber.cpp
 *
 *  Created on: Jan 14, 2017
 *      Author: tim
 */

#include "HillClimber.h"
#include <cmath>
#include "../Random/random_numbers.h"
#define M_PI 3.14159265



HillClimber::HillClimber(double x, double y) {
	// TODO Auto-generated constructor stub
	this->x = x;
	this->y = y;
}

HillClimber::HillClimber(Chromosome chrom) {
	// TODO Auto-generated constructor stub
	this->x = x;
	this->y = y;
}

HillClimber::HillClimber(double xstart, double xend, double ystart, double yend) {
	// TODO Auto-generated constructor stub
	this->x = rng_range<double>(xstart, xend);
	this->y = rng_range<double>(ystart, yend);
}

HillClimber::~HillClimber() {
	// TODO Auto-generated destructor stub
}


void HillClimber::EvaluateFitness()
{
	Evolvable::fitness = fit_eval(x, y);
}
vector<Evolvable *> HillClimber::MakeInitialPopulation(size_t count, double xstart, double xend, double ystart, double yend)
{
	vector<Evolvable *> pop = vector<Evolvable *>();
	pop.reserve(count);
	for(size_t i = 0; i < count; ++i)
	{
		pop[i] = new HillClimber(xstart, xend, ystart, yend);
	}
	return pop;
}
double HillClimber::fit_eval(double x, double y, double gx, double gy, double sigma)
{
	if( x < 0.0 or y < 0.0 or x > 5.0 or y > 5.0)
	{
		return 0.1;
	}
	double fit = 0;
	fit = exp(pow((x - gx), 2) + pow((y - gy), 2));
	fit /= (sqrt(2.0 * M_PI) * abs(sigma));
	return fit + 0.1;
}
