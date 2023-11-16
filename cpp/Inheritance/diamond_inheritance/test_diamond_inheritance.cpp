#include <iostream>
using std::cout;
using std::endl;

//������
class Animal
{
public:
	Animal() : age_(1000) {}
	void func() {
		cout << "Animal::func" << endl;
	}
	int age_; // ����
};

#if 1
// ��̳�
class Sheep : virtual public Animal {};
class Tuo : virtual public Animal {};
#else
// ��ͨ�̳�
class Sheep :  public Animal {};
class Tuo :  public Animal {};
#endif

//����
class SheepTuo : public Sheep, public Tuo {};

// ���μ̳в���������
void test01()
{
	SheepTuo st;
	// 1. ���ò���������,��֪�������ĸ������Ա
	//st.age_ = 10; 
	st.Sheep::age_ = 10;
	st.Tuo::age_ = 20;
	cout << "Sheep::age_ = " << st.Sheep::age_ << endl;
	cout << "Tuo::age_ = " << st.Tuo::age_ << endl;
	//2. �ظ��̳�,�˷��ڴ�
	cout << "SheepTuo size:" << sizeof(SheepTuo) << endl; //8 �ظ��̳���age_��Ա

}

// ʹ��������
void test02()
{
	cout << "SheepTuo size:" << sizeof(SheepTuo) << endl; //8 
	SheepTuo st;
	st.func();
	cout << st.age_ << endl;

}


// ̽����̳е�ʵ��ԭ��
void test03()
{
	// ʹ����̳к�ÿ����Ĵ�С
	// ʹ����̳к󣬱��������Զ�������������vbptr (virtual base pointer)������ָ�룬��ָ�����
	// ע�⣺ ƽ̨��64λ��������ָ���СΪ8�ֽ�
	cout << "Sheep size: " << sizeof(Sheep) << endl;			// �ڴ����[��8 + 4��] = 16 
	cout << "Tuo size: " << sizeof(Tuo) << endl;				// 16
	cout << "SheepTuo size: " << sizeof(SheepTuo) << endl;		// �ڴ����[�����������ָ�� + 4] = 24

	SheepTuo st;
	st.age_ = 10;
	// ����������๲����������ĳ�Ա��������һ��
	cout << "Sheep::age_ = " << st.Sheep::age_ << " , &Sheep::age_ = "  << &st.Sheep::age_ << endl;
	cout << "Tuo::age_ = " << st.Tuo::age_ << " , &Tuo::age_ = " << &st.Tuo::age_ << endl;
	cout << "Animal::age_ = " << st.Animal::age_ << " , &Animal::age_ = " << &st.Animal::age_ << endl;

	cout << "---------------------------------------------------------------------------------------" << endl;

	/*
		��������̳к�sheep��tuo���� �̳���һ�� vbptrָ��,�������ָ�룬��ָ�����һ��������vbtable
		�������м�¼�˸��������������׵�ַ��ƫ���� ��ͨ��ƫ���� �����ҵ�Ψһ��һ��age_
	*/

	/* 
		̽��ԭ��ͨ����ָ��������ʻ���������ĳ�Ա
		��VS������Ա����ߣ� cd ��ת��Ŀ���ļ�·��
		���� cl /d1 reportSingleClassLayout����  �ļ��� ���۲����ļ̳�ģ��
	 */

	/* 
		ͨ��Sheep�ҵ� �������е�ƫ����
		1. *(int *)&st �����õ��� �������У�һ��ʼ�� 0λ��
	 
		SheepTuo::$vbtable@Sheep@:
		0 | 0
		1 | 8 (SheepTuod(Sheep + 0)Animal)

	 2.  (int*) *(int*)&(st) + 1  ����������һλ�� 1 */

	/*
		��32λϵͳ�ϣ�size_t���ܱ�����Ϊunsigned int��Ҳ����32λ�޷������ͣ�
		����64λϵͳ�ϣ�����ܱ�����Ϊunsigned long����64λ�޷������Ρ�
		size_t����ҪĿ����Ϊ���ṩһ�ֿ���ֲ�ķ�����������ϵͳ�п�Ѱַ���ڴ�����һ�µĳ��ȡ�
	*/
	// ͨ��Sheepƫ����
	size_t sheep_offset = *((size_t*)*(size_t*)&st + 1);
	size_t tuo_offset = *((size_t*)*((size_t*)&st + 1) + 1);
	cout << "Sheep offset = " << *((int*)*(int*)&st + 1) << endl;   // 8
	cout << "Sheep offset = " << sheep_offset << endl; // 8
	
	// ͨ��Tuo�ҵ�ƫ����
	cout << "Tuo offset = " << tuo_offset << endl;	  // 4

	// ͨ��Sheep��Tuo��������ƫ����������������е�age_��Ա�ͳ�Ա����
	cout << "age_ = " << *((int*)((char*)&st + sheep_offset)) << endl; // 10
	cout << "age_ = " << ((Animal*)((char*)&st + sheep_offset))->age_ << endl; // 10
	cout << "use func()" << endl; 

	((Animal*)((char*)&st + sheep_offset))->func();

	((Animal*)((char*)&st + tuo_offset))->func();


	//cout << *((int*)*(int*)&st + 1) << endl;
	//cout << *(  ( int*)        *(int*)&st + 1) << endl;
	//cout << "(size_t*)&st  " << (size_t*)&st << endl;
	//cout << "(size_t*)&st + 1 " << (size_t*)&st + 1 << endl;

}


void test04()
{
	cout << "sizeof(Sheep) = " << sizeof(Sheep) << endl;
	cout << "sizeof(Tuo) = " << sizeof(Tuo) << endl;
}

int main() {

	//test01();
	//test02();
	test03();
	//test04();

	system("pause");
	return EXIT_SUCCESS;
}