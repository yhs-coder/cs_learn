#include <iostream>

// ʹ����ʽ���ӵķ�ʽ��ʹ�ö�̬���з�װ����
#pragma comment(lib, "../x64/Debug/ClassDll.lib")

# if 0
// һ���÷�
class _declspec(dllimport) Math {
public:
	int Add(int a, int b);
	int Sub(int a, int b);
};


#else 
// ���������ö�̬���ͷ�ļ�
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