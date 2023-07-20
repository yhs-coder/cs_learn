#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <memory>
#include <functional>
using namespace std;

/*
	智能指针的删除器：deltor
	智能指针：能够保证资源绝对的释放 ,默认是delete ptr;
*/

// ~unique_ptr() 是一个函数对象的调用！ deletor(ptr)
/*template <typename T>
class Deletor
{
public:
	void poerator()(T* ptr)
	{
		delete ptr;
	}
};*/


/* 库里unique_ptr的定义
template <class _Ty, class _Dx = default_delete<_Ty>>
class unique_ptr;
*/

template <typename T>
class MyDeletor
{
public:
	void operator()(T* ptr) const
	{
		cout << "call MyDeletor.operator()" << endl;
		delete[] ptr;
	}
};

template <typename T>
class MyFileDeletor
{
public:
	void operator()(T* ptr) const
	{
		cout << "call MyFileDeletor.operator()" << endl;
		fclose(ptr);
	}
};


int main()
{
	/*unique_ptr<int, MyDeletor<int>> ptr1(new int[100]);	// delete []ptr;
	unique_ptr<FILE,MyFileDeletor<FILE>> ptr2(fopen("data.txt","w"));	// delete []ptr;
	*/

	// 使用lambda表达式 ==> 函数对象 确定lambda表达式的类型，使用function
	unique_ptr<int, function<void(int*)>> ptr1(new int[100],[](int*p) {
			cout << "call MyDeletor.operator()" << endl;
			delete[]p;
		});

	unique_ptr<FILE, function<void(FILE*)>> ptr2(fopen("data.txt", "w"), [](FILE* p) {
			cout << "call MyFileDeletor.operator()" << endl;
			fclose(p);
		});

	return 0;
}