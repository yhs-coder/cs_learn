#include <iostream>
#include <memory>
#include <thread>
using namespace std;
/*
	多线程访问共享对象的线程安全问题
*/

class A
{
public:
	A() { cout << "A()" << endl; }
	~A() { cout << "~A()" << endl; }
	void test() { cout << "test()" << endl; }
};

// 子线程
void handler01(weak_ptr<A> pw)
{
	
	// 访问A对象时，需要侦测以下A对象是否存活
	shared_ptr<A> sp = pw.lock();
	if (sp != nullptr)
	{
		sp->test();
	}
	else
	{
		cout << "A对象已经析构，不能再访问！" << endl;
	}
}

#if 0
// main线程
int main()
{
	{
		shared_ptr<A> p(new A());
		thread t1(handler01, weak_ptr<A>(p));
		t1.detach();	// 分离线程
		std::this_thread::sleep_for(std::chrono::seconds(2));
	}
	std::this_thread::sleep_for(std::chrono::seconds(10));
	return 0;
}
#endif