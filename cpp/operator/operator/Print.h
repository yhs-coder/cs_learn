#pragma once
#include<iostream>
#include <string>
using std::cout;
using std::endl;

class Print
{
public:
	// �����������������
	void operator ()(std::string text) {
		cout << text << endl;
	}
};
