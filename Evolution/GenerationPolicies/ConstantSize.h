/*
 * ConstantSize.h
 *
 *  Created on: Feb 27, 2017
 *      Author: tim
 */

#ifndef EVOLUTION_GENERATIONPOLICIES_CONSTANTSIZE_H_
#define EVOLUTION_GENERATIONPOLICIES_CONSTANTSIZE_H_

#include <vector>
#include "../Evolvable.h"
#include "../../CrossoverPolicies.h"
#include <memory>
/**
 * Generation policy that does not change the size of the population.
 * @author Timothy Van Slyke
 */
template <typename SP, typename CP, typename MP>
class ConstantSize
{
public:
	/**
	 * Construct a ConstantSize generation policy from it's component policies.
	 * @param sp - The sampling policy to use.
	 * @param cp - The crossover policy to use.
	 * @param mp - The mutation policy to use.
	 */
	ConstantSize(const SP & sp, const CP & cp, const MP & mp):  sp_(sp), cp_(cp), mp_(mp){}

	/**
	 * Default constructor.
	 */
	ConstantSize() = default;

	/**
	 * Call the policy as a functor.  Replaces the current generation with the next generation.
	 * @param pop - reference to the current generation.
	 */
	template <typename Ev>
	void operator()(std::vector<Ev> & pop)
	{
		using Chrom = typename Ev::ChromosomeType;

		auto popSize = pop.size();
		auto nextGen = std::vector<Chrom>();
		nextGen.reserve(popSize);

		// build the sample
		sp_.buildSample(pop.begin(), pop.end());

		// instantiate two pointers for the parents
		Ev* parent1 = nullptr;
		Ev* parent2 = nullptr;

		// fill the temporary nextGen vector with child chromosomes
		// created from randomly selected parents
		for(auto i = 0u; i < popSize; ++i)
		{
			parent1 = sp_.next();
			parent2 = sp_.next();
			nextGen.push_back(cp_.cross(parent1->viewChromosome(), parent2->viewChromosome(), ONE_CHILD));
		}
		// set the chromosomes of each element of the population
		for(auto i = 0u; i < popSize; ++i)
		{
			pop[i].setChromosome(nextGen[i]);
		}
		// mutate each member of the population
		mp_.mutate(pop.begin(), pop.end());
	}
private:
	/** Sampling policy to use. */
	SP sp_;
	/** Crossover policy to use. */
	CP cp_;
	/** Mutation policy to use. */
	MP mp_;
};

#endif /* EVOLUTION_GENERATIONPOLICIES_CONSTANTSIZE_H_ */
