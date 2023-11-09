#include "String.h"
#include <cstring>


std::ostream& operator<<(std::ostream& cout, String& str)
{
	cout << str._p_string << std::endl;
	return cout;
}

std::istream& operator>>(std::istream& cin, String& str)
{
	//先清空原来堆区数据
	if (str._p_string != nullptr)
	{
		delete[] str._p_string;
		str._p_string = nullptr;
	}
	char buf[1024]; //开辟临时数组，记录用户输入内容
	cin >> buf;
	str._p_string = new char[strlen(buf) + 1];
	strcpy(str._p_string, buf);
	str._size = strlen(buf);
	return cin;
}

String::String(char* str)
{
	_p_string = new char[strlen(str) + 1];
	strcpy(_p_string, str);
	_size = strlen(str);
}

String::String(const String& str)
{
	_p_string = new char[strlen(str._p_string) + 1];
	strcpy(_p_string, str._p_string);
	_size = str._size;
}

String& String::operator=(const char* str)
{
	// 深拷贝
	if (_p_string != nullptr) {
		delete[] _p_string;
		_p_string = nullptr;
	}
	_p_string = new char[strlen(str) + 1];
	strcpy(_p_string, str);
	_size = strlen(str);
	return *this;
}

String& String::operator=(const String& str)
{

	if (_p_string) {
		delete[] _p_string;
		_p_string = nullptr;
	}
	
	_p_string = new char[str._size + 1];
	strcpy(_p_string, str._p_string);
	_size = str._size;
	return *this;
}

char& String::operator[](int index)
{
	return _p_string[index];
}

const char& String::operator[](int index) const
{
	return _p_string[index];
}

String String::operator+(const char* str)
{
	int new_size = strlen(this->_p_string) + strlen(str);
	char* arr = new char[new_size+ 1];
	memset(arr, 0, new_size);	
	strcat(arr, _p_string);
	strcat(arr, str);
	String temp = arr;
	delete[] arr;
	return temp;
}

String String::operator+(const String& str)
{
	int new_size = strlen(this->_p_string) + strlen(str._p_string);
	char* arr = new char[new_size + 1];
	memset(arr, 0, new_size);
	strcat(arr, _p_string);
	strcat(arr, str._p_string);
	String temp = arr;
	delete[] arr;
	return temp;
}

bool String::operator==(const char* str)
{
	if (strcmp(_p_string, str) == 0) {
		return true;
	}
	return false;
}

bool String::operator==(const String& str)
{
	if (strcmp(_p_string, str._p_string) == 0) {
		return true;
	}
	return false;
}

String::~String()
{
	if (_p_string != nullptr) {
		delete[] _p_string;
		_p_string = nullptr;
	}
}



