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

int main (int argc, char* argv[])
{

	Base* classtest=new Derived(3, 5);
	//cout<<classtest->func_a()<<endl;

	vector<int> &vec_ref=classtest->calc();
	cout<<vec_ref[0]<<endl;

	vector<shared_ptr<int>> vec(10, nullptr);
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
	while (getchar()!='q');
	return 0;
}



