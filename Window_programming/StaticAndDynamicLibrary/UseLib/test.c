#include <stdio.h>
// ����ʹ�����·��
#pragma comment(lib,"../x64/Debug/StaticAndDynamicLibrary.lib")

int main()
{
	int sum, sub;
	sum = Clib_add(1, 1);
	sub = Clib_sub(1, 1);
	printf("sum = %d, sub = %d\n", sum, sub);
	system("pause");
	return 0;
}
