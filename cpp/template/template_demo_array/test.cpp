#include <iostream>
#include "array.hpp"

using std::cout; 
using std::endl;

// ²âÊÔ´úÂë
class Person {
public:
	Person() = default;
	Person(std::string name, int age)
		: name_(name)
		, age_(age) {}
public:
	std::string name_;
	int age_;
};

void print_array_int(Array<int>& arr) {
	for (int i = 0; i < arr.get_size(); i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

void print_person(Array<Person>& person_arr)
{
	for (int i = 0; i < person_arr.get_size(); i++) {
		cout << "ĞÕÃû£º" << person_arr[i].name_ << " ÄêÁä£º " << person_arr[i].age_ << endl;
	}
}

int main()
{
	Array<int> array_int(10);
	for (int i = 0; i < 9; i++) {
		array_int.push_back(i);
	}
	array_int.get_size();
	array_int.push_back(1111);
	print_array_int(array_int);

	Array<int> cpoy_array(array_int);
	array_int.get_size();
	print_array_int(cpoy_array);

	Array<Person> array_person(10);
	Person p1("aa", 30);
	Person p2("bb", 20);
	Person p3("cc", 18);
	Person p4("dd", 15);
	Person p5("vv", 24);
	array_person.push_back(p1);
	array_person.push_back(p2);
	array_person.push_back(p3);
	array_person.push_back(p4);
	array_person.push_back(p5);
	array_person.get_size();
	print_person(array_person);
	Array<Person> copy_person(array_person);
	array_person.get_size();
	print_person(array_person);

	return 0;
}