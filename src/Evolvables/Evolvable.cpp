/*
 * Evolvable.cpp
 *
 *  Created on: Jan 10, 2017
 *      Author: tim
 */

#include "Evolvable.h"
#include "../crossover.h"


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

void CrossoverInPlace(Evolvable * other, unsigned int crossover_type_flag)
{
	switch(crossover_type_flag)
	{
	case UNIFORM:
		//uniform_in_place(this, other);
		break;
	case 2:
		break;
	default:
		break;
	}
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


