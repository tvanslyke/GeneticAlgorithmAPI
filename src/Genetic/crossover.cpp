/*
 * crossover.cpp
 *
 *  Created on: Jan 11, 2017
 *      Author: tim
 */



#include "crossover.h"
#include <cassert>
#include "../Random/random_numbers.h"
#include <unordered_set>
#include <algorithm>



void n_point_in_place(Chromosome & c1, Chromosome & c2, size_t num_break_points)
{

	assert(c1.genes.size() == c2.genes.size());
	size_t num_genes = c1.genes.size();
	if(num_genes <= num_break_points)
	{
		cout << "[crossover::n_point_new_child()] Warning: Number of chromosome segments exceeds number of genes." << endl <<
				"Switching to uniform crossover instead." << endl;
		uniform_in_place(c1, c2, .5);
	}
	num_break_points += (num_break_points == 0);

	if(num_break_points == 1)
	{
		size_t index = rng_range<size_t>(0, num_break_points + 1);
		swap_ranges(c1.genes.begin() + index, c1.genes.end(), c2.genes.begin() + index);
	}
	else
	{
		vector<size_t> breakpoints = rng_range_sample_unq<size_t>(num_break_points, 0, num_genes);
		std::sort(breakpoints.begin(), breakpoints.end());
		if(num_genes & 1)
		{
			swap_ranges(c1.genes.begin() + breakpoints[num_break_points - 1], c1.genes.end(), c2.genes.begin() + breakpoints[num_break_points - 1]);
			--num_break_points;
		}
		for(size_t i = 0; i < num_break_points; i += 2)
		{
			swap_ranges(c1.genes.begin() + breakpoints[i], c1.genes.begin() + breakpoints[i + 1], c2.genes.begin() + breakpoints[i]);
		}
	}
}
Chromosome n_point_new_child(Chromosome & c1, Chromosome & c2, size_t num_break_points)
{
	assert(c1.genes.size() == c2.genes.size());
	size_t num_genes = c1.genes.size();

	// gotta be at least 1
	num_break_points += (num_break_points == 0);

	// the provided parameters are invalid.  Print a warning and use uniform crossover instead.
	if(num_genes <= num_break_points)
	{
		cout << "[crossover::n_point_new_child()] Warning: Number of chromosome segments exceeds number of genes." << endl <<
				"Switching to uniform crossover instead." << endl;
		return uniform_new_child(c1, c2, .5);
	}


	Chromosome child = Chromosome(num_genes);
	if(num_break_points == 1)
	{
		size_t index = rng_range<size_t>(0, num_break_points + 1);
		if(rand() & 1)
		{
			child.CopyGenomeSegmentFrom(c1, 0, index);
			child.CopyGenomeSegmentFrom(c2, index, num_genes);
		}
		else
		{
			child.CopyGenomeSegmentFrom(c2, 0, index);
			child.CopyGenomeSegmentFrom(c1, index, num_genes);
		}
	}
	else
	{
		bool p_select = rand() & 1;
		vector<size_t> breakpoints = rng_range_sample_unq<size_t>(num_break_points, 0, num_genes);
		std::sort(breakpoints.begin(), breakpoints.end());
		size_t i = 0;

		child.CopyGenomeSegmentFrom(p_select ? c1 : c2, breakpoints[i], breakpoints[i + 1]);
		p_select = !p_select;

		for(++i; i < num_break_points - 1; ++i)
		{
			child.CopyGenomeSegmentFrom(p_select ? c1 : c2, breakpoints[i], breakpoints[i + 1]);
			p_select = !p_select;
		}

		child.CopyGenomeSegmentFrom(p_select ? c1 : c2, breakpoints[i], breakpoints[i + 1]);
		p_select = !p_select;
	}
	return child;
}

void uniform_in_place(Chromosome & c1, Chromosome & c2, float prob)
{
	assert(c1.genes.size() == c2.genes.size());
	size_t num_genes = c1.genes.size();
	// optimize for default case
	if(prob == 0.5)
	{
		vector<bool> select = rand_bool_vector(num_genes);
		for(size_t i = 0; i < num_genes; ++i)
		{
			if(select[i])
			{
				Gene::Swap(c1.genes[i], c2.genes[i]);
			}
		}
	}
	else
	{
		// approximate value to nearest int for faster comparisons
		int threshhold = (int)(RAND_MAX * prob);
		for(size_t i = 0; i < num_genes; ++i)
		{
			if(rand() > threshhold)
			{
				Gene::Swap(c1.genes[i], c2.genes[i]);
			}
		}
	}
}

Chromosome uniform_new_child(Chromosome & c1, Chromosome & c2, float prob)
{
	assert(c1.genes.size() == c2.genes.size());

	size_t num_genes = c1.genes.size();
	Chromosome child = Chromosome(num_genes);
	// optimize for default case
	if(prob == 0.5)
	{
		vector<bool> select = rand_bool_vector(num_genes);
		for(size_t i = 0; i < num_genes; ++i)
		{
			if(select[i])
			{
				child.genes[i] = c1.genes[i].Copy();
			}
			else
			{
				child.genes[i] = c2.genes[i].Copy();
			}
		}
	}
	else
	{
		// approximate value to nearest int for faster comparisons
		int threshhold = (int)(RAND_MAX * prob);
		for(size_t i = 0; i < num_genes; ++i)
		{
			if(rand() > threshhold)
			{
				child.genes[i] = c1.genes[i].Copy();
			}
			else
			{
				child.genes[i] = c2.genes[i].Copy();
			}
		}
	}
	return child;
}
