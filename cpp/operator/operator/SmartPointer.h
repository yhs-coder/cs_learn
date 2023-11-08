#pragma once
#include<iostream>
using std::cout;
using std::endl;

class Man
{
public:
	Man(int age = 0) : _age(age) {
		cout << "Man���вι���" << endl;
	}
	void show_age() {
		cout << "age = " << _age << endl;
	}

	~Man() {
		cout << "Man����������" << endl;
	}

private:
	int _age;
};

class SmartPointer
{
public:
	SmartPointer(Man* Man) 
		: _man(Man) {}

	// ���� -> �����
	Man* operator -> () {
		return _man;
	}

	// ����*�����
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
