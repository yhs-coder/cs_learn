#include <iostream>
#include <memory>
using namespace std;

/*
* C++11 boost��
shared_ptr : ǿ����ָ�룬 ���Ըı���Դ�����ü���
weak_ptr : ������ָ�룬 ����ı���Դ�����ü���,�۲�����,����ʹ����Դ������ʹ��operator * ,operator-> ���ʡ�������Դ
weak_ptr => shared_ptr => ��Դ���ڴ棩
weak_ptr�۲�shared_ptr��shared_ptr��ȥ�۲���Դ

Ϊʲô��Ҫ��ָ�룿
ǿ����ָ���ѭ�����ã��������ã���ʲô���⣿
=> ���new��������Դ�޷��ͷţ�����������Դй©����
�������������ʱ����ǿ����ָ�룻���ö���ĵط���ʹ��������ָ�룡
*/

class B;
class A
{
public:
	A() { cout << "A()" << endl; }
	~A() { cout << "~A()" << endl; }
	//!shared_ptr<B> _ptrb;
	weak_ptr<B> _ptrb;
	void test() { cout << "test()" << endl; }
};

class B
{
public:
	B() { cout << "B()" << endl; }
	~B() { cout << "~B()" << endl; }
	//!shared_ptr<A> _ptra;
	weak_ptr<A> _ptra;
	void func()
	{
		//_ptra->test(); //error
		shared_ptr<A> ps = _ptra.lock();	   //��������
		if (ps != nullptr)
		{
			ps->test();
		}
	}
};

#if 0
int main()
{
	shared_ptr<A> pa(new A);
	shared_ptr<B> pb(new B);

	// use_count() ��Դ��Ӧ�����ü���
	cout << pa.use_count() << endl;
	cout << pb.use_count() << endl;

	// ��������!
	pa->_ptrb = pb;
	pb->_ptra = pa;

	cout << pa.use_count() << endl;
	cout << pb.use_count() << endl;
	pb->func();
	return 0;
}
#endif