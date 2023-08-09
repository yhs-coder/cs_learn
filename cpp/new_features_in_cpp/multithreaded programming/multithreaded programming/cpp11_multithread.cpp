#include <iostream>
#include <thread>

// 尽量少写全局的std，避免命名冲突 using namespace std;

/*

目录：
	C++语言级别的多线程编程 ==> 代码可以跨平台 windows/linux
	- thread/mutex/condition_variable
	- lock_quard/unique_lock
	- atomic 原子类型 基于CAS操作的原子类型 线程安全
	- sleep_for

	C++语言层面 thread 
	通过编译器进行编译后，来识别当前系统，在底层上再调用系统提供的函数。
	本质上是调用当前系统线程的API，只是在语言层面进行了封装
	windows -> createThread
	Linux	-> thread_create

*/

/*
线程内容：
1. 创建启动一个线程
std::thread 定义一个线程对象，传入线程所需要的线程函数和参数，线程自动开启

2. 子线程什么时候结束
> 子线程函数运行结束时，线程就结束了

3. 主线程运行完成时，如果发现当前进程还有未运行完成的子线程，进程就会异常终止
||	
4. 主线程如何处理子线程
t.join()   :	等待t线程结束，当前线程才继续往下运行	
t.detach() :	将t线程设置为分离线程（与主线程无关了），主线程结束后，整个进程结束，无需关心t线程是否运行完成

3. 线程分离 t.detach()

*/
void threadHandle(int num, int time)
{
	// 让子线程睡眠time秒
	std::this_thread::sleep_for(std::chrono::seconds(time));// this_thread sleep_for chrono 是名字空间
	std::cout << "hello thread" << num << std::endl;
}

#if 0
int main()
{
	// 定义线程对象，传入一个线程处理函数,线程开始运行
	std::thread t1(threadHandle, 1, 1);
	std::thread t2(threadHandle, 2, 2);
	// 主线程需等待子线程结束，主线程才继续往往下运行
	t1.join();
	t2.join();
	// 把子线程设置为分离线程
	//t1.detach();
	// std::this_thread::sleep_for(std::chrono::seconds(5));

	std::cout << "main thread done!" << std::endl;

	return 0;
}
#endif
