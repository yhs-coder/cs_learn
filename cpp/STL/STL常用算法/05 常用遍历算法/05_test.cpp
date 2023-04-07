#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

class MyPrint
{
public:
	void operator()(int val)
	{
		cout << val << endl;
		m_count++;
	}
	int m_count = 0;
};


//for_each  用于遍历
//有返回值,仿函数对象
void test01()
{
	vector<int>v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}
	//for_each()第三个参数可以是仿函数，也可以是回调函数
	MyPrint print = for_each(v.begin(),v.end(),MyPrint());
	cout << "print.count = " << print.m_count << endl;
}


//for_each 绑定参数输出
class MyPrint2:public binary_function<int,int,void>
{
public:
	void operator()(int val, int start) const
	{
		cout << val + start << endl;
	}
};

void test02()
{
	vector<int>v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}
	for_each(v.begin(), v.end(), bind2nd(MyPrint2(), 1000));
}

//transform算法 将指定容器区间元素搬运到另一容器中
class MyTransform
{
public:
	int operator()(int val)
	{
		return val + 10000;
	}
};

void test03()
{
	vector<int>v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}
	vector<int>v2;
	v2.resize(v.size());
	transform(v.begin(), v.end(),v2.begin(), MyTransform());
	for_each(v2.begin(), v2.end(), [](int val) {cout << val << " "; });


}


int main()
{
	//test01();
	//test02();
	test03();
	system("pause");
	return 0;
}

