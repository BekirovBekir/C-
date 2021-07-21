/*
 * type_erasure.hpp
 *
 *  Created on: 18 июл. 2021 г.
 *      Author: bekir
 */

#ifndef TYPE_ERASURE_HPP_
#define TYPE_ERASURE_HPP_


#include <iostream>
#include <type_traits>

class any_test
{
public:

	template<typename T>
	any_test(const T &param) : param_ptr(new derived<T>(param))
	{
		std::cout << "this value is " << this << std::endl;
		std::cout << "any_test constructor is invoked" << std::endl;
	}


//	template<typename T, typename... Args>
//	any_test(Args&&... args) : param_ptr(new derived<T>(std::forward<T>(args)...))
//	{
//		std::cout << "any_test constructor is invoked" << std::endl;
//	}

	any_test(const any_test &rhs) : param_ptr(rhs.param_ptr->clone())
	{
		std::cout << "this value is " << this << std::endl;
		std::cout << "any_test copy constructor is invoked" << std::endl;
	}

	any_test &operator=(const any_test &rhs)
	{
		delete param_ptr;
		param_ptr = rhs.param_ptr->clone();
		std::cout << "any_test assign operator is invoked" << std::endl;

		return *this;
	}

//	template<typename T, typename... Args>
//	any_test &operator=(Args&&... args)
//	{
//		delete param_ptr;
//		param_ptr = new derived<T>(std::forward<T>(args)...);
//		std::cout << "any_test param assign operator is invoked" << std::endl;
//
//		return *this;
//	}

	template<typename T>
	any_test &operator=(const T &param)
	{
		delete param_ptr;
		param_ptr = new derived<T>(param);
		std::cout << "any_test param assign operator is invoked" << std::endl;

		return *this;
	}
	~any_test()
	{
		delete param_ptr;
		std::cout << "any_test destructor is invoked" << std::endl;
	}

private:

	class base
	{
	public:
		virtual ~base() {}
		virtual base *clone(void)
		{
			return this;
		}
	};

	template<typename T>
	class derived : public base
	{
	public:
		typedef T value_type;
		derived(const T& derv_param) : param(derv_param) {}
		derived(const derived& rhs) : base(rhs)
		{
			param = rhs.param;
			std::cout << "derived copy constructor is invoked" << std::endl;
		}
		base *clone(void) override
		{
			return new derived<T>(*this);
		}

		T param;
	};

	base *param_ptr;
};


#endif /* TYPE_ERASURE_HPP_ */
