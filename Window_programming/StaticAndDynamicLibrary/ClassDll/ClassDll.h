#ifndef _CLASSDLL_H
#define _CLASSDLL_H

// �����������ʹ�ö�̬���а������ͷ�ļ�
// ʹ����������ָ���л���ĵ�����������

#ifdef DLLCLASS
#define EXT_CLASS _declspec(dllexport)
#else
#define EXT_CLASS _declspec(dllimport)
#endif 

class EXT_CLASS Math {
public:
	int Add(int a, int b);
	int Sub(int a, int b);
};

#endif