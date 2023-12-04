#pragma once
#include <iostream>
using std::cout;
using std::endl;



template <class NameType, class AgeType> 
class Person
{
public:
#if 0
	// 类模板类内实现
	Person(NameType name, AgeType age)
		: name_(name)
		, age_(age) {}

	void show_person() {
		cout << "name: " << name_ << " , age: " << age_ << endl;
	}
#else
	// 在模板中，不要进行分离编译，应该将声明和定义放在同一个文件进行编译
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

