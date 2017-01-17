/*
 * MutatableTest.h
 *
 *  Created on: Jan 11, 2017
 *      Author: tim
 */

#ifndef MUTATABLES_MUTATABLETEST_H_
#define MUTATABLES_MUTATABLETEST_H_
#include "Mutatable.h"
#include <iostream>


using std::cout;
using std::endl;
template <typename T>
class MutatableTest : public Mutatable
{
private:
	T data;
public:
	MutatableTest(T data)
	{
		this->data = data;
	}
	virtual ~MutatableTest()
	{
		;
	}
	void Mutate()
	{
		cout << "I'm a derived class!" << endl;
	}
	MutatableTest * Copy()
	{
		MutatableTest * new_mt = new MutatableTest<T>(data);
		return new_mt;
	}
};

#endif /* MUTATABLES_MUTATABLETEST_H_ */




