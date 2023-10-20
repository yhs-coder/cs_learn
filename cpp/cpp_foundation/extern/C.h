#ifdef __cplusplus
//#ifdef 是预处理指令，在预编译阶段起作用，用于判断是否定义了某个宏。
//__cplusplus 是 C++ 的内置宏，如果代码是在 C++ 编译器下编译，该宏被定义为一个非零值。
extern "C" {
#endif

	/*
	因此，在上面的例子中，第一个 #ifdef __cplusplus 判断的是代码编译环境是不是 C++；
	如果是 C++， 则采用 extern "C" 的方式来修饰 show() 函数的声明；
	第二个 #ifdef __cplusplus 仍然判断的是代码编译环境是不是 C++，
	如果是，则将 C++ 相关的头文件和代码包含到 extern "C"中，以便于使用 C++ 的相关特性。
	*/
#include<stdio.h>
	void show();

#ifdef __cplusplus
}
#endif

