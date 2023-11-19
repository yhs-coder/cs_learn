#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using std::cout;
using std::endl;

class Animal
{
public:
#if 1
	virtual void speak()
	{
		cout << "动物在说话..." << endl;
	}

	virtual void eat() {
		cout << "动物在进食..." << endl;
	}
	
#else
	void speak() {
		cout << "动物在说话" << endl;
	}
	void eat() {
		cout << "动物在进食..." << endl;
	}

#endif

};

class Cat : public Animal
{
public:
	void speak() {
		cout << "小猫在说话" << endl;
	}

	void eat() {
		cout << "小猫吃猫粮..." << endl;
	}

};


class Dog : public Animal
{
public:
	void speak() {
		cout << "小狗在说话" << endl;
	}

	void eat() {
		cout << "小狗吃狗粮..." << endl;
	}
};

void do_speak(Animal& animal)
{
	// 由于子类类型转换为父类类型，最后都调用到了Animal中的speak,使用虚函数后，可调用传入对象的speak
	animal.speak();
}

// 测试虚函数
void test1()
{
	Cat cat;
	do_speak(cat);

	Dog dog;
	do_speak(dog);

}




class A {
public:
	virtual void func1() {}
	virtual void func2() {}
};

//B类为空，那么大小应该是1字节，实际情况是这样吗？
class B : public A {};

void test2() {
	// 使用虚函数后，基类和派生类在编译时会自动添加一个虚函数指针，指向该类的虚函数表
	cout << "A size:" << sizeof(A) << endl;	// 8
	cout << "B size:" << sizeof(B) << endl;	// 8
}




/* 探索虚函数的实现原理 ，并且使用虚函数表中的偏移量访问虚函数
*/
void test3()
{
	cout << "sizeof Animal = " << sizeof(Animal) << endl;
	cout << "sizeof Cat = " << sizeof(Cat) << endl;

	Animal* animal = new Cat;
	//animal->speak();

	/*
		32位运行环境：4字节
		((void(*)()) (*(int *)*(int*)animal)) ();
	*/

	/*
		如果运行环境是64位，那每个指针的大小是8字节，当访问类内部的
		虚函数表，指针每次移动的大小得是8字节！否则会找不到对一个的地址
	*/


	/*
		1. *(size_t*)animal   ==> 跳到Cat中vfptr指针所指的vftable（虚函数表)
		2. * (size_t*)*(size_t*)animal) ==> 解引用得到虚函数的地址
		3. 转换成函数指针，调用函数地址所指向的函数
	*/


	// 记得将平台换成x8平台，因为开发者工具运行的也是x86
	// 调用Cat::speak()和 Cat::eat()
	cout << "-----------------------------" << endl;
	((void(*)()) (*(size_t*)*(size_t*)animal)) ();
	((void(*)()) (  *((size_t*)*(size_t*)animal + 1) )  ) ();

	//使用typedef类型定义简化
	typedef void(*FUNPOINT)();

	//__stdcall 是用于指定 C 函数调用约定的一种关键字，它告诉编译器在函数调用时使用 stdcall 调用约定，
	//  FUNPOINT 是一个指向无参数整数函数的指针类型，所以它期望接收一个整型参数作为函数的输入。
	//在调用该函数指针时，可以将任何整数值传递给它，只要它的数据类型与函数定义中指定的参数类型匹配即可
	//typedef void( __stdcall *FUNPOINT)(int);

	//((void(*)()) (*((size_t*)*(size_t*)animal + 1)))();
	(FUNPOINT(*((size_t*)*(size_t*)animal + 1)))    ();
	FUNPOINT(*((size_t*)*(size_t*)animal + 1))();
	
	//C/C++默认调用惯例  __cdecl
	//用下列调用时候 真实调用惯例  是 __stdcall
}


int main()
{
	//test1();
	//test2();
	test3();
	system("pause");
	return 0;
}