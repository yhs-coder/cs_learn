#pragma once
// 定义删除的函数  =delete

struct NoCopy
{
	NoCopy() = default;	// 使用合成的默认构造函数
	NoCopy(const NoCopy&) = delete;	// 阻止拷贝
	NoCopy& operator = (const NoCopy&) = delete;	// 阻止赋值
	~NoCopy() = default; // 使用合成的析构函数
};

struct NoDtor
{
	NoDtor() = default;
	~NoDtor() = delete;	// 阻止析构，导致不能销毁NoDtor类型的对象
};
