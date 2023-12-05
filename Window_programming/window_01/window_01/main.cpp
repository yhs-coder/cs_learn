#include <windows.h>
/*
	创建一个窗口程序

*/

// 2. 窗口处理函数（自定义，处理消息）
LRESULT CALLBACK WndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM IParam) {
	return DefWindowProc(hWnd, msgID, wParam, IParam);
}

// 1.定义WinMain入口函数
int CALLBACK WinMain(HINSTANCE hIns, HINSTANCE hPerIns, LPSTR IpCmdLine, int nCmdShow) {

	// 3. 注册窗口类 （向系统内核写入数据）
	WNDCLASS wc = { 0 };
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hCursor = NULL;
	wc.hIcon = NULL;
	wc.hInstance = hIns;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = "Main";
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);	// 将以上所有赋值全部写入操作系统

	// 4. 在内存创建窗口 (内存存储窗口的各种数据)
	HWND hWnd = CreateWindow("Main", "window", WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hIns, NULL);

	// 5.显示窗口 (在显示器中绘制窗口的图像)
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd); // 刷新窗口
	
	// 6. 消息循环
	MSG nMsg = {0};
	while (GetMessage(&nMsg, NULL, 0, 0)) {
		TranslateMessage(&nMsg);
		DispatchMessage(&nMsg);	// 将消息交给窗口处理函数处理
	}
	return 0;
}



#if 0
int WINAPI WinMain(
	HINSTANCE hIns,
	HINSTANCE hPreIns,
	LPSTR IpCmdLine,
	int nCmdShow)
{
	MessageBox(NULL, (LPCSTR)"hello world", (LPCSTR)"Information", MB_YESNOCANCEL | MB_ICONERROR);
	return 0;
}
#endif


 

