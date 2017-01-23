/*
 * ChromosomeBuilder.h
 *
 *  Created on: Jan 17, 2017
 *      Author: tim
 */

#ifndef GENETIC_CHROMOSOMEBUILDER_H_
#define GENETIC_CHROMOSOMEBUILDER_H_
#include "Chromosome.h"
#include <vector>
#include <boost/any.hpp>
#include <cassert>

using std::vector;
using boost::any;

class ChromosomeBuilder {
private:
	vector<Gene> gene_data_seq;
public:
	ChromosomeBuilder();
	ChromosomeBuilder(size_t n_genes);
	virtual ~ChromosomeBuilder();
	template <typename T>
	void Append(T data)
	{
		gene_data_seq.push_back(Gene(data));
	}
	Chromosome * Collapse();
};

#endif /* GENETIC_CHROMOSOMEBUILDER_H_ */
