#include <Windows.h>
#include <stdio.h>


// char*�ַ���
void C_char()
{
	const char* pszText = "hello char";
	int len = strlen(pszText);
	int size = sizeof(pszText);
	printf("%s %d %d\n", pszText, len, size);
}

// ���ֽ��ַ���
void W_char()
{
	const wchar_t* pszText = L"hello wchar";
	int len = wcslen(pszText); //  11 ������ַ������ȣ����ַ��ĸ�����������ռ�ݶ��ٸ��ֽ�
	int size = sizeof(pszText);
	wprintf(L"%s %d %d\n", pszText, len, size);
}

void test_tchar()
{
	// ���û�ж���unicode���뷽ʽ��__TEXTΪchar������Ϊwchar_t
	// #define __TEXT(quote) L##quote // �������quote�滻�������L##quote
	const TCHAR* pszText = __TEXT("hello txt"); // char* pszText
	// ��ӡ
#ifdef UNICODE
	wprintf(L"%s\n", pszText);
#else
	printf("��%s\n", pszText);
#endif
}

void PrintUnicode()
{
	const wchar_t* pszText = L"���";
	// wprintf��ӡunicode�ַ������֣�ʱ������
	wprintf(L"%s\n", pszText);
	
	// �õ���׼������
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	WriteConsole(hOut, pszText, wcslen(pszText), NULL,NULL);
}

int main()
{
	// C_char();
	W_char();
	//test_tchar();
	PrintUnicode();
	return 0;
}
