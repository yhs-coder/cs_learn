#include <iostream>
#include <memory>
#include <thread>
using namespace std;
/*
	���̷߳��ʹ��������̰߳�ȫ����
*/

class A
{
public:
	A() { cout << "A()" << endl; }
	~A() { cout << "~A()" << endl; }
	void test() { cout << "test()" << endl; }
};

// ���߳�
void handler01(weak_ptr<A> pw)
{
	
	// ����A����ʱ����Ҫ�������A�����Ƿ���
	shared_ptr<A> sp = pw.lock();
	if (sp != nullptr)
	{
		sp->test();
	}
	else
	{
		cout << "A�����Ѿ������������ٷ��ʣ�" << endl;
	}
}

#if 0
// main�߳�
int main()
{
	{
		shared_ptr<A> p(new A());
		thread t1(handler01, weak_ptr<A>(p));
		t1.detach();	// �����߳�
		std::this_thread::sleep_for(std::chrono::seconds(2));
	}
	std::this_thread::sleep_for(std::chrono::seconds(10));
	return 0;
}
#endif