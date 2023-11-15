#include<iostream>
using std::cout;
using std::endl;


class Base
{
public:
	int a_;
protected:
	int b_;
private:
	int c_;  //父类中私有属性，子类访问不到，是由编译器给隐藏了
};

class Derived : public Base
{
public:
	int d_;
};

void test01()
{
	cout << "size of  Base = " << sizeof(Base) << endl; // 结果为12
	cout << "size of  Derived = " << sizeof(Derived) << endl; // 结果为16
}

int main()
{
	test01();
	system("pause");
	return EXIT_SUCCESS;

}