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
	HillClimber(double x, double y);
	virtual ~HillClimber();
	void EvaluateFitness(double (*)(double, double));

};

#endif /* EVOLVABLES_HILLCLIMBER_H_ */
