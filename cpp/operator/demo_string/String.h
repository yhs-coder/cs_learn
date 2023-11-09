#pragma once
#include <iostream>

class String
{
	//左移运算符友元
	friend std::ostream& operator<<(std::ostream& cout, String& str);
	//右移运算符 友元
	friend std::istream& operator>>(std::istream& cin, String& str);

	
public:
	String(): _p_string(nullptr), _size(){};
	String(char* str);
	String(const String& str);

	//重载=运算符
	String& operator=(const char* str);
	String& operator=(const String& str);

	//重载[]运算符
	char& operator[](int index);
	const char& operator[](int index) const;

	//重载+运算符
	String operator+(const char* str);
	String operator+(const String& str);

	//重载==运算符 
	bool operator==(const char* str);
	bool operator==(const String& str);

	~String();

private:
	char* _p_string; //维护在堆区开辟的字符数组
	int _size;  //字符串长度 不统计\0
};