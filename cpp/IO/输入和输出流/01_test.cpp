#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

/***********************************************
	��׼������

	1.cin.get() ��ȡһ���ַ�
	2.cin.get(��������) ��ȡ�ַ���
		2.1 ����cin.get��ȡ�ַ���ʱ�򣬻��з������ڻ�������
	3.cin.getline() ��ȡ�ַ���
		3.1 ����cin.getline��ȡ�ַ���ʱ�򣬻��з����ᱻȡ�ߣ�Ҳ���ڻ������У�����ֱ���ӵ�
	4.cin.ignore() ���� Ĭ�Ϻ���1���ַ��� ����������X���������X���ַ�
	5.cin.peek()  ͵��
	6.cin.putback()  �Ż� �Ż�ԭλ��
*************************************************/

void test01()
{
	//����  a  s     ��һ�� a  �ڶ���  s  ������ ����  ���Ĵ� �ȴ��´�����

	char c = cin.get();
	cout << "c = " << c << endl;

	c = cin.get();
	cout << "c = " << c << endl;

	c = cin.get();
	cout << "c = " << c << endl;	

	c = cin.get();
	cout << "c = " << c << endl;

}

void test02()
{
	char buf[1024] = { 0 };
	cin.get(buf, 1024);
	char c = cin.get();
	cout << "c = " << c << endl;
	//����cin.get��ȡ�ַ���ʱ�򣬻��з������ڻ�������
	if (c == '\n') {
		cout << "���з������ڻ������ˣ�" << endl;
	}
	else
	{
		cout << "���з����ڻ������У�" << endl;
	}
	cout << buf << endl;
}

void test03()
{
	char buf[1024] = { 0 };
	//����cin.getline��ȡ�ַ���ʱ�򣬻��з����ᱻȡ�ߣ�Ҳ���ڻ������У�����ֱ���ӵ�
	cin.getline(buf, 1024);
	char c = cin.get();
	if (c == '\n')
	{
		cout << "���з������ڻ�����" << endl;
	}
	else
	{
		cout << "���з����ڻ�����" << endl;
	}
	cout << buf << endl;
}

int main() {
	test01();
	//test02();
	//test03();
	//test04();
	//test05();
	//test06();
	//test07();
	//test08();



	system("pause");
	return EXIT_SUCCESS;
}













