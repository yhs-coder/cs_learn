#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using std::cout;
using std::endl;

class Animal
{
public:
#if 1
	virtual void speak()
	{
		cout << "������˵��..." << endl;
	}

	virtual void eat() {
		cout << "�����ڽ�ʳ..." << endl;
	}
	
#else
	void speak() {
		cout << "������˵��" << endl;
	}
	void eat() {
		cout << "�����ڽ�ʳ..." << endl;
	}

#endif

};

class Cat : public Animal
{
public:
	void speak() {
		cout << "Сè��˵��" << endl;
	}

	void eat() {
		cout << "Сè��è��..." << endl;
	}

};


class Dog : public Animal
{
public:
	void speak() {
		cout << "С����˵��" << endl;
	}

	void eat() {
		cout << "С���Թ���..." << endl;
	}
};

void do_speak(Animal& animal)
{
	// ������������ת��Ϊ�������ͣ���󶼵��õ���Animal�е�speak,ʹ���麯���󣬿ɵ��ô�������speak
	animal.speak();
}

// �����麯��
void test1()
{
	Cat cat;
	do_speak(cat);

	Dog dog;
	do_speak(dog);

}




class A {
public:
	virtual void func1() {}
	virtual void func2() {}
};

//B��Ϊ�գ���ô��СӦ����1�ֽڣ�ʵ�������������
class B : public A {};

void test2() {
	// ʹ���麯���󣬻�����������ڱ���ʱ���Զ����һ���麯��ָ�룬ָ�������麯����
	cout << "A size:" << sizeof(A) << endl;	// 8
	cout << "B size:" << sizeof(B) << endl;	// 8
}




/* ̽���麯����ʵ��ԭ�� ������ʹ���麯�����е�ƫ���������麯��
*/
void test3()
{
	cout << "sizeof Animal = " << sizeof(Animal) << endl;
	cout << "sizeof Cat = " << sizeof(Cat) << endl;

	Animal* animal = new Cat;
	//animal->speak();

	/*
		32λ���л�����4�ֽ�
		((void(*)()) (*(int *)*(int*)animal)) ();
	*/

	/*
		������л�����64λ����ÿ��ָ��Ĵ�С��8�ֽڣ����������ڲ���
		�麯����ָ��ÿ���ƶ��Ĵ�С����8�ֽڣ�������Ҳ�����һ���ĵ�ַ
	*/


	/*
		1. *(size_t*)animal   ==> ����Cat��vfptrָ����ָ��vftable���麯����)
		2. * (size_t*)*(size_t*)animal) ==> �����õõ��麯���ĵ�ַ
		3. ת���ɺ���ָ�룬���ú�����ַ��ָ��ĺ���
	*/


	// �ǵý�ƽ̨����x8ƽ̨����Ϊ�����߹������е�Ҳ��x86
	// ����Cat::speak()�� Cat::eat()
	cout << "-----------------------------" << endl;
	((void(*)()) (*(size_t*)*(size_t*)animal)) ();
	((void(*)()) (  *((size_t*)*(size_t*)animal + 1) )  ) ();

	//ʹ��typedef���Ͷ����
	typedef void(*FUNPOINT)();

	//__stdcall ������ָ�� C ��������Լ����һ�ֹؼ��֣������߱������ں�������ʱʹ�� stdcall ����Լ����
	//  FUNPOINT ��һ��ָ���޲�������������ָ�����ͣ���������������һ�����Ͳ�����Ϊ���������롣
	//�ڵ��øú���ָ��ʱ�����Խ��κ�����ֵ���ݸ�����ֻҪ�������������뺯��������ָ���Ĳ�������ƥ�伴��
	//typedef void( __stdcall *FUNPOINT)(int);

	//((void(*)()) (*((size_t*)*(size_t*)animal + 1)))();
	(FUNPOINT(*((size_t*)*(size_t*)animal + 1)))    ();
	FUNPOINT(*((size_t*)*(size_t*)animal + 1))();
	
	//C/C++Ĭ�ϵ��ù���  __cdecl
	//�����е���ʱ�� ��ʵ���ù���  �� __stdcall
}


int main()
{
	//test1();
	//test2();
	test3();
	system("pause");
	return 0;
}