/*
 * MutatorKey.h
 *
 *  Created on: Jan 17, 2017
 *      Author: tim
 */

#ifndef MUTATION_MUTATORS_MUTATORKEY_H_
#define MUTATION_MUTATORS_MUTATORKEY_H_

#include <functional>
#include <cstdlib>



template <typename T, typename FPType>
class MutatorKey
{
private:
	size_t mut_id;
	T lb;
	T ub;
	FPType prop;

public:
	MutatorKey(size_t mut_id, T lb, T ub, FPType prop)
	{
		this->mut_id = mut_id;
		this->lb = lb;
		this->ub = ub;
		this->prop = prop;
	}
	size_t self_hash() const
	{
		size_t s_hash = std::hash<size_t>(mut_id);
		s_hash += std::hash<T>(lb);
		s_hash += std::hash<T>(ub);
		s_hash += std::hash<FPType>(prop);
		return s_hash;

	}
	bool operator ==(const MutatorKey<T, FPType> & other)
	{
		return (this->mut_id == other.mut_id) &&
			   (this->lb == other.lb) &&
			   (this->ub == other.ub) &&
			   (this->prop == other.prop);
	}
};




namespace std
{
    template <typename T, typename FPType>
	struct hash<MutatorKey<T, FPType> >
    {
    	size_t operator()(const MutatorKey<T, FPType> mk) const
		{
    		return mk.self_hash();
		}
    };
}



















#endif /* MUTATION_MUTATORS_MUTATORKEY_H_ */
