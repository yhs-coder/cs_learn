#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
using namespace std;

//�������󣨷º������������˺������ò���������Ķ���
class Myprint
{
public:
	void operator()(int num)
	{
		cout << num << endl;
		m_count++;
	}
	int m_count = 0;
};

void myPrint02(int num)
{
	cout << num << endl;
}

void test01()
{
	Myprint myPrint;
	myPrint(100); //�º������������������ˣ�������������ʵ�����Ķ��󣬿��������ǰ���ã��в�����Ҳ�����з���ֵ

	myPrint02(1000);
}


//�������󳬳�����ͨ�����ĸ�����Ա��溯���ĵ���״̬
void test02()
{
	Myprint myPrint;
	myPrint(100);
	myPrint(100);
	myPrint(100);
	myPrint(100);
	cout << "���ô���Ϊ�� " << myPrint.m_count << endl;
}


//�������������Ϊ��������
void doPrint(Myprint myPrint, int num)
{
	myPrint(num);
}

void test03()
{
	doPrint(Myprint(), 222);
}

int main()
{
	//test01();
	//test02();
	test03();
	system("pause");
	return 0;
}

