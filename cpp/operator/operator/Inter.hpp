#pragma once
/**
++/-- ���������
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

	//ǰ��++ ����   ++a,�����㣬�ڷ���
	Inter& operator ++ () {
		_num++;
		return *this;
	}

	//���� ++ ����   a++�ȷ��أ�������
	Inter operator++(int) {
		//�ȼ�¼��ʼ״̬
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
