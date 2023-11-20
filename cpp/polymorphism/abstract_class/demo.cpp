#include <iostream>
using std::cout;
using std::endl;

//����������Ʒ
class AbstractDrinking
{
public:
	//��ˮ
	virtual void Boil() = 0;
	//����
	virtual void Brew() = 0;
	//���뱭��
	virtual void PourInCup() = 0;
	//���븨��
	virtual void PutSomething() = 0;
	//�涨����
	void MakeDrink() {
		Boil();
		Brew();
		PourInCup();
		PutSomething();
	}
};

//��������
class Coffee : public AbstractDrinking
{
public:
	//��ˮ
	virtual void Boil()
	{
		cout << "��ũ��ɽȪ��" << endl;
	}
	//����
	virtual void Brew()
	{
		cout << "���ݿ���" << endl;
	}
	//���뱭��
	virtual void PourInCup()
	{
		cout << "�����ȵ��뱭��!" << endl;
	}
	virtual void PutSomething()
	{
		cout << "����ţ��!" << endl;
	}
};

//������ˮ
class Tea : public AbstractDrinking {
public:
	//��ˮ
	virtual void Boil() {
		cout << "������ˮ!" << endl;
	}
	//����
	virtual void Brew() {
		cout << "���ݲ�Ҷ!" << endl;
	}
	//���뱭��
	virtual void PourInCup() {
		cout << "����ˮ���뱭��!" << endl;
	}
	//���븨��
	virtual void PutSomething() {
		cout << "����ʳ��!" << endl;
	}
};

//ҵ����
void DoBussiness(AbstractDrinking* drink)
{
	drink->MakeDrink();
	delete drink;
}

void test()
{
	DoBussiness(new Coffee);
	cout << "--------------------------" << endl;
	DoBussiness(new Tea);
}

int main()
{
	test();
	system("pause");
	return 0;
}