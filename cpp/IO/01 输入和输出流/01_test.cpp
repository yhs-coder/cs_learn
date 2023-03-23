#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <limits>
using namespace std;

/***********************************************
	标准输入流

	1.cin.get() 获取一个字符 
		1.1 使用 cin.get() 会从输入缓冲区中读取内容，而不是直接从屏幕输入读取内容。
		1.2 输入缓冲区是一段内存区域，它用于临时存储键盘或文件等输入设备输入的数据，然后再将其传输到程序中进行处理。在使用 cin.get() 时，如果输入缓冲区中没有任何数据，则会等待用户输入，直到用户输入数据并按下回车键时，cin.get() 才会读取输入缓冲区中的数据。
	2.cin.get(两个参数) 获取字符串
		2.1 利用cin.get获取字符串时候，换行符遗留在缓冲区中
		2.2 当 cin.get(buf, 1024) 函数读取输入时，它会读取到缓冲区中的所有字符，直到读取到 1024-1 个字符、遇到换行符 \n 或者遇到文件结尾为止。读取到的字符会存储在 buf 数组中，并在最后自动添加一个字符串终止符 '\0'，以表示字符串的结束。
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


////cin.ignore() 忽略 默认忽略1个字符， 如果填入参数X，代表忽略X个字符
void test04()
{
	cin.ignore(2);
	char c = cin.get();
	cout << "c = " << c << endl;
	cout << "c = " << c << endl;

}

//cin.peek() 偷窥
void test05()
{
	char c = cin.peek();
	cout << "c = " << c << endl;

	c = cin.get();
	cout << "c = " << c << endl;

	c = cin.get();
	cout << "c = " << c << endl;
}

//cin.putback() 放回
void test06()
{
	char b = cin.get();
	cin.putback(b);

	char buf[1024] = { 0 };
	cin.getline(buf, 1024);
	cout << buf << endl;
}

//案例1、 判断用户输入的内容 是字符串还是数字  12345     abcde
void test07()
{
	cout << "请输入一个字符串或者数字" << endl;
	char c = cin.peek();
	if (c >= '0' && c <= '9')
	{
		int num;
		cin >> num;
		cout << "您输入的是数字 为：" << num << endl;
	}
	else
	{
		char buf[1024] = { 0 };
		cin >> buf;
		cout << "您输入的是字符串 ：" << buf << endl;
	}

}

//案例2、 用户输入 0 ~ 10 之间的数字，如果输入有误，重新输入

void test08()
{
	int num;
	while (true)
	{
		
		cout << "请输入 0 ~ 10 之间的数字" << endl;
		cin >> num;
		//如果标志位为 0  代表缓冲区正常    如果标志位为1   缓冲区异常
		if (cin.fail()||num < 0 || num > 10 )
		{
			cout << "输入有误，请重新输入" << endl;
			cin.clear(); //用于清除流的错误状态标志
			cin.ignore(numeric_limits<streamsize>::max(), '\n');  // 清除输入缓冲区中的内容
			//cin.sync(); 在输入错误时，输入缓冲区中仍然有剩余的字符，而cin.sync()函数并不会清除输入缓冲区中的所有字符.所以这里不宜使用！
			
			//cin.sync()用于清除输入缓冲区中的任何未读取的字符
		} 
		else
		{
			break;
		}
	}
	cout << "您输入的数字是：" << num << endl;
}


int main() {
	//test01();
	//test02();
	//test03();
	//test04();
	//test05();
	//test06();
	//test07();
	test08();



	system("pause");
	return EXIT_SUCCESS;
}













