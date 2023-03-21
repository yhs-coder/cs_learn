#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <stdexcept> //  std 标准  except 异常

class Person
{
public:
	Person(int age)
	{
		if (age < 0 || age > 150)
		{
			//throw out_of_range("年龄必须在 0 - 150之间！");
			throw length_error("年龄长度必须在 0 - 150之间！");
		}
		else
		{
			m_Age = age;
		}

	}
	int m_Age;
};


void test01()
{
	try
	{
		Person p(151);
	}
	
	//catch (exception &e) 也可以用基类的exception来接收
	//catch ( out_of_range &e)
	catch (exception& e)
	{
		cout << e.what() << endl;
	}

}

int main(){
	test01();
	system("pause");
	return EXIT_SUCCESS;
}





