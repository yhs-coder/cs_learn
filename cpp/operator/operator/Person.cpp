#include "Person.h"
std::ostream& operator << (std::ostream& os, const Person& p)
{
	os << "name��" << p._name << "  , age: " << p._age;
	return os;
}