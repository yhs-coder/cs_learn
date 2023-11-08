#pragma once
#include<iostream>
using std::cout;
using std::endl;

class Man
{
public:
	Man(int age = 0) : _age(age) {
		cout << "Man的有参构造" << endl;
	}
	void show_age() {
		cout << "age = " << _age << endl;
	}

	~Man() {
		cout << "Man的析构调用" << endl;
	}

private:
	int _age;
};

class SmartPointer
{
public:
	SmartPointer(Man* Man) 
		: _man(Man) {}

	// 重载 -> 运算符
	Man* operator -> () {
		return _man;
	}

	// 重载*运算符
	Man& operator*() {
		return *_man;
	}

	~SmartPointer() {
		if (_man != nullptr) {
			delete _man;
			_man = nullptr;
		}
	}
private:
	Man* _man;
};
