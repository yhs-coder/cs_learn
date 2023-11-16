#include <iostream>
using std::cout;
using std::endl;

//////////////   ���м̳�   //////////////
class Base1
{
public:
	Base1() : a_(10), b_(20), c_(30) {
		cout << "Base1 Constructor..." << endl;
	}

public:
	int a_;
protected:
	int b_;
private:
	int c_;
};

class Derived1 : public Base1
{
public:
	void func()
	{
		a_ = 100; // �����й���Ȩ�� �����б�Ϊ ����Ȩ��
		b_ = 100; // ������ ����Ȩ�� �����б�Ϊ ����Ȩ��
		// c_ = 100; // ������˽�г�Ա�� �����޷�����
	}
	int _c;

};

void test01()
{
	Derived1 s1;
	s1.a_ = 100; //��Derived1�� a_�ǹ���Ȩ��  ������Է���
	// s1.b_ = 100; //��Derived1�� b_�Ǳ���Ȩ��  ���ⲻ���Է���

	cout << "Base1 size: " << sizeof(Base1) << endl;
	cout << "Derived1 size: " << sizeof(Derived1) << endl;
}

//////////////   �����̳�   //////////////
class Base2
{
public:
	int a_;
protected:
	int b_;
private:
	int c_;
};

class Derived2 : protected Base2
{
public:
	void func()
	{
		a_ = 100;//������ ����Ȩ�� �����б�Ϊ  ����Ȩ��
		b_ = 100;//������ ����Ȩ�� �����б�Ϊ  ����Ȩ��
		//c_ = 100;//������˽�г�Ա�������޷�����
	}
};
void test02()
{
	Derived2 s;
	//s.a_ = 100;  //������ ����Ȩ�� �޷�����
	//s.b_ = 100;  //������ ����Ȩ�� �޷�����
	//s.c_ = 100;  //���౾��û�з���Ȩ��
}

//////////////   �����̳�   //////////////
class Base3
{
public:
	int a_;
protected:
	int b_;
private:
	int c_;
};

class Derived3 :private Base3
{
public:
	void func()
	{
		a_ = 100;  //������ ����Ȩ�� �����б�Ϊ  ˽��Ȩ��
		b_ = 100;  //������ ����Ȩ�� �����б�Ϊ  ˽��Ȩ��
		//c_ = 100;//������˽�г�Ա�������޷�����
	}
};

class GrandDerived3 : public Derived3
{
	void func()
	{
		//a_ = 100; // ��Derived3�� �Ѿ���Ϊ˽��Ȩ�ޣ�GrandDerived3���ʲ���
		//b_ = 200;
	}
};
void test03()
{
	Derived3 s;
	//s.a_ = 100;//��Derived3�б�Ϊ˽��Ȩ�ޣ�������ʲ���
	//s.b_ = 100;//��Derived3�б�Ϊ˽��Ȩ�ޣ�������ʲ���

}

int main()
{
	test01();
	system("pause");
	return EXIT_SUCCESS;
}
