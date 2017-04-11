/*
 * Simulation.h
 *
 *  Created on: Apr 4, 2017
 *      Author: tim
 */

#ifndef EXAMPLES_AUTOMATA_SIMULATION_H_
#define EXAMPLES_AUTOMATA_SIMULATION_H_

#include "../../SamplingPolicies.h"
#include "../../GenerationPolicies.h"
#include "../../CrossoverPolicies.h"
#include "../../MutationPolicies.h"
#include "../../RandomNumbers.h"
#include "../../Evolution/Population.h"
#include "../../Mutators.h"
#include "Automaton.h"
#include <iostream>
/**
 * Class to oversee the simulation and evolution of Automaton instances.
 *
 * @author Timothy Van Slyke
 */
template <size_t N, size_t M>
class Simulation {

public:
	using GenPolicy = ConstantSize<StochasticAcceptance<Automaton>, NPointCrossover<6>, UniformRandomMutation>;
	/**
	 * Initialize with boundaries.
	 * @param xmin - lower bound in x direction.
	 * @param xmax - upper bound in x direction.
	 * @param ymin - lower bound in y direction.
	 * @param ymax - upper bound in y direction.
	 */
	Simulation(double xmin, double xmax, double ymin, double ymax):
		pop_(StochasticAcceptance<Automaton>(), NPointCrossover<6>(), UniformRandomMutation(0.1, 1.0)),
		xmin_(xmin), xmax_(xmax), ymin_(ymin), ymax_(ymax), xgen_(xmin, xmax), ygen_(ymin, ymax )
	{
		rng::UniformRNG<double> randInitr(0.0, 2.0);
		// initialize the chromosome
		StaticChromosome<12> chrom = StaticChromosome<12>();
		for(auto i = 0u; i < N; ++i)
		{
			chrom = StaticChromosome<12>();
			// set PID params with low values and slower mutators
			for(auto i = 0u; i < 6; ++i)
			{
				chrom[i] = Gene(Gene::makeMutator<RandIncrMutator<double>>(-0.025, 0.025), randInitr());
			}
			// scale the other parameters according to the size of the simulation region
			auto width = (xmax - xmin);
			for(auto i = 6u; i < 12; ++i)
			{
				chrom[i] = Gene(Gene::makeMutator<RandIncrMutator<double>>(-1 * width * 0.1, width * 0.1), width * randInitr());
			}
			pop_.emplace_back(xgen_(), ygen_(), chrom);
		}
		// generate the food instances
		foods_.reserve(M);
		for(auto i = 0u; i < M; ++i)
		{
			foods_.emplace_back(xgen_(), ygen_());
		}
	}
	/**
	 * Fully update one cycle of the simulation.
	 * @param timeStep - how long this cycle/frame lasts.
	 */
	void update(double timeStep = 1.0)
	{

		// update the setpoint for each
		for(auto & aut:pop_)
		{
			aut.updateSetPoint(pop_.begin(), pop_.end(), foods_.begin(), foods_.end());
		}
		// update the positions for each
		for(auto autIter = pop_.begin(); autIter != pop_.end(); ++autIter)
		{
			auto & aut = *autIter;
			aut.updatePosition(timeStep);
			// make sure they stay in bounds.
			limitPosition(aut);
		}

		// map of food to the largest Automaton that is close enough to eat the food.
		std::map<FoodIter, AutIter> foodMap;
		// map of Automaton to be eaten to the largest Automaton that is close enough
		// to eat the Automaton to be eaten.
		std::map<AutIter, AutIter> preyMap;

		// iterate over all potential predators/consumers
		for(auto autIter = pop_.begin(); autIter != pop_.end(); ++autIter)
		{
			for(auto foodIter = foods_.begin(); foodIter != foods_.end(); ++foodIter)
			{
				// insert autIter only when it can eat the food and either:
				// 	   1) nobody else is trying to eat the food or
				//     2) the automata associated with autIter is larger than the one stored in foodMap
				if(autIter->canEat(*foodIter) and ((not foodMap.count(foodIter)) or (*foodMap[foodIter] < *autIter)))
				{
					foodMap[foodIter] = autIter;
				}
			}
			for(auto preyIter = pop_.begin(); preyIter != pop_.end(); ++preyIter)
			{
				// insert autIter only when it can eat the prey and either:
				// 	   1) nobody else is trying to eat the prey or
				//     2) the automata associated with autIter is larger than the one stored in preyMap
				if(autIter->canEat(*preyIter) and ((*preyIter < *autIter) and (not preyMap.count(preyIter) or *preyMap[preyIter] < *autIter)))
				{
					preyMap[preyIter] = autIter;
				}
			}
		}

		// deal with the food map first
		for(auto & pair:foodMap)
		{
			pair.second->eat(*(pair.first));
			pair.first->setPosition(xgen_(), ygen_());
		}

		// handle the predator-prey consumptions of the Automata gracefully.
		auto consumedAuts = collapseConsumptionMap(preyMap);

		// iterate over the automata consumed
		for(auto & aut:consumedAuts)
		{
			eatenCounts_[aut] += 1;
			// static cast because eclipse CDT's CODAN can't figure out the inheritance
			// hierarchy here and I don't like seeing the red underline.
			static_cast<Food&>(*aut).setPosition(xgen_(), ygen_());
			aut->setToDefaults();
		}
	}
	/**
	 * Set the fitness of each Automaton.
	 * @param useDiversity - set to false to ignore diversity as a metric.
	 */
	void setFitnesses(bool useDiversity = true)
	{
		// use pointers instead of iterators to save some memory.
		// this part can be a bit bulky
		std::map<Automaton *, double> fitMap;
		for(auto & aut:pop_)
		{
			fitMap.emplace(&aut, 0.0);
		}
		// fitness based on genetic diversity
		if(useDiversity)
		{
			// function to use to find cartesian distance between chromosomes.
			auto geneDist = [](const StaticChromosome<12> & a, const StaticChromosome<12> & b)->double
			{
				double dist = 0;
				double diff = 0;
				for(auto i = 0u; i < 12; ++i)
				{
					diff = double(a[i]) - double(b[i]);
					dist += (diff * diff);
				}
				return sqrt(dist);
			};

			// use pointers instead of iterators to save some memory.
			std::map<Automaton *, std::set<Automaton *>> distSkips;
			for(auto & aut:pop_)
			{
				distSkips[&aut] = std::set<Automaton *>();
			}

			bool found = false;
			double dist = 0.0;
			// get total genetic distance for each.
			for(auto & aut1:pop_)
			{
				for(auto & aut2:pop_)
				{
					if(&aut2 != &aut1)
					{
						std::tie(std::ignore, found) = distSkips[&aut1].insert(&aut2);

						if(found)
						{
							distSkips[&aut2].insert(&aut1);
							dist = geneDist(aut1.viewChromosome(), aut2.viewChromosome());
							fitMap[&aut1] += dist;
							fitMap[&aut2] += dist;
						}
					}
				}
			}
			// scale each by diversity factor
			for(auto & pair:fitMap)
			{
				pair.second *= diversityFactor_;
			}
		}
		// set the fitnesses
		for(auto aut = pop_.begin(); aut != pop_.end(); ++aut)
		{
			aut->setFitness(double(fitMap[&(*aut)] + (predCounts_[aut] * performanceFactor_) / (eatenCounts_[aut] + 1)));
			eatenCounts_[aut] = 0;
			predCounts_[aut] = 0;
		}

	}
	/**
	 * Update to the next generation.
	 */
	void nextGeneration()
	{
		pop_.nextGeneration();
		for(auto & aut:pop_)
		{
			aut.setPosition(xgen_(), ygen_());
			aut.setToDefaults();
		}
	}
	/**
	 * Send each food and automaton instance to an output file in binary format.
	 * @param out
	 */
	void pack(std::ostream & out)
	{
		for(auto & aut:pop_)
		{
			aut.pack(out);
		}
		for(auto & food:foods_)
		{
			food.pack(out);
		}
	}


private:
	/** The population of Automata. */
	Population<Automaton, GenPolicy> pop_;

