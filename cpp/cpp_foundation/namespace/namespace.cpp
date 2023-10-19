#pragma once
#include <iostream>
using std::cout;
using std::endl;

// 1. 命名空间的普通定义
namespace  A {
	int a;
	void show() {
		std::cout << "A::show" << std::endl;
	}

	class N {};
}

// 2. 可存在多个相同名称的命名空间，编译器最后会将其成员合成在同一个命名空间中
namespace A{
	// 在原有的命名空间上增加了新的成员
	int c;

	//！error,不可以重定义已经存在的成员
	// int a;
}
 

// 3. 命名空间的嵌套
namespace  B {
	namespace C {
		int b;
	}
}

// 4. 命名空间的使用
//4.1 命名空间名称加作用域限定符
void test01()
{
	// 命名空间名称::命名空间成员
	A::a = 10;
	cout << "A::a = " << A::a << endl;
}

//4.2 使用using声明将命名空间中的成员引入
using A::a;
void test02()
{
	// 命名空间名称::命名空间成员
	A::a = 20;
	cout << "A::a = " << A::a << endl;
}

// 4.3 使用 “using namespace 命名空间名称” 将命名空间内全部成员引入
using namespace A;
void test03()
{
	// 命名空间名称::命名空间成员
	A::a = 30;
	cout << "A::a = " << A::a << endl;
	show();
}

// 5. 命名空间只能在全局范围内定义
void test04() {
	// 错误写法
	/*namespace A {
		int a = 10;
	}
	namespace B {
		int a = 20;
	}
	cout << "A::a : " << A::a << endl;
	cout << "B::a : " << B::a << endl;*/
}

//6. 声明和实现可分离
namespace A {
	void func1();
	void func2(int param);
}

void A::func1() {
	cout << "A::func" << endl;
}

void A::func2(int param) {
	cout << "A::func2 : " << param << endl;
}


//7. 无名命名空间
namespace {
	int num = 10;
	void print() {
		cout << "hello world" << endl;
	}
}

void test05()
{
	cout << "num = " << num << endl;
	print();
}

// 7. 命名空间别名
namespace LongName {
	int a = 100;
	void f() {
		std::cout << "f()" << std::endl;
	}
}

void test06()
{
	namespace ShortName = LongName;
	cout << "LongName::a = " << ShortName::a << endl;
	LongName::f();
	ShortName::f();
}

void test07()
{
	using namespace LongName;
	cout << num << endl;
	
	int num = 1024;
	cout << num << endl;

}


int main()
{
	/*test01();
	test02();
	test03();
	A::func1();
	test05();
	test06();*/
	test07();


	return 0;
}



