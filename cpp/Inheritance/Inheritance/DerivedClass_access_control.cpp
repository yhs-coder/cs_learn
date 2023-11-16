#include <iostream>
using std::cout;
using std::endl;

//////////////   公有继承   //////////////
class Base1
{
public:
	Base1() : a_(10), b_(20), c_(30) {
		cout << "Base1 Constructor..." << endl;
	}

public:
	int a_;
protected:
	int b_;
private:
	int c_;
};

class Derived1 : public Base1
{
public:
	void func()
	{
		a_ = 100; // 父类中公共权限 子类中变为 公共权限
		b_ = 100; // 父类中 保护权限 子类中变为 保护权限
		// c_ = 100; // 父类中私有成员， 子类无法访问
	}
	int _c;

};

void test01()
{
	Derived1 s1;
	s1.a_ = 100; //在Derived1中 a_是公共权限  类外可以访问
	// s1.b_ = 100; //在Derived1中 b_是保护权限  类外不可以访问

	cout << "Base1 size: " << sizeof(Base1) << endl;
	cout << "Derived1 size: " << sizeof(Derived1) << endl;
}

//////////////   保护继承   //////////////
class Base2
{
public:
	int a_;
protected:
	int b_;
private:
	int c_;
};

class Derived2 : protected Base2
{
public:
	void func()
	{
		a_ = 100;//父类中 公共权限 子类中变为  保护权限
		b_ = 100;//父类中 保护权限 子类中变为  保护权限
		//c_ = 100;//父类中私有成员，子类无法访问
	}
};
void test02()
{
	Derived2 s;
	//s.a_ = 100;  //子类中 保护权限 无法访问
	//s.b_ = 100;  //子类中 保护权限 无法访问
	//s.c_ = 100;  //子类本身没有访问权限
}

//////////////   保护继承   //////////////
class Base3
{
public:
	int a_;
protected:
	int b_;
private:
	int c_;
};

class Derived3 :private Base3
{
public:
	void func()
	{
		a_ = 100;  //父类中 公共权限 子类中变为  私有权限
		b_ = 100;  //父类中 保护权限 子类中变为  私有权限
		//c_ = 100;//父类中私有成员，子类无法访问
	}
};

class GrandDerived3 : public Derived3
{
	void func()
	{
		//a_ = 100; // 在Derived3中 已经变为私有权限，GrandDerived3访问不到
		//b_ = 200;
	}
};
void test03()
{
	Derived3 s;
	//s.a_ = 100;//在Derived3中变为私有权限，类外访问不到
	//s.b_ = 100;//在Derived3中变为私有权限，类外访问不到

}

int main()
{
	test01();
	system("pause");
	return EXIT_SUCCESS;
}
