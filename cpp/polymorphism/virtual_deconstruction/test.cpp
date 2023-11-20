#include<iostream>
using std::cout;
using std::endl;

class People
{
public:
	People() {
		cout << "构造函数 People!" << endl;
	}
	virtual void show_name() = 0;
	
	//纯虚析构，需要声明，也需要实现
	//如果一个类有了纯虚析构函数，那么此类也属于抽象类
	// virtual ~People() = 0;
#if 0
	// 使用一般的析构函数：
	// 当基类的指针指向派生对象时，如果派生类有动态分配的内存，此时销毁基指针时，不会调用派生类的析构
	// 造成内存泄漏
	~People() {
		cout << "析构函数 People..." << endl;
	}
#else
	// 如果子类中有指向堆区的属性，那么要利用虚析构技术, 在delete的时候，会调用子类的析构函数
	virtual ~People()
	{
		cout << "虚析构函数 People..." << endl;
	}
#endif
	int num_ = 10;
};

#if 0
People::~People()
{
	cout << "纯虚析构函数 People!" << endl;
}
#endif

class Worker : public People
{
public:
	Worker() {
		cout << "构造函数 Worker!" << endl;
		pname_ = new char[10];
	}

	virtual void show_name() {
		cout << "Worker::show_name..." << endl;
	}

	~Worker() {
		if (pname_ != NULL) {
			delete[] pname_;
		}
		cout << "析构函数 Worker..." << endl;
	}
private:
	char* pname_ = nullptr;
};

void test()
{
	People* people = new Worker;
	//people->~People();
	delete people;
}

int main()
{
	test();
	system("pause");
	return 0;
}
