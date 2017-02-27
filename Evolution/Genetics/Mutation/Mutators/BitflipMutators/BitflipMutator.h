/*
 * BitflipMutator.h
 *
 *  Created on: Feb 10, 2017
 *      Author: tim
 */

#ifndef MUTATION_MUTATORS_BITFLIPMUTATOR_H_
#define MUTATION_MUTATORS_BITFLIPMUTATOR_H_

#include "../Mutator.h"

/*
template <typename T, typename U = T>
class BitflipMutator;
*/
#include "../../../../../Random/RandomNumbers.h"

#include "../../../../../Utilities/Endian.h"


template <typename T>
class BitflipMutator: public Mutator {
private:

protected:

public:
	BitflipMutator()
	{
		static_assert(std::is_integral<T>::value, "[Error] BitflipMutator is valid only for integral types.");
	}
	virtual ~BitflipMutator()
	{

	}
	virtual void mutate(boost::any &)
	{

	}

	virtual size_t getID() const
	{
		return BitflipMutator<T>::mutatorID;
	}
	static const size_t mutatorID;
};

template <typename T>
const size_t BitflipMutator<T>::mutatorID = MutatorDiagnostics::assignID();

/*
template <typename T>
class BitflipMutator<T, typename std::enable_if<!std::is_integral<T>::value, T>::type>: public Mutator {};
*/
#endif /* MUTATION_MUTATORS_BITFLIPMUTATOR_H_ */
