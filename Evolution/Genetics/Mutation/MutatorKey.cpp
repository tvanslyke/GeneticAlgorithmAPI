/*
 * MutatorKey.cpp
 *
 *  Created on: Feb 4, 2017
 *      Author: tim
 */

#include "MutatorKey.h"
#include "Mutators/Mutator.h"
#include "../../../Utilities/GenericWeakKey.h"
MutatorKey::MutatorKey(size_t id): GenericWeakKey(), id_(id)
{
	;
}

bool MutatorKey::operator==(const MutatorKey & other) const
{
	return (this->id_ == other.id_) and (this->hashcode_ == other.hashcode_);
}

size_t MutatorKey::Hash::operator()(const MutatorKey & key) const
{
	return key.getHash();
}
