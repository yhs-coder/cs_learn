#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <map>
#include <ctime>
#include <string>
using namespace std;

/*
//公司招聘了5个员工，5名员工进入公司之后，需要指派员工在那个部门工作
1、人员信息有: 姓名、工资等组成
2、通过Multimap进行信息的插入 保存 显示
3、分部门显示员工信息 显示全部员工信息
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
		worker.m_name = "员工";
		worker.m_name += nameSeed[i];
		worker.m_money = rand() % 10000 + 10000; 
		v.push_back(worker);
	}

}

void showWorker(multimap<int, Worker>& m)
{
	cout << "财务部门员工信息如下：" << endl;
	multimap<int, Worker>::iterator pos = m.find(CAIWU);
	int num = m.count(CAIWU);
	int index = 0; 
	for (; pos != m.end() && index < num; pos++, index++) {
		cout << "姓名： " << pos->second.m_name << "  工资：" << pos->second.m_money << endl;
	}
	cout << "研发部门员工信息如下：" << endl;
	pos = m.find(YANFA);
	num = m.count(YANFA);
	index = 0;
	for (; pos != m.end() && index < num; pos++, index++) {
		cout << "姓名： " << pos->second.m_name << "  工资：" << pos->second.m_money << endl;
	}

	cout << "人力部门员工信息如下：" << endl;
	pos = m.find(RENLI);
	num = m.count(RENLI);
	index = 0;
	for (; pos != m.end() && index < num; pos++, index++) {
		cout << "姓名： " << pos->second.m_name << "  工资：" << pos->second.m_money << endl;
	}


}


void setGroup(vector<Worker>& v, multimap<int, Worker>& m)
{
	for (vector<Worker>::iterator it = v.begin(); it != v.end(); it++) {
		//随机产生部门编号 0 1 2
		int id = rand() % 3;
		m.insert(make_pair(id, *it));
	}
}


int main()
{
	srand((unsigned int)time(NULL));
	//1、创建5名员工
	vector<Worker>v;
	createWorker(v);
	
	//2、员工分组
	multimap<int, Worker>m;
	setGroup(v, m);

	//3、分部门显示员工
	showWorker(m);

	//测试
	/*for (vector<Worker>::iterator it = v.begin(); it != v.end(); it++) {
		cout << "姓名： " << it->m_name << "  工资： " << it->m_money << endl;
	}*/
	system("pause");
	return 0;
}

