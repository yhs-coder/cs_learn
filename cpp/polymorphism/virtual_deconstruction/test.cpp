#include<iostream>
using std::cout;
using std::endl;

class People
{
public:
	People() {
		cout << "���캯�� People!" << endl;
	}
	virtual void show_name() = 0;
	
	//������������Ҫ������Ҳ��Ҫʵ��
	//���һ�������˴���������������ô����Ҳ���ڳ�����
	// virtual ~People() = 0;
#if 0
	// ʹ��һ�������������
	// �������ָ��ָ����������ʱ������������ж�̬������ڴ棬��ʱ���ٻ�ָ��ʱ��������������������
	// ����ڴ�й©
	~People() {
		cout << "�������� People..." << endl;
	}
#else
	// �����������ָ����������ԣ���ôҪ��������������, ��delete��ʱ�򣬻�����������������
	virtual ~People()
	{
		cout << "���������� People..." << endl;
	}
#endif
	int num_ = 10;
};

#if 0
People::~People()
{
	cout << "������������ People!" << endl;
}
#endif

class Worker : public People
{
public:
	Worker() {
		cout << "���캯�� Worker!" << endl;
		pname_ = new char[10];
	}

	virtual void show_name() {
		cout << "Worker::show_name..." << endl;
	}

	~Worker() {
		if (pname_ != NULL) {
			delete[] pname_;
		}
		cout << "�������� Worker..." << endl;
	}
private:
	char* pname_ = nullptr;
};

void test()
{
	People* people = new Worker;
	//people->~People();
	delete people;
}

int main()
{
	test();
	system("pause");
	return 0;
}
