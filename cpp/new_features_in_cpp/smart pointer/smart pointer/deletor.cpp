#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <memory>
#include <functional>
using namespace std;

/*
	����ָ���ɾ������deltor
	����ָ�룺�ܹ���֤��Դ���Ե��ͷ� ,Ĭ����delete ptr;
*/

// ~unique_ptr() ��һ����������ĵ��ã� deletor(ptr)
/*template <typename T>
class Deletor
{
public:
	void poerator()(T* ptr)
	{
		delete ptr;
	}
};*/


/* ����unique_ptr�Ķ���
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

	// ʹ��lambda���ʽ ==> �������� ȷ��lambda���ʽ�����ͣ�ʹ��function
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