#include <iostream>
#include <string>
#include "Singleton.h"
using std::cout;
using std::endl;

class A {
	static int _s_n;
};
int A::_s_n = 10;

class Test {
public:
	static void func() {
		_s_n = 100;
		// cout << "_count = " << _count << endl; // �޷����ʷǾ�̬���ݳ�Ա
		cout << "_s_n = " << _s_n << endl;
	}
	static int _s_n;
private:
	int _count {1};
};
int Test::_s_n = 20;
int main()
{
	Test t;
	cout << sizeof(t) << endl;
	cout << sizeof(Test) << endl;
	cout << Test::_s_n << endl;
	cout << Test()._s_n << endl;
	cout << t._s_n << endl;
	Test::func();
	return 0;
}

#if 0
// Singleton ����ģʽ����
int main()
{
	Singleton* s1 = Singleton::get_instance();
	Singleton* s2 = Singleton::get_instance();
	s1->print("����ģʽ");
	s1->print("����");
	s1->print("��ְ֤��");
	s1->print("֪ͨ��Ϣ");
	cout << "_count = " << s1->_count << endl;

	s2->print("��ӡ����ӡ");
	cout << "s1->_count = " << s1->_count << endl;
	cout << "s2->_count = " << s2->_count << endl;

	return 0;
}
#endif

#if 0
// static����
class Person {
	/*
		1����̬��Ա����
			1����̬��Ա������ ����׶βŷ���ռ�
			2�����������������ʼ��
			3����̬��Ա���������ж�����һ������
	*/
public:
	// const��̬��Ա����
	const static int _s_share = 23;	// ���ڳ�ʼ����������ֻ�����������޸�
	static int _s_a;
	int _b;
	/* 
		2����̬��Ա����
		���ж��󶼹���ú���
	*/
	static void func() {
		// ��̬��Ա����û��������thisָ��
		// _b = 12; //��̬��Ա���������ܷ��ʷǾ�̬��Ա����
		_s_a = 100;
		cout << "static func����" << endl;
	}

	void fun3() {
		_b = 20;
		_s_a = 30;
		cout << "func3����" << endl;
	}

private:
	static int _s_c;
	static void func2();
};
// ע�⣺ �����ⶨ�徲̬��Աʱ�������ٳ���static�ؼ���
// static�ؼ���ֻ���������ڲ�������
//! static int Person::_s_a = 10; //error
int Person::_s_a = 10;
int Person::_s_c = 11;

void Person::func2() {
	cout << "static func2����" << endl;
}

// static��Ա����/�����ķ��ʷ�ʽ
void test01()
{
	//1. ͨ��������з���
	Person p1;
	cout << "p1._s_a = " << p1._s_a << endl;
	p1.func();
	cout << "_s_a = " << p1._s_a << endl;	// 100
	p1.fun3();
	cout << "_s_a = " << p1._s_a << endl;	// 30


	Person p2;
	p2._s_a = 100;
	cout << "p1._s_a = " << p1._s_a << endl;

	//2��ͨ���������з���
	cout << Person::_s_a << endl;
	Person::func();

	//��̬��Ա����Ҳ���з���Ȩ�ޣ� ˽��Ȩ��������ʲ�����
	// cout << Person::_s_c << endl;

	//3��ͨ������������з���
	cout << Person()._s_a << endl;
	Person().func();
}

int main()
{
	test01();
	cout << Person::_s_share << endl;
	//! Person::_s_share = 10; �����޸�
	return 0;
}
#endif

