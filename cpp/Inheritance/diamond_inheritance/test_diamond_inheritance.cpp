#include <iostream>
using std::cout;
using std::endl;

//动物类
class Animal
{
public:
	Animal() : age_(1000) {}
	void func() {
		cout << "Animal::func" << endl;
	}
	int age_; // 年龄
};

#if 1
// 虚继承
class Sheep : virtual public Animal {};
class Tuo : virtual public Animal {};
#else
// 普通继承
class Sheep :  public Animal {};
class Tuo :  public Animal {};
#endif

//羊驼
class SheepTuo : public Sheep, public Tuo {};

// 菱形继承产生的问题
void test01()
{
	SheepTuo st;
	// 1. 调用产生二义性,不知道调用哪个父类成员
	//st.age_ = 10; 
	st.Sheep::age_ = 10;
	st.Tuo::age_ = 20;
	cout << "Sheep::age_ = " << st.Sheep::age_ << endl;
	cout << "Tuo::age_ = " << st.Tuo::age_ << endl;
	//2. 重复继承,浪费内存
	cout << "SheepTuo size:" << sizeof(SheepTuo) << endl; //8 重复继承了age_成员

}

// 使用虚基类后
void test02()
{
	cout << "SheepTuo size:" << sizeof(SheepTuo) << endl; //8 
	SheepTuo st;
	st.func();
	cout << st.age_ << endl;

}


// 探索虚继承的实现原理
void test03()
{
	// 使用虚继承后，每个类的大小
	// 使用虚继承后，编译器会自动向类对象中添加vbptr (virtual base pointer)，即虚指针，其指向虚表
	// 注意： 平台是64位，所以虚指针大小为8字节
	cout << "Sheep size: " << sizeof(Sheep) << endl;			// 内存对齐[（8 + 4）] = 16 
	cout << "Tuo size: " << sizeof(Tuo) << endl;				// 16
	cout << "SheepTuo size: " << sizeof(SheepTuo) << endl;		// 内存对齐[两个基类的虚指针 + 4] = 24

	SheepTuo st;
	st.age_ = 10;
	// 基类和派生类共享虚基类对象的成员，输出结果一致
	cout << "Sheep::age_ = " << st.Sheep::age_ << " , &Sheep::age_ = "  << &st.Sheep::age_ << endl;
	cout << "Tuo::age_ = " << st.Tuo::age_ << " , &Tuo::age_ = " << &st.Tuo::age_ << endl;
	cout << "Animal::age_ = " << st.Animal::age_ << " , &Animal::age_ = " << &st.Animal::age_ << endl;

	cout << "---------------------------------------------------------------------------------------" << endl;

	/*
		当发生虚继承后，sheep和tuo类中 继承了一个 vbptr指针,即虚基类指针，它指向的是一个虚基类表vbtable
		虚基类表中记录了该类相对于虚基类首地址的偏移量 ，通过偏移量 可以找到唯一的一个age_
	*/

	/* 
		探索原理：通过虚指针和虚表访问基类和虚基类的成员
		打开VS开发人员命令工具， cd 跳转到目标文件路径
		输入 cl /d1 reportSingleClassLayout类名  文件名 ，观察对象的继承模型
	 */

	/* 
		通过Sheep找到 虚基类表中的偏移量
		1. *(int *)&st 解引用到了 虚基类表中，一开始在 0位置
	 
		SheepTuo::$vbtable@Sheep@:
		0 | 0
		1 | 8 (SheepTuod(Sheep + 0)Animal)

	 2.  (int*) *(int*)&(st) + 1  跳到虚表的下一位置 1 */

	/*
		在32位系统上，size_t可能被定义为unsigned int，也就是32位无符号整型；
		而在64位系统上，则可能被定义为unsigned long，即64位无符号整形。
		size_t的主要目的是为了提供一种可移植的方法来声明与系统中可寻址的内存区域一致的长度。
	*/
	// 通过Sheep偏移量
	size_t sheep_offset = *((size_t*)*(size_t*)&st + 1);
	size_t tuo_offset = *((size_t*)*((size_t*)&st + 1) + 1);
	cout << "Sheep offset = " << *((int*)*(int*)&st + 1) << endl;   // 8
	cout << "Sheep offset = " << sheep_offset << endl; // 8
	
	// 通过Tuo找到偏移量
	cout << "Tuo offset = " << tuo_offset << endl;	  // 4

	// 通过Sheep和Tuo离虚基类的偏移量，访问虚基类中的age_成员和成员函数
	cout << "age_ = " << *((int*)((char*)&st + sheep_offset)) << endl; // 10
	cout << "age_ = " << ((Animal*)((char*)&st + sheep_offset))->age_ << endl; // 10
	cout << "use func()" << endl; 

	((Animal*)((char*)&st + sheep_offset))->func();

	((Animal*)((char*)&st + tuo_offset))->func();


	//cout << *((int*)*(int*)&st + 1) << endl;
	//cout << *(  ( int*)        *(int*)&st + 1) << endl;
	//cout << "(size_t*)&st  " << (size_t*)&st << endl;
	//cout << "(size_t*)&st + 1 " << (size_t*)&st + 1 << endl;

}


void test04()
{
	cout << "sizeof(Sheep) = " << sizeof(Sheep) << endl;
	cout << "sizeof(Tuo) = " << sizeof(Tuo) << endl;
}

int main() {

	//test01();
	//test02();
	test03();
	//test04();

	system("pause");
	return EXIT_SUCCESS;
}