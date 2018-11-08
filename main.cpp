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
#include <mutex>
#include <condition_variable>
#include <memory>
#include <initializer_list>
#include <future>


using namespace std;

mutex mut;
condition_variable cond_var;

template <typename T>
using TempUse = vector<vector<T> >;

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

class TOUT
{
private:
	int c;

public:
	int a;
	int b;
	void func1(int& a)
	{
		tin.e=1;
	}

	//friend class TIN;

	class TIN
	{
	private:
		int d;
	public:
		int e;

		 void func2(TOUT& out)
		 {
			 out.c=5;
			 cout<<"Inner class c="<<out.c<<endl;
		 }
	};

	TIN tin;
};

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
	long double distance;
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
	friend long double operator "" _km(long double km);

};

long double operator "" _km(long double km)
		{
			return km*1000.0;
		}

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

template <typename T>
T& rval (T&& rvalue)
{
	cout<<++rvalue<<endl;
	return rvalue;
}

unsigned int factorial(unsigned int a)
{
	if (a>=1)
	{
		return a*factorial(a-1);
	}
	if (a==0)
	{
	  return 1;
	}

}

void threadFunction(void)
{

}

class IList
{
public:
	IList(): ref(a)
	{
		a=0;
		b=0;
		c=0;
	}

	IList(const IList& obj): ref(obj.ref)
	{
		this->a=obj.a;
		this->b=obj.b;
		this->c=obj.c;
	}

	IList& operator= (const IList& rhs)
	{
		if (this!=&rhs)
		{
			this->~IList();
			new (this) IList(rhs);
		}
		return *this;
	}

	IList(initializer_list<int> ls)
	{
		auto it=ls.begin();

		a=*it++;
		b=*it++;
		c=*it++;
		ref=*it;
	}

	int a;
	int b;
	//vector<int> v;

	int ref;

private :
	int c;
};

class FSM;
using Ptr_State=void(FSM::*)(void);

class FSM
{
public:

	FSM(int state=1): next_state(&FSM::State1), state(state) {};

	void State1(void);
	void State2(void);
	void State3(void);

	Ptr_State next_state;
	//void (FSM::*next_state)(void);

private:
	int state;

};

void FSM::State1(void)
{
	cout<<"State1 is active, next State2"<<endl;
	next_state=&FSM::State2;

}

void FSM::State2(void)
{
	cout<<"State2 is active, next State3"<<endl;
	next_state=&FSM::State3;

}

void FSM::State3(void)
{
	cout<<"State3 is active, next State1"<<endl;
	next_state=&FSM::State1;

}


int main (int argc, char* argv[])
{
	int x, y;
	TempUse<int> vec_template{{1,2}, {1,2}, {3}};

	x=1;
	y=1;

	int aaa=1;

	if (aaa)
	{
		weak_ptr<int> ptr1;
		weak_ptr<int> ptr2;
		shared_ptr<int> a (new int (32));
		shared_ptr<int> b (new int (42));

		ptr1=a;

		ptr2=b;
		ptr1=ptr2;
		ptr2=ptr1;
	}

	TOUT class_out;
	class_out.tin.func2(class_out);

	//Thread thr;
	//thr.ThreadRun(x);

	cout<<vec_template[0][1]<<endl;

	thread test1([&x, &y](){
			for (;;)
			{
			cout<<"Thread test1"<<"x="<<x<<" y="<<y<<endl;
			this_thread::sleep_for(chrono::milliseconds(100));
			x++;
				if (x>=10)
				{
					cout<<"Thread test1 notify sent"<<endl;
					lock_guard<std::mutex> lock(mut);
					cond_var.notify_all();
					return;
				}
			}

	});

	thread test2([&x, &y](){
			for (;;)
			{

			unique_lock<std::mutex> lock(mut);
			while (x<10)
			{
				cond_var.wait(lock);
			}
			cout<<"Thread test2 received notify"<<endl;
			this_thread::sleep_for(chrono::milliseconds(100));
			return;
			}

	});

	test1.join();
	test2.join();

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

	int r_a=1;
	float r_b=1.5;

	cout<<"I'm here!"<<rval(std::move(r_a))<<endl;

	cout<<"I'm here!"<<factorial(3)<<endl;


	Derived* der1= new Derived_1 (5, 5);
	der1->vec.clear();
	der1->vec.push_back(123);

	Derived_1* der2= new Derived_1 (5, 5);
	cout<<der2->Base1::func_c(10, 10)<<endl;


	Derived der3(6,7);
	der3.distance=34.0_km;
	cout<<der3.distance<<endl;


	//std::setlocale(LC_ALL, "Russian");
	//printf("Русский текст\n");
	cout<<"Русский текст"<<endl;

	vector<vector<int> > vec_massive;//vec_src{1, 2, 3, 4, 5};
	vector<int> vec_dest{1, 2, 3, 4, 5};


	//vec_dest=move(vec_src);
	//vec_src.push_back(5);
	vec_massive.push_back(move(vec_dest));

	vec_dest.push_back(5);
	cout<<vec_dest[1000]<<endl;


	IList list{1,2,3,6};
	//IList list1;
	//list1=list;
	cout<<list.a<<" "<<list.b<<endl;

	future<long> future_test=async(launch::async, []()-> long {
													long S=0;
														for (int i=0; i<=10000; i++)
														{
														S+=i;
														}
													return S;
													});
	cout<<"Future result is "<<future_test.get()<<endl;


	packaged_task<int()>task( []()-> int {return 1;} );
	future<int> ftr_task=task.get_future();
	thread task1(move(task));

	cout<<ftr_task.get()<<endl;

	FSM fsm(1);
	//fsm.next_state=&FSM::State1;

		for (;;)
		{
			//(fsm.*fsm.FSM::next_state)();
			//this_thread::sleep_for(chrono::milliseconds(1000));

			future<void> ftr_fsm_task=async(launch::async, fsm.next_state, &fsm);
			ftr_fsm_task.get();
			this_thread::sleep_for(chrono::milliseconds(1000));
		}


	while (getchar()!='q');
	return 0;
}



