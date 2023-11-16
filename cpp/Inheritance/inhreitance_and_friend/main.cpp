#include <iostream>
#include <string>
using std::cout;
using std::endl;

class Student;
class Person
{
public:
	//声明Display是Person的友元
	friend void Display(const Person& p, const Student& s);
protected:
	std::string _name; //姓名
};

class Student : public Person
{
protected:
	int _id; //学号
};

void Display(const Person& p, const Student& s)
{
	cout << p._name << endl; //可以访问
	// cout << s._id << endl; //无法访问
}
int main()
{
	Person p;
	Student s;
	Display(p, s);
	return 0;
}
