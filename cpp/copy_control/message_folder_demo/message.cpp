#include "message.h"
#include <iostream>

Message::Message(const Message& m)
	: contents_(m.contents_)
	, folders_(m.folders_)
{
	// ����Message������ӵ� ÿ��ָ��m��Folder�У�ʹ��Folder���������Message�����ָ��
	add_to_folders(m);
}

Message& Message::operator=(const Message& rhs)
{
	remove_from_folders();	// �������������folders��ɾ����Messageָ��
	contents_ = rhs.contents_;
	folders_ = rhs.folders_;
	add_to_folders(rhs);	// ����Message������ӵ�����rhs��Folder��
	return *this;
}

Message::~Message()
{
	remove_from_folders();
}

void Message::save(Folder& f)
{
	folders_.insert(&f); // ������Folder��ӵ�folders������
	f.add_msg(this);	 // ����Message��ӵ�f��messge������
}

void Message::remove(Folder& f)
{
	folders_.erase(&f);	// ������Folder��f��folders������ɾ��
	f.remove_msg(this);
}

void Message::print_debug()
{
	std::cout << contents_ << std::endl;
}

void Message::add_to_folders(const Message& m)
{
	// ��ÿ��ָ��m��ԭMessage���󣩵�Folder�� ���һ��ָ����Message�����ָ��
	for (auto f : m.folders_) {
		f->add_msg(this);	// ���Folder�������һ��ָ����Message��ָ��
	}
}

void Message::remove_from_folders()
{
	for (auto f : folders_) {
		f->remove_msg(this);	// �ӵ�ǰFolder��ɾ��Message����
	}
}

void swap(Message& lhs, Message& rhs)
{
	using std::swap;
	// ��ÿ����Ϣ��ָ��������ڵ�Folder��ɾ��
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
		m->add_folder(this);	// ��ÿ��Message�������ָ�����Folder�����ָ��
	}
}

void Folder::remove_from_messages()
{
	for (auto m : msgs_) {
		m->remove_folder(this);
	}
	msgs_.clear();	// �������Ԫ��
}

