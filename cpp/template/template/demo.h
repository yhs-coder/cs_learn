#pragma once
#include <iostream>
using std::cout; 
using std::endl;

// ���� ͨ��һ��ͨ��������  ʵ�ֶ�char��int���������
// ,����˳�� �Ӵ�С�� �㷨  ѡ������


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
		// ����
		for (int j = i + 1; j < len; j++) {
			if (arr[j] < arr[i]) {
				swap_(arr[j], arr[i]);
			}
		}
#else
		// ���򣬴Ӵ�С
		for (int j = len - 1; j > i; j--) {
			if (arr[j] > arr[j - 1]) {
				swap_(arr[j], arr[j - 1]);
			}
		}
#endif
	}
}

// ģ���ӡ����
template <typename T>
void print_array(T arr[], int len)
{
	for (int i = 0; i < len; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}
