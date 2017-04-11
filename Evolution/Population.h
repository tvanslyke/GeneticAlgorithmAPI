/*
 * Population.h
 *
 *  Created on: Feb 13, 2017
 *      Author: tim
 */

#ifndef GENETICSTRUCTURES_POPULATION_H_
#define GENETICSTRUCTURES_POPULATION_H_

#include <memory>
#include <vector>

#include "Genetics/CrossoverPolicies/CrossoverPolicy.h"
#include "Genetics/CrossoverPolicies/NPointCrossover.h"
#include "Genetics/CrossoverPolicies/UniformRandomCrossover.h"
#include "GenerationPolicies/ConstantSize.h"
#include "Evolvable.h"


/**
 * Container-like class that provides top-level control of Evolvable instances.
 *
 * Except for a select few methods, the class's interface mimics that of std::vector to
 * allow access to the internally-contained Evolvable instances. This allows users to
 * treat the class as a container, while allowing the Population instance to maintain
 * certain guarantees about the lifetime of the evolvables that it interacts with.
 *
 * Although inheritance from std::vector would make this class definition much simpler,
 * it is not done because std::vector has no virtual destructor.
 *
 *
 * The trailing template parameters exist to allow end-users to specialize this class
 * template according to unforeseen needs.  They are otherwise meaningless.
 *
 * @author Timothy Van Slyke
 */

template <class E, 	    // the evolvable being contained
		  typename ... T>	// other optional types that may be used for specializing the template generation policy
class Population;

template <class E, 	// the evolvable being simulated
		  class G>	// GenerationPolicy
class Population<E, G>
{
protected:
	/** The internally contained Evolvables. */
	std::vector<E> pop_;
	/** The generation policy*/
	G generationPolicy_;
public:
	// types accessible in std::vector.
	using value_type = typename std::vector<E>::value_type;
	using size_type = typename std::vector<E>::size_type;
	using difference_type = typename std::vector<E>::difference_type;
	using reference = typename std::vector<E>::reference;
	using const_reference = typename std::vector<E>::const_reference;
	using pointer = typename std::vector<E>::pointer;
	using const_pointer = typename std::vector<E>::const_pointer;
	using iterator = typename std::vector<E>::iterator;
	using const_iterator = typename std::vector<E>::const_iterator;
	using reverse_iterator = typename std::vector<E>::reverse_iterator;
	using const_reverse_iterator = typename std::vector<E>::const_reverse_iterator;

	/** Default constructor. */
	Population(): generationPolicy_(), pop_()
	{

	}
	/**
	 * Construct the Population with a parameter pack forwarded to the
	 * generation policy being used.
	 */
	template <typename ... T>
	Population(T && ... args):
		pop_(),
		generationPolicy_(std::forward<T>(args)...)

	{

	}
	/**
	 * Construct from a single generation policy.
	 * @param gp - the generation policy to use.
	 */
	Population(const G & gp): generationPolicy_(gp), pop_()
	{

	}

	/**
	 * Call the generation policy ro load the pop_ vector with the
	 * next generation of evolvables.
	 */
	void nextGeneration(bool loadChromosomes = false)
	{
		generationPolicy_(pop_);
		if(loadChromosomes)
		{
			for(auto & evolvable:pop_)
			{
				evolvable.loadFromChromosome();
			}
		}
	}


	/**
	 * Index operator delegated to pop_.
	 * @param i - index;
	 * @return reference to the E instance at index i.
	 */
	reference operator[](size_type i)
	{
		return pop_[i];
	}
	/**
	 * Index operator delegated to pop_.
	 * @param i - index;
	 * @return const reference to the E instance at index i.
	 */
	const_reference operator[](size_type i) const
	{
		return pop_[i];
	}
	/**
	 * Bounded index access delegated to pop_.
	 * @param i - index;
	 * @return reference to the E instance at index i.
	 */
	reference at(size_type i)
	{
		return pop_[i];
	}
	/**
	 * Bounded index access delegated to pop_.
	 * @param i - index;
	 * @return const reference to the E instance at index i.
	 */
	const_reference  at(size_type i) const
	{
		return pop_[i];
	}

	/**
	 * Get the E instance at the front of pop_.
	 * @return reference to the E instance at the front.
	 */
	reference front()
	{
		return pop_.front();
	}


	/**
	 * Get the E instance at the front of pop_.
	 * @return const reference to the E instance at the front.
	 */
	const_reference front() const
	{
		return pop_.front();
	}
	/**
	 * Get the E instance at the back of pop_.
	 * @return const reference to the E instance at the back.
	 */
	const_reference back() const
	{
		return pop_.back();
	}
	/**
	 * Get the E instance at the back of pop_.
	 * @return reference to the E instance at the back.
	 */
	reference back()
	{
		return pop_.back();
	}
	/**
	 * Get an iterator to the front.
	 * @return std::vector<E>::iterator to the front.
	 */
	iterator begin()
	{
		return pop_.begin();
	}

