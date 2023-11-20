#include <iostream>
using std::cout;
using std::endl;

/*
C++11 override 和 final关键字

final： 修饰虚函数，表示该虚函数不能再被重写
> 关键字final放在函数参数列表之后

override: 检查派生类虚函数是否重写了基类的某个虚函数，如果没有重写则编译报错
*/

#if 0
// 父类
class Person
{
public:
	// 该虚函数被final修饰，不能再被重写
	virtual void buy_ticket() final {
		cout << "买票 - 全价" << endl;
	}
};

// 子类
class Student : public Person
{
public:

#if 0
	// 不能重写，编译报错
	virtual void buy_ticket() {
		cout << "买票 - 半价" << endl;
	}
#endif
};

#else
// 测试override
// 父类
class Person
{
public:
	virtual void buy_ticket() {
		cout << "买票 - 全价" << endl;
	}
};

// 子类
class Student : public Person
{
public:
	// 子类完成了父类虚函数的重写，编译通过
	virtual void buy_ticket() override {
		cout << "买票 - 半价" << endl;
	}
};

class Soldier : public Person
{
public:
	// 子类没有重写父类中的虚函数，编译报错
#if 0
	virtual void buy_ticket(int i) override {
		cout << "优先 - 买票" << endl;
	}
#endif
};


#endif

int main()
{
	return 0;
}
