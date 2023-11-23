#include <iostream>
#include <string>
using std::cout;
using std::endl;

/********************************************************
	类模板
********************************************************/


template <class NAMETYPE, class AGETYPE>
class Person
{
public:
	Person(NAMETYPE name, AGETYPE age)
		: name_(name)
		, age_(age) {}
	void show() {
		cout << "姓名：" << name_ << " 年龄：" << age_ << endl;

	}

	NAMETYPE name_;
	AGETYPE age_;
};

void test1()
{
	/* 类模板和函数模板的区别：
		1. 类模板不可以使用自动类型推导，只能用显示指定类型
		2. 类模板中，可以有默认参数
	*/
	//Person p1("jerry", 100); //错误！缺少类模板参数列表
	Person<std::string, int> p1("tom", 100);
	p1.show();
}

/********************************************************
	类模板中成员函数的创建时机:
	- 类模板中的成员函数，并不是一开始创建的，而是在运行阶段确定出T的数据类型才去创建

********************************************************/

class Person1
{
public:
	Person1() {
		cout << "Person1 调用" << endl;
	}

	void show_person1() {
		cout << "Person1 show 调用" << endl;
	}
};

class Person2
{
public:
	Person2()  {
		cout << "Person2 调用" << endl;
	}

	void show_person2() {
		cout << "Person2 show 调用" << endl;
	}

};

template <class T>
class MyClass
{
public:

	void func1() {
		obj_.show_person1();
	}

	void func2() {
		obj_.show_person2();
	}
	T obj_;
};

void test2()
{
	MyClass <Person1> p1;
	MyClass <Person2> p2;

	cout << "--------------------------" << endl;
	p1.func1();
	p2.func2();

}

int main()
{
	test1();
	test2();
	return 0;
}
