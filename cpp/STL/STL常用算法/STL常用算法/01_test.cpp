#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
using namespace std;

//函数对象（仿函数）是重载了函数调用操作符的类的对象
class Myprint
{
public:
	void operator()(int num)
	{
		cout << num << endl;
		m_count++;
	}
	int m_count = 0;
};

void myPrint02(int num)
{
	cout << num << endl;
}

void test01()
{
	Myprint myPrint;
	myPrint(100); //仿函数，本质上是重载了（）操作符的类实例化的对象，可以像函数那般调用，有参数，也可以有返回值

	myPrint02(1000);
}


//函数对象超出了普通函数的概念，可以保存函数的调用状态
void test02()
{
	Myprint myPrint;
	myPrint(100);
	myPrint(100);
	myPrint(100);
	myPrint(100);
	cout << "调用次数为： " << myPrint.m_count << endl;
}


//函数对象可以作为函数参数
void doPrint(Myprint myPrint, int num)
{
	myPrint(num);
}

void test03()
{
	doPrint(Myprint(), 222);
}

int main()
{
	//test01();
	//test02();
	test03();
	system("pause");
	return 0;
}

