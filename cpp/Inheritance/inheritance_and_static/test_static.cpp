#include  <iostream>
using std::cout;
using std::endl;

class Base
{
public:

	static void func() {
		cout << "Base�е�func���� " << endl;
	}

	static void func(int a) {
		cout << "Base�е�func(int a)���� " << endl;
	}
	static int a_;
};
int Base::a_ = 10;

class Derived : public Base
{
public:
	// �ض��徲̬��Ա���������������صĺ���������
	static void func() {
		cout << "Derived�е�func���� " << endl;
	}
	// �ı���ຯ����ĳ������������ֵ���߲����������������ػ������صĺ���
	static void func(int a, int b = 100) {
		cout << "Base�е�func(int a, int b)���� " << endl;
	}
	static int a_;	// �������ж���һ��ͬ���ľ�̬��Ա�����ྲ̬��Ա���Խ�������
};
int Derived::a_ = 20;

void test01()
{
	//���ʾ�̬��Ա
	Derived s;
	//1��ͨ���������
	cout << "a_ = " << s.a_ << endl; //20
	cout << "Base�е�a_ = " << s.Base::a_ << endl; //10

	//2��ͨ����������
	cout << "a_ = " << Derived::a_ << endl; //20
	//ͨ�������ķ�ʽ ���� �����������µ�a_��̬��Ա����
	cout << "Base::a_ = " << Derived::Base::a_ << endl; //10
	cout << "a_ = " << Base::a_ << endl;	// 10

	//3.ͨ�������������
	cout << "Derived().a_ = " << Derived().a_ << endl;	// 20
}

void test02()
{
	//1��ͨ������
	Derived s;
	s.func();		 //Derived
	s.Base::func();  //base


	//2��ͨ������
	Derived::func();
	//�������ض��常����ͬ����Ա����������ĳ�Ա���������ص����������а汾����Ҫ�����������
	Derived::Base::func();

	s.func(1111);
	s.Base::func(2222);
}

int main() 
{
	//test01();
	test02();

	system("pause");
	return EXIT_SUCCESS;
}