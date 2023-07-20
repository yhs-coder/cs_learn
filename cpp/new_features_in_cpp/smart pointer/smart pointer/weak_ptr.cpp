#include <iostream>
#include <memory>
using namespace std;

/*
* C++11 boost库
shared_ptr : 强智能指针， 可以改变资源的引用计数
weak_ptr : 弱智能指针， 不会改变资源的引用计数,观察作用,不可使用资源！不可使用operator * ,operator-> 访问、操作资源
weak_ptr => shared_ptr => 资源（内存）
weak_ptr观察shared_ptr，shared_ptr再去观察资源

为什么需要弱指针？
强智能指针的循环引用（交叉引用）是什么问题？
=> 造成new出来的资源无法释放！！！引发资源泄漏问题
解决：定义对象的时候，用强智能指针；引用对象的地方，使用弱智能指针！
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
		shared_ptr<A> ps = _ptra.lock();	   //提升方法
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

	// use_count() 资源对应的引用计数
	cout << pa.use_count() << endl;
	cout << pb.use_count() << endl;

	// 交叉引用!
	pa->_ptrb = pb;
	pb->_ptra = pa;

	cout << pa.use_count() << endl;
	cout << pb.use_count() << endl;
	pb->func();
	return 0;
}
#endif