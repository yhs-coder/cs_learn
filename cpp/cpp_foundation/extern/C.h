#ifdef __cplusplus
//#ifdef ��Ԥ����ָ���Ԥ����׶������ã������ж��Ƿ�����ĳ���ꡣ
//__cplusplus �� C++ �����ú꣬����������� C++ �������±��룬�ú걻����Ϊһ������ֵ��
extern "C" {
#endif

	/*
	��ˣ�������������У���һ�� #ifdef __cplusplus �жϵ��Ǵ�����뻷���ǲ��� C++��
	����� C++�� ����� extern "C" �ķ�ʽ������ show() ������������
	�ڶ��� #ifdef __cplusplus ��Ȼ�жϵ��Ǵ�����뻷���ǲ��� C++��
	����ǣ��� C++ ��ص�ͷ�ļ��ʹ�������� extern "C"�У��Ա���ʹ�� C++ ��������ԡ�
	*/
#include<stdio.h>
	void show();

#ifdef __cplusplus
}
#endif

