#include <iostream>
#include <string>
using std::cout;
using std::endl;

/********************************************************
	类模板的应用：
		1. 让类模板做为函数参数
			1.1 指定模板参数传入类型
			1.2 函数参数模板化
			1.3 整个类模板化
		2. 使用类模板派生普通类
		3. 使用类模板派生类模板
********************************************************/



// 注意：类模板中，可以有默认参数
template <class NAMETYPE, class AGETYPE>
class Person
{
public:
	Person(NAMETYPE name = "tom", AGETYPE age = 10)
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
	Person<std::string, int> p1;
	p1.show();
}

/**************************************************
1. 类模板做为函数参数
**************************************************/
// 1.1 指定(参数)传入类型
void show_person(Person<std::string, int>& p)
{
	p.show();
}

void test2()
{
	Person<std::string, int> p("jerry", 10);
	show_person(p);
}

// 1.2 参数模板化
template <class T1, class T2>
void show_person2(Person<T1, T2>& p)
{
	//编译器利用模板参数推导，推导出p的参数类型是     Person<string,int>
	p.show();
	cout << "T1数据类型： " << typeid(T1).name() << endl;
	cout << "T2数据类型： " << typeid(T2).name() << endl;
}
void test3()
{
	Person <std::string, int> p("Tomy", 88);
	show_person2(p);
}

// 1.3 函数参数类型 整个类模板化 --> 函数模板
template <class T>
void show_person3(T& p)
{
	cout << "T的数据类型： " << typeid(T).name() << endl;
	p.show();
}
void test4()
{
	Person <std::string, int> p("john", 66);
	show_person3(p);
}

/**************************************************
2. 使用类模板派生普通类
**************************************************/

template <class T>
class Base
{
public:
	T a_;
};

// 
// 当继承于类模板时，子类必须指定父类中的T数据类型，才能给子类分配内存
class Derived : public Base<double>
{
};

/**************************************************
2. 使用类模板派生类模板
**************************************************/
template <class T>
class Base2
{
public:
	Base2() {
		cout << "T Type :" << typeid(T).name() << endl;
	}
	T b_;
};
template <class T1, class T2>
class Derived2 : public Base2<T2>
{
public:
	Derived2() {
		cout << "call Derive " << endl;
		cout << "T1 Type: " << typeid(T1).name() << endl;
		cout << "T2 Type: " <<typeid(T2).name() << endl;
	}
	T1 c_;
};

void test5()
{
	cout << "sizeof(Derived) :" << sizeof(Derived) << endl;
	Derived2 <int, double> d;
}


int main()
{
	/*test1();
	test2();
	test3();*/
	//test4();
	test5();
	return 0;
}
