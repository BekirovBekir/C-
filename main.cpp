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
#include <functional>
#include <clocale>
#include <thread>
#include <chrono>

using namespace std;

class Thread
{

private:


public:
	void ThreadRun(int& a)
	{
		thread thr(&Thread::FuncThread, this, ref(a));
		thr.join();
	}

	void FuncThread(int& a)
	{
		for (;;)
		{
			a++;
			cout<<"Thread works!"<<endl;
			this_thread::sleep_for(chrono::milliseconds(100));
				if (a>=10)
				{
					return;
				}
		}
	}
};

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

class Base1
{
public:
	Base1();

	virtual int func_c(int a, int b)
	{
		return a-b;
	}
	virtual ~Base1();

	int a;
	int b;
};

Base1::Base1()
{
	a=10;
	b=10;
}

Base1::~Base1()

{

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

class Derived_1 : public Derived, public Base1
{
public:
	Derived_1(int a, int b);

	int func_a() override
	{
		return a*b;
	}

	int func_c(int a, int b)
	{
		return a/b;
	}
public:
	int a;
	int b;
	int c;
};

Derived_1::Derived_1 (int a, int b): Derived(a, b), Base1(), a(a), b(b), c(0)
{

}

void rval (int&& rvalue)
{
	cout<<++rvalue<<endl;
}

void threadFunction(void)
{

}

int main (int argc, char* argv[])
{
	int x, y;

	x=1;
	y=1;

	Thread thr;
	thr.ThreadRun(x);

	/*thread test([x, y](){
			for (;;)
			{
			cout<<"Thread test"<<"x="<<x<<"y="<<y<<endl;
			this_thread::sleep_for(chrono::milliseconds(100));
			}

	});

	test.join();*/

	cout<<"x="<<x<<endl;

	x=10; y=10;

	function<int (int, int)>lambda=[&x, &y] (int a , int b) mutable -> int {return (2*(a+b)+x+y);};
	cout<<lambda(3,3)<<endl;

	x=20; y=20;

	cout<<lambda(3,3)<<endl;

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

	Derived* der1= new Derived_1 (5, 5);
	der1->vec.clear();
	der1->vec.push_back(123);

	Derived_1* der2= new Derived_1 (5, 5);
	cout<<der2->Base1::func_c(10, 10)<<endl;

	//std::setlocale(LC_ALL, "Russian");
	//printf("Русский текст\n");
	cout<<"Русский текст"<<endl;

	while (getchar()!='q');
	return 0;
}



