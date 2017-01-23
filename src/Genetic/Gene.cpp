/*
 * Gene.cpp
 *
 *  Created on: Jan 17, 2017
 *      Author: tim
 */
#include "Gene.h"


Gene::Gene()
{
	genetic_info = NULL;
}

Gene::Gene(Mutatable * gene_data)
{
	this->genetic_info = gene_data->Copy();
}
Gene::Gene(const Gene & gene)
{
	this->genetic_info = gene.genetic_info->Copy();
}
Gene::~Gene()
{
	delete genetic_info;
}
void Gene::Mutate()
{
	genetic_info->Mutate();
}

Gene Gene::Copy() const
{
	Gene new_gene = Gene(genetic_info);
	return new_gene;
}
void Gene::Swap(Gene & g1, Gene & g2)
{
	Gene temp = Gene(g1.genetic_info);
	g1 = g2.Copy();
	g2 = temp;
}
