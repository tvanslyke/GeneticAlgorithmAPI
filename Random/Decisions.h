/*
 * Decisions.h
 *
 *  Created on: Feb 27, 2017
 *      Author: tim
 */

#ifndef RANDOM_DECISIONS_H_
#define RANDOM_DECISIONS_H_
#include <cstdint>

#include <functional>
namespace rng {
/**
 * Class for making binomial decisions with a given probability.
 *
 * @author Timothy Van Slyke
 */
class Decisions {
private:
	uint_fast64_t prob_;
public:
	Decisions(double prob, double total = 1.0);
	Decisions();
	virtual ~Decisions();
	bool next();
	bool decide();
	void setProbability(double prob, double total = 1.0);
	std::function<bool()> generator();
	std::function<bool()> generator(double prob, double total = 1.0);
	static bool equalChanceDecision();
	static const uint_fast64_t & maxm;
	static const uint_fast64_t & minm;
};

} /* namespace rng */

#endif /* RANDOM_DECISIONS_H_ */
