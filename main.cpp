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
#include<tuple>
#include<list>
#include "Allocator.hpp"
#include "type_erasure.hpp"
#include <any>

using namespace std;

mutex mut;
condition_variable cond_var;

template <typename T>
using TempUse = vector<vector<T> >;

class Super
{
private:
	int pr1;
	int pr2;

	virtual int f1 (int x)
	{
		return 2*x;
	}

public:
	int pub1;
	int pub2;

	virtual int f2 (int x)
	{
		return ++x;
	}
};

class SubSuper : private Super
{
private:
	int pr1;

public:
	int pub1;

	virtual ~SubSuper ()
	{
		pr1 = 0;
		pub1 = 0;
	}

	int f2(int x) override
	{
		Super::pub1 = 0;
		return (x+2);
	}

};


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

vector<int> rv_test(vector<int>&& a)
{
	vector<int> vec(a.begin(), a.end());

	//vec.push_back(a);

	return move(vec);
}


class RBase
{
public:

	RBase(): rb1(0), ptr_rb1(new int (0))
	{

	}

	RBase(RBase&& rhs) noexcept
	{
		rb1 = rhs.rb1;
		ptr_rb1 = rhs.ptr_rb1;
		rhs.ptr_rb1 = nullptr;
	}

	RBase& operator= (RBase&& rhs) noexcept
	{
		rb1 = rhs.rb1;
		ptr_rb1 = rhs.ptr_rb1;
		rhs.ptr_rb1 = nullptr;
		return *this;
	}

	int rb1;
private:
	int* ptr_rb1;
};

class RClass : public RBase
{
public:
	RClass(): rc1(0)
	{

	}

	RClass(RClass&& rhs) noexcept : RBase(move(rhs))
	{
		rc1 = rhs.rc1;
	}

	RClass& operator= (RClass&& rhs) noexcept
	{
		RBase::operator= (move(rhs));
		rc1 = rhs.rc1;

		return *this;
	}
private:
	int rc1;

};

template<typename... Args>
void foo(Args... args)
{
	std::cout << sizeof...(args) << std::endl;
}

struct rvalue_test;

struct rvalue_test
{
	rvalue_test()
	{
		a = 0;
		b = 0;
	}

	rvalue_test(const rvalue_test& rhs)
	{
		a = rhs.a;
		b = rhs.b;
		cout << "Copy constructor" << endl;
	}
	rvalue_test(rvalue_test&& rhs) noexcept
	{
		a = rhs.a;
		b = rhs.b;
		rhs.a = 0;
		rhs.b = 0;
		cout << "Move constructor" << endl;
	}
	rvalue_test& operator= (const rvalue_test& rhs)
	{
		a = rhs.a;
		b = rhs.b;
		return *this;
	}

	rvalue_test& operator= (rvalue_test&& rhs) noexcept
	{
		a = rhs.a;
		b = rhs.b;
		rhs.a = 0;
		rhs.b = 0;
		return *this;
	}

	int a;
	int b;

};

int bar_val = 10;
int bar_val1 = 11;
int *bar_ptr = &bar_val;

void incr(int& a)
{
	a++;
}

template<typename T>
void fbar(T&& a)
{
	int g;
	g++;

	//incr(forward<T>(a));
	a = &bar_val1;
	//arg--;
	//*arg = 1;
}

void RvalueTest(rvalue_test rvalue)
{
	rvalue_test a;
	rvalue.a++;
	a = rvalue;
}

void RvalueTest(rvalue_test &&rvalue)
{
	rvalue.a++;
}

class ReplacementTest
{
public:
	int8_t a;
	int8_t b;

	int& ref;

public:
	ReplacementTest(int8_t a, int8_t b, int& ref) : a(a), b(b), ref(ref)
	{

	}

	~ReplacementTest()
	{
		a=0;
		b=0;
	}

	ReplacementTest(const ReplacementTest& rhs) : ref(rhs.ref)
	{
		a = rhs.a;
		b = rhs.b;
	}

	ReplacementTest& operator= (const ReplacementTest& rhs)
	{

		if (this == &rhs)
		return *this;

		this->~ReplacementTest();
		new (this) ReplacementTest(rhs);
		return *this;
	}

};

class test_ctor
{
public:
	int a;
	int b;

	test_ctor(): a(0), b(0)
	{
		cout<<"Ctor ctor test_ctor!"<<endl;
	}

	test_ctor(const test_ctor& rhs ): a(rhs.a), b(rhs.b)
	{
		cout<<"Copy ctor test_ctor!"<<endl;
	}

	test_ctor& operator= (const test_ctor& rhs)
	{

		if (this == &rhs)
		return *this;

		a = rhs.a;
		b = rhs.b;
		return *this;
	}

	bool operator< (test_ctor const & rhs)
	{
		return a < rhs.a;
	}
};

class test_struct
{
public:
	test_struct()
	{
		cout<<"Ctor test_struct!"<<endl;
	}
	struct test
	{
		test()
		{
			cout<<"Ctor test!"<<endl;
		}

		test(test_ctor& rhs): tc(rhs)
		{
			rhs.a = 1;
		}

		test_ctor tc;
	};

