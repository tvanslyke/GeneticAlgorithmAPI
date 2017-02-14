/*
 * UniformRandomCrossover.h
 *
 *  Created on: Feb 13, 2017
 *      Author: tim
 */

#ifndef GENETICS_CROSOVERPOLICIES_UNIFORMRANDOMCROSSOVER_H_
#define GENETICS_CROSOVERPOLICIES_UNIFORMRANDOMCROSSOVER_H_

class UniformRandomCrossover {
protected:
	unsigned int cutoff_;

public:
	UniformRandomCrossover();
	virtual ~UniformRandomCrossover();
	void cross();
};

#endif /* GENETICS_CROSOVERPOLICIES_UNIFORMRANDOMCROSSOVER_H_ */
