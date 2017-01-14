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

double Evolvable::GetFitness()
{
	return this->fitness;
}


bool Evolvable::operator<(const Evolvable & other) const
{
	return this->fitness < other.fitness;
}
bool Evolvable::operator<=(const Evolvable & other) const
{
	return this->fitness <= other.fitness;
}
bool Evolvable::operator>(const Evolvable & other) const
{
	return this->fitness > other.fitness;
}
bool Evolvable::operator>=(const Evolvable & other) const
{
	return this->fitness >= other.fitness;
}


