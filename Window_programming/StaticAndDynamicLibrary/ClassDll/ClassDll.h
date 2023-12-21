#ifndef _CLASSDLL_H
#define _CLASSDLL_H

// 如果其他人想使用动态库中包含类的头文件
// 使用条件编译指令切换类的导出导出定义

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