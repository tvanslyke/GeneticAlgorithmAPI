/*
 * Vec.h
 *
 *  Created on: Mar 28, 2017
 *      Author: tim
 */

#ifndef EXAMPLES_AUTOMATA_VEC_H_
#define EXAMPLES_AUTOMATA_VEC_H_
#include <array>
#include <cmath>
#include <iostream>
/**
 * Simple vector (in the mathematical, linear-algebra sense) class for making kinematic
 * calculations easier to write and follow.
 *
 * @author Timothy Van Slyke
 */
template <typename T, size_t N>
class Vec {
public:
	using value_type = typename std::array<T, N>::value_type;
	using size_type = typename std::array<T, N>::size_type;
	using difference_type = typename std::array<T, N>::difference_type;
	using reference = typename std::array<T, N>::reference;
	using const_reference = typename std::array<T, N>::const_reference;
	using pointer = typename std::array<T, N>::pointer;
	using const_pointer = typename std::array<T, N>::const_pointer;
	using iterator = typename std::array<T, N>::iterator;
	using const_iterator = typename std::array<T, N>::const_iterator;
	using reverse_iterator = typename std::array<T, N>::reverse_iterator;
	using const_reverse_iterator = typename std::array<T, N>::const_reverse_iterator;

	/**
	 * Default ctor.
	 */
	Vec()
	{
		vec_ = std::array<T, N>();
	}
	/**
	 * Construct from initializer list/
	 * @param init_list - initializer list to copy.
	 */
	Vec(const std::initializer_list<T> & init_list)
	{
		vec_ = std::array<T, N>();
		auto iter = init_list.begin();
		for(auto i = 0u; i < N; ++i)
		{
			vec_[i] = *iter;
			++iter;
		}
	}
	/**
	 * Index the vector.
	 * @param i - index to get.
	 * @return const reference to stored value at the index.
	 */
	constexpr const_reference operator[](size_type i) const noexcept
	{
		return vec_[i];
	}
	/**
	 * Index the vector.
	 * @param i - index to get.
	 * @return reference to stored value at the index.
	 */
	reference operator[](size_type i) noexcept
	{
		return vec_[i];
	}
	/**
	 *
	 * @param init_list - new values of the internal array.
	 * @return
	 */
	Vec<T, N> & operator=(const std::initializer_list<T> & init_list)
	{
		auto iter = init_list.begin();
		for(auto i = 0u; i < N; ++i)
		{
			vec_[i] = *iter;
			++iter;
		}
		return *this;
	}
	/**
	 * Copy assignment.
	 * @param other - reference to other vector.
	 * @return reference to this instance.
	 */
	Vec<T, N> & operator=(const Vec<T, N> & other)
	{
		for(auto i = 0u; i < N; ++i)
		{
			vec_[i] = other[i];
		}
		return *this;
	}
	/**
	 * Add two vectors.
	 * @param other - reference to other vector.
	 * @return Superposition of added vectors.
	 */
	Vec<T, N> operator+(const Vec<T, N> & other) const
	{
		Vec<T, N> ret;
		for(auto i = 0u; i < N; ++i)
		{
			ret[i] = vec_[i] + other[i];
		}
		return ret;
	}
	/**
	 * Add-assign vector.
	 * @param other - reference to other vector.
	 * @return reference to this instance.
	 */
	Vec<T, N> & operator+=(const Vec<T, N> & other)
	{
		for(auto i = 0u; i < N; ++i)
		{
			vec_[i] += other[i];
		}
		return *this;
	}
	/**
	 * Subtract two vectors.
	 * @param other - reference to other vector.
	 * @return The difference vector.
	 */
	Vec<T, N> operator-(const Vec<T, N> & other) const
	{
		Vec<T, N> ret;
		for(auto i = 0u; i < N; ++i)
		{
			ret[i] = vec_[i] - other[i];
		}
		return ret;
	}
	/**
	 * Subtract-assign vector.
	 * @param other - reference to other vector.
	 * @return reference to this instance.
	 */
	Vec<T, N> & operator-=(const Vec<T, N> & other)
	{
		for(auto i = 0u; i < N; ++i)
		{
			vec_[i] -= other[i];
		}
		return *this;
	}
	/**
	 * Vector dot-product.
	 * @param other - other vector in the dot product.
	 * @return the dot product of the vectors.
	 */
	value_type operator*(const Vec<T, N> & other) const
	{
		T ret = T(0);
		for(auto i = 0u; i < N; ++i)
		{
			ret += vec_[i] * other[i];
		}
		return ret;
	}

	/**
	 * Scale the vector.
	 * @param scalar - Scalar to multiply by.
	 * @return new vector scaled by 'scalar'.
	 */
	Vec<T, N> operator*(const T & scalar) const
	{
		Vec<T, N> ret;
		for(auto i = 0u; i < N; ++i)
		{
			ret[i] = vec_[i] * scalar;
		}
		return ret;
	}

	/**
	 * Multiply-assign scalar.
	 * @param scalar - scalar to muliply by.
	 * @return reference to this instance.
	 */
	Vec<T, N> & operator*=(const T & scalar)
	{
		for(auto i = 0u; i < N; ++i)
		{
			vec_[i] *= scalar;
		}
		return *this;
	}

	/**
	 * Vector division by scalar.
	 * @param scalar - scalar to divide by.
	 * @return new vector divided elementwise by 'scalar'
	 */
	Vec<T, N> operator/(const T & scalar) const
	{
		Vec<T, N> ret;
		for(auto i = 0u; i < N; ++i)
		{
			ret[i] = vec_[i] / scalar;
		}
		return ret;
	}
	/**
	 * Divide-assign scalar.
	 * @param scalar - scalar to divide by.
	 * @return reference to this instance.
	 */
	Vec<T, N> & operator/=(const T & scalar)
	{
		for(auto i = 0u; i < N; ++i)
		{
			vec_[i] /= scalar;
		}
		return *this;
	}

	/**
	 * return angle between two vectors.
	 * @param other - vector angle is measured from
	 * @return the angle in radians.
	 */
	typename std::enable_if<std::is_floating_point<T>::value, T>::type
	angleBetween(const Vec<T, N> & other)
	{
		return acos(((*this) * other) / sqrt(((*this) * (*this)) * (other * other)));
	}
	/**
	 * Get the norm of the vector.
	 * @return the norm of the vector.
	 */
	typename std::enable_if<std::is_floating_point<T>::value, T>::type
	norm() const
	{
		return sqrt((*this) * (*this));
	}


private:
	std::array<T, N> vec_;
};


#endif /* EXAMPLES_AUTOMATA_VEC_H_ */
