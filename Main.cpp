/*
 * Main.cpp
 *
 *  Created on: Feb 3, 2017
 *      Author: tim
 */

// -pthread -lboost_system -lboost_iostreams  -lboost_system -lboost_filesystem

#include "Evolution/Sampling/StochasticAcceptance.h"
#include "Evolution/Sampling/FitnessProportionate.h"
#include <vector>
#include <iostream>

#include "Random/UniqueIntGenerator.h"
#include "Utilities/more_type_traits.h"
using std::cout;
using std::endl;

class Float:public Evolvable
{
	float val;
public:
	Float(float a)
	{
		val = a;
	}
	~Float()
	{

	}
	double getFitness() const
	{
		return this->val;
	}
	operator float()
	{
		return this->val;
	}
};


using namespace rng;
int main(void)
{

	cout << "Start." << endl;


	cout << endl<< "Done." << endl;

	return 0;
}
