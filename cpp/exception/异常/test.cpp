#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;



class MyException
{
public:
	void printError()
	{
		cout << "MyException类型异常捕获" << endl;
	}
};

class Person
{
public:
	Person()
	{
		cout << "Person的默认构造函数调用" << endl;
	}
	~Person()
	{
		cout << "Person的析构函数调用" << endl;
	}
};



int myDivision(int a, int b)
{
	if (b == 0)
	{
		//return -1;
		//throw - 1; //抛出int 类型的异常
		//throw 'a'; //抛出char 类型的异常
		//throw 3.14; //抛出double类型的异常

		/*string str = "abc";
		throw str;*/

		//从try代码块开始，到throw抛出异常之前，所有栈上的数据都会被释放掉，
		//释放的顺序和创建顺序相反的，这个过程我们称为栈解旋
		Person p1;
		Person p2;
		throw MyException(); //抛出MyException的匿名对象
		
	}
	return a / b;
}


void test01()
{
	int a = 10;
	//int b = 0;
	//如果传进去的是-10
	int b = 0;
	//C语言处理异常 有缺陷：返回值不统一，返回值只有一个，无法区分是结果还是异常
	//int ret = myDivision(a, b);
	//if (ret == -1)
	//{
	//	cout << "异常" << endl;
	//}

	try
	{
		myDivision(a, b);
	}
	catch (int)
	{
		cout << "int类型异常捕获" << endl;
	}
	catch (char)
	{
		cout << "char类型异常捕获" << endl;
	}
	catch (double)
	{
		//捕获到了异常，但是不想处理，继续向上抛出这个异常
		//异常必须有函数进行处理，如果没有任何处理，程序自动调用 terminate 函数，让程序中断
		throw;
		cout << "double类型异常捕获" << endl;
	}
	catch (MyException e)
	{
		e.printError();
	}
	catch (...)
	{
		cout << "其他类型异常捕获" << endl;
	}
}


int main()
{
	//test01();

	try
	{
		test01();
	}
	catch (double)
	{
		cout << "main函数中 double类型异常捕获" << endl;
	}
	catch (...)
	{
		cout << "main函数中 其他类型异常捕获" << endl;
	}
	system("pause");
	return EXIT_SUCCESS;
}





