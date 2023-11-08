#pragma once
#include <iostream>
#include <cstring>

class Person
{
	// 重载输出运算符 << 
	friend std::ostream& operator << (std::ostream& os, const Person& p);
// 编译器 默认给一个类4个函数   默认构造   析构   拷贝构造 （值拷贝）  operator= (值拷贝)
public:
	Person(char* name, int age) {
		_name = new char[strlen(name) + 1];
		strcpy(_name, name);
		_age = age;
	}

	// 赋值重载 =, 深拷贝
	Person& operator= (const Person& p) {
		// 先判断原来堆区释放有内容，如果有先释放
		if (_name != nullptr) {
			delete[] _name;
			_name = nullptr;
		}
		_name = new char[strlen(p._name) + 1];
		strcpy(_name, p._name);
		_age = p._age;
		return *this;
	}

	// 拷贝构造, 深拷贝
	Person(const Person& p) {
		_name = new char[strlen(p._name) + 1];
		strcpy(_name, p._name);
		_age = p._age;
	}

	//关系运算符： == 运算符重载
	bool operator == (const Person& p) {
		return _age == p._age && strcmp(_name, p._name);
	}

	bool operator != (const Person& p) {
		return !(*this == p);
	}

	~Person()
	{
		if (_name != nullptr)
		{
			std::cout << "_name已释放内存..." << std::endl;
			delete[] _name;
			_name = nullptr;
		}
	}

	char* _name;
	int _age;
};



