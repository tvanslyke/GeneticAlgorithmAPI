/*
 * StaticChromosome.h
 *
 *  Created on: Apr 6, 2017
 *      Author: tim
 */

#ifndef EVOLUTION_GENETICS_STATICCHROMOSOME_H_
#define EVOLUTION_GENETICS_STATICCHROMOSOME_H_


#include <array>
#include "DynamicChromosome.h"


/**
 * Class for containing an ordered sequence of Genes with a compile-time size.
 *
 * This class is suitable for most optimization problems and inherently provides
 * some minor optimizations over the DynamicChromosome option (vague cache locality
 * and *some* compile-time pre-computation).
 *
 * Both chromosome classes (StaticChromosome and DynamicChromosome) provide little
 * abstraction over std::array and std::vector for the time being, but will see expansion
 * in the future.
 *
 * @author Timothy Van Slyke
 */
template <size_t N>
class StaticChromosome
{
private:
	/** Const-sized storage of sequential Gene instances. */
	std::array<Gene, N> genes_;
public:

	using value_type = typename std::array<Gene, N>::value_type;
	using size_type = typename std::array<Gene, N>::size_type;
	using difference_type = typename std::array<Gene, N>::difference_type;
	using reference = typename std::array<Gene, N>::reference;
	using const_reference = typename std::array<Gene, N>::const_reference;
	using pointer = typename std::array<Gene, N>::pointer;
	using const_pointer = typename std::array<Gene, N>::const_pointer;
	using iterator = typename std::array<Gene, N>::iterator;
	using const_iterator = typename std::array<Gene, N>::const_iterator;
	using reverse_iterator = typename std::array<Gene, N>::reverse_iterator;
	using const_reverse_iterator = typename std::array<Gene, N>::const_reverse_iterator;

	/** Default ctor. */
	StaticChromosome(): genes_{}
	{
		genes_.fill(Gene());
	}
	/** Copy a provided array. */
	StaticChromosome(const std::array<Gene, N> & genes)
	{
		for(auto i = size_type(0); i < N; ++i)
		{
			genes_[i] = genes[i];
		}
	}
	/** Move a provided array. */
	StaticChromosome(std::array<Gene, N> && genes): genes_(std::move(genes)){}
	/** Move ctor. */
	StaticChromosome(StaticChromosome<N> && other): genes_(std::move(other.genes_)){}
	/** Copy ctor. */
	StaticChromosome(const StaticChromosome<N> & other): genes_(other.genes_){}
	/** Init-list ctor.*/
	StaticChromosome(std::initializer_list<Gene> initList)
	{
		const size_type sizeToCopy = (N > initList.size()) ? initList.size() : N;
		auto iter = initList.begin();
		for(auto i = size_type(0); i < sizeToCopy; ++i, ++iter)
		{
			genes_[i] = *iter;
		}
		for(auto i = size_type(sizeToCopy); i < N; ++i)
		{
			genes_[i] = Gene();
		}
	}
	/** Copy a DynamicChromosome.*/
	StaticChromosome(const DynamicChromosome & other)
	{
		const size_type sizeToCopy = (N > other.size()) ? other.size() : N;
		for(auto i = size_type(0); i < sizeToCopy; ++i)
		{
			genes_[i] = other[i];
		}
		for(auto i = size_type(sizeToCopy); i < N; ++i)
		{
			genes_[i] = Gene();
		}
	}

	/** Copy assignment operator.*/
	StaticChromosome<N> & operator=(const StaticChromosome<N> & other)
	{
		if(&other != this)
		{
			std::copy(other.begin(), other.end(), begin());
		}
		return *this;
	}

	/**
	 * Intended for template specialization.
	 * @return true
	 */
	static constexpr bool isStatic()
	{
		return true;
	}

	/**
	 * Intended for template specialization.
	 * @return false
	 */
	static constexpr bool isDyanamic()
	{
		return false;
	}

	/**
	 * Bounded index access delegated to genes_.
	 * @param i - index;
	 * @return reference to the Gene instance at index i.
	 */
	reference at(size_type i)
	{
		return genes_[i];
	}
	/**
	 * Bounded index access delegated to genes_.
	 * @param i - index;
	 * @return const reference to the Gene instance at index i.
	 */
	constexpr const_reference  at(size_type i) const
	{
		return genes_[i];
	}
	/**
	 * Index operator delegated to genes_.
	 * @param i - index;
	 * @return reference to the Gene instance at index i.
	 */
	reference operator[](size_type i)
	{
		return genes_[i];
	}
	/**
	 * Index operator delegated to genes_.
	 * @param i - index;
	 * @return const reference to the Gene instance at index i.
	 */
	constexpr const_reference operator[](size_type i) const
	{
		return genes_[i];
	}


