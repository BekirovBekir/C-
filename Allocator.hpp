/*
 * Allocator.hpp
 *
 *  Created on: 17 июл. 2021 г.
 *      Author: bekir
 */

#ifndef ALLOCATOR_HPP_
#define ALLOCATOR_HPP_


#include "iostream"


template <typename T>
class TestAllocator
{
public:

	T *allocate(size_t cnt)
	{
		 return ptr = static_cast<T *>(::operator new(sizeof(T) * cnt));
	}

	void deallocate(T *ptr)
	{
		::operator delete(ptr);
	}

	template <typename... Args>
	void construct(T *ptr_item, Args... args)
	{
		new (ptr_item) T(std::forward<T>(args)...);
	}

	void destroy(T *ptr_item)
	{
		ptr_item->~T();
	}

private:
	T *ptr;
};

#endif /* ALLOCATOR_HPP_ */
