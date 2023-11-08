#include "Test.h"

// ������������ << 
std::ostream& operator << (std::ostream& os, const Test& p)
{
	os << "_a = " << p._a << " _b = " << p._b;
	return os;
}

// ������������� >> ���غ���
std::istream& operator >> (std::istream& is, Test& p)
{
	is >> p._a >> p._b;
	// ��������Ƿ�ɹ�
	if (!is) {
		std::cout << "�������...";
		p._a = 0;
		p._b = 0;
	}
	return is;
}

//����ȫ�ֺ���ʵ�ּӺ���������أ�
Test operator + (Test& p1, Test& p2)
{
	Test temp;
	temp.set_value_a(p1.get_value_a() + p2.get_value_a());
	temp.set_value_b(p1.get_value_b() + p2.get_value_b());
	return temp;
}