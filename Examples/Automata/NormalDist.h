/*
 * NormalDist.h
 *
 *  Created on: Apr 5, 2017
 *      Author: tim
 */

#ifndef EXAMPLES_AUTOMATA_NORMALDIST_H_
#define EXAMPLES_AUTOMATA_NORMALDIST_H_


/**
 * Class representing a normal distribution centered at zero.
 *
 * @author Timothy Van Slyke
 */
class NormalDist
{

public:
	/** Default constructor. */
	NormalDist();
	/** Construct with particular sigma. */
	NormalDist(double sigma);
	/** Construct with particular sigma. */
	void setSigma(double sigma) noexcept;
	/**
	 * Evaluate the pdf of the normal distribution with coordinate 'dist'.
	 * @param dist - distance from center of the normal distribution.
	 * @return the pdf evaluated at 'dist'
	 */
	double operator()(double dist) const;
private:
	/**
	 * Value of (2 * sigma) ^ 2 instead of sigma.  Avoids repeated calculation
	 * of the same value.
	 */
	double twoSigmaSqrd_;
};

#endif /* EXAMPLES_AUTOMATA_NORMALDIST_H_ */
