#pragma once
#include <iostream>

// ������Ϊ��ֵ����

class HasPtr
{
	friend void swap(HasPtr&, HasPtr&);
public:
	HasPtr(const std::string& s = std::string()) 
		: _ps(new std::string(s)), _i(0) 
		{}

	// ����_psָ���string,ÿ��HasPtr�������Լ��Ŀ����������
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


