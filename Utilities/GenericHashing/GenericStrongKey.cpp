/*
 * GenericStrongKey.cpp
 *
 *  Created on: Feb 11, 2017
 *      Author: tim
 */

#include "GenericStrongKey.h"
GenericStrongKey::	GenericStrongKey(size_t & hashcode,
		  size_t & totalbytes,
		  std::stack<std::pair<size_t, void *>> & pending,
		  std::vector<std::type_index> & types):GenericWeakKey(hashcode, totalbytes, pending),
				  	  	  	  	  	  	  	    types_(types)
{
	;
}
GenericStrongKey::~GenericStrongKey()
{
	;
}

bool GenericStrongKey::operator==(const GenericStrongKey & other) const
{
	return (this->types_.size() == other.types_.size()) and
			(this->GenericWeakKey::operator==(dynamic_cast<const GenericWeakKey&>(other))) and
			(this->types_ == other.types_);
}

bool GenericStrongKey::operator==(GenericStrongKey && other) const
{
	return (this->types_.size() == other.types_.size()) and
			(this->GenericWeakKey::operator==(dynamic_cast<const GenericWeakKey&>(other))) and
			(this->types_ == other.types_);
}

size_t GenericStrongKey::getHash() const
{
	return this->hashcode_;
}


