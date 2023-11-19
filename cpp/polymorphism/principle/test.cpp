#include <iostream>
using std::cout;
using std::endl;

/*
	探索多态的原理
*/

#if 0
//父类
class Base
{
public:
	//虚函数
	virtual void func1() {
		cout << "Base::Func1()" << endl;
	}
	//虚函数
	virtual void func2() {
		cout << "Base::Func2()" << endl;
	}
	//普通成员函数
	void func3() {
		cout << "Base::Func3()" << endl;
	}
private:
	int a_ = 1;
};
//子类
class Derive : public Base
{
public:
	//重写虚函数Func1
	virtual void func1()
	{
		cout << "Derive::Func1()" << endl;
	}
private:
	int b_ = 2;
};

// 通过调试，打开监视窗口，观察对象内部
void test1()
{
	Base b;
	Derive d;
}
#endif

// 父类
class Person
{
public:
	virtual void buy_ticket() {
		cout << "买票 - 全价" << endl;
	}
	int p_ = 1;
};

// 子类
class Student : public Person
{
public: 
	virtual void buy_ticket() {
		cout << "买票 - 半价" << endl;
	}

	int s_ = 2;
};

void test2()
{
	Person jerry;
	Student bobo;
	bobo.p_ = 3;
	Person* p1 = &jerry;
	Person* p2 = &bobo;
	p1->buy_ticket();
	p2->buy_ticket();
}

void test3()
{
	// 同类型的对象共享一张虚表
	Person jerry;
	Student bobo;
	Student s;
	Person p1 = jerry;
	Person p2 = bobo;
	Person p3;
	Person p4;
}

/** 单继承的虚函数表 **/
// 基类
class Base
{
public:
	virtual void func1() {
		cout << "Base::func1()" << endl;
	}
	virtual void func2() {
		cout << "Base::func2()" << endl;
	}
private:
	int a_ = 10;
};

class Derived : public Base
{
public:
	virtual void func1() {
		cout << "Derived::func1()" << endl;
	}
	virtual void func3() {
		cout << "Derived::func3()" << endl;
	}
	virtual void func4() {
		cout << "Derived::func4()" << endl;
	}
private:
	int b_ = 20;
};


// 调试查看对象中的虚指针，以及虚函数表
void test4()
{
	Base b;
	Derived d;
}


// 虚表本质上是一个指针数组，最后一个元素放nullptr
// 打印虚表地址及其内容
typedef void(*VFPTR)();	// 函数指针类型重命名
void print_vftable(VFPTR* ptr) // VFPTR*为二级指针，可看作指针数组,方便打印出虚函数地址
{
	printf("虚表地址：%p\n", ptr);
	cout << "虚表中的虚函数地址: " << endl;
	for (int i = 0; ptr[i] != nullptr; i++) {
		printf("ptr[%d]: %p --> ", i, ptr[i]);	// 打印虚表中的虚函数地址(使用C格式化输出)
		ptr[i]();	// 使用虚函数地址调用虚函数
	}
	cout << endl;
}

// 打印虚表内容
void test5()
{
	Base b;
	//print_vftable((VFPTR*)(*(int*)&b));
	// *(size_t*)&b --> 跳转到虚函数表，在把虚函数表地址强制转换成 函数指针的指针，即指针数组
	cout << sizeof(size_t*) << endl;
	print_vftable((VFPTR*)(*(size_t*)&b));
	Derived d;
	print_vftable((VFPTR*)(*(size_t*)&d));

}



/** 多继承的虚函数表 **/
class Base1
{
public:
	virtual void func1() {
		cout << "Base1::func1()" << endl;
	}
	virtual void func2() {
		cout << "Base1::func2()" << endl;
	}
private:
	int b1_ = 10;
};


class Base2
{
public:
	virtual void func1() {
		cout << "Base2::func1()" << endl;
	}
	virtual void func2() {
		cout << "Base2::func2()" << endl;
	}
private:
	int b2_ = 10;
};

class Derived2 : public Base1, public Base2
{
public:
	virtual void func1() {
		cout << "Derived::func1()" << endl;
	}
	virtual void func3() {
		cout << "Derived::func3()" << endl;
	}
private:
	int d_ = 10;
};



// 调试查看多继承关系中的虚函数表
void test6()
{
	Base1 b1;
	Base2 b2;
	print_vftable((VFPTR*)(*(size_t*)&b1));
	print_vftable((VFPTR*)(*(size_t*)&b2));
	Derived2 d;
	print_vftable((VFPTR*)(*(size_t*)&d));	// 打印d第一个虚表地址及其内容
	print_vftable((VFPTR*)  (*(size_t*)((char*)&d + sizeof(Base1))));   // 向后移sizeof(Base1)个字节得到第二个虚表的地址,打印第二个虚表地址及其内容
}


int main()
{
	//test1();
	//test2();
	//test3();
	////test4();
	//test5();
	test6();
	return 0;
}

