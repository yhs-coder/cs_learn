#include "HasPtr.h"


HasPtr::~HasPtr()
{
	if (--*_use == 0) {  // 如果计数器为0，即管理资源的对象为0
		// 释放计数器和_ps指向的
		delete _use;
		_use = nullptr;
		delete _ps;
		_ps = nullptr;
		std::cout << "delete...." << std::endl;
 	}
}

HasPtr& HasPtr::operator = (const HasPtr& rhs)
{
	++* rhs._use;	// 先递增右侧对象的引用计数
	if (-- * this->_use == 0) { // 递减左侧对象的引用计数
		delete _ps;	// 释放本对象管理的资源
		_ps = nullptr;
		delete _use;
		_use = nullptr;
	}
	_ps = rhs._ps;
	_i = rhs._i;
	_use = rhs._use;
	return *this;
}