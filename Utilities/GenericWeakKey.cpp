/*
 * GenericKey.cpp
 *
 *  Created on: Feb 13, 2017
 *      Author: tim
 */

#include "GenericWeakKey.h"

#include <algorithm>


size_t GenericWeakKey::getHash() const
{
	return hashcode_;
}
bool GenericWeakKey::operator==(const GenericWeakKey & other) const
{
	// byte-for-byte equality
	return (mem_ == other.mem_);
}
size_t GenericWeakKey::Hash::operator()(const GenericWeakKey & gwk) const
{
	return gwk.getHash();
}
