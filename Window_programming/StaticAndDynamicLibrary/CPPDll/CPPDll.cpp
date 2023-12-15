#if 0
// 使用声明导出 _declspec(dllexport)
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
// 模块定义文件
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