	/** lower bound in x direction. */
	double xmin_;
	/** upper bound in x direction. */
	double xmax_;
	/** lower bound in y direction. */
	double ymin_;
	/** upper bound in y direction. */
	double ymax_;

	/** Generates positions along the x direction. */
	rng::UniformRNG<double> xgen_;
	/** Generates positions along the y direction. */
	rng::UniformRNG<double> ygen_;

	/** Food instances. */
	std::vector<Food> foods_;

	using FoodIter = typename decltype(foods_)::iterator;
	using AutIter = typename decltype(pop_)::iterator;
	/** Number of time each Automaton has been eaten. */
	std::map<AutIter, size_t> eatenCounts_;
	/** Number of time each Automaton has eaten something. */
	std::map<AutIter, size_t> predCounts_;

	/** Scaling factor for diversity component of fitness. */
	static double diversityFactor_;
	/** Scaling factor for performance component of fitness. */
	static double performanceFactor_;
	/** Drag coefficient */
	static double dragCoeff_;

	/**
	 * Adjust the position of an Automaton if it's out of bounds.
	 * @param aut - the Automaton to check.
	 */
	void limitPosition(Automaton & aut)
	{
		Vec<double, 2> pos = aut.getPosition();
		Vec<double, 2> vel = aut.getVelocity();
		bool newpos = false;
		if(pos[0] > xmax_)
		{
			newpos = true;
			pos[0] = xmax_;
			vel[0] = 0;
		}
		else if(pos[0] < xmin_)
		{
			newpos = true;
			pos[0] = xmin_;
			vel[0] = 0;
		}
		if(pos[1] > ymax_)
		{
			newpos = true;
			pos[1] = ymax_;
			vel[1] = 1;
		}
		else if(pos[1] < ymin_)
		{
			newpos = true;
			pos[1] = ymin_;
			vel[1] = 1;
		}
		if(newpos)
		{
			aut.setPosition(pos[0], pos[1]);
			aut.setVelocity(vel[0], vel[1]);
		}
	}


