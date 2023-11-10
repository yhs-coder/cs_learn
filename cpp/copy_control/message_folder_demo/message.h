#pragma once
#include <string>
#include <set>

class Folder
{
	friend class Message;
	friend void swap(Message&, Message&);
	friend void swap(Folder&, Folder&);

private:
	std::set<Message*> msgs_;	// ��ǰFolder������ָ��Message��ָ�뼯��
	void add_to_message(const Folder&);	// ��Folder�����Message
	void remove_to_message();			// ��Folder��ɾ��Message
	
	void add_msg(Message* m) { msgs_.insert(m); }
	void remove_msg(Message* m) { msgs_.erase(m); }
};


class Message
{
	friend class Folder;
	friend void swap(Message&, Message&);
	friend void swap(Folder&, Folder&);

public:
	// folderʹ�����ڳ�ʼֵ����ʼ��Ϊ�ռ���
	explicit Message(const std::string& str = "")
		: contents_(str) {}

	Message(const Message&);

	Message& operator = (const Message&);
	~Message();

	// ��Message ���/ɾ���ڸ���Folder��
	void save(Folder&);
	void remove(Folder&);
private:
	std::string contents_;			// ʵ����Ϣ�ı�
	std::set<Folder*> folders_ {};	// ָ�� ��Message����Folder��ָ�� �ļ���

	// �������캯�����������������������������Ҫ�õ��Ĺ��ߺ����������Ƿ�װ��private
	void add_to_folders(const Message&);	 // �ѱ�Message��ӵ�folder��
	void remove_from_folders();				 // ��folders�����У�ÿ��Folder��ɾ����Message;

};

void swap(Message&, Message&);