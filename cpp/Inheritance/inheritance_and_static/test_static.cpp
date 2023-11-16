#include  <iostream>
using std::cout;
using std::endl;

class Base
{
public:

	static void func() {
		cout << "Base中的func调用 " << endl;
	}

	static void func(int a) {
		cout << "Base中的func(int a)调用 " << endl;
	}
	static int a_;
};
int Base::a_ = 10;

class Derived : public Base
{
public:
	// 重定义静态成员函数，基类中重载的函数被隐藏
	static void func() {
		cout << "Derived中的func调用 " << endl;
	}
	// 改变基类函数的某个特征，返回值或者参数个数，将会隐藏基类重载的函数
	static void func(int a, int b = 100) {
		cout << "Base中的func(int a, int b)调用 " << endl;
	}
	static int a_;	// 派生类中定义一个同名的静态成员，基类静态成员属性将被隐藏
};
int Derived::a_ = 20;

void test01()
{
	//访问静态成员
	Derived s;
	//1、通过对象访问
	cout << "a_ = " << s.a_ << endl; //20
	cout << "Base中的a_ = " << s.Base::a_ << endl; //10

	//2、通过类名访问
	cout << "a_ = " << Derived::a_ << endl; //20
	//通过类名的方式 访问 父类作用域下的a_静态成员变量
	cout << "Base::a_ = " << Derived::Base::a_ << endl; //10
	cout << "a_ = " << Base::a_ << endl;	// 10

	//3.通过匿名对象访问
	cout << "Derived().a_ = " << Derived().a_ << endl;	// 20
}

void test02()
{
	//1、通过对象
	Derived s;
	s.func();		 //Derived
	s.Base::func();  //base


	//2、通过类名
	Derived::func();
	//当子类重定义父类中同名成员函数，子类的成员函数会隐藏掉父类中所有版本，需要加作用域调用
	Derived::Base::func();

	s.func(1111);
	s.Base::func(2222);
}

int main() 
{
	//test01();
	test02();

	system("pause");
	return EXIT_SUCCESS;
}