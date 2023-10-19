#pragma once
#include <iostream>
using std::cout;
using std::endl;

// 1. �����ռ����ͨ����
namespace  A {
	int a;
	void show() {
		std::cout << "A::show" << std::endl;
	}

	class N {};
}

// 2. �ɴ��ڶ����ͬ���Ƶ������ռ䣬���������Ὣ���Ա�ϳ���ͬһ�������ռ���
namespace A{
	// ��ԭ�е������ռ����������µĳ�Ա
	int c;

	//��error,�������ض����Ѿ����ڵĳ�Ա
	// int a;
}
 

// 3. �����ռ��Ƕ��
namespace  B {
	namespace C {
		int b;
	}
}

// 4. �����ռ��ʹ��
//4.1 �����ռ����Ƽ��������޶���
void test01()
{
	// �����ռ�����::�����ռ��Ա
	A::a = 10;
	cout << "A::a = " << A::a << endl;
}

//4.2 ʹ��using�����������ռ��еĳ�Ա����
using A::a;
void test02()
{
	// �����ռ�����::�����ռ��Ա
	A::a = 20;
	cout << "A::a = " << A::a << endl;
}

// 4.3 ʹ�� ��using namespace �����ռ����ơ� �������ռ���ȫ����Ա����
using namespace A;
void test03()
{
	// �����ռ�����::�����ռ��Ա
	A::a = 30;
	cout << "A::a = " << A::a << endl;
	show();
}

// 5. �����ռ�ֻ����ȫ�ַ�Χ�ڶ���
void test04() {
	// ����д��
	/*namespace A {
		int a = 10;
	}
	namespace B {
		int a = 20;
	}
	cout << "A::a : " << A::a << endl;
	cout << "B::a : " << B::a << endl;*/
}

//6. ������ʵ�ֿɷ���
namespace A {
	void func1();
	void func2(int param);
}

void A::func1() {
	cout << "A::func" << endl;
}

void A::func2(int param) {
	cout << "A::func2 : " << param << endl;
}


//7. ���������ռ�
namespace {
	int num = 10;
	void print() {
		cout << "hello world" << endl;
	}
}

void test05()
{
	cout << "num = " << num << endl;
	print();
}

// 7. �����ռ����
namespace LongName {
	int a = 100;
	void f() {
		std::cout << "f()" << std::endl;
	}
}

void test06()
{
	namespace ShortName = LongName;
	cout << "LongName::a = " << ShortName::a << endl;
	LongName::f();
	ShortName::f();
}

void test07()
{
	using namespace LongName;
	cout << num << endl;
	
	int num = 1024;
	cout << num << endl;

}


int main()
{
	/*test01();
	test02();
	test03();
	A::func1();
	test05();
	test06();*/
	test07();


	return 0;
}



