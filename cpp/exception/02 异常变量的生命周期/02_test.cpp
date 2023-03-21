#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;


class MyException
{
public:
	MyException()
	{
		cout << "MyException默认构造函数调用" << endl;
	}
	MyException(const MyException& e)
	{
		cout << "MyException拷贝构造函数调用" << endl;
	}
	~MyException()
	{
		cout << "MyException析构构造函数调用" << endl;
	}
};




void doWork()
{
	
	/*
		throw抛出的异常对象具有特殊的生命周期行为。
		解释：
			1.调用 MyException 的默认构造函数，创建一个匿名的 MyException 对象
			2.将这个匿名对象复制到一个临时对象中，并且延长它的生命周期，以便它可以在 catch 块中被访问和处理。
			3.抛出这个临时对象，让控制流程进入异常处理模式。
			4.如果throw MyException() 创建的匿名对象在执行完离开当前作用域时被销毁，则无法被一场捕获和处理！
	*/
	//throw MyException();

	/*MyException excp;
	throw &excp;*/

	throw new MyException();

}

void test01()
{
	try
	{
		doWork();
	}
	//抛出的是 throw MyException();  catch (MyException e) 调用拷贝构造函数 效率低
	//抛出的是 throw MyException();  catch (MyException &e)  只调用默认构造函数 效率高 推荐
	//抛出的是 throw &MyException(); catch (MyException *e) 对象会提前释放掉，不能在非法操作
	//抛出的是 new MyException();   catch (MyException *e) 只调用默认构造函数 自己要管理释放
	catch (MyException *e)
	{
		cout << "自定义异常捕获" << endl;
		delete e;
	}
}

int main()
{
	test01();
	system("pause");
	return 0;
}