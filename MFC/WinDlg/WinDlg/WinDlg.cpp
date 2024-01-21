#include <windows.h>
#include "resource.h"

HINSTANCE g_hInstance = 0;

INT_PTR CALLBACK DlgProc(HWND hwndDlg, UINT msgID, WPARAM wParam, LPARAM lParam)
{
	switch (msgID) {
	case WM_SYSCOMMAND:
		if (wParam == SC_CLOSE) {
			// ������֮ǰʹ�����ڿ���
			HWND hWnd = GetParent(hwndDlg);	// �õ���ģʽ�Ի���ĸ�����
			EnableWindow(hWnd, TRUE);

			// ������ģʽ�Ի���
			DestroyWindow(hwndDlg);	// ������EndDialog���ٴ���
			// ֻ��������ģʽ�Ի���û�����٣����Բ鿴�Ƿ���WM_DESTROY��Ϣ�� ���Ǹú�����������ģʽ�Ի���
			//EndDialog(hwndDlg, 1001); 
		}
		break;
	case WM_DESTROY:
		MessageBox(NULL, "dialog die...", "dialog", MB_OK);
		break;
	}
	return FALSE;	// �Ի������Ϣ���������ĶԻ��򴰿ڴ���������
}

void OnNoModel(HWND hWnd)
{
	// ��ģʽ�Ի���ģ��ģʽ�Ի���
	// ʹ�����ڲ�����
	EnableWindow(hWnd, FALSE);
	// ������ģʽ�Ի���
	HWND hDlg = CreateDialog(g_hInstance, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, DlgProc);
	// ��ʾ��ģʽ�Ի���
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
