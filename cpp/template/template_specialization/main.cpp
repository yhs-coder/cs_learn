#include <iostream>
#include <string>
using std::cout;
using std::endl;

/********************************************************
	模板特化：针对特殊的类型，进行特殊化的实现方式

	模板特化：
		1.函数模板特化
		2. 类模板特化
			2.1 全特化
			2.2 偏特化
********************************************************/


/********************************************************
	函数模板特化步骤：
	1. 首先必须要有一个基础的函数模板
	2. 关键字template后面接一对空的尖括号<>
	3. 在函数模板名后加<>,并在<>中指定需要特化的类型
	4. 函数形参必须和函数模板<>中特化的类型一致，否则不同的编辑器可能会报错
*********************************************************/

// 基础的函数模板
template <typename T>
bool is_equal(T x, T y)
{
	return x == y;
}

// 函数模板特化 --> 针对char*类型进行特殊处理
template<>
bool is_equal<char*>(char* x, char* y)
{
	return strcmp(x, y) == 0;
}

# if 0
// 测试
int main()
{
	cout << is_equal(1, 1) << endl;
	cout << is_equal(1.1, 1.2) << endl;
	char a1[] = "hello";
	char a2[] = "hello";
	cout << is_equal(a1, a2) << endl; // 优先调用特化的函数模板
}
#endif 

class Person
{
public:
	Person(std::string name, int age)
		: name_(name)
		, age_(age){}
	std::string name_;
	int age_;
};

template <class T>
bool compare(T& a, T& b)
{
	if (a == b) {
		return true;
	}
	return false;
}


// 模板特例化，为自定义数据类型提供特殊模板
// 以template<>开头，并通过名称来指出类型，特例化优先于常规模板
template<>
bool compare<Person>(Person& a, Person& b)
{
	return a.name_ == b.name_ && a.age_ == b.age_;
}

#if 0
int main()
{
	int a = 10;
	int b = 20;
	bool ret = compare(a, b);
	if (ret) {
		cout << "a == b" << endl;
	}
	else {
		cout << "a != b" << endl;
	}

	// 模板函数无法比较类类型或结构体类型，或者数组
	// 此时需要为这些特定的类型提供具体化的模板。也就是模板特例化
	Person p1("tom", 100);
	//Person p2("tom", 100);
	Person p2("tom", 1200);
	ret = compare(p1, p2);
	if (ret) {
		cout << "a == b" << endl;
	}
	else {
		cout << "a != b" << endl;
	}
	
	return 0;
}
#endif

/********************************************************
	类模板的特化：
		1. 全特化：将模板参数列表中所有的参数都确定化。
		2. 偏特化（半特化）：针对模板参数进一步进行条件限制设计的特化版本。
			2.1 部分特化 ：对模板参数列表中的部分参数进行确定化
			2.2 参数更进一步的限制：比如指定当T1和T2为某种类型时 如(T1*,T2*)，使用特殊化的类模板.
			针对模板参数进一步的条件限制所设计出来的一个特化版本。
	
	类模板特化步骤：
	1. 首先必须要有一个基础的类模板
	2. 关键字template后面接一对空的尖括号<>，（表示模板的特化）
	3. 在类模板名后加<>,并在<>中指定需要特化的类型

*********************************************************/

// 1. 全特化
template <class T1, class T2>
class Yang
{
public:
	Yang() {
		cout << "Yang<T1, T2>" << endl;
	}
private:
	T1 y1_;
	T2 y2_;
};

template <>
class Yang<int, double>
{
public:
	Yang() {
		cout << "Yang<int, double>" << endl;
	}
private:
	int y1_;
	double y2_;
};

#if 0
// 测试
int main()
{
	Yang<double, double> y1;
	Yang<int, double> y2;
	return 0;
}
#endif

// 偏特化
// 部分特化
template <class T2>
class Yang<int, T2>
{
public:
	Yang() {
		cout << "Yang<int, T2>" << endl;
	}
private:
	int y1_;
	T2 y2_;
};

#if 0
int main()
{
	Yang<int, int> y1;
	Yang<double, int> y2;
	return 0;
}
#endif


// 两个参数偏特化为指针类型
template <class T1, class T2>
class Yang<T1*, T2*>
{
public:
	Yang() {
		cout << "Yang<T1*, T2*>" << endl;
		cout << typeid(T1).name() << endl;
		cout << typeid(T2).name() << endl;
	}
private:
	T1 y1_;
	T2 y2_;
};


// 两个参数偏特化为引用类型
template <class T1, class T2>
class Yang<T1&, T2&>
{
public:
	Yang() {
		cout << "Yang<T1&, T2&>" << endl;
		cout << typeid(T1).name() << endl;
		cout << typeid(T2).name() << endl;
	}
private:
	T1 y1_;
	T2 y2_;
};

int main()
{
	Yang<int, int> y1;
	Yang<int*, int*> y2;
	Yang<int&, int&> y3;
	return 0;
}


