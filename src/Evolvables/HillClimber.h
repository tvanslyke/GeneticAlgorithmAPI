/*
 * HillClimber.h
 *
 *  Created on: Jan 14, 2017
 *      Author: tim
 */

#ifndef EVOLVABLES_HILLCLIMBER_H_
#define EVOLVABLES_HILLCLIMBER_H_
#include "Evolvable.h"
class HillClimber: public Evolvable
{
private:
	double x, y;
public:
	static double gx, gy;
	double fit_eval(double x, double y, double gx = 0, double gy = 0, double sigma = 1.0);
	HillClimber(double x, double y);
	HillClimber(double , double, double , double);
	HillClimber(Chromosome);
	virtual ~HillClimber();
	void EvaluateFitness();
	static vector<Evolvable *> MakeInitialPopulation(size_t, double , double, double , double);
};

#endif /* EVOLVABLES_HILLCLIMBER_H_ */
