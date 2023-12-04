#include <iostream>
#include "Person.hpp"


void test1()
{
	Person<std::string, int> p("tom", 30);
	p.show_person();
}

int main()
{
	test1();
	return 0;
}