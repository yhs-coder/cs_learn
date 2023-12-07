#include <Windows.h>
#include <stdio.h>


// char*字符串
void C_char()
{
	const char* pszText = "hello char";
	int len = strlen(pszText);
	int size = sizeof(pszText);
	printf("%s %d %d\n", pszText, len, size);
}

// 宽字节字符串
void W_char()
{
	const wchar_t* pszText = L"hello wchar";
	int len = wcslen(pszText); //  11 求的是字符串长度，即字符的个数，而不是占据多少个字节
	int size = sizeof(pszText);
	wprintf(L"%s %d %d\n", pszText, len, size);
}

void test_tchar()
{
	// 如果没有定义unicode编码方式，__TEXT为char，否则为wchar_t
	// #define __TEXT(quote) L##quote // 将传入的quote替换到后面的L##quote
	const TCHAR* pszText = __TEXT("hello txt"); // char* pszText
	// 打印
#ifdef UNICODE
	wprintf(L"%s\n", pszText);
#else
	printf("单%s\n", pszText);
#endif
}

void PrintUnicode()
{
	const wchar_t* pszText = L"你好";
	// wprintf打印unicode字符（汉字）时会乱码
	wprintf(L"%s\n", pszText);
	
	// 拿到标准输出句柄
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
