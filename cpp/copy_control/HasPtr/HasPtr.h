#pragma once
#include <iostream>

// ����һ��ʹ�����ü�������

class HasPtr
{
public:
	HasPtr(const std::string& s = std::string())
		: _ps(new std::string(s)), _i(0), _use(new size_t(1))
	{}


	HasPtr(const HasPtr& p)
		: _ps(p._ps),	// ����ָ�룬ָ��ͬһ����Դ(�ڴ�)
		_i(p._i),
		_use(p._use)
	{
		++*_use;	// ÿ�ο������Ͷ�һ���������ͬһ����Դ,����������
	}

	HasPtr& operator = (const HasPtr&);
	size_t get_count() {
		return *_use;
	}
	~HasPtr();

private:
	std::string* _ps;
	int _i;
	size_t* _use;	// ������¼�ж��ٸ�������*ps�ĳ�Ա����������Դ��
};


