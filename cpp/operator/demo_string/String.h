#pragma once
#include <iostream>

class String
{
	//�����������Ԫ
	friend std::ostream& operator<<(std::ostream& cout, String& str);
	//��������� ��Ԫ
	friend std::istream& operator>>(std::istream& cin, String& str);

	
public:
	String(): _p_string(nullptr), _size(){};
	String(char* str);
	String(const String& str);

	//����=�����
	String& operator=(const char* str);
	String& operator=(const String& str);

	//����[]�����
	char& operator[](int index);
	const char& operator[](int index) const;

	//����+�����
	String operator+(const char* str);
	String operator+(const String& str);

	//����==����� 
	bool operator==(const char* str);
	bool operator==(const String& str);

	~String();

private:
	char* _p_string; //ά���ڶ������ٵ��ַ�����
	int _size;  //�ַ������� ��ͳ��\0
};