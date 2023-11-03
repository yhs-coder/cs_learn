#include <iostream>
#include <string>
#include "Singleton.h"
using std::cout;
using std::endl;

class A {
	static int _s_n;
};
int A::_s_n = 10;

class Test {
public:
	static void func() {
		_s_n = 100;
		// cout << "_count = " << _count << endl; // 无法访问非静态数据成员
		cout << "_s_n = " << _s_n << endl;
	}
	static int _s_n;
private:
	int _count {1};
};
int Test::_s_n = 20;
int main()
{
	Test t;
	cout << sizeof(t) << endl;
	cout << sizeof(Test) << endl;
	cout << Test::_s_n << endl;
	cout << Test()._s_n << endl;
	cout << t._s_n << endl;
	Test::func();
	return 0;
}

#if 0
// Singleton 单例模式测试
int main()
{
	Singleton* s1 = Singleton::get_instance();
	Singleton* s2 = Singleton::get_instance();
	s1->print("单例模式");
	s1->print("测试");
	s1->print("入职证明");
	s1->print("通知信息");
	cout << "_count = " << s1->_count << endl;

	s2->print("打印机打印");
	cout << "s1->_count = " << s1->_count << endl;
	cout << "s2->_count = " << s2->_count << endl;

	return 0;
}
#endif

#if 0
// static测试
class Person {
	/*
		1、静态成员变量
			1）静态成员变量： 编译阶段才分配空间
			2）类内声明，类外初始化
			3）静态成员变量，所有对象共享一份数据
	*/
public:
	// const静态成员属性
	const static int _s_share = 23;	// 类内初始化，并且在只读区，不可修改
	static int _s_a;
	int _b;
	/* 
		2、静态成员函数
		所有对象都共享该函数
	*/
	static void func() {
		// 静态成员函数没有隐含的this指针
		// _b = 12; //静态成员函数，不能访问非静态成员变量
		_s_a = 100;
		cout << "static func调用" << endl;
	}

	void fun3() {
		_b = 20;
		_s_a = 30;
		cout << "func3调用" << endl;
	}

private:
	static int _s_c;
	static void func2();
};
// 注意： 在类外定义静态成员时，不能再出现static关键字
// static关键字只出现在类内部声明中
//! static int Person::_s_a = 10; //error
int Person::_s_a = 10;
int Person::_s_c = 11;

void Person::func2() {
	cout << "static func2调用" << endl;
}

// static成员变量/函数的访问方式
void test01()
{
	//1. 通过对象进行访问
	Person p1;
	cout << "p1._s_a = " << p1._s_a << endl;
	p1.func();
	cout << "_s_a = " << p1._s_a << endl;	// 100
	p1.fun3();
	cout << "_s_a = " << p1._s_a << endl;	// 30


	Person p2;
	p2._s_a = 100;
	cout << "p1._s_a = " << p1._s_a << endl;

	//2、通过类名进行访问
	cout << Person::_s_a << endl;
	Person::func();

	//静态成员变量也是有访问权限， 私有权限类外访问不到！
	// cout << Person::_s_c << endl;

	//3、通过匿名对象进行访问
	cout << Person()._s_a << endl;
	Person().func();
}

int main()
{
	test01();
	cout << Person::_s_share << endl;
	//! Person::_s_share = 10; 不可修改
	return 0;
}
#endif

