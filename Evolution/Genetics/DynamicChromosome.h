/*
 * DynamicChromosome.h
 *
 *  Created on: Apr 6, 2017
 *      Author: tim
 */

#ifndef EVOLUTION_GENETICS_DYNAMICCHROMOSOME_H_
#define EVOLUTION_GENETICS_DYNAMICCHROMOSOME_H_
#include <vector>
#include <initializer_list>
#include <cstddef>
#include "Gene.h"

/** Forward declaration of StaticChromosome. */
template < size_t>
class StaticChromosome;

/**
 * Class provided for end users who wish to implement some sort of non-uniform
 * chromosome size into their algorthim.
 *
 * This class currently provides little abstraction over a simple using declaration
 * or a typedef for the time being.  In the future, the interface will be expanded.
 * @author Timothy Van Slyke
 */
class DynamicChromosome {
private:
	/** Sequential container of genes. */
	std::vector<Gene> genes_;

public:
	/** Default ctor. */
	DynamicChromosome() = default;
	/** Construct with given length. */
	DynamicChromosome(size_t len);
	/** Construct from init-list.	 */
	DynamicChromosome(std::initializer_list<Gene> initList);
	/** Copy from StaticChromosome. */
	template <size_t N>
	DynamicChromosome(const StaticChromosome<N> & other)
	{
		genes_.reserve(N);
		for(auto & gene:other)
		{
			genes_.push_back(gene);
		}
	}


	/**
	 * Intended for template specialization.
	 * @return false
	 */
	static constexpr bool isStatic()
	{
		return false;
	}

	/**
	 * Intended for template specialization.
	 * @return true
	 */
	static constexpr bool isDyanamic()
	{
		return true;
	}



	/////////////////////////////////////////////////////////
	///     Methods to allow user access to population    ///
	/////////////////////////////////////////////////////////



	using value_type = typename std::vector<Gene>::value_type;
	using size_type = typename std::vector<Gene>::size_type;
	using difference_type = typename std::vector<Gene>::difference_type;
	using reference = typename std::vector<Gene>::reference;
	using const_reference = typename std::vector<Gene>::const_reference;
	using pointer = typename std::vector<Gene>::pointer;
	using const_pointer = typename std::vector<Gene>::const_pointer;
	using iterator = typename std::vector<Gene>::iterator;
	using const_iterator = typename std::vector<Gene>::const_iterator;
	using reverse_iterator = typename std::vector<Gene>::reverse_iterator;
	using const_reverse_iterator = typename std::vector<Gene>::const_reverse_iterator;



	/**
	 * Index operator delegated to genes_.
	 * @param i - index;
	 * @return reference to the Gene instance at index i.
	 */
	reference operator[](size_type i);
	/**
	 * Index operator delegated to genes_.
	 * @param i - index;
	 * @return const reference to the Gene instance at index i.
	 */
	const_reference operator[](size_type i) const;
	/**
	 * Bounded index access delegated to genes_.
	 * @param i - index;
	 * @return reference to the Gene instance at index i.
	 */
	reference at(size_type i);
	/**
	 * Bounded index access delegated to genes_.
	 * @param i - index;
	 * @return const reference to the Gene instance at index i.
	 */
	const_reference  at(size_type i) const;

	/**
	 * Get the Gene instance at the front of genes_.
	 * @return reference to the Gene instance at the front.
	 */
	reference front();


	/**
	 * Get the Gene instance at the front of genes_.
	 * @return const reference to the Gene instance at the front.
	 */
	const_reference front() const;
	/**
	 * Get the Gene instance at the back of genes_.
	 * @return const reference to the Gene instance at the back.
	 */
	const_reference back() const;
	/**
	 * Get the Gene instance at the back of genes_.
	 * @return reference to the Gene instance at the back.
	 */
	reference back();
	/**
	 * Get an iterator to the front.
	 * @return std::vector<Gene>::iterator to the front.
	 */
	iterator begin();

	/**
	 * Get an iterator to the end.
	 * @return std::vector<Gene>::iterator to the end.
	 */
	iterator end();
	/**
	 * Get a const iterator to the front.
	 * @return std::vector<Gene>::const_iterator to the front.
	 */
	const_iterator begin() const;
	/**
	 * Get a const iterator to the end.
	 * @return std::vector<Gene>::const_iterator to the end.
	 */
	const_iterator end() const;

	/**
	 * Get a const iterator to the front.
	 * @return std::vector<Gene>::const_iterator to the front.
	 */
	const_iterator cbegin() const noexcept;
	/**
	 * Get a const iterator to the end.
	 * @return std::vector<Gene>::const_iterator to the end.
	 */
	const_iterator cend() const noexcept;
	/**
	 * Get a reverse iterator to the front.
	 * @return std::vector<Gene>::reverse_iterator to the front.
	 */
	reverse_iterator rbegin() const noexcept;
	/**
	 * Get a reverse iterator to the end.
	 * @return std::vector<Gene>::reverse_iterator to the end.
	 */
	reverse_iterator rend() const noexcept;
	/**
	 * Get a const reverse iterator to the front.
	 * @return std::vector<Gene>::const_reverse_iterator to the front.
	 */
	const_reverse_iterator crbegin() const noexcept;
	/**
	 * Get a const reverse iterator to the end.
	 * @return std::vector<Gene>::const_reverse_iterator to the end.
	 */
	const_reverse_iterator crend() const noexcept;

	/**
	 * Checks if the population is empty.
	 * @return true if the population is empty, false otherwise.
	 */
	bool empty() const noexcept;
	/**
	 * Get the population size.
	 * @return the population size.
	 */
	size_type size() const noexcept;
	/**
	 * Get the capacity of the internal vector.
	 * @return the capacity of the internal vector.
	 */
	size_type capacity() const noexcept;
	/**
	 * Clear the internal vector.
	 */
	void clear();
	/**
	 * Append a new gene to the back.
	 * @param ev - the new Gene to push back.
	 */
	void push_back(const Gene & ev);

	/**
	 * Emplace a new gene at the back.
	 * @param args - Parameter pack of constructor args.
	 */
	template <typename ... U>
	void emplace_back(U && ... args)
	{
		genes_.emplace_back(std::forward<U>(args)...);
	}
	/**
	 * Emplace a new gene at the location of the given iterator.
	 * @param args - Parameter pack of constructor args.
	 */
	template <typename ... U>
	void emplace(const_iterator pos, U && ... args)
	{
		genes_.emplace(pos, std::forward<U>(args)...);
	}
	/**
	 * Erase the gene at the given iterator.
	 * @param pos - the iterator to the gene to be erased.
	 * @return the iterator following pos.
	 */
	iterator erase(const_iterator pos);
	/**
	 * Erase the genes in the range [first, last).
	 * @param first - the iterator to the first gene to be erased.
	 * @param first - the iterator to the first gene to not be erased.
	 * @return the iterator following the last gene to be erased.
	 */
	iterator erase(const_iterator first, const_iterator last);
	/**
	 * Remove the last gene in the internal vector.
	 */
	void pop_back();
	/**
	 * Change the size of the internal vector.
	 * @param count - the new size of the internal vector.
	 */
	void resize( size_type count );
	/**
	 * Change the size of the internal vector.
	 * @param count - the new size of the internal vector.
	 * @param value - the value with which the new elements will be instantiated.
	 */
	void resize( size_type count, const value_type& value );



};

#endif /* EVOLUTION_GENETICS_DYNAMICCHROMOSOME_H_ */
