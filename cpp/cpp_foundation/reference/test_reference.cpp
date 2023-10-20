#include<iostream>
using namespace std;

/*
	1. ���õĻ����﷨��	���� &���� = ԭ��
	���õ�Ŀ�ģ� �����
*/
void test01() {
	int a = 10;
	int& b = a;
	//ָ��(����)ͬһ���ڴ�ռ�
	cout << "&b = " << &b << ", &a = " << &a << endl;
	b = 100;
	cout << "b = " << b << endl;
	cout << "a = " << a << endl;
}

/*	
	2. ��ע�����
		2.1 ���ñ����ʼ��
		2.2 ���ñ���ָ��һ�������ڴ�ռ�
		2.3 ����һ����ʼ���󣬾Ͳ�����������������
		2.4 ��Ҫ���ؾֲ�����������
		2.5 ���ͱ�ʶ�� �� Ŀ����������� ��ͬ
*/

void test02() {

	int a = 11;
	//int &b; //erroe,# 2.1���ñ���Ҫ��ʼ��
	//int &b = 10;    # 2.2
	int& b = a;

	int  c = 100;
	b = c;  //��ֵ

	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "c = " << c << endl;
	// #2.3 
	cout << "&b = " << &b << ", &c = " << &c << endl;
}
int& func() {
	int a = 10;
	return a;
}

//# ����2.4
void test2_4() {
	int& ref = func();
	cout << "ref = " << ref << endl;
	cout << "ref = " << ref << endl;
}

/*
	3. �����齨������
		������3.1 ֱ�ӽ�������
			 3.2 �ȶ����������ͣ���ͨ�����Ͷ�������
*/
void test03() {
	//3.1 ֱ�ӽ�������
	int arr[10];
	//type* ref = &arr;
	int(&pArr)[10] = arr;
	for (int i = 0; i < 5; i++)
	{
		arr[i] = 100 + i;
		cout << pArr[i] << endl;
	}

	//3.2 �ȶ����������ͣ���ͨ�����Ͷ�������
	typedef int(ARRAY_TYPE)[10];
	//����  &���� = ԭ��
	ARRAY_TYPE& pArr2 = arr;
	for (int i = 0; i < 5; i++)
	{
		cout << pArr2[i] << endl;
	}
}

/*
	4. ���õ�ʹ�ó�����
		1. ����������
		2. ����������ֵ
		3. �������ķ���ֵ�����ã������ĵ��ÿ�����Ϊ��ֵ
*/

//��ַ����
void PointerSwap(int* m, int* n) {
	int temp = *m;
	*m = *n;
	*n = temp;
}
//���ô���
void ReferenceSwap(int& m, int& n) {
	int temp = m;
	m = n;
	n = temp;
}
int& func2() {
	static int a = 10;
	return a;
}

void test4_3() {
	int& ref = func2();
	cout << "ref = " << ref << endl;
	cout << "ref = " << ref << endl;
	func2() = 1000;
	cout << "ref = " << ref << endl;

}

void test04() {
	int a = 10;
	int b = 20;
	cout << "a:" << a << " b:" << b << endl;
	//��ַ����
	PointerSwap(&a, &b);
	cout << "a:" << a << " b:" << b << endl;
	//���ô���
	ReferenceSwap(a, b);
	cout << "a:" << a << " b:" << b << endl;
}

//6. ָ������
struct Person
{
	int age;
};

void AllocateSpace(Person** p)
{
	if (p == nullptr) return;
	//pָ��ָ���ָ��    *p  ָ��ָ�����personָ��   **p  person����
	*p = (Person*)malloc(sizeof(Person));
	if (*p == nullptr) {
		exit(-1);
	}
	(*p)->age = 10;

}

void test05() {
	Person* p = nullptr;
	AllocateSpace(&p);
	cout << "p.age = " << p->age << endl;
	free(p);
}


void AllocateSpace2(Person*& pp) // Person * &pp = p;
{
	pp = (Person*)malloc(sizeof(Person));
	if (pp == nullptr) {
		exit(-1);
	}
	pp->age = 20;
}
void test06()
{
	Person* p = nullptr;
	AllocateSpace2(p);
	if (p == nullptr)
		cout << "p = nullptr" << endl;
	cout << "p.age = " << p->age << endl;
	free(p);
}

/*
	7. ����������
*/

void test07() {
	const int& ref = 10;
	// int temp = 10; const int * &ref = temp;
	int* p = (int*)&ref;
	*p = 666;
	cout << "*p = " << *p << endl;
	cout << "ref = " << ref << endl;


	int a = 100;
	const int& aRef = a; //��ʱaRef����a
	// aRef = 200;			//�����޸�aRef��ֵ
	a = 100; //OK
	cout << "a:" << a << endl;
	cout << "aRef:" << aRef << endl;

}

int main() {
	//test01();
	//test02();
	//test2_4();
	//test03();
	//test04();
	//test4_3();
	//test05();
	//test06();
	test07();
	//showValue(567);
	char var = 'a';
	char& ref = var;
	cout << "sizeof(var) = " << sizeof(var) << endl;
	cout << "sizeof(ref) = " << sizeof(ref) << endl;

	system("pause");
	return 0;
}



