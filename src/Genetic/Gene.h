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
#include "../Mutation/mutation.h"
#include "../Mutation/Mutatables/MutatablePrimitives.h"
#include <type_traits>
#include <exception>

class Gene {
	friend class Chromosome;
private:
	Mutatable * genetic_info;
public:
	Gene();
	template <typename T>
	Gene(T data)
	{
		genetic_info = MakeNewMutatablePrimitive<T>(data);
	}
	Gene(Mutatable * gene_data);
	Gene(const Gene & gene);
	void Mutate();
	virtual ~Gene();
	Gene Copy() const;
	static void Swap(Gene & g1, Gene & g2);

};
















#endif /* GENE_H_ */
