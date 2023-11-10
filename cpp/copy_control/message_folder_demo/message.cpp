#include "message.h"


Message::Message(const Message& m)
	: contents_(m.contents_)
	, folders_(m.folders_)
{
	// ����Message������ӵ� ָ��m��Folder��
	add_to_folders(m);
}

Message& Message::operator=(const Message& rhs)
{
	remove_from_folders();	// �������������folders��ɾ����Messageָ��
	contents_ = rhs.contents_;
	folders_ = rhs.folders_;
	add_to_folders(rhs);	// ����Message������ӵ�rhs��Folder��
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

void Message::add_to_folders(const Message& m)
{
	// ��ÿ��ָ��ԭMessage��Folder�����һ��ָ����Message��ָ��
	for (auto f : m.folders_) {
		f->add_msg(this);	// ���Folder�������һ��ָ����Message��ָ��
	}
}

void Message::remove_from_folders()
{
	for (auto f : folders_) {
		f->remove_msg(this);	// �ӵ�ǰFolder��ɾ����Message
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
}
