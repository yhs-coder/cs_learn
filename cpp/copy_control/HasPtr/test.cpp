#define _CRT_SECURE_NO_WARNINGS
#include "HasPtr.h"

int main()
{
	HasPtr p1;
	std::cout << p1.get_count() << std::endl;
	HasPtr p2("hello world!");
	p1 = p2;
	HasPtr p3 = p1;
	std::cout << p2.get_count() << std::endl;
	return 0;

}