#include <iostream>
using std::cout;
using std::endl;

/*
C++11 override �� final�ؼ���

final�� �����麯������ʾ���麯�������ٱ���д
> �ؼ���final���ں��������б�֮��

override: ����������麯���Ƿ���д�˻����ĳ���麯�������û����д����뱨��
*/

#if 0
// ����
class Person
{
public:
	// ���麯����final���Σ������ٱ���д
	virtual void buy_ticket() final {
		cout << "��Ʊ - ȫ��" << endl;
	}
};

// ����
class Student : public Person
{
public:

#if 0
	// ������д�����뱨��
	virtual void buy_ticket() {
		cout << "��Ʊ - ���" << endl;
	}
#endif
};

#else
// ����override
// ����
class Person
{
public:
	virtual void buy_ticket() {
		cout << "��Ʊ - ȫ��" << endl;
	}
};

// ����
class Student : public Person
{
public:
	// ��������˸����麯������д������ͨ��
	virtual void buy_ticket() override {
		cout << "��Ʊ - ���" << endl;
	}
};

class Soldier : public Person
{
public:
	// ����û����д�����е��麯�������뱨��
#if 0
	virtual void buy_ticket(int i) override {
		cout << "���� - ��Ʊ" << endl;
	}
#endif
};


#endif

int main()
{
	return 0;
}
