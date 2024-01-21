#include <windows.h>
#include "resource.h"

HINSTANCE g_hInstance = 0;

INT_PTR CALLBACK DlgProc(HWND hwndDlg, UINT msgID, WPARAM wParam, LPARAM lParam)
{
	switch (msgID) {
	case WM_SYSCOMMAND:
		if (wParam == SC_CLOSE) {
			// 在销毁之前使主窗口可用
			HWND hWnd = GetParent(hwndDlg);	// 得到无模式对话框的父窗口
			EnableWindow(hWnd, TRUE);

			// 销毁无模式对话框
			DestroyWindow(hwndDlg);	// 不能用EndDialog销毁窗口
			// 只能隐藏无模式对话框，没有销毁，可以查看是否有WM_DESTROY消息。 但是该函数可以销毁模式对话框
			//EndDialog(hwndDlg, 1001); 
		}
		break;
	case WM_DESTROY:
		MessageBox(NULL, "dialog die...", "dialog", MB_OK);
		break;
	}
	return FALSE;	// 对话框的消息交给真正的对话框窗口处理函数处理
}

void OnNoModel(HWND hWnd)
{
	// 无模式对话框模拟模式对话框
	// 使主窗口不可用
	EnableWindow(hWnd, FALSE);
	// 创建无模式对话框
	HWND hDlg = CreateDialog(g_hInstance, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, DlgProc);
	// 显示无模式对话框
	ShowWindow(hDlg, SW_SHOW);

}
void OnCommand(HWND hWnd, WPARAM wParam)
{
	switch (LOWORD(wParam)) {
	case ID_NOMODEL:
		OnNoModel(hWnd);
		break;
	}
	

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam) {
	switch (msgID) {
	case WM_COMMAND:
		OnCommand(hWnd, wParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, msgID, wParam, lParam);

}

int CALLBACK WinMain(HINSTANCE hIns, HINSTANCE hPerIns, LPSTR IpCmdLine, int nCmdShow)
{
	HINSTANCE g_hInstance = hIns;
	WNDCLASS wc = { 0 };
	wc.cbClsExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hCursor = NULL;
	wc.hIcon = NULL;
	wc.hInstance = hIns;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = "Main";
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);
	HWND hWnd = CreateWindow("Main", "dialog window", WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hIns, NULL);
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	MSG nMsg = { 0 };
	while (GetMessage(&nMsg, NULL, 0, 0)) {
		TranslateMessage(&nMsg);
		DispatchMessage(&nMsg);
	}
	return 0;
}
