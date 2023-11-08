#include "Test.h"

// 重载输出运算符 << 
std::ostream& operator << (std::ostream& os, const Test& p)
{
	os << "_a = " << p._a << " _b = " << p._b;
	return os;
}

// 重载输入运算符 >> 重载函数
std::istream& operator >> (std::istream& is, Test& p)
{
	is >> p._a >> p._b;
	// 检查输入是否成功
	if (!is) {
		std::cout << "输入错误...";
		p._a = 0;
		p._b = 0;
	}
	return is;
}

//利用全局函数实现加号运算符重载！
Test operator + (Test& p1, Test& p2)
{
	Test temp;
	temp.set_value_a(p1.get_value_a() + p2.get_value_a());
	temp.set_value_b(p1.get_value_b() + p2.get_value_b());
	return temp;
}