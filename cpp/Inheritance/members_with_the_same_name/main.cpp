#include <iostream>
using std::cout;
using std::endl;

class Base
{
public:
	Base() : a_(100) {}
	void func() {
		cout << "Base中的func调用" << endl;
	}
	void func(int a) {
		cout << "Base中的func(int)调用" << endl;
	}

	int a_;
};

class Son : public Base
{
public:
	Son() : a_(200) {}
	void func() {
		cout << "Son中的func调用" << endl;
	}
	int a_;
};

void test01()
{
	Son s1;
	cout << "s1.a_ = " << s1.a_ << endl;	// 200
	cout << "sizeof(Son) = " << sizeof(Son) << endl;	// 8
	cout << "sizeof(Base) = " << sizeof(Base) << endl;  // 4

	//我们可以利用作用域 访问父类中的同名成员
	cout << "Base中的a_ = " << s1.Base::a_ << endl;	// 100
}


void test02()
{
	//当子类重新定义了父类中的同名成员函数，子类的成员函数会 隐藏掉父类中所有重载版本的同名成员，可以利用作用域显示指定调用
	Son s1;
	// s1.func(100);	父类的同名的重载函数被隐藏无法调用
	s1.func();
	// 显示调用
	s1.Base::func();
	Base().func();
	Base().func(100);
}

int main()
{
	//test01();
	test02();
	system("pause");
	return 0;
}





