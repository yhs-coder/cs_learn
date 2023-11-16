#include <iostream>
using std::cout;
using std::endl;

class Base1
{
public:
	Base1()
	{
		cout << "Base1�Ĺ��캯������" << endl;
	}
	~Base1()
	{
		cout << "Base1��������������" << endl;
	}
};

class Other
{
public:
	Other()
	{
		cout << "Other�Ĺ��캯������" << endl;
	}

	~Other()
	{
		cout << "Other��������������" << endl;
	}
};

class Derived1 : public Base1
{
public:
	Derived1()
	{
		cout << "Derived1�Ĺ��캯������" << endl;
	}
	~Derived1()
	{
		cout << "Derived1��������������" << endl;
	}
	Other other_;
};

void test01()
{
	//�ȵ��ø��๹�죬�ٵ����������������Ա���죬 �ٵ��������� ��������˳���빹���෴
	Derived1 s;
}


/* 
�����๹�캯���в���ʱ����Ҫ�������ʼ���б�(�����б�)����ʾ���ø��๹�캯��
*/
class Base2
{
public:
	Base2(int a, int b)
	{
		a_ = a;
		b_ = b;
		cout << "Base2�Ĺ��캯������" << endl;
#if 1
		cout << "Base::&a_ = " << &a_ << endl;
		cout << "--------------------------------" << endl;
#endif
	}
public:
	int a_;
private:
	int b_;
};

class Derived2 : public Base2
{
public:
	//���ó�ʼ���б��﷨  ��ʾ���ø����е��������캯��
	Derived2(int a = 100, int b = 100) 
		: Base2(a, b)
		, other_()
	{
		cout << "Derived2�Ĺ��캯������" << endl;
#if 1
		// �����ิ�ã���������ĳ�Ա
		cout << "Derived2::&a_ = " << &(Derived2::a_) << endl;
		cout << "Base2::&a_ = " << &(Base2::a_) << endl;
		cout << "-----------------------------------" << endl;
		Derived2::a_ = 1024;
		cout << "Base2::a_ = " << Base2::a_ << endl; // 1024
		cout << "Derived2::a_ = " << Derived2::a_ << endl; // 1024

#endif
}

private:
	Other other_;
};

class Derived3 : public Base2
{
public:
	//���ó�ʼ���б��﷨  ��ʾ���ø����е��������캯��
	Derived3(int a = 100, int b = 100) : Base2(a, b)
	{
		cout << "Derived3�Ĺ��캯������" << endl;
		cout << "Base2::a_ = " << Base2::a_ << endl;
		cout << "Derived3::&a_ = " << &a_ << endl;
		Derived3::a_ = 1111111;
	}
};

void test02()
{
	Derived2 s(1, 1);
	Derived3 s3;
	cout << "-----------------------------------" << endl;
	cout << "Derived2 ::a_ = " << s.a_ << endl;
	cout << "Derived3 ::a_ = " << s3.a_ << endl;

}


void test03()
{
	Derived3 d3;
	cout << "Derived3 ::a_ = " << d3.Derived3::a_ << endl;
	cout << "Base2::a_ = " << d3.Base2::a_ << endl;

}
//������ ���졢�������������� ��operator=  �ǲ��ᱻ����̳���ȥ��


int main()
{
	//test01();
	test02();
	//test03();
	system("pause");
	return 0;
}