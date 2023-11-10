#pragma once
#include <string>
#include <set>

class Folder
{
	friend class Message;
	friend void swap(Message&, Message&);
	friend void swap(Folder&, Folder&);

private:
	std::set<Message*> msgs_;	// 当前Folder包含的指向Message的指针集合
	void add_to_message(const Folder&);	// 在Folder中添加Message
	void remove_to_message();			// 在Folder中删除Message
	
	void add_msg(Message* m) { msgs_.insert(m); }
	void remove_msg(Message* m) { msgs_.erase(m); }
};


class Message
{
	friend class Folder;
	friend void swap(Message&, Message&);
	friend void swap(Folder&, Folder&);

public:
	// folder使用类内初始值，初始化为空集合
	explicit Message(const std::string& str = "")
		: contents_(str) {}

	Message(const Message&);

	Message& operator = (const Message&);
	~Message();

	// 本Message 添加/删除在给定Folder中
	void save(Folder&);
	void remove(Folder&);
private:
	std::string contents_;			// 实际消息文本
	std::set<Folder*> folders_ {};	// 指向 本Message所在Folder的指针 的集合

	// 拷贝构造函数、拷贝复制运算符和析构函数需要用到的工具函数，在它们封装在private
	void add_to_folders(const Message&);	 // 把本Message添加到folder中
	void remove_from_folders();				 // 从folders集合中，每个Folder中删除本Message;

};

void swap(Message&, Message&);