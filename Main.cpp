/*
 * Main.cpp
 *
 *  Created on: Feb 3, 2017
 *      Author: tim
 */

// -pthread -lboost_system -lboost_iostreams  -lboost_system -lboost_filesystem

#include "Evolution/Genetics/Sampling/FitnessProportionate.h"
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

	SamplingPolicy<FitnessProportionate> * samp = new FitnessProportionate();
	std::cout << size_t(samp) << " " << endl;
	if(samp == nullptr or samp == NULL)
	{
		cout << "ERROR" << endl;
		exit(1);
	}
	std::vector<std::shared_ptr<Evolvable>> a;
	for(float e:{1,2,3,4,5, 6,7,8,9,20})
	{
		a.push_back(std::make_shared<Float>(e));
	}
	std::shuffle(a.begin(), a.end(), rng::BaseRNG::twister_);
	samp->buildSample(a.begin(), a.end());


	for(auto e:a)
	{

		cout << e->getFitness() << " " << (samp->next())->getFitness() << endl;
	}

	cout << endl<< "Done." << endl;
	delete samp;

	return 0;
}
