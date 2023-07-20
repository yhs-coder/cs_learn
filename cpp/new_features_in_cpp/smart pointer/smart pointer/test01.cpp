#include <iostream>
#include <memory>
using namespace std;

/* ����ָ�����֪ʶ */

// ����ָ��  ��֤��������Դ���Զ��ͷ�
// ����ջ�ϵĶ�����������Զ���������������������Դ���Զ��ͷ�
template <typename T>
class CSmartPtr
{
public:
	CSmartPtr(T* ptr = nullptr) :mptr(ptr) {}
	~CSmartPtr() { delete mptr; }
	CSmartPtr(const CSmartPtr<T>& ptr)
	{
		mptr = new T(*ptr.mptr);
	}
	

	T& operator*() { return *mptr; }
	T* operator->() { return mptr; }
private:
	T* mptr;
};

#if 0
int main()
{
	/*
	* �������ü���������ָ��
		1. auto_ptr:C++����ԭ��
		C++11�±�׼��
		2. scoped_ptr
		ֱ�ӽ��ÿ�������Ϳ�����ֵ
		scoped_ptr(const scoped_ptr<T>&) = delete;
		 scoped_ptr<T>& operator = (const scoped_ptr<T>&) = delete;

		// �Ƽ�ʹ�ã�������ֵ����
		3. unique_ptr
		unique_ptr(const unique_ptr<T>&) = delete;
		unique_ptr<T>& operator = (const unique_ptr<T>&) = delete;
		unique_ptr(unique_ptr<T> &&src)
		unique_ptr<T>& operator =(unique_ptr<T> &&src) 

		����;
		template<typename T>
		unique_ptr<T> getSmartPtr()
		{
			unique_ptr<int> ptr(new T());
			return ptr;
		}
		unique_ptr<T> ptr1 = getSmartPtr<int>();	   //��ʱ���󿽱����죬������ֵ���ÿ������죡
		
	*/

	 // �����ö���������ͬһ��Դ����ǳ���������⣬ʹ������ֲ��ܴﵽĿ��
	//CSmartPtr<int> p1(new int);
	//CSmartPtr<int> p2(p1);	// ǳ�������⣬����p1,p2ָ��ͬһ���ڴ棬���ڴ汻�ͷ������� ���������ͨ��������

	// ��ν��ǳ��������
	unique_ptr<int> p1(new int);
	unique_ptr<int> p2(std::move(p1));	// ʹ��move�õ���ǰ��������ֵ����


	// ʹ��auto_ptr ��Դ����Ȩת�� , ���Ƽ�ʹ��auto_ptr�����ǳ���ʮ�ּ򵥣�
	//auto_ptr<int> ptr1(new int);
	//auto_ptr<int> ptr2(ptr1);
	//*ptr2 = 20;
	//cout << *ptr1 << endl; // error,ʹ��auto_ptr���п�������ʱ���Ὣptr1����Դת�Ƹ�ptr2,��ʱptr1���ÿգ���Ȩ�ٷ��ʸ���Դ
}
#endif

# if 0 
// �����Զ��������ָ��
int main()
{
	CSmartPtr<int> ptr1(new int);
	// int *p = new int; *p p->
	*ptr1 = 20;

	class Test
	{
	public:
		void test()
		{
			cout << "call Test::test" << endl;
		}
	};

	CSmartPtr<Test> ptr2(new Test());
	// (ptr2.operator->()) -> test();
	ptr2->test();

	/*
		���԰�����ָ�붨���ڶ�����
		CSmartPtr<int> *p = new CSmartPtr(new int);
		���У���Ϊ�������ͷŶѣ�����ָ������
		delete p;
	*/

}
#endif

#if 0
int main()
{
	// һ��ָ����Ҫ�ֶ����١��ֶ��ͷ��ڴ�
	int* p = new int(10);
	*p = 30;

	/*
		������Щ�߼�ֱ�ӷ��أ������ͷ��ڴ�Ĵ���û���е���
		if(xxx)
			return -1;
	*/
	delete p;
	return 0;
}
#endif 