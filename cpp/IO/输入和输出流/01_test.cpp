#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

/***********************************************
	标准输入流

	1.cin.get() 获取一个字符
	2.cin.get(两个参数) 获取字符串
		2.1 利用cin.get获取字符串时候，换行符遗留在缓冲区中
	3.cin.getline() 获取字符串
		3.1 利用cin.getline获取字符串时候，换行符不会被取走，也不在缓冲区中，而是直接扔掉
	4.cin.ignore() 忽略 默认忽略1个字符， 如果填入参数X，代表忽略X个字符
	5.cin.peek()  偷窥
	6.cin.putback()  放回 放回原位置
*************************************************/

void test01()
{
	//输入  a  s     第一次 a  第二次  s  第三次 换行  第四次 等待下次输入

	char c = cin.get();
	cout << "c = " << c << endl;

	c = cin.get();
	cout << "c = " << c << endl;

	c = cin.get();
	cout << "c = " << c << endl;	

	c = cin.get();
	cout << "c = " << c << endl;

}

void test02()
{
	char buf[1024] = { 0 };
	cin.get(buf, 1024);
	char c = cin.get();
	cout << "c = " << c << endl;
	//利用cin.get获取字符串时候，换行符遗留在缓冲区中
	if (c == '\n') {
		cout << "换行符遗留在缓冲区了！" << endl;
	}
	else
	{
		cout << "换行符不在缓冲区中！" << endl;
	}
	cout << buf << endl;
}

void test03()
{
	char buf[1024] = { 0 };
	//利用cin.getline获取字符串时候，换行符不会被取走，也不在缓冲区中，而是直接扔掉
	cin.getline(buf, 1024);
	char c = cin.get();
	if (c == '\n')
	{
		cout << "换行符遗留在缓冲区" << endl;
	}
	else
	{
		cout << "换行符不在缓冲区" << endl;
	}
	cout << buf << endl;
}

int main() {
	test01();
	//test02();
	//test03();
	//test04();
	//test05();
	//test06();
	//test07();
	//test08();



	system("pause");
	return EXIT_SUCCESS;
}













