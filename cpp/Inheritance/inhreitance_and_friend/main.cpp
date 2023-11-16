#include <iostream>
#include <string>
using std::cout;
using std::endl;

class Student;
class Person
{
public:
	//����Display��Person����Ԫ
	friend void Display(const Person& p, const Student& s);
protected:
	std::string _name; //����
};

class Student : public Person
{
protected:
	int _id; //ѧ��
};

void Display(const Person& p, const Student& s)
{
	cout << p._name << endl; //���Է���
	// cout << s._id << endl; //�޷�����
}
int main()
{
	Person p;
	Student s;
	Display(p, s);
	return 0;
}
