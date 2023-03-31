#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
using namespace std;


/*
1��string ���캯��
string();//����һ���յ��ַ��� ����: string str;      
string(const string& str);//ʹ��һ��string�����ʼ����һ��string����
string(const char* s);//ʹ���ַ���s��ʼ��
string(int n, char c);//ʹ��n���ַ�c��ʼ�� 

*/
void test01()
{
	string str;
	string str2(str);
	string str3 = "abc";
	string str4(10, 'a');
	cout << "str3 = " << str3 << endl;
	cout << "str4 = " << str4 << endl;
}


/*
2�� string������ֵ����
string& operator=(const char* s);//char*�����ַ��� ��ֵ����ǰ���ַ���
string& operator=(const string &s);//���ַ���s������ǰ���ַ���
string& operator=(char c);//�ַ���ֵ����ǰ���ַ���
string& assign(const char *s);//���ַ���s������ǰ���ַ���
string& assign(const char *s, int n);//���ַ���s��ǰn���ַ�������ǰ���ַ���
string& assign(const string &s);//���ַ���s������ǰ�ַ���
string& assign(int n, char c);//��n���ַ�c������ǰ�ַ���
string& assign(const string &s, int start, int n);//��s��start��ʼn���ַ���ֵ���ַ���
*/

void test02()
{
	string str;
	str = "abc";
	
	str.assign("hello",3);
	cout << str << endl;

	string str2;
	str2.assign(str);
	cout << str2 << endl;

	//string& assign(const string & s, int start, int n);
	str2.assign(str, 0, 2);
	cout << str2 << endl;
}

/*
3�� string��ȡ�ַ�����
char& operator[](int n);//ͨ��[]��ʽȡ�ַ�
char& at(int n);//ͨ��at������ȡ�ַ�
*/

void test03()
{
	string str = "hello world!";
	//for (int i = 0; i < str.size(); i++)
	//{
	//	//cout << str[i] << endl;
	//	cout << str.at(i) << endl;
	//}

	//!!! []��at������
	//		[]����Խ�磬ֱ�ӹҵ�
	//		at����Խ�磬�׳�out_of_range�쳣
	try
	{
		//cout << str[100] << endl;
		cout << str.at(100) << endl;
	}
	catch (out_of_range& e)
	{
		cout << e.what() << endl;
	}
	catch (...)
	{
		cout << "�쳣����" << endl;
	}
}


/*
4�� stringƴ�Ӳ���
string& operator+=(const string& str);//����+=������
string& operator+=(const char* str);//����+=������
string& operator+=(const char c);//����+=������
string& append(const char *s);//���ַ���s���ӵ���ǰ�ַ�����β
string& append(const char *s, int n);//���ַ���s��ǰn���ַ����ӵ���ǰ�ַ�����β
string& append(const string &s);//ͬoperator+=()
string& append(const string &s, int pos, int n);//���ַ���s�д�pos��ʼ��n���ַ����ӵ���ǰ�ַ�����β
string& append(int n, char c);//�ڵ�ǰ�ַ�����β���n���ַ�c

*/

void test04()
{
	//ƴ��
	string str1 = "I ";
	string str2 = "love China";
	str1 += str2;
	cout << str1 << endl;

	str1.append("! engaga");
	str1.append("! engaga",5);
	cout << str1 << endl;
}

/*
5��string���Һ��滻
int find(const string& str, int pos = 0) const; //����str��һ�γ���λ��,��pos��ʼ����
int find(const char* s, int pos = 0) const;  //����s��һ�γ���λ��,��pos��ʼ����
int find(const char* s, int pos, int n) const;  //��posλ�ò���s��ǰn���ַ���һ��λ��
int find(const char c, int pos = 0) const;  //�����ַ�c��һ�γ���λ��
int rfind(const string& str, int pos = npos) const;//����str���һ��λ��,��pos��ʼ����
int rfind(const char* s, int pos = npos) const;//����s���һ�γ���λ��,��pos��ʼ����
int rfind(const char* s, int pos, int n) const;//��pos����s��ǰn���ַ����һ��λ��
int rfind(const char c, int pos = 0) const; //�����ַ�c���һ�γ���λ��

string& replace(int pos, int n, const string& str); //�滻��pos��ʼn���ַ�Ϊ�ַ���str
string& replace(int pos, int n, const char* s); //�滻��pos��ʼ��n���ַ�Ϊ�ַ���s
*/

