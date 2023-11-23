#pragma once
#include <iostream>
using std::cout; 
using std::endl;

// 需求 通过一个通用排序函数  实现对char和int数组的排序
// ,排序顺序 从大到小， 算法  选择排序


template <typename T>
void swap_(T& a, T& b)
{
	T tmp = a;
	a = b;
	b = tmp;
}

template <typename T>
void bubble_sort(T arr[], int len)
{
	for (int i = 0; i < len; i++) {
#if 1
		// 升序
		for (int j = i + 1; j < len; j++) {
			if (arr[j] < arr[i]) {
				swap_(arr[j], arr[i]);
			}
		}
#else
		// 降序，从大到小
		for (int j = len - 1; j > i; j--) {
			if (arr[j] > arr[j - 1]) {
				swap_(arr[j], arr[j - 1]);
			}
		}
#endif
	}
}

// 模板打印函数
template <typename T>
void print_array(T arr[], int len)
{
	for (int i = 0; i < len; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}
