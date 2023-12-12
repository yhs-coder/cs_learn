#include <iostream>

// ʹ�þ�̬�⺯��ʱ����Ҫ�����������������ñ�����֪��
int cpplib_add(int a, int b);
int cpplib_sub(int a, int b);

// �ñ��������ӵ����ļ�
#pragma comment(lib, "../x64/Debug/CPPLib.lib")


#pragma comment(lib,"../x64/Debug/StaticAndDynamicLibrary.lib")
// һ��Ҫʹ���ⲿ���ӣ���Ȼ�ڱ�������У�C���Եĺ����ڱ����лᱻ������������
// ���ӹ����оͻᰴ����������ĺ��������ھ�̬����ң���������ò���ԭ�ȵĺ���
extern  "C" int Clib_add(int a, int b);
extern  "C" int Clib_sub(int a, int b);

int main()
{
	// ����C++��̬��⺯��
	int sum = cpplib_add(2, 2);
	int sub = cpplib_sub(10, 2);
	std::cout << "sum = " << sum << " , sub = " << sub << std::endl;

	//  ���ܵ���C���Ծ�̬��⺯��
	int c_sum, c_sub;
	c_sum = Clib_add(1, 1);
	c_sub = Clib_sub(1, 1);
	std::cout << "c_sum = " << c_sum << " , c_sub = " << c_sub << std::endl;

	return 0;
}