#pragma once
#include <iostream>

// 定义行为像值的类

class HasPtr
{
	friend void swap(HasPtr&, HasPtr&);
public:
	HasPtr(const std::string& s = std::string()) 
		: _ps(new std::string(s)), _i(0) 
		{}

	// 对于_ps指向的string,每个HasPtr对象都有自己的拷贝，即深拷贝
	HasPtr(const HasPtr& p) 
		: _ps(new std::string(*p._ps)), _i(p._i)
		{}

	HasPtr& operator = (HasPtr);
	
	std::string* get_ps();
	~HasPtr() {
		std::cout << "delete _ps..." << std::endl;
		delete _ps;
	}

private:
	std::string* _ps;
	int _i;
};


