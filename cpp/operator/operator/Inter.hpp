#pragma once
/**
++/-- 运算符重载
**/

#include<iostream>
using std::cout;
using std::ostream;

class Inter
{
	friend ostream& operator << (ostream& os, const Inter& myInt);
public:
	Inter() {
		_num = 0;
	}

	//前置++ 重载   ++a,先运算，在返回
	Inter& operator ++ () {
		_num++;
		return *this;
	}

	//后置 ++ 重载   a++先返回，再运算
	Inter operator++(int) {
		//先记录初始状态
		Inter temp(*this);
		_num++;
		return temp;
	}

private:
	int _num;
};

ostream& operator << (ostream& os, const Inter& myInt) {
	os << "_num = " << myInt._num;
	return os;
}
