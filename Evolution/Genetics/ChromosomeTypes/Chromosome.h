/*
 * Chromosome.h
 *
 *  Created on: Feb 13, 2017
 *      Author: tim
 */

#ifndef GENETICSTRUCTURES_CHROMOSOMETYPES_CHROMOSOME_H_
#define GENETICSTRUCTURES_CHROMOSOMETYPES_CHROMOSOME_H_

class Chromosome {
private:

protected:
	Chromosome();
public:
	virtual void mutate();
	virtual ~Chromosome();
};

#endif /* GENETICSTRUCTURES_CHROMOSOMETYPES_CHROMOSOME_H_ */