#pragma once
// ����ɾ���ĺ���  =delete

struct NoCopy
{
	NoCopy() = default;	// ʹ�úϳɵ�Ĭ�Ϲ��캯��
	NoCopy(const NoCopy&) = delete;	// ��ֹ����
	NoCopy& operator = (const NoCopy&) = delete;	// ��ֹ��ֵ
	~NoCopy() = default; // ʹ�úϳɵ���������
};

struct NoDtor
{
	NoDtor() = default;
	~NoDtor() = delete;	// ��ֹ���������²�������NoDtor���͵Ķ���
};
