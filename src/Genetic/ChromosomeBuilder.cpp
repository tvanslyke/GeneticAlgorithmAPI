/*
 * ChromosomeBuilder.cpp
 *
 *  Created on: Jan 17, 2017
 *      Author: tim
 */

#include "ChromosomeBuilder.h"

ChromosomeBuilder::ChromosomeBuilder() {
	// TODO Auto-generated constructor stub
	gene_data_seq = vector<Gene>();
}
ChromosomeBuilder::ChromosomeBuilder(size_t n_genes)
{
	gene_data_seq = vector<Gene>();
	gene_data_seq.reserve(n_genes);
}
ChromosomeBuilder::~ChromosomeBuilder() {
	// TODO Auto-generated destructor stub
}


Chromosome * ChromosomeBuilder::Collapse()
{
	return new Chromosome(gene_data_seq);
}
