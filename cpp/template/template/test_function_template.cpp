#include <iostream>
#include "demo.h"
using std::cout;
using std::endl;

/*
	函数模板

	基本调用:
	1.直接调用:自动类型推导
	2.调用函数模板时，显式指定类型
*/

void _swap(int& a, int& b)
{
	cout << "_swap(int& a, int& b)..." << endl;
	int tmp = a;
	a = b;
	b = tmp;
}
void _swap(double& a, double& b)
{
	cout << "_swap(double& a, double& b)..." << endl;
	double tmp = a;
	a = b;
	b = tmp;
}

// 利用函数模板，实现通用交换函数
// T代表了一个通用类型，告诉编译器如果下面紧跟着的函数或者类中出现T不要报错
template <typename T>
void _swap(T& a, T& b)
{
	cout << "_swap(T& a, T& b)..." << endl;
	T tmp = a;
	a = b;
	b = tmp;
}

template <class T, class N>
void _swap2(T& a, N& b)
{
	cout << "_swap2(T& a, N& b)..." << endl;
	T temp = a;
	a = b;
	b = temp;
}

//模板不能单独使用，当没有类型参数时，必须指定出T才可以使用
template<class T>
void my_swap()
{
	cout << "my_swap()..." << endl;
}

int main()
{
#if 0
	int a = 10;
	int b = 20;
	char c1 = 'c';
	char c2 = 'd';
	double c = 3.14;
	double d = 4.14;
	_swap(a, b);
	_swap(c, d);

	// 1.自动类型推导 函数模板可以自动推导参数的类型
	_swap(c1, c2);
	cout << c1 << endl;
	cout << c2 << endl;
	// 函数模板只有一个类型参数，只接受一种数据类型
	// 推导不出一致的T,因此没法调用
	// _swap(a, c);
	_swap2(a, c);
	cout << a << endl;
	cout << c << endl;

	// 2. 显式指定类型
	_swap<int>(a, b);
	_swap<double>(c, d);

	// 当模板没有类型参数时，不能单独使用，必须指定出T才可以使用
	// my_swap(); // error
	my_swap<int>(); //✔

#else
	// char数组
	char char_array[] = "helloworld";
	int len = strlen(char_array);
	bubble_sort(char_array, len);
	print_array(char_array, len);
	cout << endl;

	int int_array[] = { 5, 7, 1, 4, 2, 3 };
	len = sizeof(int_array) / sizeof(int);
	bubble_sort(int_array, len);
	print_array(int_array, len);
#endif
	return 0;
}

