#include <iostream>
#include <string>
using std::cout;
using std::endl;

/********************************************************
	��ģ���Ӧ�ã�
		1. ����ģ����Ϊ��������
			1.1 ָ��ģ�������������
			1.2 ��������ģ�廯
			1.3 ������ģ�廯
		2. ʹ����ģ��������ͨ��
		3. ʹ����ģ��������ģ��
********************************************************/



// ע�⣺��ģ���У�������Ĭ�ϲ���
template <class NAMETYPE, class AGETYPE>
class Person
{
public:
	Person(NAMETYPE name = "tom", AGETYPE age = 10)
		: name_(name)
		, age_(age) {}
	void show() {
		cout << "������" << name_ << " ���䣺" << age_ << endl;

	}

	NAMETYPE name_;
	AGETYPE age_;
};

void test1()
{
	Person<std::string, int> p1;
	p1.show();
}

/**************************************************
1. ��ģ����Ϊ��������
**************************************************/
// 1.1 ָ��(����)��������
void show_person(Person<std::string, int>& p)
{
	p.show();
}

void test2()
{
	Person<std::string, int> p("jerry", 10);
	show_person(p);
}

// 1.2 ����ģ�廯
template <class T1, class T2>
void show_person2(Person<T1, T2>& p)
{
	//����������ģ������Ƶ����Ƶ���p�Ĳ���������     Person<string,int>
	p.show();
	cout << "T1�������ͣ� " << typeid(T1).name() << endl;
	cout << "T2�������ͣ� " << typeid(T2).name() << endl;
}
void test3()
{
	Person <std::string, int> p("Tomy", 88);
	show_person2(p);
}

// 1.3 ������������ ������ģ�廯 --> ����ģ��
template <class T>
void show_person3(T& p)
{
	cout << "T���������ͣ� " << typeid(T).name() << endl;
	p.show();
}
void test4()
{
	Person <std::string, int> p("john", 66);
	show_person3(p);
}

/**************************************************
2. ʹ����ģ��������ͨ��
**************************************************/

template <class T>
class Base
{
public:
	T a_;
};

// 
// ���̳�����ģ��ʱ���������ָ�������е�T�������ͣ����ܸ���������ڴ�
class Derived : public Base<double>
{
};

/**************************************************
2. ʹ����ģ��������ģ��
**************************************************/
template <class T>
class Base2
{
public:
	Base2() {
		cout << "T Type :" << typeid(T).name() << endl;
	}
	T b_;
};
template <class T1, class T2>
class Derived2 : public Base2<T2>
{
public:
	Derived2() {
		cout << "call Derive " << endl;
		cout << "T1 Type: " << typeid(T1).name() << endl;
		cout << "T2 Type: " <<typeid(T2).name() << endl;
	}
	T1 c_;
};

void test5()
{
	cout << "sizeof(Derived) :" << sizeof(Derived) << endl;
	Derived2 <int, double> d;
}


int main()
{
	/*test1();
	test2();
	test3();*/
	//test4();
	test5();
	return 0;
}
