#include <iostream>
#include "Test.h"
#include "Person.h"
#include "Inter.hpp"
#include "SmartPointer.h"
#include "Print.h"

using std::cout;
using std::endl;



#if 0 
class Test
{
public:
	Test(int m = 0):_a(m){}
	
	Test& operator += (Test& t)
	{
		this->_a += t._a;
		return *this;
	}

	int _a;
};

Test operator+(Test& a, Test& b)
{
	return Test(a._a + b._a);
}



void test_person()
{
	Person p1((char*)"Tom", 10);
	Person p2((char*)"Jetty", 20);
	if (p1 == p2) {
		cout << "p1 == p2 " << endl;
	} else {
		cout << "p1 != p2 " << endl;
	}

	if (p1 != p2) {
		cout << "p1 != p2 " << endl;
	} else {
		cout << "p1 == p2 " << endl;
	}	
	// 拷贝赋值
	p2 = p1;
	Person p3((char*)" ", 0);
	p3 = p2;

	Person p4 = p3 = p1;
	cout << p2;
	cout << endl;
	cout << p3;
	cout << endl;
	cout << p4;
	cout << endl;


}

void test_inter()
{
	// 测试前置/后置++
	Inter a;
	cout << ++(++a) << endl;// 2

	cout << a++ << endl;	// 2
	cout << a << endl;		// 3

	// 显示调用后置运算符
	cout << a.operator++(10) << endl;	//3 后置++

	a.operator++();		// 前置++
	cout << a << endl;		// 5

}

void test()
{
	Test p(10, 20);
	cout << p << endl;
	// 可以使用，但与习惯相悖
	/*p << cout;
	p.operator<<(cout);*/

#if 0 
	// 测试重载输入运算符 
	std::cin >> p;
	cout << p << endl; 
#endif

	// 测试加号运算符重载
	Test p2(20, 20);
	Test p3 = p + p2;
	cout << p3;
	cout << endl;
	p3 = operator+(p2, p3);
	cout << p3;
}
#endif

void test_smartpoint() {
	Man* p = new Man(22);
	p->show_age();
	(*p).show_age();
	delete p;

	//利用智能指针管理 new 出来的person对象
	SmartPointer sp(new Man(10));
	sp->show_age();   //sp->  == Person*  本质上是 sp->->showAge() ;被编译器简化为 sp->showAge();
	(sp.operator->())->show_age();
	(*sp).show_age(); 
	sp.operator*().show_age();
}

void print2(std::string str)
{
	cout << str << endl;
}
void test_print()
{
	Print print;
	print("hello world!");// 仿函数  本质是一个对象,函数对象
	print2("hello world!"); //普通函数
}
int main()
{
//	Test t1, t2;
//	Test tmp = t1 + t2;		  // 像普通的表达式一样使用
//	std::cout << tmp._a << std::endl; // 0
//	tmp = operator+(t1, t2);  // 等价的函数调用
//	std::cout << tmp._a << std::endl; // 0

	//test();
	//test_person();
	//test_inter();
	test_smartpoint();
	//test_print();
	return 0;
}