#pragma once
#include <iostream>

class Test
{
	// ����������<<���غ�������Ϊ��Ԫ
	friend std::ostream& operator << (std::ostream& os, const Test& p);

	//  �����������>>���غ�������Ϊ��Ԫ
	friend std::istream& operator >> (std::istream& is, Test& p);

public:
	Test(int a = 0, int b = 0) : _a(a), _b(b) {}

	// ����������<<���غ�����Ϊ��Ա����ʱ����Ȼ����ʵ�֣�����ϰ����Υ��
	/*void operator << (std::ostream& cout)
	{
		//p.operator<<(cout)  ==>  p<<cout!
		cout << "_a = " << _a << " _b = " << _b;
	}*/
	int get_value_a() {
		return _a;
	}
	int get_value_b() {
		return _b;
	}

	void set_value_a(int a) {
		_a = a;
	}
	void set_value_b(int b)
	{
		_b = b;
	}



private:
	int _a;
	int _b;
};

//// ������������ <<  ��Ҫ�Ѻ�������ʵ�ַŵ�Test.cpp�ļ��У��������ӳ���
//std::ostream& operator << (std::ostream& os, const Test& p)
//{
//	os << "_a = " << p._a << " _b = " << p._b;
//	return os;
//}

//����ȫ�ֺ���ʵ�ּӺ���������أ�
Test operator + (Test& p1, Test& p2);




