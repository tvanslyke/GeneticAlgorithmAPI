/*
 * Evolvable.cpp
 *
 *  Created on: Jan 10, 2017
 *      Author: tim
 */

#include "Evolvable.h"



void Evolvable::LoadNewGenome(Chromosome & newGenome)
{
	this->genome = newGenome;
	this->Update();
}
void Evolvable::Update()
{

}
Chromosome & Evolvable::GetGenomeReference()
{
	return this->genome;
}

Chromosome Evolvable::GetGenome()
{
	return this->genome;
}
