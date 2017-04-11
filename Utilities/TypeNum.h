/*
 * TypeNum.h
 *
 *  Created on: Mar 8, 2017
 *      Author: tim
 */

#ifndef UTILITIES_TYPENUM_H_
#define UTILITIES_TYPENUM_H_
#include <cstddef>
/**
 * Simple class for assigning a type a unique number at compile-time.
 *
 * This is simpler and less costly (and less flexible) than trying to make
 * use of the typeid() function.  It also guarantees a unique id, unlike typeid.
 */
class TypeNum
{
public:
	/**
	 * Get the unique ID for type T.
	 * @return the ID of type T.
	 */
	template <typename T>
	static constexpr const size_t getNum() noexcept
	{
		return Tnum<T>::tnum_;
	}
	/**
	 * Assign the unique ID for type T.
	 * @return the ID of type T.
	 */
	template <typename T>
	static constexpr const size_t assignNum() noexcept
	{
		return (TypeNum::tnum_ = TypeNum::tnum_ + 1);
	}
private:
	/** No public constructors. */
	TypeNum();
	/** The smallest, non-zero type ID number not yet assigned to a type. */
	static size_t tnum_;

	/**
	 * Inner class for ensuring that a particular type
	 */
	template <typename T>
	class Tnum
	{
	public:
		/** The unique ID assigned to this type. */
		static const size_t tnum_;
	};
};

template <typename T>
const size_t TypeNum::Tnum<T>::tnum_ = TypeNum::assignNum<T>();
#endif /* UTILITIES_TYPENUM_H_ */
