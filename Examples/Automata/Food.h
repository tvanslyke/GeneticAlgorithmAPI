/*
 * Food.h
 *
 *  Created on: Mar 28, 2017
 *      Author: tim
 */

#ifndef EXAMPLES_FOOD_H_
#define EXAMPLES_FOOD_H_
#include "Vec.h"
#include <string>
/**
 * Simple food class that can be eaten by Automaton instances.  Foods do not move,
 * are smaller than automata, and cannot eat other Foods.
 *
 * @author Timothy Van Slyke
 */
class Food {

public:
	friend class Automaton;
	/**
	 * Construct from an x and y coordinate
	 * @param x - the x coordinate
	 * @param y - the y coordinate
	 * @param mass - the mass
	 */
	Food(double x, double y, double mass = defaultMass_);
	/**
	 * Set the position.
	 * @param x - the new x coordinate.
	 * @param y - the new y coordinate.
	 */
	void setPosition(double x, double y) noexcept;
	/**
	 * Compares objects according to their mass.
	 * @param other - other Food instance
	 * @return true if other weighs more.
	 */
	bool operator<(const Food & other);
	/**
	 * Get the position vector.
	 * @return the position vector.
	 */
	Vec<double, 2> getPosition();
	/**
	 * Get a const ref to the position vector.
	 * @return a const ref to the position vector.
	 */
	const Vec<double, 2> & viewPosition();
	/**
	 * Get the mass of the food object.
	 * @return the mass of the food object.
	 */
	double getMass() const noexcept;

	/**
	 * Get the radius of the food object.
	 * @return the radius of the Food object.
	 */
	double getRadius() const noexcept;
	/**
	 * Write the position and radius of the food object to an output
	 * file stream in binary format.
	 * @param out - the output file stream.
	 */
	void pack(std::ostream & out) const;

protected:

	/** default mass of all food instances*/
	static double defaultMass_;
	/** mass/area density of all Food instances */
	static double density_;
	/** mass of the object. */
	double mass_;
	/** radius of the object*/
	double radius_;

	/** location of the object */
	Vec<double, 2> pos_;
};

#endif /* EXAMPLES_FOOD_H_ */
