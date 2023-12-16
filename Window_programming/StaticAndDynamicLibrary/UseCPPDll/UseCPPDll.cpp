#include <iostream>
// 使用动态链接库 ： 1. 隐式链接  2. 显示链接


#if 0
// 隐式链接
_declspec(dllimport) int cppdll_add(int a, int b);
_declspec(dllimport) int cppdll_sub(int a, int b);
_declspec(dllimport) int cppdll_mul(int a, int b);
_declspec(dllimport) int cppdll_div(int a, int b);

// 添加动态库路径,通知连接器到哪抓 编号 和 dll文件名
#pragma comment(lib, "../x64/Debug/CPPDll.lib")

int main()
{
	int sum = cppdll_add(1, 1);
	int sub = cppdll_sub(1, 1);
	int mul = cppdll_mul(1, 1);
	int div = cppdll_div(1, 1);
	std::cout << "sum = " << sum << ", sub = " << sub << ", mul = " << mul << ", div = " << div << std::endl;
}

#else 
// 显示链接

#include <windows.h>

typedef int(*ADD)(int m, int n);
typedef int(*SUB)(int m, int n);
typedef int(*MUL)(int m, int n);
typedef int(*DIV)(int m, int n);


int main() {
	// 加载动态库
	HINSTANCE hDll = LoadLibrary(L"CPPDll.dll");
	std::cout << "hDll: " << hDll << std::endl;

	// 得到动态库函数的绝对地址
	ADD myAdd = (ADD)GetProcAddress(hDll, "cppdll_add");
	std::cout << "myAdd: " << myAdd << std::endl;
	int sum = myAdd(5, 4);
	std::cout << "sum = " << sum << std::endl;

	SUB mySub = (SUB)GetProcAddress(hDll, "cppdll_sub");
	std::cout << "mySub: " << mySub << std::endl;
	int sub = mySub(5, 4);
	std::cout << "sub = " << sub << std::endl;

	MUL myMul = (MUL)GetProcAddress(hDll, "cppdll_mul");
	std::cout << "myMul: " << myMul << std::endl;
	int mul = myMul(5, 4);
	std::cout << "mul = " << mul << std::endl;

	DIV myDiv = (DIV)GetProcAddress(hDll, "cppdll_div");
	std::cout << "myDiv: " << myDiv << std::endl;
	int div = myDiv(5, 4);
	std::cout << "div = " << div << std::endl;
	return 0;
}
#endif






