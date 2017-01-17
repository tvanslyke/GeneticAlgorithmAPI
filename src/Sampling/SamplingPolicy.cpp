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
#include "../Misc/StringTable.h"
using std::cout;
using std::endl;


unordered_map<string, SamplingPolicy *> SamplingPolicy::active_policies = unordered_map<string, SamplingPolicy *>();

vector<string> SamplingPolicy::policy_names = vector<string>();

string boolean_yesno(bool val)
{
	if(val)
	{
		return string("Yes");
	}
	else
	{
		return string("No");
	}
}




SamplingPolicy::SamplingPolicy(string policy_name, bool is_elitist, bool is_rank_based, size_t lb, size_t ub) {
	// TODO Auto-generated constructor stub
	this->policy_name = policy_name;
	if(active_policies.count(policy_name))
	{
		throw new std::invalid_argument("[SamplingPolicy::SamplingPolicy()] A sampling policy already owns the requested name.\n");
	}
	active_policies[policy_name] = this;
	policy_names.push_back(policy_name);
	this->is_elitist = is_elitist;
	this->is_rank_based = is_rank_based;
	pop_bounds[0] = lb;
	pop_bounds[1] = ub;
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
	StringTable table = StringTable(4);
	size_t active_policy_count = active_policies.size();
	string this_entry;
	string this_name;
	SamplingPolicy * this_policy;
	string heading = "Name Elitest Rank-Based Bounded";
	table.SetHeading(heading);
	for(size_t i = 0; i < active_policy_count; ++i)
	{
		this_name = policy_names[i];
		this_policy = active_policies[this_name];
		this_entry = this_name + " ";
		this_entry += boolean_yesno(this_policy->is_elitist)+ " ";
		this_entry += boolean_yesno(this_policy->is_rank_based)+ " ";
		this_entry += boolean_yesno(this_policy->IsBounded())+ " ";
		table.Append(this_entry);
	}
	table.Display();
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

