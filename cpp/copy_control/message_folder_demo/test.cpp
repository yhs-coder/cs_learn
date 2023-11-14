#include <iostream>
#include "message.h"

int main()
{
	Folder f1;
	Folder f2;
	Folder f3;

	Message m1("hello");
	Message m2("cpp");

	
	m1.save(f1);
	m1.save(f2);
	m1.save(f3);
	f1.print_debug();	// hello
	f2.print_debug();	// hello
	f3.print_debug();	// hello

	Message m3(m1);
	f1.print_debug();	// hello hello
	f2.print_debug();	// hello hello
	f3.print_debug();	// hello hello

	m1.remove(f1);
	f1.print_debug();	// hello
	std::cout << "----------------" << std::endl;

	m1.print_debug();
	m2.print_debug();

	std::cout << "----------------" << std::endl;
	
	m2.save(f1);
	m2.save(f2);


	m3 = m2;
	f1.print_debug();	// cpp cpp
	f2.print_debug();	// hello cpp cpp
	f3.print_debug();	// hello  
	
	std::cout << "----------------" << std::endl;
	
	f1.print_debug();	// cpp cpp
	f2.print_debug();	// hello cpp cpp
	f2 = f1;
	f2.print_debug();	// cpp cpp
	f1.print_debug();	// cpp cpp

	std::cout << "----------------" << std::endl;

	swap(m1, m2);
	m1.print_debug();	// cpp
	m2.print_debug();	// hello
	
	f1.print_debug();	// cpp cpp
	f2.print_debug();	// cpp cpp
	f3.print_debug();	// hello  

	swap(f1, f3);
	f1.print_debug();	// hello
	f3.print_debug();	// cpp cpp

	return 0;
}