	/**
	 * Decide who-eats-who while making sure that nobody's catch gets missed
	 * due to bad ordering.
	 * @param map - map from prey to the predator that wins out on eating the prey.
	 * @return set of Automata that were consumed.
	 */
	template <typename P>
	std::set<typename P::key_type> collapseConsumptionMap(P & map)
	{

		// initialize the set of consumed and pending to-be-condumed
		std::set<typename P::key_type> consumed;
		std::set<typename P::key_type> toBeConsumed;
		auto prey = typename P::key_type();
		auto pred = typename P::mapped_type();
		auto location = map.begin();

		// while we still have pred-prey pairs to resolve.
		while(not map.empty())
		{
			// get the first iterator
			location = map.begin();

			// while this location is a valid iterator
			while(location != map.end())
			{
				// grab the predator and the prey from the current location in the map
				std::tie(prey, pred) = *location;
				predCounts_[pred] += 1;
				// remove the current pred-prey pair from the map
				map.erase(location);
				// insert the prey into the set of prey to be consumed.
				toBeConsumed.insert(prey);
				// set the location to the the location in the map in which 'pred' is preyed upon
				location = map.find(pred);
			}
			auto apexPredCount = predCounts_[pred] - 1;
			// iterator over the food items in the map and consume them
			for(auto & food:toBeConsumed)
			{
				++apexPredCount;
				pred->eat(*food);
			}
			predCounts_[pred] = apexPredCount;
			// transfer the now-consumed prey to the consumed set.
			consumed.insert(toBeConsumed.begin(), toBeConsumed.end());

			// clear the set of pending prey
			toBeConsumed.clear();
		}
		return consumed;
	}
};
template <size_t N, size_t M>
double Simulation<N, M>::diversityFactor_ = 0.025;
template <size_t N, size_t M>
double Simulation<N, M>::performanceFactor_ = 1.0;
template <size_t N, size_t M>
double Simulation<N, M>::dragCoeff_ = 1.0;

#endif /* EXAMPLES_AUTOMATA_SIMULATION_H_ */
