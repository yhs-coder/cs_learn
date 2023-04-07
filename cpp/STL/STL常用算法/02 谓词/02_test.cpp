#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//一元谓词
class GreaterThan20
{
public:
	bool operator()(int val)
	{
		return val > 20;
	}
};

void test01()
{
	vector<int>v;
	v.push_back(10);
	v.push_back(20);
	v.push_back(30);
	v.push_back(40);
	v.push_back(50);
	vector<int>::iterator ret =   find_if(v.begin(), v.end(),GreaterThan20());
	if (ret != v.end())
	{
		cout << "找到大于20的数字为： " << *ret << endl;
	}
	else
	{
		cout << "未找到." << endl;
	}
}


void myPrintInt(int val)
{
	cout << val << " ";
}
//二元谓词
class MyCompare
{
public:
	bool operator()(int v1, int v2)
	{
		return v1 > v2;
	}
};

void test02()
{
	vector<int>v;

	v.push_back(10);
	v.push_back(30);
	v.push_back(20);
	v.push_back(40);
	v.push_back(50);
	sort(v.begin(), v.end()); //从小到大进行排序
	for_each(v.begin(), v.end(), myPrintInt);
	cout << endl;

	sort(v.begin(), v.end(), MyCompare());
	//使用lambda表达式 匿名函数 []代表lambda表达式
	for_each(v.begin(), v.end(), [](int val) {cout << val << " "; });
	cout << endl;

}

int main()
{
	//test01();
	test02();
	system("pause");
	return 0;
}

