#include<iostream>
using namespace std;
#include "C.h"
//#include "C.h" ����extern����C����ʱ����ע�͵�ͷ�ļ�
//���߱�����  show������C���Է�ʽ ������

extern int i = 2;
extern "C" {
	// ����C���Ժ���
	void show();
}
void test1() {
	show(); //����extern "C" void show(); ��error����Ϊ��C++���к������ػ����κ�������
	//����show��c�����ļ����������ʧ��

}
// ʹ��file.cpp�е�ȫ�ֱ���
// ��Ҫʹ��extern�����ñ������ڱ���ʱ����������Ϊ global_var ����һ�����ű�����ڸ��ļ��½���һ���Ը÷��ŵ����á�

extern int global_var;

int main() {
	test1();
	cout << "file.cpp: global_var = " << global_var << endl;
	
	system("pause");
	return 0;
}


