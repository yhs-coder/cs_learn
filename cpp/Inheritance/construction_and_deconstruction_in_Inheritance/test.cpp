#include <iostream>
using std::cout;
using std::endl;

class Base1
{
public:
	Base1()
	{
		cout << "Base1的构造函数调用" << endl;
	}
	~Base1()
	{
		cout << "Base1的析构函数调用" << endl;
	}
};

class Other
{
public:
	Other()
	{
		cout << "Other的构造函数调用" << endl;
	}

	~Other()
	{
		cout << "Other的析构函数调用" << endl;
	}
};

class Derived1 : public Base1
{
public:
	Derived1()
	{
		cout << "Derived1的构造函数调用" << endl;
	}
	~Derived1()
	{
		cout << "Derived1的析构函数调用" << endl;
	}
	Other other_;
};

void test01()
{
	//先调用父类构造，再调用类内其他对象成员构造， 再调用自身构造 ，析构的顺序与构造相反
	Derived1 s;
}


/* 
当父类构造函数有参数时，需要在子类初始化列表(参数列表)中显示调用父类构造函数
*/
class Base2
{
public:
	Base2(int a, int b)
	{
		a_ = a;
		b_ = b;
		cout << "Base2的构造函数调用" << endl;
#if 1
		cout << "Base::&a_ = " << &a_ << endl;
		cout << "--------------------------------" << endl;
#endif
	}
public:
	int a_;
private:
	int b_;
};

class Derived2 : public Base2
{
public:
	//利用初始化列表语法  显示调用父类中的其他构造函数
	Derived2(int a = 100, int b = 100) 
		: Base2(a, b)
		, other_()
	{
		cout << "Derived2的构造函数调用" << endl;
#if 1
		// 派生类复用（共享）基类的成员
		cout << "Derived2::&a_ = " << &(Derived2::a_) << endl;
		cout << "Base2::&a_ = " << &(Base2::a_) << endl;
		cout << "-----------------------------------" << endl;
		Derived2::a_ = 1024;
		cout << "Base2::a_ = " << Base2::a_ << endl; // 1024
		cout << "Derived2::a_ = " << Derived2::a_ << endl; // 1024

#endif
}

private:
	Other other_;
};

class Derived3 : public Base2
{
public:
	//利用初始化列表语法  显示调用父类中的其他构造函数
	Derived3(int a = 100, int b = 100) : Base2(a, b)
	{
		cout << "Derived3的构造函数调用" << endl;
		cout << "Base2::a_ = " << Base2::a_ << endl;
		cout << "Derived3::&a_ = " << &a_ << endl;
		Derived3::a_ = 1111111;
	}
};

void test02()
{
	Derived2 s(1, 1);
	Derived3 s3;
	cout << "-----------------------------------" << endl;
	cout << "Derived2 ::a_ = " << s.a_ << endl;
	cout << "Derived3 ::a_ = " << s3.a_ << endl;

}


void test03()
{
	Derived3 d3;
	cout << "Derived3 ::a_ = " << d3.Derived3::a_ << endl;
	cout << "Base2::a_ = " << d3.Base2::a_ << endl;

}
//父类中 构造、析构、拷贝构造 、operator=  是不会被子类继承下去的


int main()
{
	//test01();
	test02();
	//test03();
	system("pause");
	return 0;
}