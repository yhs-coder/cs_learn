#pragma once
#include <string>
#include <set>
class Folder;

class Message
{
	friend class Folder;
	friend void swap(Message&, Message&);
	friend void swap(Folder&, Folder&);

public:
	// folders_�����ڳ�ʼֵ����ʼ��Ϊ�ռ���
	explicit Message(const std::string& str = "")
		: contents_(str) {}

	Message(const Message&);

	Message& operator = (const Message&);
	~Message();

	// ��Message ���/ɾ���ڸ���Folder��
	void save(Folder&);
	void remove(Folder&);
	void print_debug();		// ��ӡcontents����
private:
	std::string contents_;			// ʵ����Ϣ�ı�
	std::set<Folder*> folders_{};	// ָ�� ��Message����Folder��ָ�� �ļ��ϣ�����Message���󷢸�����ЩFolder����

	// �������캯�����������������������������Ҫ�õ��Ĺ��ߺ����������Ƿ�װ��private
	void add_to_folders(const Message&);	 // �ѱ�Message��ӵ�folder��
	void remove_from_folders();				 // ��folders�����У�ÿ��Folder��ɾ����Message

	void add_folder(Folder* f) {
		folders_.insert(f);
	}

	void remove_folder(Folder* f) {
		folders_.erase(f);
	}
};

// void swap(Message&, Message&);

class Folder
{
	friend class Message;
	friend void swap(Message&, Message&);
	friend void swap(Folder&, Folder&);

public:
	Folder() = default;
	Folder(const Folder&);
	Folder& operator = (const Folder&);
	~Folder();
	void print_debug();

private:
	std::set<Message*> msgs_;			// ��ǰFolderָ��Message�����ָ�뼯�ϣ����洢����ЩMessage����
	void add_to_message(const Folder&);	// ��Folder�����Message
	void remove_to_message();			// ��Folder��ɾ��Message

	void add_msg(Message* m) { msgs_.insert(m); }
	void remove_msg(Message* m) { msgs_.erase(m); }
};

// void swap(Folder&, Folder&);