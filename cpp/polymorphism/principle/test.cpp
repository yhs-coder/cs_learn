#include <iostream>
using std::cout;
using std::endl;

/*
	̽����̬��ԭ��
*/

#if 0
//����
class Base
{
public:
	//�麯��
	virtual void func1() {
		cout << "Base::Func1()" << endl;
	}
	//�麯��
	virtual void func2() {
		cout << "Base::Func2()" << endl;
	}
	//��ͨ��Ա����
	void func3() {
		cout << "Base::Func3()" << endl;
	}
private:
	int a_ = 1;
};
//����
class Derive : public Base
{
public:
	//��д�麯��Func1
	virtual void func1()
	{
		cout << "Derive::Func1()" << endl;
	}
private:
	int b_ = 2;
};

// ͨ�����ԣ��򿪼��Ӵ��ڣ��۲�����ڲ�
void test1()
{
	Base b;
	Derive d;
}
#endif

// ����
class Person
{
public:
	virtual void buy_ticket() {
		cout << "��Ʊ - ȫ��" << endl;
	}
	int p_ = 1;
};

// ����
class Student : public Person
{
public: 
	virtual void buy_ticket() {
		cout << "��Ʊ - ���" << endl;
	}

	int s_ = 2;
};

void test2()
{
	Person jerry;
	Student bobo;
	bobo.p_ = 3;
	Person* p1 = &jerry;
	Person* p2 = &bobo;
	p1->buy_ticket();
	p2->buy_ticket();
}

void test3()
{
	// ͬ���͵Ķ�����һ�����
	Person jerry;
	Student bobo;
	Student s;
	Person p1 = jerry;
	Person p2 = bobo;
	Person p3;
	Person p4;
}

/** ���̳е��麯���� **/
// ����
class Base
{
public:
	virtual void func1() {
		cout << "Base::func1()" << endl;
	}
	virtual void func2() {
		cout << "Base::func2()" << endl;
	}
private:
	int a_ = 10;
};

class Derived : public Base
{
public:
	virtual void func1() {
		cout << "Derived::func1()" << endl;
	}
	virtual void func3() {
		cout << "Derived::func3()" << endl;
	}
	virtual void func4() {
		cout << "Derived::func4()" << endl;
	}
private:
	int b_ = 20;
};


// ���Բ鿴�����е���ָ�룬�Լ��麯����
void test4()
{
	Base b;
	Derived d;
}


// ���������һ��ָ�����飬���һ��Ԫ�ط�nullptr
// ��ӡ����ַ��������
typedef void(*VFPTR)();	// ����ָ������������
void print_vftable(VFPTR* ptr) // VFPTR*Ϊ����ָ�룬�ɿ���ָ������,�����ӡ���麯����ַ
{
	printf("����ַ��%p\n", ptr);
	cout << "����е��麯����ַ: " << endl;
	for (int i = 0; ptr[i] != nullptr; i++) {
		printf("ptr[%d]: %p --> ", i, ptr[i]);	// ��ӡ����е��麯����ַ(ʹ��C��ʽ�����)
		ptr[i]();	// ʹ���麯����ַ�����麯��
	}
	cout << endl;
}

// ��ӡ�������
void test5()
{
	Base b;
	//print_vftable((VFPTR*)(*(int*)&b));
	// *(size_t*)&b --> ��ת���麯�����ڰ��麯�����ַǿ��ת���� ����ָ���ָ�룬��ָ������
	cout << sizeof(size_t*) << endl;
	print_vftable((VFPTR*)(*(size_t*)&b));
	Derived d;
	print_vftable((VFPTR*)(*(size_t*)&d));

}



/** ��̳е��麯���� **/
class Base1
{
public:
	virtual void func1() {
		cout << "Base1::func1()" << endl;
	}
	virtual void func2() {
		cout << "Base1::func2()" << endl;
	}
private:
	int b1_ = 10;
};


class Base2
{
public:
	virtual void func1() {
		cout << "Base2::func1()" << endl;
	}
	virtual void func2() {
		cout << "Base2::func2()" << endl;
	}
private:
	int b2_ = 10;
};

class Derived2 : public Base1, public Base2
{
public:
	virtual void func1() {
		cout << "Derived::func1()" << endl;
	}
	virtual void func3() {
		cout << "Derived::func3()" << endl;
	}
private:
	int d_ = 10;
};



// ���Բ鿴��̳й�ϵ�е��麯����
void test6()
{
	Base1 b1;
	Base2 b2;
	print_vftable((VFPTR*)(*(size_t*)&b1));
	print_vftable((VFPTR*)(*(size_t*)&b2));
	Derived2 d;
	print_vftable((VFPTR*)(*(size_t*)&d));	// ��ӡd��һ������ַ��������
	print_vftable((VFPTR*)  (*(size_t*)((char*)&d + sizeof(Base1))));   // �����sizeof(Base1)���ֽڵõ��ڶ������ĵ�ַ,��ӡ�ڶ�������ַ��������
}


int main()
{
	//test1();
	//test2();
	//test3();
	////test4();
	//test5();
	test6();
	return 0;
}

