#pragma once
#include <iostream>
using std::cout;
using std::endl;



template <class NameType, class AgeType> 
class Person
{
public:
#if 0
	// ��ģ������ʵ��
	Person(NameType name, AgeType age)
		: name_(name)
		, age_(age) {}

	void show_person() {
		cout << "name: " << name_ << " , age: " << age_ << endl;
	}
#else
	// ��ģ���У���Ҫ���з�����룬Ӧ�ý������Ͷ������ͬһ���ļ����б���
	Person(NameType name, AgeType age);
	void show_person();
#endif
private:
	NameType name_;
	AgeType age_;
};

template <class NameType, class AgeType>
Person<NameType, AgeType>::Person(NameType name, AgeType age)
{
	name_ = name;
	age_ = age;
}

template <class NameType, class AgeType>
void Person<NameType, AgeType>::show_person()
{
	cout << "name: " << name_ << " , age: " << age_ << endl;
}

