#include <iostream>
#include <string>
using std::cout;
using std::endl;

/********************************************************
	模板特例化
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

// 模板特例化，为自定义数据类型提供特殊模板
// 以template<>开头，并通过名称来指出类型，特例化优先于常规模板
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

	// 模板函数无法比较类类型或结构体类型，或者数组
	// 此时需要为这些特定的类型提供具体化的模板。也就是模板特例化
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