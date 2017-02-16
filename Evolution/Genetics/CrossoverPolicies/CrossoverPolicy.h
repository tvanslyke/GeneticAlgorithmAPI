/*
 * CrossoverPolicy.h
 *
 *  Created on: Feb 13, 2017
 *      Author: tim
 */

#ifndef GENETICSTRUCTURES_CROSOVERPOLICIES_CROSSOVERPOLICY_H_
#define GENETICSTRUCTURES_CROSOVERPOLICIES_CROSSOVERPOLICY_H_


class CrossoverPolicy {
private:
protected:
	CrossoverPolicy();
public:
	virtual ~CrossoverPolicy();

	void cross(void * begin1, void * end1, void * start2);
	void cross(void * begin1, void * end1, void * begin2, void * dest);
};

#endif /* GENETICSTRUCTURES_CROSOVERPOLICIES_CROSSOVERPOLICY_H_ */
