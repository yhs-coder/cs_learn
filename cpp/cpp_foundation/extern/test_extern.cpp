#include<iostream>
using namespace std;
#include "C.h"
//#include "C.h" ，用extern链接C语言时，需注释掉头文件
//告诉编译器  show函数用C语言方式 做链接

extern int i = 2;
extern "C" {
	// 声明C语言函数
	void show();
}
void test1() {
	show(); //若无extern "C" void show(); 则error，因为在C++中有函数重载会修饰函数名，
	//但是show是c语言文件，因此链接失败

}
// 使用file.cpp中的全局变量
// 需要使用extern声明该变量，在编译时，编译器会为 global_var 生成一个符号表项，并在该文件下建立一个对该符号的引用。

extern int global_var;

int main() {
	test1();
	cout << "file.cpp: global_var = " << global_var << endl;
	
	system("pause");
	return 0;
}


