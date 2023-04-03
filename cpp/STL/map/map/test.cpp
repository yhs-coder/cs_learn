#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <map>
using namespace std;

/*
1�� map���캯��
map<T1, T2> mapTT;//mapĬ�Ϲ��캯��,T1Ϊ����T2Ϊʵֵ
map(const map &mp);//�������캯��

2�� map��ֵ����
map& operator=(const map &mp);//���صȺŲ�����
swap(mp);//����������������

3�� map��С����
size();//����������Ԫ�ص���Ŀ
empty();//�ж������Ƿ�Ϊ��

4�� map��������Ԫ�ز���
map.insert(...); //����������Ԫ�أ�����pair<iterator,bool>
map<int, string> mapStu;
// ��һ�� ͨ��pair�ķ�ʽ�������
mapStu.insert(pair<int, string>(3, "С��"));
// �ڶ��� ͨ��pair�ķ�ʽ�������
mapStu.inset(make_pair(-1, "У��"));
// ������ ͨ��value_type�ķ�ʽ�������
mapStu.insert(map<int, string>::value_type(1, "С��"));
// ������ ͨ������ķ�ʽ����ֵ
mapStu[3] = "С��";
mapStu[5] = "С��";
*/

void test01()
{
	map<int, int>m;

	//��һ�ֲ��뷽ʽ
	m.insert(pair<int, int>(1, 10));

	//�ڶ��ַ�ʽ ���Ƽ�
	m.insert(make_pair(2, 20));

	//�����ֲ��뷽ʽ
	m.insert(map<int, int>::value_type(3, 30));

	//�����֣���̫�Ƽ�
	m[4] = 40;

	//cout << m[5] << endl; //���ʹ��δָ����key��������keyΪָ����ֵ��valueΪ0�����ݲ��뵽map��

	for (map<int, int>::iterator it = m.begin(); it != m.end(); it++)
	{
		cout << "key = " << it->first << "  value = " << it->second << endl;
	}
}

/*
5�� mapɾ������
clear();//ɾ������Ԫ��
erase(pos);//ɾ��pos��������ָ��Ԫ�أ�������һ��Ԫ�صĵ�������
erase(beg,end);//ɾ������[beg,end)������Ԫ�� ��������һ��Ԫ�صĵ�������
erase(keyElem);//ɾ��������keyΪkeyElem�Ķ��顣
*/

void test02()
{
	map<int, int>m;
	m.insert(pair<int, int>(1, 10));
	m.insert(make_pair(2, 20));
	m.insert(map<int, int>::value_type(3, 30));
	m[4] = 40;

	m.erase(3); //ɾ�������keyֵ

	for (map<int, int>::iterator it = m.begin(); it != m.end(); it++)
	{
		cout << "key = " << it->first << " value = " << it->second << endl;
	}
}

/*
6�� map���Ҳ���
find(key);//���Ҽ�key�Ƿ����,�����ڣ����ظü���Ԫ�صĵ�������/�������ڣ�����map.end();
count(keyElem);//����������keyΪkeyElem�Ķ����������map��˵��Ҫô��0��Ҫô��1����multimap��˵��ֵ���ܴ���1��
lower_bound(keyElem);//���ص�һ��key>=keyElemԪ�صĵ�������
upper_bound(keyElem);//���ص�һ��key>keyElemԪ�صĵ�������
equal_range(keyElem);//����������key��keyElem��ȵ������޵�������������
*/

void test03()
{
	map<int, int> m;
	m.insert(pair<int, int>(1, 10));
	m.insert(make_pair(2, 20));
	m.insert(map<int, int>::value_type(3, 30));
	m[4] = 40;
	map<int, int>::iterator ret = m.find(30);
	if (ret != m.end())
	{
		cout << "�ҵ���keyΪ: " << ret->first << "  value Ϊ�� " << ret->second << endl;
	}
	else
	{
		cout << "δ�ҵ�..." << endl;
	}

	//ͳ�� count
	int num = m.count(4);
	cout << "keyΪ4�Ķ������Ϊ�� " << num << endl;

	//lower_bound(keyElem);//���ص�һ��key>=keyElemԪ�صĵ�������
	map<int, int>::iterator pos = m.lower_bound(3);
	if (pos != m.end())
	{
		cout << "�ҵ���lower_bound key: " << pos->first << " value: " << pos->second << endl;
	}
	else
	{
		cout << "δ�ҵ�..." << endl;
	}
	//upper_bound(keyElem);//���ص�һ��key>keyElemԪ�صĵ�������
	
	pos = m.upper_bound(3);
	if (pos != m.end())
	{
		cout << "�ҵ���upper_bound key: " << pos->first << " value: " << pos->second << endl;
	}
	else
	{
		cout << "δ�ҵ�..." << endl;
	}
	//equal_range(keyElem);//����������key��keyElem��ȵ������޵�������������
	pair < map<int, int>::iterator, map<int, int>::iterator> res = m.equal_range(3);
	if (res.first != m.end())
	{
		cout << "�ҵ���equal_range�е� lower_bound�� key =  " << res.first->first << " value = " << res.first->second << endl;
	}
	else
	{
		cout << "δ�ҵ�" << endl;
	}

	if (res.second != m.end())
	{
		cout << "�ҵ���equal_range�е� upper_bound�� key =  " << res.second->first << " value = " << res.second->second << endl;
	}
	else
	{
		cout << "δ�ҵ�" << endl;
	}
}

class myCompareInt
{
public:
	bool operator()(int v1, int v2) const
	{
		return v1 > v2;
	}
};

void test04()
{
	map<int, int, myCompareInt>m;
	m.insert(pair<int, int>(1, 10));
	m.insert(make_pair(2, 20));
	m.insert(map<int, int>::value_type(3, 30));
	m[4] = 40;
	for (map<int, int, myCompareInt>::iterator it = m.begin(); it != m.end(); it++)
	{
		cout << "key = " << it->first << " value = " << it->second << endl;
	}
}

int main()
{
	//test01();
	//test02();
	//test03();
	test04();
	system("pause");
	return 0;
}

