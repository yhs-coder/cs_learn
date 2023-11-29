#include <iostream>
#include <string>
using std::cout;
using std::endl;

template <class T1, class T2>
class Person;

// 告诉编译器这个函数模板是存在
template <class T1, class T2>
void print_person(Person<T1, T2>& p);

// 友元函数在类实现
template <class T1, class T2>
class Person
{
	// 1. 友元函数在类内实现
	friend void print_person(Person<T1, T2>& p) {
		cout << "name: " << p.name_ << " age：" << p.age_ << endl;
	}

	// 2.友元函数类外实现 ,告诉编译器这个函数模板是存在
	friend void print_person2<>(Person<T1, T2>& p);
	
	// 3.类模板使用友元函数模板
	template <class U1, class U2>
	friend void print_person(Person<U1, U2>& p);

public:
	Person(T1 name, T2 age)
		: name_(name)
		, age_(age) {}

	void show() {
		cout << "name: " << name_ << " age：" << age_ << endl;
	}

private:
	T1 name_;
	T2 age_;

};


// 2.友元函数类外实现 (类模板碰到友元函数)
//友元函数类外实现 ,在友元类内声明时需要加上<>空参数列表，告诉编译去匹配函数模板
template <class T1, class T2>
void print_person2(Person<T1, T2>& p)
{
	cout << "name: " << p.name_ << " age：" << p.age_ << endl;
}

void test1() 
{
	Person<std::string, int> p("jerry", 100);
	p.show();
	print_person(p);
}

void test2()
{
	Person<std::string, int> p("jerry", 100);
	print_person2(p);
}
int main()
{
	test1();
	return 0;
}