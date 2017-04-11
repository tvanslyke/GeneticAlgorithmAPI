/*
 * Automoton.h
 *
 *  Created on: Mar 28, 2017
 *      Author: tim
 */

#ifndef EXAMPLES_AUTOMATON_H_
#define EXAMPLES_AUTOMATON_H_
#include <tuple>

#include "../../Evolution/Evolvable.h"
#include "../../MutationPolicies.h"
#include <set>
#include "Vec.h"
#include "PID.h"
#include "Food.h"
#include "NormalDist.h"
#include <cmath>
#include <iostream>
/**
 * Class to simulate a small organism trying to feed itself and not get eaten.
 *
 * I have no idea why I named it Automaton, but the name stuck long enough for me
 * to not want to change all the associated code and variables names (like autIter),
 * so the name is staying...
 *
 * @author Timothy Van Slyke
 */
class Automaton:
		public Evolvable<UniformRandomMutation, StaticChromosome<12>>,
		public Food
{


public:
	/** Default mass. */
	static double defaultMass_;
	/** Density of Automaton instances. */
	static double density_;
	/**
	 * Construct with initial position.
	 * @param x - x coordinate.
	 * @param y - y coordinate.
	 * @param chromosome - chromosome from which parameters will be loaded.
	 */
	Automaton(double x, double y, StaticChromosome<12> chromosome);
	/**
	 * Load parameters from chromosome.
	 */
	void loadFromChromosome();
	/**
	 * Get the velocity.
	 * @return the velocity vector.
	 */
	Vec<double, 2> getVelocity();
	/**
	 * Get a view of the velocity (reference).
	 * @return const reference to the velocity vector.
	 */
	const Vec<double, 2> & viewVelocity();
	/**
	 * Set the velocity.
	 * @param x - the x component.
	 * @param y - the y component.
	 */
	void setVelocity(double x, double y);
	/**
	 * Get the force vector
	 * @return the force vector.
	 */
	Vec<double, 2> getForceVector();
	/**
	 * Resets non-chromosomal parameters to defaults.
	 */
	void setToDefaults();
	/**
	 * Updates the setpoint position based on the goings-on in the automaton's environment.
	 * Update the set point.
	 * @param autBegin - iterator to beginning of list of automata.
	 * @param autEnd - iterator to end of list of automata.
	 * @param foodBegin - iterator to beginning of list of foods.
	 * @param foodEnd - iterator to end of list of foods.
	 */
	template <typename A, typename F>
	void updateSetPoint(A autBegin, A autEnd, F foodBegin, F foodEnd)
	{

		setPointPos_ = {0, 0};
		// ptrs to target food and the most dangerous automaton nearby
		Food * target = nullptr;
		Automaton * avoid = nullptr;

		// decide based on scores
		double avoidScore = 0;
		double pursueScore = 0;
		double candidateScore = 0;

		// temp storage for difference in positions.
		auto diffVec = pos_;
		// temp storage for norm of diffvec
		double norm = 0.0;
		// inspect each automaton
		for(auto autIter = autBegin; autIter != autEnd; ++autIter)
		{

			if((&(*autIter) != this))
			{
				diffVec = (autIter->pos_ - pos_);

				norm = diffVec.norm();
				// if this instance can eat them
				if(autIter->getMass() < mass_)
				{
					// use chromosomal parameters to rank the importance of this guy on our menu.
					candidateScore = autIter->getMass() * pursueWeight_ * pursueDist_(norm) * -1 * (vel_ * autIter->viewVelocity()) ;
					if(candidateScore > pursueScore)
					{
						pursueScore = candidateScore;
						target = static_cast<Food*>(&(*autIter));
					}
				}
				else if(autIter->getMass() > mass_)
				{
					// use chromosomal parameters to rank the importance of running away from this guy.
					candidateScore = autIter->getMass() * avoidWeight_ * avoidDist_(norm) * (vel_ * autIter->viewVelocity());
					if(candidateScore > avoidScore)
					{
						avoidScore = candidateScore;
						avoid = &(*autIter);
					}
				}
			}
		}
		for(auto foodIter = foodBegin; foodIter != foodEnd; ++foodIter)
		{
			diffVec = (foodIter->viewPosition() - pos_);
			norm = diffVec.norm();
			// use chromosomal parameters to rank the importance of this food instance on our menu.
			candidateScore = foodWeight_ * foodIter->getMass() * (foodDist_(norm));
			if(candidateScore > pursueScore)
			{
				pursueScore = candidateScore;
				target = static_cast<Food*>(&(*foodIter));
			}
		}
		// decide if we should chase something or run away from something.
		if(pursueScore < avoidScore)
		{
			auto diffVec = (pos_ - target->viewPosition());
			// run away
			setPointPos_ = pos_ + diffVec / (diffVec * diffVec);
		}
		else
		{
			// chase
			setPointPos_ = target->viewPosition();
		}
	}
	/**
	 * updates position based on the setpoint position, the drag coefficient, and the timestep.
	 * @param timeStep - time step for this update.
	 * @param dragCoeff - drag coefficient.
	 */
	void updatePosition(double timeStep = 1.0, double dragCoeff = 0.0);
	/**
	 * See if this instance can eat the food instance
	 * @param other - food instance.
	 * @return true if this instance is close enough.
	 */
	bool canEat(const Food & other) const;
	/**
	 * See if this instance can eat the Automaton instance
	 * @param other - other Automaton instance.
	 * @return true if this instance is close enough and is bigger than the other.
	 */
	bool canEat(const Automaton & other) const;
	/**
	 * Eat the food instance. (gain mass)
	 * @param other - the food instance.
	 */
	void eat(const Food & other);
	/**
	 * Eat the Automaton instance. (gain mass)
	 * @param other - the other Automaton instance.
	 */
	void eat(const Automaton & other);
	/**
	 * Set the fitness to the given value.
	 * @param fitness - the new fitness.
	 */
	void setFitness(double fitness) noexcept;
	/**
	 * Set the mass to the given value.
	 * @param mass - The new mass.
	 */
	void setMass(double mass) noexcept;
	/**
	 * Get the fitness value of this instance.
	 * @return the fitness of this instance.
	 */
	double getFitness();
protected:




    /** Velocity vector. */
	Vec<double, 2> vel_;
    /** Force direction (radians). */
	double forceDirection_;
    /** Force magnitude. */
	double force_;

	/** PID for force direction. */
	PID<double> headingPID_;
	/** PID for force magnitude. */
	PID<double> forcePID_;
	/** Setpoint position. */
	Vec<double, 2> setPointPos_;

	/** Relative importance of chasing Food. */
	double foodWeight_;
	/** Relative importance of avoiding predators. */
	double avoidWeight_;
	/** Relative importance of chasing other Automata. */
	double pursueWeight_;

	/** Normal distribution for distance of food. */
	NormalDist foodDist_;
	/** Normal distribution for distance of predators. */
	NormalDist avoidDist_;
	/** Normal distribution for distance of automata this instance can eat. */
	NormalDist pursueDist_;

	/** Genetic fitness. */
	double fitness_;
	/**
	 * Add mass to this Automatons total mass.
	 * @param mass - the amount to add.
	 */
	void addMass(const double mass);
};

#endif /* EXAMPLES_AUTOMATON_H_ */
