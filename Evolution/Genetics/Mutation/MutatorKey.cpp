/*
 * MutatorKey.cpp
 *
 *  Created on: Feb 4, 2017
 *      Author: tim
 */

#include "MutatorKey.h"
#include "Mutators/Mutator.h"


MutatorKey::~MutatorKey()
{

}
MutatorKey::MutatorKey(size_t & bytecount, size_t & hashcode, std::stack<std::pair<size_t, void*>> & pending, const size_t & id):
		   GenericWeakKey(bytecount, hashcode, pending),
		   id_(id)
{
	;
}
bool MutatorKey::operator==(MutatorKey && other) const
{
	return (this->id_ == other.id_) and (this->hashcode_ == other.hashcode_);
}
bool MutatorKey::operator==(const MutatorKey & other) const
{
	return (this->id_ == other.id_) and (this->hashcode_ == other.hashcode_);
}
