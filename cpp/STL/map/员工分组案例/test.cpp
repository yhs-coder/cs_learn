#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <map>
#include <ctime>
#include <string>
using namespace std;

/*
//��˾��Ƹ��5��Ա����5��Ա�����빫˾֮����Ҫָ��Ա�����Ǹ����Ź���
1����Ա��Ϣ��: ���������ʵ����
2��ͨ��Multimap������Ϣ�Ĳ��� ���� ��ʾ
3���ֲ�����ʾԱ����Ϣ ��ʾȫ��Ա����Ϣ
*/

enum {
	CAIWU,
	RENLI,
	YANFA
};

class Worker
{
public:
	string m_name;
	int m_money;
};

void createWorker(vector<Worker>& v)
{
	string nameSeed = "ABCDE";
	for (int i = 0; i < 5; i++) {
		Worker worker;
		worker.m_name = "Ա��";
		worker.m_name += nameSeed[i];
		worker.m_money = rand() % 10000 + 10000; 
		v.push_back(worker);
	}

}

void showWorker(multimap<int, Worker>& m)
{
	cout << "������Ա����Ϣ���£�" << endl;
	multimap<int, Worker>::iterator pos = m.find(CAIWU);
	int num = m.count(CAIWU);
	int index = 0; 
	for (; pos != m.end() && index < num; pos++, index++) {
		cout << "������ " << pos->second.m_name << "  ���ʣ�" << pos->second.m_money << endl;
	}
	cout << "�з�����Ա����Ϣ���£�" << endl;
	pos = m.find(YANFA);
	num = m.count(YANFA);
	index = 0;
	for (; pos != m.end() && index < num; pos++, index++) {
		cout << "������ " << pos->second.m_name << "  ���ʣ�" << pos->second.m_money << endl;
	}

	cout << "��������Ա����Ϣ���£�" << endl;
	pos = m.find(RENLI);
	num = m.count(RENLI);
	index = 0;
	for (; pos != m.end() && index < num; pos++, index++) {
		cout << "������ " << pos->second.m_name << "  ���ʣ�" << pos->second.m_money << endl;
	}


}


void setGroup(vector<Worker>& v, multimap<int, Worker>& m)
{
	for (vector<Worker>::iterator it = v.begin(); it != v.end(); it++) {
		//����������ű�� 0 1 2
		int id = rand() % 3;
		m.insert(make_pair(id, *it));
	}
}


int main()
{
	srand((unsigned int)time(NULL));
	//1������5��Ա��
	vector<Worker>v;
	createWorker(v);
	
	//2��Ա������
	multimap<int, Worker>m;
	setGroup(v, m);

	//3���ֲ�����ʾԱ��
	showWorker(m);

	//����
	/*for (vector<Worker>::iterator it = v.begin(); it != v.end(); it++) {
		cout << "������ " << it->m_name << "  ���ʣ� " << it->m_money << endl;
	}*/
	system("pause");
	return 0;
}

