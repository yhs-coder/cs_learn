#include <iostream>
#include <thread>

// ������дȫ�ֵ�std������������ͻ using namespace std;

/*

Ŀ¼��
	C++���Լ���Ķ��̱߳�� ==> ������Կ�ƽ̨ windows/linux
	- thread/mutex/condition_variable
	- lock_quard/unique_lock
	- atomic ԭ������ ����CAS������ԭ������ �̰߳�ȫ
	- sleep_for

	C++���Բ��� thread 
	ͨ�����������б������ʶ��ǰϵͳ���ڵײ����ٵ���ϵͳ�ṩ�ĺ�����
	�������ǵ��õ�ǰϵͳ�̵߳�API��ֻ�������Բ�������˷�װ
	windows -> createThread
	Linux	-> thread_create

*/

/*
�߳����ݣ�
1. ��������һ���߳�
std::thread ����һ���̶߳��󣬴����߳�����Ҫ���̺߳����Ͳ������߳��Զ�����

2. ���߳�ʲôʱ�����
> ���̺߳������н���ʱ���߳̾ͽ�����

3. ���߳��������ʱ��������ֵ�ǰ���̻���δ������ɵ����̣߳����̾ͻ��쳣��ֹ
||	
4. ���߳���δ������߳�
t.join()   :	�ȴ�t�߳̽�������ǰ�̲߳ż�����������	
t.detach() :	��t�߳�����Ϊ�����̣߳������߳��޹��ˣ������߳̽������������̽������������t�߳��Ƿ��������

3. �̷߳��� t.detach()

*/
void threadHandle(int num, int time)
{
	// �����߳�˯��time��
	std::this_thread::sleep_for(std::chrono::seconds(time));// this_thread sleep_for chrono �����ֿռ�
	std::cout << "hello thread" << num << std::endl;
}

#if 0
int main()
{
	// �����̶߳��󣬴���һ���̴߳�����,�߳̿�ʼ����
	std::thread t1(threadHandle, 1, 1);
	std::thread t2(threadHandle, 2, 2);
	// ���߳���ȴ����߳̽��������̲߳ż�������������
	t1.join();
	t2.join();
	// �����߳�����Ϊ�����߳�
	//t1.detach();
	// std::this_thread::sleep_for(std::chrono::seconds(5));

	std::cout << "main thread done!" << std::endl;

	return 0;
}
#endif
