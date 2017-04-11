/*
 * Gene.cpp
 *
 *  Created on: Feb 3, 2017
 *      Author: tim
 */

#include "Gene.h"
#include "MakeGene.h"


void Gene::mutate()
{
	this->mutator_->mutate(data_);
}
Gene::Gene(const std::shared_ptr<Mutator> & mutator):data_(), mutator_(mutator){}
Gene::Gene(const std::shared_ptr<Mutator> & mutator, const boost::any & data):data_(data), mutator_(mutator){}





MutatorManager Gene::mutatorMaker_ = MutatorManager();
