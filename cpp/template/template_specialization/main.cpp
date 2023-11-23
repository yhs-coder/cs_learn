#include <iostream>
#include <string>
using std::cout;
using std::endl;

/********************************************************
	ģ��������
********************************************************/

class Person
{
public:
	Person(std::string name, int age)
		: name_(name)
		, age_(age){}
	std::string name_;
	int age_;
};

template <class T>
bool compare(T& a, T& b)
{
	if (a == b) {
		return true;
	}
	return false;
}

// ģ����������Ϊ�Զ������������ṩ����ģ��
// ��template<>��ͷ����ͨ��������ָ�����ͣ������������ڳ���ģ��
template<>
bool compare<Person>(Person& a, Person& b)
{
	return a.name_ == b.name_ && a.age_ == b.age_;
}

void test1()
{
	int a = 10;
	int b = 20;
	bool ret = compare(a, b);
	if (ret) {
		cout << "a == b" << endl;
	}
	else {
		cout << "a != b" << endl;
	}

	// ģ�庯���޷��Ƚ������ͻ�ṹ�����ͣ���������
	// ��ʱ��ҪΪ��Щ�ض��������ṩ���廯��ģ�塣Ҳ����ģ��������
	Person p1("tom", 100);
	//Person p2("tom", 100);
	Person p2("tom", 1200);
	ret = compare(p1, p2);
	if (ret) {
		cout << "a == b" << endl;
	}
	else {
		cout << "a != b" << endl;
	}
}
int main()
{
	test1();
	return 0;
}