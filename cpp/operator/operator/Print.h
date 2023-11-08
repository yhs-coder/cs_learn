#pragma once
#include<iostream>
#include <string>
using std::cout;
using std::endl;

class Print
{
public:
	// 函数调用运算符重载
	void operator ()(std::string text) {
		cout << text << endl;
	}
};
