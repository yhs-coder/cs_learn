#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <functional>
using namespace std;

/*
find算法 查找元素
@param beg 容器开始迭代器
@param end 容器结束迭代器
@param value 查找的元素
@return 返回查找元素的位置

find_if算法 条件查找
@param beg 容器开始迭代器
@param end 容器结束迭代器
@param  callback 回调函数或者谓词(返回bool类型的函数对象)
@return bool 查找返回true 否则false

*/

void test01()
{
	vector<int>v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}
	vector<int>::iterator pos = find(v.begin(), v.end(), 5);
	if (pos != v.end())
	{
		cout << "找到了元素：" << *pos << endl;
	}
	else
	{
		cout << "未找到" << endl;
	}
}











int main()
{
	test01();
	system("pause");
	return 0;
}

