#include <iostream>
#include "delete.h"
#include "HasPtr.h"

/*
	深拷贝（行为像值的类）
*/

int main()
{
	std::string str("hello");
	HasPtr p(str);
	std::cout << p.get_ps() << std::endl;
	std::cout << *p.get_ps() << std::endl;
	
	HasPtr p2 = p;
	std::cout << p2.get_ps() << std::endl;
	std::cout << *p2.get_ps() << std::endl;

	HasPtr p3;
	p3 = p2;
	std::cout << p3.get_ps() << std::endl;
	std::cout << *p3.get_ps() << std::endl;
}


/* 
	== delete
*/
#if 0
int main()
{
	NoCopy cp, cp2;
	// NoCopy cp2 = cp;	//无法拷贝
	// cp2 = cp;	// 无法赋值
	//NoDtor nd;	// 类的析构函数被删除，无法创建该类的对象
	NoDtor* p = new NoDtor();	// 可以动态分配该类型的对象
	//delete p;					// 但不能释放 
}
#endif



/*
	练习 13.14
*/
class Numbered
{
public:
	Numbered() {
		_mysn = _unique++;
	}

	Numbered(const Numbered& num) {
		_mysn = _unique++;
	}

	int _mysn;
	static int _unique;	// 生成唯一的序号
};
int Numbered::_unique = 10;

/*
void f(Numbered s) {
	std::cout << s._mysn << std::endl;
}*/

void f(const Numbered& s) {
	std::cout << s._mysn << std::endl;
}


class A
{
public:
	A() = default;
	int* point;
};
#if 0
int main()
{
	
	std::cout << A().point << std::endl;
	return 0;
}
#endif

#if 0
int main()
{
	Numbered a, b = a, c = b;	// 10 11 12
#if 0
	// 使用合成的拷贝构造函数
	f(a);	// 10
	f(b);	// 10
	f(c);	// 10
----------------------------------
	// 使用定义的拷贝构造函数
	f(a);	// 13
	f(b);	// 14
	f(c);	// 15
	std::cout << Numbered::_unique << std::endl; // 16
#endif
	f(a);	// 10 
	f(b);	// 11
	f(c);	// 12
	return 0;
}
#endif