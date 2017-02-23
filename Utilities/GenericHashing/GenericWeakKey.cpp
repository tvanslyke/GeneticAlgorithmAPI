/*
 * GenericKey.cpp
 *
 *  Created on: Feb 13, 2017
 *      Author: tim
 */

#include "GenericWeakKey.h"

#include <algorithm>
GenericWeakKey::GenericWeakKey(size_t & bytecount, size_t & hashcode, std::stack<std::pair<size_t, void*>> & pending): nbytes_(bytecount), hashcode_(hashcode)
{
	size_t offset = 0;
	mem_ = (void*)(new char[bytecount]);
	char * window = (char *)mem_;
	std::pair<size_t, void *> param;
	size_t bcount = 0;
	char * mem = nullptr;
	while(pending.size())
	{
		param = pending.top();
		pending.pop();
		bcount = param.first;
		mem = (char *)param.second;
		std::copy(mem, mem + bcount, window + offset);
		offset += bcount;
	}
}
GenericWeakKey::GenericWeakKey(const GenericWeakKey & other):nbytes_(other.nbytes_), hashcode_(other.hashcode_)
{
	this->mem_ = (void *)(new char[other.nbytes_]);
	std::copy(((char *)(other.mem_)), ((char *)(other.mem_)) + nbytes_, (char*)this->mem_);
}
GenericWeakKey::GenericWeakKey(GenericWeakKey && other) :nbytes_(other.nbytes_), hashcode_(other.hashcode_)
{
	this->mem_ = other.mem_;
	std::copy(((char *)(other.mem_)), ((char *)(other.mem_)) + nbytes_, (char*)this->mem_);
	other.mem_ = nullptr;
}
GenericWeakKey::~GenericWeakKey()
{
	if(this->mem_ != nullptr)
	{
		delete [] (char *)mem_;
	}
}
size_t GenericWeakKey::getHash() const
{
	return hashcode_;
}
bool GenericWeakKey::operator==(GenericWeakKey && other) const
{
	return (this->nbytes_ == other.nbytes_) and
			(std::equal((char *)this->mem_, ((char *)(this->mem_) + this->nbytes_), (char *)other.mem_));
}
bool GenericWeakKey::operator==(const GenericWeakKey & other) const
{
	return (this->nbytes_ == other.nbytes_) and
			(std::equal((char *)this->mem_, ((char *)(this->mem_) + this->nbytes_), (char *)other.mem_));
}
