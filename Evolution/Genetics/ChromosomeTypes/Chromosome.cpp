/*
 * Chromosome.cpp
 *
 *  Created on: Feb 13, 2017
 *      Author: tim
 */

#include "Chromosome.h"
#include <stdexcept>
Chromosome::Chromosome()
{
	;
}


Chromosome::~Chromosome()
{
	;
}

void Chromosome::mutate()
{
	;
}
void * Chromosome::begin()
{
	throw std::runtime_error("[Chromosome] Attempted call to begin() on Chromosome interface base class.");
	return nullptr;
}
void * Chromosome::end()
{
	throw std::runtime_error("[Chromosome] Attempted call to end() on Chromosome interface base class.");
	return nullptr;
}
