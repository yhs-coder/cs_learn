#pragma once
#include <iostream>
#include <cstring>

class Person
{
	// ������������ << 
	friend std::ostream& operator << (std::ostream& os, const Person& p);
// ������ Ĭ�ϸ�һ����4������   Ĭ�Ϲ���   ����   �������� ��ֵ������  operator= (ֵ����)
public:
	Person(char* name, int age) {
		_name = new char[strlen(name) + 1];
		strcpy(_name, name);
		_age = age;
	}

	// ��ֵ���� =, ���
	Person& operator= (const Person& p) {
		// ���ж�ԭ�������ͷ������ݣ���������ͷ�
		if (_name != nullptr) {
			delete[] _name;
			_name = nullptr;
		}
		_name = new char[strlen(p._name) + 1];
		strcpy(_name, p._name);
		_age = p._age;
		return *this;
	}

	// ��������, ���
	Person(const Person& p) {
		_name = new char[strlen(p._name) + 1];
		strcpy(_name, p._name);
		_age = p._age;
	}

	//��ϵ������� == ���������
	bool operator == (const Person& p) {
		return _age == p._age && strcmp(_name, p._name);
	}

	bool operator != (const Person& p) {
		return !(*this == p);
	}

	~Person()
	{
		if (_name != nullptr)
		{
			std::cout << "_name���ͷ��ڴ�..." << std::endl;
			delete[] _name;
			_name = nullptr;
		}
	}

	char* _name;
	int _age;
};



