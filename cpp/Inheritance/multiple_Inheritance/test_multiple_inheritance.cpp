#include <iostream>
using std::cout;
using std::endl;

class Base1
{
public:
	Base1() : a_(10) {}
	void func() {
		cout << "Base1::func1" << endl; 
	}
	int a_;
};

class Base2
{
public:
	Base2() : a_(20) {}
	void func() {
		cout << "Base2::func1" << endl;
	}
	int a_;
};

//��̳�
class Son : public Base1, public Base2
{
public:
	int c_;
	int d_;
};

void test01()
{
	cout << "sizeof Son = " << sizeof(Son) << endl; //16
	Son s;
	// ����̳е�������������ͬ����Ա����Ҫ������������
	// cout << s.a_ << endl;error
	cout << s.Base1::a_ << endl;
	cout << s.Base2::a_ << endl;
	//s.func();	// ����������
	s.Base1::func();
	s.Base2::func();

}
int main() {
	test01();


	system("pause");
	return EXIT_SUCCESS;
}