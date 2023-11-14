#include "message.h"
#include <iostream>

Message::Message(const Message& m)
	: contents_(m.contents_)
	, folders_(m.folders_)
{
	// 将新Message对象添加到 每个指向m的Folder中，使得Folder存有这个新Message对象的指针
	add_to_folders(m);
}

Message& Message::operator=(const Message& rhs)
{
	remove_from_folders();	// 从左侧运算对象的folders中删除此Message指针
	contents_ = rhs.contents_;
	folders_ = rhs.folders_;
	add_to_folders(rhs);	// 将该Message对象添加到存有rhs的Folder中
	return *this;
}

Message::~Message()
{
	remove_from_folders();
}

void Message::save(Folder& f)
{
	folders_.insert(&f); // 将给定Folder添加到folders集合中
	f.add_msg(this);	 // 将本Message添加到f的messge集合中
}

void Message::remove(Folder& f)
{
	folders_.erase(&f);	// 将给定Folder从f的folders集合中删除
	f.remove_msg(this);
}

void Message::print_debug()
{
	std::cout << contents_ << std::endl;
}

void Message::add_to_folders(const Message& m)
{
	// 在每个指向m（原Message对象）的Folder中 添加一个指向新Message对象的指针
	for (auto f : m.folders_) {
		f->add_msg(this);	// 向该Folder对象添加一个指向新Message的指针
	}
}

void Message::remove_from_folders()
{
	for (auto f : folders_) {
		f->remove_msg(this);	// 从当前Folder中删除Message对象
	}
}

void swap(Message& lhs, Message& rhs)
{
	using std::swap;
	// 将每个消息的指针从它所在的Folder中删除
	for (auto f : lhs.folders_) {
		f->remove_msg(&lhs);
	}
	for (auto f : rhs.folders_) {
		f->remove_msg(&rhs);
	}

	swap(lhs.folders_, rhs.folders_);
	swap(lhs.contents_, rhs.contents_);

	for (auto f : lhs.folders_) {
		f->add_msg(&lhs);
	}

	for (auto f : rhs.folders_) {
		f->add_msg(&rhs);
	}

}

void swap(Folder& lhs, Folder& rhs)
{
	using std::swap;
	for (auto m : lhs.msgs_) {
		m->remove_folder(&lhs);
	}
	for (auto m : rhs.msgs_) {
		m->remove_folder(&rhs);
	}

	swap(lhs.msgs_, rhs.msgs_);

	for (auto m : lhs.msgs_) {
		m->add_folder(&lhs);
	}
	for (auto m : rhs.msgs_) {
		m->add_folder(&rhs);
	}
}

Folder::Folder(const Folder& f) : msgs_(f.msgs_)
{
	add_to_messages(f);
}

Folder& Folder::operator=(const Folder& rhs)
{
	remove_from_messages();
	msgs_ = rhs.msgs_;
	add_to_messages(rhs);
	return *this;
}

Folder::~Folder()
{
	remove_from_messages();
}

void Folder::print_debug()
{
	for (auto m : msgs_) {
		std::cout << m->contents_ << " ";
	}
	std::cout << std::endl;
}

void Folder::add_to_messages(const Folder& f)
{
	for (auto m : f.msgs_) {
		m->add_folder(this);	// 让每个Message对象存有指向这个Folder对象的指针
	}
}

void Folder::remove_from_messages()
{
	for (auto m : msgs_) {
		m->remove_folder(this);
	}
	msgs_.clear();	// 清空所有元素
}

