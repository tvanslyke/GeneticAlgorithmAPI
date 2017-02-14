/*
 * NewGenerationPolicy.h
 *
 *  Created on: Feb 13, 2017
 *      Author: tim
 */

#ifndef EVOLUTION_NEWGENERATIONPOLICIES_NEWGENERATIONPOLICY_H_
#define EVOLUTION_NEWGENERATIONPOLICIES_NEWGENERATIONPOLICY_H_

#include <vector>
#include "../Evolvable.h"

class NewGenerationPolicy {
public:
	NewGenerationPolicy();
	virtual ~NewGenerationPolicy();
private:
	void newGeneration(std::vector<Evolvable *> & oldpop);
};

#endif /* EVOLUTION_NEWGENERATIONPOLICIES_NEWGENERATIONPOLICY_H_ */
