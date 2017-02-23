/*
 * more_type_traits.h
 *
 *  Created on: Feb 19, 2017
 *      Author: tim
 */

#ifndef UTILITIES_MORE_TYPE_TRAITS_H_
#define UTILITIES_MORE_TYPE_TRAITS_H_

#include <type_traits>

namespace mtt{








/**
 *  all_same:
 *		all_same<Types...>::value == true   iff Types... are all the same type.
 */
template <typename T, typename ... U>
class all_same
{
public:
	static const bool value;
	typedef bool value_type;
	typedef T type;
};
template <typename T, typename ... U>
const bool all_same<T, U...>::value = all_same<U...>::value and std::is_same<T, typename all_same<U...>::type>::value;

template <typename T, typename U>
class all_same<T, U>
{
public:
	static const bool value;
	typedef bool value_type;
	typedef U type;
};
template <typename T, typename U>
const bool all_same<T, U>::value = std::is_same<T, U>::value;

template <typename T>
class all_same<T>
{
public:
	static const bool value;
	typedef bool value_type;
	typedef T type;
};
template <typename T>
const bool all_same<T>::value = true;



/**
 *  is_one_of:
 *		is_one_of<T, Types...>::value == true   iff T is equivalent to one of Types...
 */

template <typename T, typename U, typename ... V>
class is_one_of
{
public:
	static const bool value;
	typedef bool value_type;
	typedef T type;
};


template <typename T, typename U>
class is_one_of<T, U>
{
public:
	static const bool value;
	typedef bool value_type;
	typedef T type;
};

template <typename T, typename U>
const bool is_one_of<T, U>::value = std::is_same<T, U>::value;
template <typename T, typename U, typename ... V>
const bool is_one_of<T, U, V...>::value = std::is_same<T, U>::value or is_one_of<T, V...>::value;



/**
 * Linked List of variadic template parameter pack types.
 */

template <typename T, typename ... Types>
class type_list
{
public:

	typedef T type;
	typedef type_list<Types...> sub_list;
	static const size_t length;
	template <size_t N>
	class next:public type_list<Types...>
	{

	};
};
template <typename T>
class type_list<T>
{
public:
	typedef T type;
	static const size_t length;
};
template <typename T>
const size_t type_list<T>::length = 1;

template <typename T, typename ... Types>
const size_t type_list<T, Types...>::length = sizeof...(Types) + 1;




template <typename T, typename ... Types>
class get
{
public:
	typedef typename  get<Types...>::type  type;
};
template <typename T>
class get<T>
{
public:
	typedef T type;
};


template <size_t N, typename TList>
class list_get
{
public:
	typedef typename list_get<N - 1, typename TList::sub_list>::type type;
};


template <typename TList>
class list_get<0, TList>
{
public:
	typedef typename TList::type type;
};



template <typename T, class P>
class use_if
{
	typedef T type;
};










} /* namespace mtt */
#endif /* UTILITIES_MORE_TYPE_TRAITS_H_ */
