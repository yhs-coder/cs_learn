#include <iostream>
using std::cout;
using std::endl;

/****************************************************
	1. ����ģ������ͨ����������	
		1) ����ģ�岻�����Զ�����ת���������ϸ�ƥ������
		2) ��ͨ�������Խ����Զ�����ת��

******************************************************/

template <typename T>
T add(T a, T b)
{
	cout << "����ģ��..." << endl;
	return a + b;
}

int add2(int a, int b)
{
	cout << "��ͨ����..." << endl;
	return a + b;
}

void test1()
{
	int a = 10;
	int b = 20;
	char c = 'c';
	add(a, b);
	
	//����ģ�����ʹ���Զ��Ƶ����ͣ��ǲ����Է�����ʽ����ת����
	// ��Ϊֻ��һ�����Ͳ��������Ա����ϸ�ƥ������,���ܴ�
	// �������Ͳ�ͬ��ʵ�Σ�����ģ�����������Ͳ���
	// add(a, c);	

	// ������ͨ����  ��ͨ����������ʽ����ת��
	add2(a, c);

}



/****************************************************
	2. ����ģ�����ͨ�����ĵ��ù���
		1) c++���������ȿ�����ͨ����
		2) ����ͨ����ģ��ʵ���б����﷨,�޶�������ֻ��ͨ��ģ��ƥ��
		3) ����ģ���������ͨ�����������Ա�����
		4) �������ģ����Բ���һ�����õ�ƥ�䣬��ôѡ��ģ�� ,���磺���ʹ����ͨ��������Ҫ�ٽ�������ת������ģ�庯������ֱ�ӽ���ʵ�����ͽ���ʹ�ã�����ƥ�亯��ģ����ѡ�
}
******************************************************/

template <typename T>
void print(T a, T b)
{
	cout << "print(T a, T b) ����ģ����� ..." << endl;
}

void print(int a, int b)
{
	cout << "��ͨ��������..." << endl;
}

template <class T>
void print(T a, T b, T c)
{
	cout << "print(T a, T b, T c) ����ģ�����..." << endl;
}

void test2()
{
	// 1. �������ģ�����ͨ���������Ե��ã�����������ת��������ô���ȵ�����ͨ����
	int a = 10;
	int b = 20;
	print(a, b);

	// 2. �����ǿ�Ƶ��ú���ģ�壬����ʹ�ÿ�ģ������б�
	print<>(a, b);

	// 3. ����ģ����Է�������
	print(a, b, 1);

	// 4. �������ģ���ܲ������õ�ƥ�䣬��ô����ʹ�ú���ģ��
	char c = 'c';
	char d = 'd';
	// ʹ����ͨ��������Ҫ��������ת������ģ��ֱ�ӽ������ͽ���ʹ��
	print(c, d);
}

int main()
{
	test2();
	return 0;
}

