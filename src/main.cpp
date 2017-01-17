/*
 * main.cpp
 *
 *  Created on: Jan 10, 2017
 *      Author: tim
 */

#include <iostream>
#include "Random/random_numbers.h"
#include <unordered_map>
#include <boost/any.hpp>
#include "Mutation/Mutators/RandIncrMutator.h"
#include "Mutation/Mutators/BitflipMutator.h"



using namespace std;
using boost::any;
using boost::any_cast;




int main(void)
{
	rng_autoinit();

	cout << "Done." << endl;
	return 0;
}
