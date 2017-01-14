/*
 * Stack.h
 *
 *  Created on: Jan 13, 2017
 *      Author: tim
 */

#ifndef STRUCTURES_FASTSTACK_H_
#define STRUCTURES_FASTSTACK_H_

#include <vector>
using std::vector;
// Similar to std::stack but makes no attempt at checking that the
// user is modifying/accessing elements safely.
namespace GA
{
	template <typename T>
	class FastStack{
	private:
		vector<T> stack;
		size_t pos;
	public:
		FastStack(size_t size)
		{
			stack = vector<T>(size);
			pos = 0;
		}
		virtual ~FastStack()
		{
			;
		}
		T Pop()
		{
			return stack[--pos];
		}
		void Add(T & new_item)
		{
			stack[pos++] = new_item;
		}
		void Add(T && new_item)
		{
			stack[pos++] = new_item;
		}
		T Peek(size_t index)
		{
			return stack[pos - index];
		}
		size_t Size()
		{
			return pos + 1;
		}
	};
}
#endif /* STRUCTURES_FASTSTACK_H_ */
