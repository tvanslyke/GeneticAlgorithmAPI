/*
 * EvolutionPolicy.h
 *
 *  Created on: Jan 12, 2017
 *      Author: tim
 */

#ifndef SAMPLINGPOLICY_H_
#define SAMPLINGPOLICY_H_

#include <cstdlib>
#include <vector>
#include <unordered_map>
#include "../Evolvables/Evolvable.h"
#include <string>
using std::string;

/*
 *  This class is meant to be used as an interface.  Classes inheriting from
 *  this structure shall handle generation-to-generation transitions by selecting
 *  members of the population with the Sample() method.
 */

class EvolutionPolicy {
private:
	// for lookup
	static unordered_map<string, EvolutionPolicy *> active_policies;
	static vector<string> policy_names;
	// unique name
protected:
	string policy_name;

	// elitist policies guarantee that some number of the fittest members
	// of a population shall be selected in the sampling process prior to
	// selecting other population members.
	bool is_elitist;
	// rank based samples do not depend on relative fitnesses
	bool is_rank_based;

	/*
	 * boundaries/limits on population size.
	 * EvolutionPolicy::Sample() shall return a vector<Evolvable *> with
	 * pop_bounds[0] <= size <= pop_bounds[1].
	 *
	 * if pop_bounds[0] == pop_bounds[1] == 0, then the population is
	 * considered unbounded.
	 */
	size_t pop_bounds[2];
public:
	EvolutionPolicy(string policy_name, bool is_elitist = false, bool is_rank_based = false, size_t lb = 0, size_t ub = 0);
	virtual ~EvolutionPolicy();
	virtual void MakeNextGeneration(vector<Evolvable *> & pop);
	static size_t GetActivePolicyCount();
	static void DisplayActivePolicies(bool verbose = false);
	void SetPopulationBounds(size_t bmin, size_t bmax);
	bool IsBounded();
	bool IsRankBased();
	bool IsElitest();
};

#endif /* SAMPLINGPOLICY_H_ */









