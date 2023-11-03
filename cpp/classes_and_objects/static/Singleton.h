#pragma once
/******************************************* 
	��̬��Աʵ�ֵ���ģʽ
*******************************************/

#include <iostream>
#include <string>
using std::cout;
using std::endl;

class Singleton {
public:
	static Singleton* get_instance() {
		return _s_single;
	}
	void print(std::string text) {
		cout << text << endl;
		_count++;
	}
	int _count;
private:
	static Singleton* _s_single;
    Singleton(const Singleton&){}
	Singleton() : _count(0) {
		cout << "�������캯������" << endl;
	}
};
Singleton* Singleton::_s_single = new Singleton;