/*
 * OrderedGenes.h
 *
 *  Created on: Feb 3, 2017
 *      Author: tim
 */

#ifndef CHROMOSOME_H_
#define CHROMOSOME_H_
#include <boost/any.hpp>
#include <functional>
#include "../Gene.h"
#include <vector>



template <template<typename = Gene> class Container = std::vector>
class OrderedGenes: public Chromosome
{
private:

	Container<Gene> genes_;


	Container<Gene>::iterator begin()
	{
		return this->genes_.begin();
	}
	Container<Gene>::iterator end()
	{
		return this->genes_.end();
	}

	Gene & front()
	{
		return this->genes_.front();
	}

	Gene & back()
	{
		return this->genes_.back();
	}

	void swap(Container<Gene>::iterator & other)
	{
		this->genes_.swap(other);
	}

public:

	OrderedGenes(size_t numgenes)
	{
		genes_ = Container<Gene>(numgenes);
	}

	virtual ~OrderedGenes()
	{

	}

	bool empty() const
	{
		return this->genes_.empty();
	}

	size_t max_size() const
	{
		return this->genes_.max_size();
	}

	size_t size() const
	{
		return genes_.size();
	}
	virtual void mutate()
	{
		size_t ngenes = this->size();
		for(size_t i = 0; i < ngenes; ++i)
		{
			this->genes_[i].mutate();
		}
	}
};



#endif /* CHROMOSOME_H_ */
