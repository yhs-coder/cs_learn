#pragma once
#include <iostream>

class Test
{
	// 将输出运算符<<重载函数声明为友元
	friend std::ostream& operator << (std::ostream& os, const Test& p);

	//  将输入运算符>>重载函数声明为友元
	friend std::istream& operator >> (std::istream& is, Test& p);

public:
	Test(int a = 0, int b = 0) : _a(a), _b(b) {}

	// 当输出运算符<<重载函数作为成员函数时，虽然可以实现，但与习惯相违背
	/*void operator << (std::ostream& cout)
	{
		//p.operator<<(cout)  ==>  p<<cout!
		cout << "_a = " << _a << " _b = " << _b;
	}*/
	int get_value_a() {
		return _a;
	}
	int get_value_b() {
		return _b;
	}

	void set_value_a(int a) {
		_a = a;
	}
	void set_value_b(int b)
	{
		_b = b;
	}



private:
	int _a;
	int _b;
};

//// 重载输出运算符 <<  需要把函数具体实现放到Test.cpp文件中，否则链接出错！
//std::ostream& operator << (std::ostream& os, const Test& p)
//{
//	os << "_a = " << p._a << " _b = " << p._b;
//	return os;
//}

//利用全局函数实现加号运算符重载！
Test operator + (Test& p1, Test& p2);