	/**
	 * Get the Gene instance at the front of genes_.
	 * @return const reference to the Gene instance at the front.
	 */
	constexpr const_reference front() const
	{
		return genes_.front();
	}
	/**
	 * Get the Gene instance at the front of genes_.
	 * @return reference to the Gene instance at the front.
	 */
	reference front()
	{
		return genes_.front();
	}
	/**
	 * Get the Gene instance at the back of genes_.
	 * @return const reference to the Gene instance at the back.
	 */
	constexpr const_reference back() const
	{
		return genes_.back();
	}
	/**
	 * Get the Gene instance at the back of genes_.
	 * @return reference to the Gene instance at the back.
	 */
	reference back()
	{
		return genes_.back();
	}
	/**
	 * Get an iterator to the front.
	 * @return std::array<Gene, N>::iterator to the front.
	 */
	iterator begin()
	{
		return genes_.begin();
	}
	/**
	 * Get a const iterator to the front.
	 * @return std::array<Gene, N>::const_iterator to the front.
	 */
	const_iterator begin() const
	{
		return genes_.begin();
	}
	/**
	 * Get a const iterator to the front.
	 * @return std::array<Gene, N>::const_iterator to the front.
	 */
	const_iterator cbegin() const
	{
		return genes_.cbegin();
	}
	/**
	 * Get a reverse iterator to the front.
	 * @return std::array<Gene, N>::reverse_iterator to the front.
	 */
	reverse_iterator rbegin()
	{
		return genes_.rbegin();
	}
	const_reverse_iterator rbegin() const
	{
		return genes_.rbegin();
	}
	/**
	 * Get a const reverse iterator to the front.
	 * @return std::array<Gene, N>::const_reverse_iterator to the front.
	 */
	const_reverse_iterator crbegin() const
	{
		return genes_.crbegin();
	}


	/**
	 * Get an iterator to the end.
	 * @return std::array<Gene, N>::iterator to the end.
	 */
	iterator end()
	{
		return genes_.end();
	}
	/**
	 * Get a const iterator to the end.
	 * @return std::array<Gene, N>::const_iterator to the end.
	 */
	const_iterator end() const
	{
		return genes_.end();
	}
	/**
	 * Get a const iterator to the end.
	 * @return std::array<Gene, N>::const_iterator to the end.
	 */
	const_iterator cend() const
	{
		return genes_.cend();
	}
	/**
	 * Get a reverse iterator to the end.
	 * @return std::array<Gene, N>::reverse_iterator to the end.
	 */
	reverse_iterator rend()
	{
		return genes_.rend();
	}
	/**
	 * Get a const reverse iterator to the end.
	 * @return std::array<Gene, N>::const_reverse_iterator to the end.
	 */
	const_reverse_iterator rend() const
	{
		return genes_.crend();
	}
	/**
	 * Get a const reverse iterator to the end.
	 * @return std::array<Gene, N>::const_reverse_iterator to the end.
	 */
	const_reverse_iterator crend() const
	{
		return genes_.crend();
	}

	/**
	 * Checks if the chromosome is empty.
	 * @return true if the chromosome is empty, false otherwise.
	 */
	bool empty()
	{
		return genes_.empty();
	}
	/**
	 * Checks if the chromosome is empty.
	 * @return true if the chromosome is empty, false otherwise.
	 */
	constexpr bool empty() const
	{
		return genes_.empty();
	}
	/**
	 * Get the chromosome size.
	 * @return the chromosome size.
	 */
	size_type size()
	{
		return genes_.size();
	}
	/**
	 * Get the chromosome size.
	 * @return the chromosome size.
	 */
	constexpr size_type size() const
	{
		return genes_.size();
	}
	/**
	 * Get the chromosome max size.
	 * @return the chromosome max size.
	 */
	size_type max_size()
	{
		return genes_.max_size();
	}
	/**
	 * Get the chromosome max size.
	 * @return the chromosome max size.
	 */
	constexpr size_type max_size() const
	{
		return genes_.max_size();
	}
	/**
	 * Fill the chromosome with a gene with a particular value.
	 * @param value
	 */
	void fill( const Gene& value )
	{
		genes_.fill(value);
	}

};

#endif /* EVOLUTION_GENETICS_STATICCHROMOSOME_H_ */
