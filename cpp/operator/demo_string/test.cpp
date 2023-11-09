#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"String.h"
using std::cout;
using std::endl;
using std::cin;


void test01()
{
	String str = (char*)"abc";
	cout << str << endl;
	cout << "请重新给str赋值：" << endl;
	cin >> str;
	cout << "str 新的值为： " << str << endl;

	String str2 = str;
	cout << "str2 = " << str2 << endl;
	String str3;
	cout << "------------------------" << endl;
	str3 = str2;
	cout << "str3 = " << str3 << endl;
}

void test02()
{
	String str = (char*)"abcd";
	String str2 = (char*)"aaa";
	str2 = str;
	cout << "str2 = " << str2 << endl;
	cout << "str2[0] = " << str2[0] << endl;
	str2[0] = 'z';
	cout << "str2[0]改为z后输出：  " << str2 << endl;

	String str3 = (char*)"abc";
	String str4 = (char*)"def";
	String str5 = str3 + str4;
	String str6 = str5 + "ghe";
	cout << "str5 = " << str5 << endl;
	cout << "str6 = " << str6 << endl;

	if (str5 == str6)
	{
		cout << "str5 == str6" << endl;
	}
	else
	{
		cout << "str5 != str6" << endl;
	}

	if (str6 == "abcdefghe")
	{
		cout << "str6 = abcdefghe" << endl;
	}
	else
	{
		cout << "str6 != abcdefghe" << endl;
	}
}
#if 0
int main()
{
	test01();
	test02();
	system("pause");
	return 0;
}
#endif

#include <vector>

struct X
{
	X() { std::cout << "X()" << std::endl; }
	X(const X&) { std::cout << "X(const X&)" << std::endl; }
	X& operator=(const X&) { std::cout << "X& operator=(const X&)" << std::endl; return *this; }
	~X() { std::cout << "~X()" << std::endl; }
};

void f(const X& rx, X x)
{
	std::vector<X> vec;
	vec.reserve(2);
	vec.push_back(rx);
	vec.push_back(x);
}

int main()
{
	X* px = new X;
	f(*px, *px);
	delete px;

	return 0;
}

