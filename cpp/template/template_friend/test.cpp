#include <iostream>
#include <string>
using std::cout;
using std::endl;

template <class T1, class T2>
class Person;

// ���߱������������ģ���Ǵ���
template <class T1, class T2>
void print_person(Person<T1, T2>& p);

// ��Ԫ��������ʵ��
template <class T1, class T2>
class Person
{
	// 1. ��Ԫ����������ʵ��
	friend void print_person(Person<T1, T2>& p) {
		cout << "name: " << p.name_ << " age��" << p.age_ << endl;
	}

	// 2.��Ԫ��������ʵ�� ,���߱������������ģ���Ǵ���
	friend void print_person2<>(Person<T1, T2>& p);
	
	// 3.��ģ��ʹ����Ԫ����ģ��
	template <class U1, class U2>
	friend void print_person(Person<U1, U2>& p);

public:
	Person(T1 name, T2 age)
		: name_(name)
		, age_(age) {}

	void show() {
		cout << "name: " << name_ << " age��" << age_ << endl;
	}

private:
	T1 name_;
	T2 age_;

};


// 2.��Ԫ��������ʵ�� (��ģ��������Ԫ����)
//��Ԫ��������ʵ�� ,����Ԫ��������ʱ��Ҫ����<>�ղ����б����߱���ȥƥ�亯��ģ��
template <class T1, class T2>
void print_person2(Person<T1, T2>& p)
{
	cout << "name: " << p.name_ << " age��" << p.age_ << endl;
}

void test1() 
{
	Person<std::string, int> p("jerry", 100);
	p.show();
	print_person(p);
}

void test2()
{
	Person<std::string, int> p("jerry", 100);
	print_person2(p);
}
int main()
{
	test1();
	return 0;
}