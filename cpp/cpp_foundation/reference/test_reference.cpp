#include<iostream>
using namespace std;

/*
	1. 引用的基本语法：	类型 &别名 = 原名
	引用的目的： 起别名
*/
void test01() {
	int a = 10;
	int& b = a;
	//指向(共用)同一块内存空间
	cout << "&b = " << &b << ", &a = " << &a << endl;
	b = 100;
	cout << "b = " << b << endl;
	cout << "a = " << a << endl;
}

/*	
	2. （注意事项）
		2.1 引用必须初始化
		2.2 引用必须指向一块合理的内存空间
		2.3 引用一旦初始化后，就不可以引向其他变量
		2.4 不要返回局部变量的引用
		2.5 类型标识符 和 目标变量的类型 相同
*/

void test02() {

	int a = 11;
	//int &b; //erroe,# 2.1引用必须要初始化
	//int &b = 10;    # 2.2
	int& b = a;

	int  c = 100;
	b = c;  //赋值

	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "c = " << c << endl;
	// #2.3 
	cout << "&b = " << &b << ", &c = " << &c << endl;
}
int& func() {
	int a = 10;
	return a;
}

//# 测试2.4
void test2_4() {
	int& ref = func();
	cout << "ref = " << ref << endl;
	cout << "ref = " << ref << endl;
}

/*
	3. 对数组建立引用
		方法：3.1 直接建立引用
			 3.2 先定义数组类型，在通过类型定义引用
*/
void test03() {
	//3.1 直接建立引用
	int arr[10];
	//type* ref = &arr;
	int(&pArr)[10] = arr;
	for (int i = 0; i < 5; i++)
	{
		arr[i] = 100 + i;
		cout << pArr[i] << endl;
	}

	//3.2 先定义数组类型，在通过类型定义引用
	typedef int(ARRAY_TYPE)[10];
	//类型  &别名 = 原名
	ARRAY_TYPE& pArr2 = arr;
	for (int i = 0; i < 5; i++)
	{
		cout << pArr2[i] << endl;
	}
}

/*
	4. 引用的使用场景：
		1. 做函数参数
		2. 做函数返回值
		3. 当函数的返回值是引用，函数的调用可以作为左值
*/

//地址传递
void PointerSwap(int* m, int* n) {
	int temp = *m;
	*m = *n;
	*n = temp;
}
//引用传递
void ReferenceSwap(int& m, int& n) {
	int temp = m;
	m = n;
	n = temp;
}
int& func2() {
	static int a = 10;
	return a;
}

void test4_3() {
	int& ref = func2();
	cout << "ref = " << ref << endl;
	cout << "ref = " << ref << endl;
	func2() = 1000;
	cout << "ref = " << ref << endl;

}

void test04() {
	int a = 10;
	int b = 20;
	cout << "a:" << a << " b:" << b << endl;
	//地址传递
	PointerSwap(&a, &b);
	cout << "a:" << a << " b:" << b << endl;
	//引用传递
	ReferenceSwap(a, b);
	cout << "a:" << a << " b:" << b << endl;
}

//6. 指针引用
struct Person
{
	int age;
};

void AllocateSpace(Person** p)
{
	if (p == nullptr) return;
	//p指向指针的指针    *p  指针指向的是person指针   **p  person本体
	*p = (Person*)malloc(sizeof(Person));
	if (*p == nullptr) {
		exit(-1);
	}
	(*p)->age = 10;

}

void test05() {
	Person* p = nullptr;
	AllocateSpace(&p);
	cout << "p.age = " << p->age << endl;
	free(p);
}


void AllocateSpace2(Person*& pp) // Person * &pp = p;
{
	pp = (Person*)malloc(sizeof(Person));
	if (pp == nullptr) {
		exit(-1);
	}
	pp->age = 20;
}
void test06()
{
	Person* p = nullptr;
	AllocateSpace2(p);
	if (p == nullptr)
		cout << "p = nullptr" << endl;
	cout << "p.age = " << p->age << endl;
	free(p);
}

/*
	7. 常量的引用
*/

void test07() {
	const int& ref = 10;
	// int temp = 10; const int * &ref = temp;
	int* p = (int*)&ref;
	*p = 666;
	cout << "*p = " << *p << endl;
	cout << "ref = " << ref << endl;


	int a = 100;
	const int& aRef = a; //此时aRef就是a
	// aRef = 200;			//不能修改aRef的值
	a = 100; //OK
	cout << "a:" << a << endl;
	cout << "aRef:" << aRef << endl;

}

int main() {
	//test01();
	//test02();
	//test2_4();
	//test03();
	//test04();
	//test4_3();
	//test05();
	//test06();
	test07();
	//showValue(567);
	char var = 'a';
	char& ref = var;
	cout << "sizeof(var) = " << sizeof(var) << endl;
	cout << "sizeof(ref) = " << sizeof(ref) << endl;

	system("pause");
	return 0;
}



