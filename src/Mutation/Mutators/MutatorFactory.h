/*
 * MutatorFactory.h
 *
 *  Created on: Jan 16, 2017
 *      Author: tim
 */

#ifndef MUTATION_MUTATORS_MUTATORFACTORY_H_
#define MUTATION_MUTATORS_MUTATORFACTORY_H_

#include "Mutator.h"
#include "BitflipMutator.h"
#include "IncrMutator.h"
#include "RandIncrMutator.h"
#include "RandMutator.h"
#include "RelIncrMutator.h"
#include "RelRandIncrMutator.h"
#include "MutatorKey.h"
#include <unordered_map>
#include <vector>
#include <iostream>


using std::unordered_map;
using std::cout;
using std::endl;


const size_t MUT_BITFLIP =        0;  // no constructor args
const size_t MUT_RAND =           1;  // lower and upper bound args of type T
const size_t MUT_INCR =           2;  // incr arg of type T
const size_t MUT_RAND_INCR =      3;  // lower and upper bound args of type T
const size_t MUT_REL_INCR =       4;  // proportion argument of type FPType
const size_t MUT_REL_RAND_INCR =  5;  // proportion argument of type FPType

template <typename T, typename FPType>
class MutatorFactory {
private:
	MutatorFactory();
	static unordered_map<Mutator<T, FPType> *, size_t> mut_counts;
	static unordered_map<MutatorKey<T, FPType>, Mutator<T, FPType> *> lookup;
	static Mutator<T, FPType> * MakeMutator(size_t mut_select, T lb, T ub, FPType prop)
	{
		switch(mut_select)
		{
		case MUT_BITFLIP:
			return new BitflipMutator<T>();
			break;
		case MUT_RAND:
			return new RandMutator<T>(lb, ub);
			break;
		case MUT_INCR:
			return new IncrMutator<T>(lb);
			break;
		case MUT_RAND_INCR:
			return new RandIncrMutator<T>(lb, ub);
			break;
		case MUT_REL_INCR:
			return new RelIncrMutator<T, FPType>(prop);
			break;
		case MUT_REL_RAND_INCR:
			return new RelIncrMutator<T, FPType>(prop);
			break;
		default:
			return new RandMutator<T>(lb, ub);
		}
	}
public:
	virtual ~MutatorFactory()
	{
		;
	}
	static Mutator<T, FPType> * GetMutator(size_t mut_select = 0, T lb = 0, T ub = 0, FPType prop = .5)
	{
		MutatorKey<T, FPType> key = MutatorKey<T, FPType>(mut_select, lb, ub, prop);
		if(lookup.count(key) and (mut_counts[lookup[key]] != 0))
		{
			mut_counts[lookup[key]] += 1;
			return lookup[key];
		}
		else
		{
			Mutator<T, FPType> * mut = MakeMutator(mut_select, lb, ub, prop);
			mut_counts[mut] = 1;
			lookup[key] = mut;
			return mut;
		}
	}
	static void Notify(Mutator<T, FPType> * mut)
	{
		if(not mut_counts.count(mut))
		{
			cout << "[MutatorFactor::Notify] Notified of an unknown Mutator!  Potential memory leak! [Warning]\n" << endl;
		}
		else
		{
			mut_counts[mut] -= 1;
			if(mut_counts[mut] == 0)
			{
				delete mut;
			}
		}
	}

};

#endif /* MUTATION_MUTATORS_MUTATORFACTORY_H_ */
