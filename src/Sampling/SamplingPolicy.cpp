/*
 * SamplingPolicy.cpp
 *
 *  Created on: Jan 12, 2017
 *      Author: tim
 */

#include "SamplingPolicy.h"
#include <cassert>
#include <unordered_map>
#include <stdexcept>
using std::cout;
using std::endl;


unordered_map<string, SamplingPolicy *> SamplingPolicy::active_policies = unordered_map<string, SamplingPolicy *>();

SamplingPolicy::SamplingPolicy(string policy_name) {
	// TODO Auto-generated constructor stub
	this->policy_name = policy_name;
	if(active_policies.count(policy_name))
	{
		throw new std::invalid_argument("[SamplingPolicy::SamplingPolicy()] A sampling policy already owns the requested name.\n");
	}
	active_policies[policy_name] = this;
	is_elitist = false;
	is_rank_based = false;
	pop_bounds[0] = 0;
	pop_bounds[1] = 1;
}

SamplingPolicy::~SamplingPolicy() {
	// TODO Auto-generated destructor stub
	active_policies.erase(policy_name);
}

size_t SamplingPolicy::GetActivePolicyCount()
{
	return active_policies.size();
}
void SamplingPolicy::DisplayActivePolicies(bool verbose)
{
	size_t active_policy_count = active_policies.size();
	cout << "Policy Name\t" << "";
	for(size_t i = 0; i < active_policy_count; ++i)
	{

	}
}
vector<Evolvable *> SamplingPolicy::Sample(vector<Evolvable *> pop)
{
	return pop;
}
void SamplingPolicy::SetPopulationBounds(size_t bmin, size_t bmax)
{
	assert(bmin <= bmax);
	pop_bounds[0] = bmin;
	pop_bounds[1] = bmax;
}
bool SamplingPolicy::IsBounded()
{
	return pop_bounds[1] != 0;
}
bool SamplingPolicy::IsRankBased()
{
	return is_rank_based;
}
bool SamplingPolicy::IsElitest()
{
	return is_elitist;
}

