#pragma once
#include <iostream>

// 定义一个使用引用计数的类

class HasPtr
{
public:
	HasPtr(const std::string& s = std::string())
		: _ps(new std::string(s)), _i(0), _use(new size_t(1))
	{}


	HasPtr(const HasPtr& p)
		: _ps(p._ps),	// 拷贝指针，指向同一块资源(内存)
		_i(p._i),
		_use(p._use)
	{
		++*_use;	// 每次拷贝，就多一个对象管理同一块资源,递增计数器
	}

	HasPtr& operator = (const HasPtr&);
	size_t get_count() {
		return *_use;
	}
	~HasPtr();

private:
	std::string* _ps;
	int _i;
	size_t* _use;	// 用来记录有多少个对象共享*ps的成员（即共享资源）
};


