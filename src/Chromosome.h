/*
 * Chromosome.h
 *
 *  Created on: Jan 10, 2017
 *      Author: tim
 */

#ifndef CHROMOSOME_H_
#define CHROMOSOME_H_

#include <cstdlib>
#include <vector>
#include "Gene.h"
#include <functional>

// crossover types for 2-parent
#define UNIFORM           0
#define SINGLE_POINT      1
#define DOUBLE_POINT      2

using namespace std;
class Chromosome {
	friend class Population;
	friend void n_point_in_place(Chromosome & c1, Chromosome & c2, size_t n);
	friend Chromosome n_point_new_child(Chromosome & c1, Chromosome & c2, size_t n);
	friend void uniform_in_place(Chromosome & c1, Chromosome & c2, float prob);
	friend Chromosome uniform_new_child(Chromosome & c1, Chromosome & c2, float prob);

private:
	vector<Gene> genes;

	void CopyGenomeSegmentFrom(const Chromosome & other, size_t start, size_t end);
public:
	static hash<size_t> hash_func;
	static float default_mutation_rate;
	Chromosome();
	Chromosome(size_t count);
	Chromosome(vector<Gene> genes);
	Chromosome(const Chromosome & other);
	virtual ~Chromosome();
	void Mutate(float prob = .5);
	Chromosome Copy();


	// in-place crossover.  reuses parents for next generation.  can save time and memory
	// compared to crossover methods that produce a new child without affecting the parents
	static void Crossover(Gene & g1, Gene & g2, int crossover_type = SINGLE_POINT);

	// out-of-place crossover.  does not change the parent chromosomes and creates a new chromosom
	static Chromosome & CrossoverNewChild(Chromosome & c1, Chromosome & c2, int crossover_type = SINGLE_POINT);

	bool operator ==(const Chromosome & other) const;
	size_t self_hash() const;
};


namespace std
{
	template<>
	struct hash<Chromosome>
	{
		size_t operator()(const Chromosome& chrom) const
		{
			return chrom.self_hash();
		}
	};
}

#endif /* CHROMOSOME_H_ */
