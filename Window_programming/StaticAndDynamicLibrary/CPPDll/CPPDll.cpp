#if 0
// ʹ���������� _declspec(dllexport)
_declspec(dllexport) int cppdll_add(int a, int b)
{
	return a + b;
}

_declspec(dllexport)  int cppdll_sub(int a, int b)
{
	return a - b;
}

_declspec(dllexport)  int cppdll_mul(int a, int b)
{
	return a * b;
}

_declspec(dllexport)  int cppdll_div(int a, int b)
{
	return a / b;
}

#else
// ģ�鶨���ļ�
int cppdll_add(int a, int b)
{
	return a + b;
}

int cppdll_sub(int a, int b)
{
	return a - b;
}

int cppdll_mul(int a, int b)
{
	return a * b;
}

int cppdll_div(int a, int b)
{
	return a / b;
}

#endif