#include<iostream>
using std::cout;
using std::endl;


class Base
{
public:
	int a_;
protected:
	int b_;
private:
	int c_;  //������˽�����ԣ�������ʲ��������ɱ�������������
};

class Derived : public Base
{
public:
	int d_;
};

void test01()
{
	cout << "size of  Base = " << sizeof(Base) << endl; // ���Ϊ12
	cout << "size of  Derived = " << sizeof(Derived) << endl; // ���Ϊ16
}

int main()
{
	test01();
	system("pause");
	return EXIT_SUCCESS;

}