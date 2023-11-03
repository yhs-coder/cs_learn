#pragma once
/******************************************* 
	静态成员实现单例模式
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
		cout << "单例构造函数调用" << endl;
	}
};
Singleton* Singleton::_s_single = new Singleton;