#include <iostream>

// 使用隐式链接的方式，使用动态库中封装的类
#pragma comment(lib, "../x64/Debug/ClassDll.lib")

# if 0
// 一般用法
class _declspec(dllimport) Math {
public:
	int Add(int a, int b);
	int Sub(int a, int b);
};


#else 
// 其他人引用动态库的头文件
#include "../ClassDll/ClassDll.h"

#endif


int main()
{
	Math math;
	int sum = math.Add(1, 2);
	int sub = math.Sub(1, 2);
	std::cout << "sum = " << sum << " , sub = " << sub << std::endl;
	return 0;
}