	/**
	 * Get an iterator to the end.
	 * @return std::vector<E>::_iterator to the end.
	 */
	iterator end()
	{
		return pop_.end();
	}
	/**
	 * Get a const iterator to the front.
	 * @return std::vector<E>::const_iterator to the front.
	 */
	const_iterator begin() const
	{
		return pop_.begin();
	}
	/**
	 * Get a const iterator to the end.
	 * @return std::vector<E>::const_iterator to the end.
	 */
	const_iterator end() const
	{
		return pop_.end();
	}

	/**
	 * Get a const iterator to the front.
	 * @return std::vector<E>::const_iterator to the front.
	 */
	const_iterator cbegin() const noexcept
	{
		return pop_.cbegin();
	}
	/**
	 * Get a const iterator to the end.
	 * @return std::vector<E>::const_iterator to the end.
	 */
	const_iterator cend() const noexcept
	{
		return pop_.cend();
	}
	/**
	 * Get a reverse iterator to the front.
	 * @return std::vector<E>::reverse_iterator to the front.
	 */
	reverse_iterator rbegin() const noexcept
	{
		return pop_.rbegin();
	}
	/**
	 * Get a reverse iterator to the end.
	 * @return std::vector<E>::reverse_iterator to the end.
	 */
	reverse_iterator rend() const noexcept
	{
		return pop_.rend();
	}
	/**
	 * Get a const reverse iterator to the front.
	 * @return std::vector<E>::const_reverse_iterator to the front.
	 */
	const_reverse_iterator crbegin() const noexcept
	{
		return pop_.crbegin();
	}
	/**
	 * Get a const reverse iterator to the end.
	 * @return std::vector<E>::const_reverse_iterator to the end.
	 */
	const_reverse_iterator crend() const noexcept
	{
		return pop_.crend();
	}

	/**
	 * Checks if the population is empty.
	 * @return true if the population is empty, false otherwise.
	 */
	bool empty() const noexcept
	{
		return pop_.empty();
	}
	/**
	 * Get the population size.
	 * @return the population size.
	 */
	size_type size() const noexcept
	{
		return pop_.size();
	}
	/**
	 * Get the capacity of the internal vector.
	 * @return the capacity of the internal vector.
	 */
	size_type capacity() const noexcept
	{
		return pop_.capacity();
	}
	/**
	 * Clear the internal vector.
	 */
	void clear()
	{
		pop_.clear();
	}
	/**
	 * Append a new evolvable to the back.
	 * @param ev - the new Evolvable to push back.
	 */
	void push_back(const E & ev)
	{
		pop_.push_back(ev);
	}

	/**
	 * Emplace a new evolvable at the back.
	 * @param args - Parameter pack of constructor args.
	 */
	template <typename ... U>
	void emplace_back(U && ... args)
	{
		pop_.emplace_back(std::forward<U>(args)...);
	}
	/**
	 * Emplace a new evolvable at the location of the given iterator.
	 * @param args - Parameter pack of constructor args.
	 */
	template <typename ... U>
	void emplace(const_iterator pos, U && ... args)
	{
		pop_.emplace(pos, std::forward<U>(args)...);
	}

	/**
	 * Erase the evolvable at the given iterator.
	 * @param pos - the iterator to the evolvable to be erased.
	 * @return the iterator following pos.
	 */
	iterator erase(const_iterator pos)
	{
		return pop_.erase(pos);
	}
	/**
	 * Erase the evolvables in the range [first, last).
	 * @param first - the iterator to the first evolvable to be erased.
	 * @param first - the iterator to the first evolvable to not be erased.
	 * @return the iterator following the last evolvable to be erased.
	 */
	iterator erase(const_iterator first, const_iterator last)
	{
		return pop_.erase(first, last);
	}
	/**
	 * Remove the last evolvable in the internal vector.
	 */
	void pop_back()
	{
		pop_.pop_back();
	}
	/**
	 * Change the size of the internal vector.
	 * @param count - the new size of the internal vector.
	 */
	void resize( size_type count )
	{
		pop_.resize(count);
	}
	/**
	 * Change the size of the internal vector.
	 * @param count - the new size of the internal vector.
	 * @param value - the value with which the new elements will be instantiated.
	 */
	void resize( size_type count, const value_type& value )
	{
		pop_.resize(count, value);
	}
};
#endif /* GENETICSTRUCTURES_POPULATION_H_ */
