/*
 * UniformRandomMutation.cpp
 *
 *  Created on: Feb 27, 2017
 *      Author: tim
 */

#include "UniformRandomMutation.h"

UniformRandomMutation::UniformRandomMutation(): decider_(0.5, 1.0)
{

}
UniformRandomMutation::UniformRandomMutation(double prob, double total): decider_(prob, total)
{
	// TODO Auto-generated constructor stub


}

