#include <iostream>
#include <string>
using std::cout;
using std::endl;

/********************************************************
	ģ���ػ��������������ͣ��������⻯��ʵ�ַ�ʽ

	ģ���ػ���
		1.����ģ���ػ�
		2. ��ģ���ػ�
			2.1 ȫ�ػ�
			2.2 ƫ�ػ�
********************************************************/


/********************************************************
	����ģ���ػ����裺
	1. ���ȱ���Ҫ��һ�������ĺ���ģ��
	2. �ؼ���template�����һ�Կյļ�����<>
	3. �ں���ģ�������<>,����<>��ָ����Ҫ�ػ�������
	4. �����βα���ͺ���ģ��<>���ػ�������һ�£�����ͬ�ı༭�����ܻᱨ��
*********************************************************/

// �����ĺ���ģ��
template <typename T>
bool is_equal(T x, T y)
{
	return x == y;
}

// ����ģ���ػ� --> ���char*���ͽ������⴦��
template<>
bool is_equal<char*>(char* x, char* y)
{
	return strcmp(x, y) == 0;
}

# if 0
// ����
int main()
{
	cout << is_equal(1, 1) << endl;
	cout << is_equal(1.1, 1.2) << endl;
	char a1[] = "hello";
	char a2[] = "hello";
	cout << is_equal(a1, a2) << endl; // ���ȵ����ػ��ĺ���ģ��
}
#endif 

class Person
{
public:
	Person(std::string name, int age)
		: name_(name)
		, age_(age){}
	std::string name_;
	int age_;
};

template <class T>
bool compare(T& a, T& b)
{
	if (a == b) {
		return true;
	}
	return false;
}


// ģ����������Ϊ�Զ������������ṩ����ģ��
// ��template<>��ͷ����ͨ��������ָ�����ͣ������������ڳ���ģ��
template<>
bool compare<Person>(Person& a, Person& b)
{
	return a.name_ == b.name_ && a.age_ == b.age_;
}

#if 0
int main()
{
	int a = 10;
	int b = 20;
	bool ret = compare(a, b);
	if (ret) {
		cout << "a == b" << endl;
	}
	else {
		cout << "a != b" << endl;
	}

	// ģ�庯���޷��Ƚ������ͻ�ṹ�����ͣ���������
	// ��ʱ��ҪΪ��Щ�ض��������ṩ���廯��ģ�塣Ҳ����ģ��������
	Person p1("tom", 100);
	//Person p2("tom", 100);
	Person p2("tom", 1200);
	ret = compare(p1, p2);
	if (ret) {
		cout << "a == b" << endl;
	}
	else {
		cout << "a != b" << endl;
	}
	
	return 0;
}
#endif

/********************************************************
	��ģ����ػ���
		1. ȫ�ػ�����ģ������б������еĲ�����ȷ������
		2. ƫ�ػ������ػ��������ģ�������һ����������������Ƶ��ػ��汾��
			2.1 �����ػ� ����ģ������б��еĲ��ֲ�������ȷ����
			2.2 ��������һ�������ƣ�����ָ����T1��T2Ϊĳ������ʱ ��(T1*,T2*)��ʹ�����⻯����ģ��.
			���ģ�������һ����������������Ƴ�����һ���ػ��汾��
	
	��ģ���ػ����裺
	1. ���ȱ���Ҫ��һ����������ģ��
	2. �ؼ���template�����һ�Կյļ�����<>������ʾģ����ػ���
	3. ����ģ�������<>,����<>��ָ����Ҫ�ػ�������

*********************************************************/

// 1. ȫ�ػ�
template <class T1, class T2>
class Yang
{
public:
	Yang() {
		cout << "Yang<T1, T2>" << endl;
	}
private:
	T1 y1_;
	T2 y2_;
};

template <>
class Yang<int, double>
{
public:
	Yang() {
		cout << "Yang<int, double>" << endl;
	}
private:
	int y1_;
	double y2_;
};

#if 0
// ����
int main()
{
	Yang<double, double> y1;
	Yang<int, double> y2;
	return 0;
}
#endif

// ƫ�ػ�
// �����ػ�
template <class T2>
class Yang<int, T2>
{
public:
	Yang() {
		cout << "Yang<int, T2>" << endl;
	}
private:
	int y1_;
	T2 y2_;
};

#if 0
int main()
{
	Yang<int, int> y1;
	Yang<double, int> y2;
	return 0;
}
#endif


// ��������ƫ�ػ�Ϊָ������
template <class T1, class T2>
class Yang<T1*, T2*>
{
public:
	Yang() {
		cout << "Yang<T1*, T2*>" << endl;
		cout << typeid(T1).name() << endl;
		cout << typeid(T2).name() << endl;
	}
private:
	T1 y1_;
	T2 y2_;
};


// ��������ƫ�ػ�Ϊ��������
template <class T1, class T2>
class Yang<T1&, T2&>
{
public:
	Yang() {
		cout << "Yang<T1&, T2&>" << endl;
		cout << typeid(T1).name() << endl;
		cout << typeid(T2).name() << endl;
	}
private:
	T1 y1_;
	T2 y2_;
};

int main()
{
	Yang<int, int> y1;
	Yang<int*, int*> y2;
	Yang<int&, int&> y3;
	return 0;
}


