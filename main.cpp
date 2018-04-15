/*
 * main.c
 *
 *  Created on: 9 апр. 2018 г.
 *      Author: bekir
 */
#include <iostream>
#include <stdio.h>
#include <memory>
#include <vector>

using namespace std;

class Base
{
public:
	Base(int a, int b): a(a), b(b), vec(10)
	{

	}
	virtual ~Base()
	{
		a=0;
		b=0;
	}
private:
	int a;
	int b;
public:
	virtual int func_a()
	{
		return a+b;
	}

	vector<int> vec;
public:
	virtual vector<int> &calc(void);

};

vector<int> &Base::calc(void)
{
	return vec;
}

class Derived : public Base
{
public:
	Derived (int a, int b);
	~Derived ()
	{

	}

	vector<int> &calc(void) override;
private:
	int a;
	int b;
	int func_b(int a)
	{
		return a*a;
	}

	int func_a() override
	{
		int c=func_b(a);
		return c;
	}

};

Derived::Derived (int a, int b): Base(a, b), a(a), b(b)
{

}

vector<int> &Derived::calc(void)
{
	vec[0]=900;
	return vec;
}

void rval (int&& rvalue)
{
	cout<<++rvalue<<endl;
}

template <typename T>
class Test: public vector<T>
{
public:
	Test(int size, int value): vector<T>(size, value)
		{
			a=0;
			b=0;
		}
	~Test()
	{
		a=0;
		b=0;
	}

public:
	template<typename E>
	Test<T>& operator = (const Test<E>& rhs);

	void push(T item);
	T& pop();
public:
	int a;
	int b;
};

template <>
class Test<float>
{
public:
	Test(float val)
		{
			a=val;
			b=0;
		}
public:
	float a;
	int b;
};

template <typename T>
void Test<T>::push(T item)
{
	this->push_back(item);
}

template <typename T>
T& Test<T>::pop()
{
	return this->back();
}

template<typename T>
template<typename E>
Test<T>& Test<T>::operator =(const Test<E>& rhs)
{
	this->clear();

		for (auto iterator=rhs.begin(); iterator!=rhs.end(); iterator++)
		{
			this->push(*iterator);
		}
	a=rhs.a;
	b=rhs.b;
	return (*this);
}

int main (int argc, char* argv[])
{

	Base* classtest=new Derived(3, 5);
	//cout<<classtest->func_a()<<endl;

	vector<int> &vec_ref=classtest->calc();
	cout<<vec_ref[0]<<endl;

	vector<shared_ptr<int> > vec(10, nullptr);
	int k=0;
		for (auto &i:vec)
		{
			i=make_shared<int>(k++);
		}
		for (auto j:vec)
		{
			cout<<j<<endl;
		}

	rval(10);

	Test<int> test(0, 0);
	Test<char> test_char(0, 0);
	Test<float> test_float(1.23);
	test.push(123);
	cout<<test.pop()<<endl;
	cout<<test_float.a<<endl;

	test.push(12);
	test.push(15);

	test_char.push(122);
	test_char.push(12);

	test_char=test;
	cout<<test_char[0]<<endl;

	while (getchar()!='q');
	return 0;
}



