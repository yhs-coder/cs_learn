#include <windows.h>
/*
	����һ�����ڳ���

*/

// 2. ���ڴ��������Զ��壬������Ϣ��
LRESULT CALLBACK WndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM IParam) {
	return DefWindowProc(hWnd, msgID, wParam, IParam);
}

// 1.����WinMain��ں���
int CALLBACK WinMain(HINSTANCE hIns, HINSTANCE hPerIns, LPSTR IpCmdLine, int nCmdShow) {

	// 3. ע�ᴰ���� ����ϵͳ�ں�д�����ݣ�
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
	RegisterClass(&wc);	// ���������и�ֵȫ��д�����ϵͳ

	// 4. ���ڴ洴������ (�ڴ�洢���ڵĸ�������)
	HWND hWnd = CreateWindow("Main", "window", WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hIns, NULL);

	// 5.��ʾ���� (����ʾ���л��ƴ��ڵ�ͼ��)
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd); // ˢ�´���
	
	// 6. ��Ϣѭ��
	MSG nMsg = {0};
	while (GetMessage(&nMsg, NULL, 0, 0)) {
		TranslateMessage(&nMsg);
		DispatchMessage(&nMsg);	// ����Ϣ�������ڴ���������
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


 

