/*
 * RandIncrMutator.h
 *
 *  Created on: Feb 5, 2017
 *      Author: tim
 */

#ifndef MUTATION_MUTATORS_RANDINCRMUTATOR_H_
#define MUTATION_MUTATORS_RANDINCRMUTATOR_H_

#include "RandomMutator.h"
#include <type_traits>

template <typename T, typename Tsigned = typename std::make_signed<T>::type>
class RandIncrMutator: public RandomMutator<Tsigned> {

protected:
	static const size_t mutatorID;
public:
	virtual ~RandIncrMutator()
	{

	}
	using RandomMutator<Tsigned>::RandomMutator;

	void mutate(boost::any & data)
	{
		this->update();
		boost::any_cast<T&>(data) += this->rand_;
	}
	virtual size_t getID() const
	{
		return RandIncrMutator<T, Tsigned>::mutatorID;
	}
};

template <typename T, typename Tsigned>
const size_t RandIncrMutator<T, Tsigned>::mutatorID = MutatorDiagnostics::assignID();

#endif /* MUTATION_MUTATORS_RANDINCRMUTATOR_H_ */
