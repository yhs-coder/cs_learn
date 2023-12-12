#include <iostream>

// 使用静态库函数时，需要声明函数给编译器让编译器知道
int cpplib_add(int a, int b);
int cpplib_sub(int a, int b);

// 让编译器链接到库文件
#pragma comment(lib, "../x64/Debug/CPPLib.lib")


#pragma comment(lib,"../x64/Debug/StaticAndDynamicLibrary.lib")
// 一定要使用外部链接，不然在编译过程中，C语言的函数在编译中会被重命名！！！
// 链接过程中就会按照重命名后的函数符号在静态库查找！！！会调用不到原先的函数
extern  "C" int Clib_add(int a, int b);
extern  "C" int Clib_sub(int a, int b);

int main()
{
	// 调用C++静态库库函数
	int sum = cpplib_add(2, 2);
	int sub = cpplib_sub(10, 2);
	std::cout << "sum = " << sum << " , sub = " << sub << std::endl;

	//  不能调用C语言静态库库函数
	int c_sum, c_sub;
	c_sum = Clib_add(1, 1);
	c_sub = Clib_sub(1, 1);
	std::cout << "c_sum = " << c_sum << " , c_sub = " << c_sub << std::endl;

	return 0;
}