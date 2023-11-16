#include <iostream>
using std::cout;
using std::endl;

class Base
{
public:
	Base() : a_(100) {}
	void func() {
		cout << "Base�е�func����" << endl;
	}
	void func(int a) {
		cout << "Base�е�func(int)����" << endl;
	}

	int a_;
};

class Son : public Base
{
public:
	Son() : a_(200) {}
	void func() {
		cout << "Son�е�func����" << endl;
	}
	int a_;
};

void test01()
{
	Son s1;
	cout << "s1.a_ = " << s1.a_ << endl;	// 200
	cout << "sizeof(Son) = " << sizeof(Son) << endl;	// 8
	cout << "sizeof(Base) = " << sizeof(Base) << endl;  // 4

	//���ǿ������������� ���ʸ����е�ͬ����Ա
	cout << "Base�е�a_ = " << s1.Base::a_ << endl;	// 100
}


void test02()
{
	//���������¶����˸����е�ͬ����Ա����������ĳ�Ա������ ���ص��������������ذ汾��ͬ����Ա������������������ʾָ������
	Son s1;
	// s1.func(100);	�����ͬ�������غ����������޷�����
	s1.func();
	// ��ʾ����
	s1.Base::func();
	Base().func();
	Base().func(100);
}

int main()
{
	//test01();
	test02();
	system("pause");
	return 0;
}





