#include <afxwin.h>

class CMyFrameWnd : public CFrameWnd {
};

class CMyWinApp : public CWinApp {
public:
	CMyWinApp(){}

	virtual BOOL InitInstance() {
		CMyFrameWnd* pFrame = new CMyFrameWnd;
		pFrame->Create(NULL, "MFCBase");
		m_pMainWnd = pFrame;
		pFrame->ShowWindow(SW_SHOW);
		pFrame->UpdateWindow();
		return TRUE;
	}
};

CMyWinApp theApp;	// ±¬ÆÆµã

