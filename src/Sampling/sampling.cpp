/*
 * sampling.cpp
 *
 *  Created on: Jan 12, 2017
 *      Author: tim
 */


#include "sampling.h"
#include "../Random/random_numbers.h"
#include "../Algorithms/searching.h"
#include <unordered_map>

using std::unordered_map;

double sum_fitness(const vector<Evolvable *> & pop)
{
	double total = 0;
	size_t pop_size = pop.size();
	for(size_t i = 0; i < pop_size; ++i)
	{
		total += pop[i]->GetFitness();
	}
	return total;
}

vector<int> reduce_pop(vector<Evolvable *> & pop)
{
	// rescale fitnesses such that [0, total_fitness] --> [0, RAND_MAX], omitting all zeros.
	// any evolvables resulting in zero fitness will be moved to the back of the vector
	size_t pop_size = pop.size();
	vector<int> int_fits = vector<int>(pop_size);
	double total = sum_fitness(pop);
	int this_fitness;
	size_t non_zero_count = pop_size;
	for(size_t i = 0; i < non_zero_count; ++i)
	{
		this_fitness = (int)((RAND_MAX * pop[i]->GetFitness()) / total);
		if(this_fitness == 0)
		{
			--non_zero_count;
			std::swap(pop[i], pop[non_zero_count]);
			--i;
		}
		else
		{
			int_fits[i] = this_fitness;
		}
	}
	int_fits.resize(non_zero_count);
	return int_fits;
}

template <typename T>
void accumulate(vector<T> & fits)
{
	size_t len = fits.size();
	for(size_t i = 1; i < len; ++i)
	{
		fits[i] += fits[i - 1];
	}
}

vector<Evolvable *> stochastic_acceptance(vector<Evolvable *> pop, const size_t & new_pop_size)
{
	vector<int> int_fits = reduce_pop(pop);
	size_t count = int_fits.size();
	vector<Evolvable *> new_pop = vector<Evolvable *>(new_pop_size);
	size_t index = 0;
	size_t select;
	while(index < new_pop_size)
	{
		select = rng_range<size_t>(0, count);
		if(int_fits[select] > rand())
		{
			new_pop[index] = pop[select];
			++index;
		}
	}
	return new_pop;
}
bool desc_compare(const Evolvable * a, const Evolvable * b)
{
	return (*a) >= (*b);
}

vector<Evolvable *> stochastic_universal(vector<Evolvable *> pop, size_t & new_pop_size)
{
	vector<Evolvable *> new_pop = vector<Evolvable *>(new_pop_size);
	double total = sum_fitness(pop);
	std::sort(pop.begin(), pop.end(), desc_compare);
	double cumsum = pop[0]->GetFitness();
	double step = total / new_pop_size;
	double pos = rng_range<double>(0, step);
	size_t index = 0;
	for(size_t i = 0; i < new_pop_size; ++i)
	{
		while(cumsum < pos)
		{
			++index;
			cumsum += pop[index]->GetFitness();
		}
		new_pop[i] = pop[index];
	}
	return new_pop;
}


vector<Evolvable *> fitness_proportionate(vector<Evolvable *> pop, const size_t & new_pop_size)
{

	// initialize the vector to be returned and sort in descending order
	vector<Evolvable *> new_pop = vector<Evolvable *>(new_pop_size);
	std::sort(pop.begin(), pop.end(), desc_compare);

	// remove all zero-fitness members of the vector and scale fitness so that they sum to RAND_MAX
	vector<int> int_fits = reduce_pop(pop);

	// replace each fitness with the cumulative sum of the preceding fitness.
	// the last value should be RAND_MAX - (largest fitness)
	accumulate<int>(int_fits);
	vector<int>::iterator lower_lim = int_fits.begin();
	vector<int>::iterator upper_lim = int_fits.end();
	size_t index = 0;

	vector<int> sample_fits =  simple_random_vector<int>(new_pop_size);
	std::sort(sample_fits.begin(), sample_fits.end());
	vector<int>::iterator v_ind;
	while(index < new_pop_size)
	{
		v_ind = binary_search_asc(lower_lim, upper_lim, sample_fits[index]);
		new_pop[index] = pop[v_ind - sample_fits.begin()];
		lower_lim = v_ind;
		++index;
	}
	return new_pop;
}





