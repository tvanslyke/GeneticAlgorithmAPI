/*
 * Chromosome.cpp
 *
 *  Created on: Jan 10, 2017
 *      Author: tim
 */

#include "Chromosome.h"
#include <functional>


hash<size_t> Chromosome::hash_func;


Chromosome::Chromosome() {
	// TODO Auto-generated constructor stub
	genes = vector<Gene>();
}

Chromosome::~Chromosome() {
	// TODO Auto-generated destructor stub

}


Chromosome::Chromosome(size_t count)
{
	genes = vector<Gene>(count);
}
Chromosome::Chromosome(vector<Gene> genes)
{
	this->genes = vector<Gene>(genes.size());
	for(size_t i = 0; i < genes.size(); ++i)
	{
		this->genes[i] = genes[i].Copy();
	}
}
Chromosome::Chromosome(const Chromosome & other)
{
	this->genes = vector<Gene>(other.genes.size());
	for(size_t i = 0; i < genes.size(); ++i)
	{
		this->genes[i] = other.genes[i].Copy();
	}
}


size_t Chromosome::self_hash() const
{
	size_t hashsum = 0;
	for(size_t i = 0; i <this->genes.size(); ++i)
	{
		hashsum += hash_func((size_t)(this->genes[i].genetic_info));
	}
	return hashsum;
}


bool Chromosome::operator ==(const Chromosome & other) const
{
	size_t count = this->genes.size();
	if(this->genes.size() != other.genes.size())
	{
		return false;
	}
	else if(this == &other)
	{
		return true;
	}
	else
	{
		while(count--)
		{
			// every Gene should have unique pointer to their respective Mutatable field
			if(this->genes[count].genetic_info != other.genes[count].genetic_info)
			{
				return false;
			}
		}
	}
	return true;
}

Chromosome Chromosome::Copy()
{
	Chromosome chrom = Chromosome(this->genes);
	return chrom;
}

void Chromosome::CopyGenomeSegmentFrom(const Chromosome & other, size_t start, size_t end)
{
	assert((start <= end) and (end < genes.size()));
	for(size_t i = start; i < end; ++i)
	{
		this->genes[i] = other.genes[i].Copy();
	}
}

void Chromosome::Mutate(float prob)
{
	size_t count = this->genes.size();
	if(prob == .5)
	{
		vector<bool> select = rand_bool_vector(this->genes.size());
		for(size_t i = 0; i < count; ++i)
		{
			if(select[i])
			{
				this->genes[i].Mutate();
			}
		}
	}
	else
	{
		int threshhold = (int)(prob * RAND_MAX);
		for(size_t i = 0; i < count; ++i)
		{
			if(rand() > threshhold)
			{
				this->genes[i].Mutate();
			}
		}
	}
}



