#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

/*
	带引用计数的智能指针shared_ptr:

	- 带引用计数：多个智能指针可以管理同一个资源，而不带引用计数的智能指针,如auto_ptr、unique_ptr只能管理一个资源！

	- 带引用计数：给每一个对象资源匹配一个引用计数
		1. 智能指针 => 管理资源 => 引用计数+1
		2. 智能指针 => 不使用资源的时候 => 引用计数-1，当引用计数为0，需要把资源释放！
*/

/* 模拟实现智能指针 */

namespace hs
{
	// 对资源进行引用计数的类
	template <typename T>
	class RefCnt
	{
	public:
		RefCnt(T* ptr = nullptr) :mptr(ptr)
		{
			if (mptr != nullptr)
				mcount = 1;
		}
		void addRef() { mcount++; } // 增加资源的引用计数

		int delRef() { return --mcount; }	//减少资源的引用计数

		int getCnt() { return mcount; }

	private:
		T* mptr;	// 对象管理的资源
		int mcount;	// 资源对应的引用计数
	};


	// 智能指针  保证能做到资源的自动释放
	// 利用栈上的对象出作用域自动析构的特征，来做到资源的自动释放
	template <typename T>
	class shared_ptr
	{
	public:
		shared_ptr(T* ptr = nullptr) :mptr(ptr)
		{
			mpRefCnt = new RefCnt<T>(mptr);
		}

		~shared_ptr()
		{
			// cout << "use_count : " << use_count() << endl;
			if (0 == mpRefCnt->delRef())
			{
				if (mptr != nullptr)
				{
					cout << "delete ~ " << endl;
					delete mptr;
					mptr = nullptr;
				}
				delete mpRefCnt;
				mpRefCnt = nullptr;
			}
		}

		shared_ptr(const shared_ptr<T>& src) :mptr(src.mptr), mpRefCnt(src.mpRefCnt)
		{
			mpRefCnt->addRef();	//增加对象管理该资源，对应的引用计数+1
		}

		shared_ptr<T>& operator = (const shared_ptr<T>& src)
		{
			if (this == &src)	// 防止自我赋值
				return *this;

			// 该对象不再使用该资源，对应的引用计数-1
			if (0 == (mpRefCnt->delRef()))
			{
				if (mptr != nullptr)
				{
					cout << "delete : " << endl;
					delete mptr;	// mcount==0 时，表示无对象管理该资源，需要释放资源
					mptr = nullptr;
				}
			}
			mptr = src.mptr;
			mpRefCnt = src.mpRefCnt;
			mpRefCnt->addRef();
			return *this;
		}

		T& operator*() { return *mptr; }
		T* operator->() { return mptr; }

		int use_count()
		{
			return mpRefCnt->getCnt();
		}
	private:
		T* mptr;	//指向资源的指针
		RefCnt<T>* mpRefCnt;	// 指向该资源引用计数对象的指针
	};
}

void test()
{
	hs::shared_ptr<int> ptr1(new int);
	hs::shared_ptr<int> ptr2(ptr1);
	cout << "use_count : " << ptr2.use_count() << endl;
	hs::shared_ptr<int> ptr3;
	ptr3 = ptr2;
	*ptr1 = 20;
	cout << *ptr2 << " " << *ptr3 << endl;
	cout << "use_count : " << ptr2.use_count() << endl;
}

#if 0
int main()
{
	test();
	return 0;
}
#endif