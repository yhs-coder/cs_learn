#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

/*
	�����ü���������ָ��shared_ptr:

	- �����ü������������ָ����Թ���ͬһ����Դ�����������ü���������ָ��,��auto_ptr��unique_ptrֻ�ܹ���һ����Դ��

	- �����ü�������ÿһ��������Դƥ��һ�����ü���
		1. ����ָ�� => ������Դ => ���ü���+1
		2. ����ָ�� => ��ʹ����Դ��ʱ�� => ���ü���-1�������ü���Ϊ0����Ҫ����Դ�ͷţ�
*/

/* ģ��ʵ������ָ�� */

namespace hs
{
	// ����Դ�������ü�������
	template <typename T>
	class RefCnt
	{
	public:
		RefCnt(T* ptr = nullptr) :mptr(ptr)
		{
			if (mptr != nullptr)
				mcount = 1;
		}
		void addRef() { mcount++; } // ������Դ�����ü���

		int delRef() { return --mcount; }	//������Դ�����ü���

		int getCnt() { return mcount; }

	private:
		T* mptr;	// ����������Դ
		int mcount;	// ��Դ��Ӧ�����ü���
	};


	// ����ָ��  ��֤��������Դ���Զ��ͷ�
	// ����ջ�ϵĶ�����������Զ���������������������Դ���Զ��ͷ�
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
			mpRefCnt->addRef();	//���Ӷ���������Դ����Ӧ�����ü���+1
		}

		shared_ptr<T>& operator = (const shared_ptr<T>& src)
		{
			if (this == &src)	// ��ֹ���Ҹ�ֵ
				return *this;

			// �ö�����ʹ�ø���Դ����Ӧ�����ü���-1
			if (0 == (mpRefCnt->delRef()))
			{
				if (mptr != nullptr)
				{
					cout << "delete : " << endl;
					delete mptr;	// mcount==0 ʱ����ʾ�޶���������Դ����Ҫ�ͷ���Դ
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
		T* mptr;	//ָ����Դ��ָ��
		RefCnt<T>* mpRefCnt;	// ָ�����Դ���ü��������ָ��
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