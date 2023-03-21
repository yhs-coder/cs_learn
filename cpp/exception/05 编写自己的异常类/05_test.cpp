#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;


class MyOutOfRangeException : public exception
{
public:
	MyOutOfRangeException(const char* str)
	{
		//const char * 可以隐式类型转换为 string  反之不可以
		m_errorInfo = str;
	}
	MyOutOfRangeException(string str)
	{
		m_errorInfo = str;
	}

    //_NODISCARD virtual char const* what() const 重写exception基类中的what函数
	 virtual const char* what() const
	{
		//将string 转为 const char * 
		return m_errorInfo.c_str();
	}
	string m_errorInfo;
};


class Person
{
public:
	Person(int age)
	{
		if (age < 0 || age > 150)
		{
			throw MyOutOfRangeException(string("MyOutOfRange:年龄必须在0到150之间"));
		}
		else
		{
			this->m_Age = age;
		}
	}

	int m_Age;
};

void test01()
{
	try
	{
		Person p(1000);
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
	}

}

int main()
{
	test01();
	system("pause");
	return 0;
}




