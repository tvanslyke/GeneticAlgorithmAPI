/*
 * Gene.cpp
 *
 *  Created on: Feb 3, 2017
 *      Author: tim
 */

#include "Gene.h"

Gene::~Gene()
{
	// TODO Auto-generated destructor stub
}

void Gene::mutate()
{
	this->mutator_->mutate(this->data_);
}
Gene::Gene(std::shared_ptr<Mutator> mutator, boost::any data):data_(data), mutator_(mutator)
{
}


MutatorManager Gene::mutatorMaker_ = MutatorManager();