	int c;
	test* ptr;
	void append(test_ctor& a)
	{
		ptr = new struct test(a);
	}
};

template<typename... Args>
void m_print(Args... args)
{

}

template<typename HEAD, typename... Args>
void m_print(HEAD head, Args... args)
{
	std::cout << head << endl;
	m_print(args...);
}

class TemplateTest
{
private:
	uint32_t a = 0;
public:
	void Set(uint32_t var)
	{
		a =var;
	}

	template <typename T>
	void test_print (T var)
	{
		cout << var << endl;
	}
};

template<typename T>
class TemplateTest1
{
private:
	T a = 0;
public:
	void Set(T var)
	{
		a = var;
	}

	void test_print (T var)
	{
		cout << var << endl;
	}
};

class mem_fn_class
{
public:

	int foo(int param)
	{
		return param++;

	};

	int m1;
};

class thread_test_functor
{
public:
	void operator() (int &a)
	{
		a++;
	}

	thread_test_functor() = default;
	thread_test_functor(const thread_test_functor &rhs) = default;
	thread_test_functor &operator= (const thread_test_functor &rhs) = default;

	thread_test_functor(thread_test_functor &&rhs) = default;
	thread_test_functor &operator= (thread_test_functor &&rhs) = default;
};

TestAllocator<size_t> alloc_test;
struct any_struct
{
	size_t a;
	float b;
};

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

/*		for (;;)
		{
			//(fsm.*fsm.FSM::next_state)();
			//this_thread::sleep_for(chrono::milliseconds(1000));

			future<void> ftr_fsm_task=async(launch::async, fsm.next_state, &fsm);
			ftr_fsm_task.get();
			this_thread::sleep_for(chrono::milliseconds(1000));
		}*/

	#define UNIQUE_PTR 1
	int* ptr = nullptr;
		if (UNIQUE_PTR)
		{
			unique_ptr<int> s_ptr(new int(12));
			ptr=s_ptr.get();
			cout<<"UNIQUE_PTR = "<<*s_ptr<<endl;
		}
	cout<<"UNIQUE_PTR = "<<*ptr<<endl;

	SubSuper testsuper;
	//Super& testsub = testsuper;

	//cout << testsub.f2(1) << endl;

	vector<int> w(300, 1);
	vector<int> v = rv_test(move(w));
	cout << v[0] << endl;

	RClass rclass1 = move(RClass());
	//RClass rclass1;
	//RClass rclass2;

	//rclass2 = move(rclass1);
	int&& t = 5;
	int f = typename remove_reference<int&&>::type (t);
	cout << f << endl;

	foo(1,2,3,4,5);

	tuple <char, int, float> geek;
	geek = make_tuple('a', 1, 2);
	cout << get<0>(geek) << " " << get<1>(geek) << endl;

	int aa = 10, bb = 0;
	std::tie(aa, bb) = std::make_tuple(bb, aa);
	cout << aa << " " << bb << endl;

	const int iii = 7;
	const int* iii_ptr = &iii;
	const int& iii_ref = iii;
	//bar(iii_ref);
	cout << iii << endl;

	rvalue_test test;
	test.a = 8;
	test.b = 8;
	//rvalue_test& ref = test;

	//bar(move(test));

	int abc1 = 100;
	int abc2 = 200;
	ReplacementTest replacement1(1, 1, abc1);
	ReplacementTest replacement2(2, 2, abc2);
	replacement2 = replacement1;

	test_ctor ctr;

	test_struct test123456;
	test123456.append(ctr);
	std::list<test_ctor> l1;
	l1.push_back(ctr);

	m_print(1, 2, 3, "Hello!");

	TemplateTest* test_template = new TemplateTest;

	test_template->test_print(34);

	TemplateTest1<int>* test_template1 = new TemplateTest1<int>;

	test_template1->test_print(35);


	fbar(bar_ptr);

	mem_fn_class mem_fn_instance;

	auto m = mem_fn(&mem_fn_class::foo);
	int m1;
	m1 = m(mem_fn_instance, 5);
	cout << m1 << endl;

	int abcd = 10;
	thread_test_functor test_functor;
	std::thread thread1(test_functor, std::ref(abcd));
	thread1.join();

	rvalue_test rv_instance;
	//RvalueTest(rvalue_test());

	size_t alloc_value = 0;
	size_t *alloc_test_ptr = alloc_test.allocate(10);


	for (size_t i = 0; i < 10; ++i) {
		alloc_test.construct(alloc_test_ptr + i, alloc_value++);
		std::cout << "Alloc test, num is: " << *(alloc_test_ptr + i) << std::endl;
	}

	for (size_t i = 0; i < 10; ++i) {
		alloc_test.destroy(alloc_test_ptr + i);
	}

	 alloc_test.deallocate(alloc_test_ptr);

	 any_struct any_struct_my;
	 any_struct_my.a =1;
	 any_struct_my.b = 1.23;
	 any_test my_any(any_struct_my);
	 any_test my_any_1(5.1);
	 my_any = 9;
	 any_test my_any_2 = my_any_1;

	 std::any aasa(2);

	while (getchar()!='q');
	return 0;
}



