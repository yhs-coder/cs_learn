#include "HasPtr.h"


HasPtr::~HasPtr()
{
	if (--*_use == 0) {  // ���������Ϊ0����������Դ�Ķ���Ϊ0
		// �ͷż�������_psָ���
		delete _use;
		_use = nullptr;
		delete _ps;
		_ps = nullptr;
		std::cout << "delete...." << std::endl;
 	}
}

HasPtr& HasPtr::operator = (const HasPtr& rhs)
{
	++* rhs._use;	// �ȵ����Ҳ��������ü���
	if (-- * this->_use == 0) { // �ݼ�����������ü���
		delete _ps;	// �ͷű�����������Դ
		_ps = nullptr;
		delete _use;
		_use = nullptr;
	}
	_ps = rhs._ps;
	_i = rhs._i;
	_use = rhs._use;
	return *this;
}