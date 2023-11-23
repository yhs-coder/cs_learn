#include <iostream>
#include <string>
using std::cout;
using std::endl;

/********************************************************
	��ģ��
********************************************************/


template <class NAMETYPE, class AGETYPE>
class Person
{
public:
	Person(NAMETYPE name, AGETYPE age)
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
	/* ��ģ��ͺ���ģ�������
		1. ��ģ�岻����ʹ���Զ������Ƶ���ֻ������ʾָ������
		2. ��ģ���У�������Ĭ�ϲ���
	*/
	//Person p1("jerry", 100); //����ȱ����ģ������б�
	Person<std::string, int> p1("tom", 100);
	p1.show();
}

/********************************************************
	��ģ���г�Ա�����Ĵ���ʱ��:
	- ��ģ���еĳ�Ա������������һ��ʼ�����ģ����������н׶�ȷ����T���������Ͳ�ȥ����

********************************************************/

class Person1
{
public:
	Person1() {
		cout << "Person1 ����" << endl;
	}

	void show_person1() {
		cout << "Person1 show ����" << endl;
	}
};

class Person2
{
public:
	Person2()  {
		cout << "Person2 ����" << endl;
	}

	void show_person2() {
		cout << "Person2 show ����" << endl;
	}

};

template <class T>
class MyClass
{
public:

	void func1() {
		obj_.show_person1();
	}

	void func2() {
		obj_.show_person2();
	}
	T obj_;
};

void test2()
{
	MyClass <Person1> p1;
	MyClass <Person2> p2;

	cout << "--------------------------" << endl;
	p1.func1();
	p2.func2();

}

int main()
{
	test1();
	test2();
	return 0;
}
