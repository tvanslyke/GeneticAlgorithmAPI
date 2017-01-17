/*
 * Gene.h
 *
 *  Created on: Jan 10, 2017
 *      Author: tim
 */
#include <typeinfo>

#ifndef GENE_H_
#define GENE_H_
#include "stdlib.h"
#include "Mutation/mutation.h"
#include "Mutation/Mutatables/Mutatable.h"
#include "Mutation/Mutatables/MutatablePrimitive.h"
#include <type_traits>
#include <exception>
class Gene {
	friend class Chromosome;
private:
	Mutatable * genetic_info;
public:
	Gene()
	{
		genetic_info = NULL;
	}
	template <typename T>
	Gene(T data)
	{
		if(std::is_fundamental<T>::value)
		{
			genetic_info = new MutatablePrimitive<T>(data);
		}
		else
		{
			throw new std::invalid_argument("[Gene::Gene()] Bad type in Gene constructor (must be primitive or inherit from Mutatable).\n");
		}
	}
	Gene(Mutatable * gene_data)
	{
		this->genetic_info = gene_data->Copy();
	}
	Gene(const Gene & gene)
	{
		this->genetic_info = gene.genetic_info->Copy();
	}
	void Mutate()
	{
		genetic_info->Mutate();
	}
	virtual ~Gene()
	{
		delete genetic_info;
	}
	Gene Copy() const
	{
		Gene new_gene = Gene(genetic_info);
		return new_gene;
	}
	static void Swap(Gene & g1, Gene & g2)
	{
		Gene temp = Gene(g1.genetic_info);
		g1 = g2.Copy();
		g2 = temp;
	}

};
















#endif /* GENE_H_ */
