#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <functional>  //内建函数对象头文件
#include <vector>
#include <algorithm>
using namespace std;


/*
template<class T> T negate<T>//取反仿函数  一元运算
*/

void test01()
{
	negate<int>n;
	cout << n(10) << endl;
}

//template<class T> T plus<T>//加法仿函数
void test02()
{
	plus<int> p;
	cout << p(10, 10) << endl;
}

//template<class T> bool greater<T>//大于
void test03()
{
	vector<int>v;
	v.push_back(20);
	v.push_back(50);
	v.push_back(10);
	v.push_back(30);
	v.push_back(40);

	//从大到小排序
	sort(v.begin(), v.end(), greater<int>());

	for_each(v.begin(), v.end(), [](int val) {cout << val << " "; });
	cout << endl;
}


int main()
{
	//test01();
	//test02();
	test03();

	system("pause");
	return 0;
}

