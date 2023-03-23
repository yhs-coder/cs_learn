#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <limits>
using namespace std;

/***********************************************
	��׼������

	1.cin.get() ��ȡһ���ַ� 
		1.1 ʹ�� cin.get() ������뻺�����ж�ȡ���ݣ�������ֱ�Ӵ���Ļ�����ȡ���ݡ�
		1.2 ���뻺������һ���ڴ�������������ʱ�洢���̻��ļ��������豸��������ݣ�Ȼ���ٽ��䴫�䵽�����н��д�����ʹ�� cin.get() ʱ��������뻺������û���κ����ݣ����ȴ��û����룬ֱ���û��������ݲ����»س���ʱ��cin.get() �Ż��ȡ���뻺�����е����ݡ�
	2.cin.get(��������) ��ȡ�ַ���
		2.1 ����cin.get��ȡ�ַ���ʱ�򣬻��з������ڻ�������
		2.2 �� cin.get(buf, 1024) ������ȡ����ʱ�������ȡ���������е������ַ���ֱ����ȡ�� 1024-1 ���ַ����������з� \n ���������ļ���βΪֹ����ȡ�����ַ���洢�� buf �����У���������Զ����һ���ַ�����ֹ�� '\0'���Ա�ʾ�ַ����Ľ�����
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


////cin.ignore() ���� Ĭ�Ϻ���1���ַ��� ����������X���������X���ַ�
void test04()
{
	cin.ignore(2);
	char c = cin.get();
	cout << "c = " << c << endl;
	cout << "c = " << c << endl;

}

//cin.peek() ͵��
void test05()
{
	char c = cin.peek();
	cout << "c = " << c << endl;

	c = cin.get();
	cout << "c = " << c << endl;

	c = cin.get();
	cout << "c = " << c << endl;
}

//cin.putback() �Ż�
void test06()
{
	char b = cin.get();
	cin.putback(b);

	char buf[1024] = { 0 };
	cin.getline(buf, 1024);
	cout << buf << endl;
}

//����1�� �ж��û���������� ���ַ�����������  12345     abcde
void test07()
{
	cout << "������һ���ַ�����������" << endl;
	char c = cin.peek();
	if (c >= '0' && c <= '9')
	{
		int num;
		cin >> num;
		cout << "������������� Ϊ��" << num << endl;
	}
	else
	{
		char buf[1024] = { 0 };
		cin >> buf;
		cout << "����������ַ��� ��" << buf << endl;
	}

}

//����2�� �û����� 0 ~ 10 ֮������֣��������������������

void test08()
{
	int num;
	while (true)
	{
		
		cout << "������ 0 ~ 10 ֮�������" << endl;
		cin >> num;
		//�����־λΪ 0  ������������    �����־λΪ1   �������쳣
		if (cin.fail()||num < 0 || num > 10 )
		{
			cout << "������������������" << endl;
			cin.clear(); //����������Ĵ���״̬��־
			cin.ignore(numeric_limits<streamsize>::max(), '\n');  // ������뻺�����е�����
			//cin.sync(); ���������ʱ�����뻺��������Ȼ��ʣ����ַ�����cin.sync()����������������뻺�����е������ַ�.�������ﲻ��ʹ�ã�
			
			//cin.sync()����������뻺�����е��κ�δ��ȡ���ַ�
		} 
		else
		{
			break;
		}
	}
	cout << "������������ǣ�" << num << endl;
}


int main() {
	//test01();
	//test02();
	//test03();
	//test04();
	//test05();
	//test06();
	//test07();
	test08();



	system("pause");
	return EXIT_SUCCESS;
}