void test05()
{
	//����
	string str = "abcdeghde";
	int pos = str.find("de");
	//rfind �Ǵ����������
	//int pos = str.rfind("de");
	if (pos == -1)
	{
		cout << "δ�ҵ��ַ���" << endl;
	}
	else
	{
		cout << "�ҵ����ַ�����λ��Ϊ�� " << pos << endl;
	}

	//�滻
	str.replace(0, 2, "dddd");
	//ddddabcdeghde; posλ�ú��n�ַ��滻���ַ������ӷ������Ա�n��
	cout << str << endl;
}

/*
6�� string�Ƚϲ���
compare������>ʱ���� 1��<ʱ���� -1��==ʱ���� 0��
�Ƚ����ִ�Сд���Ƚ�ʱ�ο��ֵ�˳����Խǰ���ԽС��
��д��A��Сд��aС��

int compare(const string &s) const;//���ַ���s�Ƚ�
int compare(const char *s) const;//���ַ���s�Ƚ�
*/

void test06()
{
	string str1 = "abdce";
	string str2 = "abdce";
	if (str1.compare(str2) == 0)
	{
		cout << "str1 == str2" << endl;
	}
	else if (str1.compare(str2) > 0)
	{
		cout << "str1 > str2" << endl;
	}
	else
	{
		cout << "str1 < str2" << endl;
	}
}


/*
7�� string�Ӵ�
string substr(int pos = 0, int n = npos) const;//������pos��ʼ��n���ַ���ɵ��ַ���
*/

void test07()
{
	//�Ӵ�
	/*string str = "abcdef";
	string subStr = str.substr(0, 3);
	cout << subStr << endl;*/

	//��ȡ�����û���
	string email = "hello@qq.com";
	int pos = email.find("@");
	string usreName = email.substr(0, pos);
	cout << "username = " << usreName << endl;
}

//�����ַ���,ȡ��ÿ���ַ���
void test08()
{
	string str  = "www.itcast.com.cn";
	vector<string> v;
	int start = 0;
	int pos = -1;
	cout << "��ȡ�ַ���" << endl;
	while (true)
	{
		string tempStr;
		//ÿ�β��ң�����posλ�ã���
		pos = str.find(".",start);
		if (pos == -1)
		{
			//��cnȡ��
			tempStr = str.substr(start, str.size() - start);
			v.push_back(tempStr);
			break;
		}
		tempStr = str.substr(start, pos-start);
		v.push_back(tempStr);
		start = pos + 1;
	}

	for (vector<string>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << endl;
	}
}


/*
8��string�����ɾ������
string& insert(int pos, const char* s); //�����ַ���
string& insert(int pos, const string& str); //�����ַ���
string& insert(int pos, int n, char c);//��ָ��λ�ò���n���ַ�c
string& erase(int pos, int n = npos);//ɾ����Pos��ʼ��n���ַ�
*/

void test09()
{

	string str = "hello";
	str.insert(1, "111");
	//h111ello 
	cout << str << endl;
	//ɾ�� 
	str.erase(1, 3);
	cout << str << endl;
}

void doWork(string str)
{

}

void doWork2(const char* str)
{

}

//9�� string��c-style�ַ���ת��
void test10()
{
	const char* str = "abcd";

	//const char * תΪ string
	string s(str);

	//string תΪ const char *
	const char* str2 = s.c_str();

	//const char * ������ʽ����ת��Ϊ  string
	doWork(str2);
	//string ��������ʽ����ת��Ϊ  const char* 
	//doWork2(s);
}

void test11()
{
	string s = "abcdefg";
	char& a = s[2];
	char& b = s[3];

	a = '1';
	b = '2';

	//cout << s << endl;
	//cout << (int*)s.c_str() << endl;

	s = "pppppppppppppppppppppppp";

	a = '1';
	b = '2';

	cout << s << endl;
	cout << (int*)s.c_str() << endl;

}

/*
дһ�������������ڲ���string�ַ����е�����Сд��ĸ����Ϊ��д��ĸ��
*/
void test12()
{
	string str = "abcdEFg";

	for (int i = 0; i < str.size(); i++)
	{
		//str[i] = toupper(str[i]);
		str[i] = tolower(str[i]);
	}

	cout << str << endl;
}



int main()
{
	//test01();
	//test02();
	//test03();
	//test04();
	//test05();
	//test06();
	//test07();
	//test08();
	//test09();
	//test11();
	test12();
	system("pause");
	return 0;
}

