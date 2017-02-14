/*
 * MutatorDiagnostics.h
 *
 *  Created on: Feb 11, 2017
 *      Author: tim
 */

#ifndef MUTATION_MUTATORDIAGNOSTICS_H_
#define MUTATION_MUTATORDIAGNOSTICS_H_

#include <cstdlib>
class MutatorDiagnostics {

public:
	static size_t assignID();
private:
	static size_t count;
};

#endif /* MUTATION_MUTATORDIAGNOSTICS_H_ */
