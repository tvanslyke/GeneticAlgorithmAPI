/*
 * Mutator.h
 *
 *  Created on: Jan 14, 2017
 *      Author: tim
 */

#ifndef MUTATABLES_MUTATOR_H_
#define MUTATABLES_MUTATOR_H_

#include <type_traits>

/*
 *   Classes in the Mutator lineage exist to help
 *
 *   Any mutators shall inherit from this class.  All inheriting classes shall
 *   implement MutateData(T & data) and MutateData(T * data), except in cases
 *   where the inheriting class is itself an interface or abstract class.
 *
 *   Standard mutatables use flags to se
 */

template <typename T, typename FPType = double>
class Mutator
{
public:
	Mutator()
	{
		static_assert(std::is_floating_point<FPType>::value,
				      "[Mutator] Template argument 2 must be a float, double, or long double.\n");
	}
	virtual ~Mutator()
	{
		;
	}
	virtual void MutateData(T & data)
	{
		;
	}
	virtual void MutateData(T * data)
	{
		;
	}
	virtual size_t self_hash()
	{
		return 0;
	}
};


#endif /* MUTATABLES_MUTATOR_H_ */
