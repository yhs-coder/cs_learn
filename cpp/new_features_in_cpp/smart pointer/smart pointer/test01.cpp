#include <iostream>
#include <memory>
using namespace std;

/* 智能指针基本知识 */

// 智能指针  保证能做到资源的自动释放
// 利用栈上的对象出作用域自动析构的特征，来做到资源的自动释放
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
	* 不带引用计数的智能指针
		1. auto_ptr:C++库里原有
		C++11新标准：
		2. scoped_ptr
		直接禁用拷贝构造和拷贝赋值
		scoped_ptr(const scoped_ptr<T>&) = delete;
		 scoped_ptr<T>& operator = (const scoped_ptr<T>&) = delete;

		// 推荐使用，带有右值引用
		3. unique_ptr
		unique_ptr(const unique_ptr<T>&) = delete;
		unique_ptr<T>& operator = (const unique_ptr<T>&) = delete;
		unique_ptr(unique_ptr<T> &&src)
		unique_ptr<T>& operator =(unique_ptr<T> &&src) 

		举例;
		template<typename T>
		unique_ptr<T> getSmartPtr()
		{
			unique_ptr<int> ptr(new T());
			return ptr;
		}
		unique_ptr<T> ptr1 = getSmartPtr<int>();	   //临时对象拷贝构造，调用右值引用拷贝构造！
		
	*/

	 // 有意让多个对象管理同一资源，有浅拷贝的问题，使用深拷贝又不能达到目的
	//CSmartPtr<int> p1(new int);
	//CSmartPtr<int> p2(p1);	// 浅拷贝问题，导致p1,p2指向同一块内存，该内存被释放了两次 程序崩溃。通过深拷贝解决

	// 如何解决浅拷贝问题
	unique_ptr<int> p1(new int);
	unique_ptr<int> p2(std::move(p1));	// 使用move得到当前变量的右值类型


	// 使用auto_ptr 资源管理权转移 , 不推荐使用auto_ptr，除非场景十分简单！
	//auto_ptr<int> ptr1(new int);
	//auto_ptr<int> ptr2(ptr1);
	//*ptr2 = 20;
	//cout << *ptr1 << endl; // error,使用auto_ptr进行拷贝构造时，会将ptr1的资源转移给ptr2,此时ptr1被置空，无权再访问该资源
}
#endif

# if 0 
// 测试自定义的智能指针
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
		可以把智能指针定义在堆上吗？
		CSmartPtr<int> *p = new CSmartPtr(new int);
		不行，因为还得先释放堆，跟裸指针无异
		delete p;
	*/

}
#endif

#if 0
int main()
{
	// 一般指针需要手动开辟、手动释放内存
	int* p = new int(10);
	*p = 30;

	/*
		可能有些逻辑直接返回，导致释放内存的代码没运行到！
		if(xxx)
			return -1;
	*/
	delete p;
	return 0;
}
#endif 