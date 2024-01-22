#include <afxwin.h>
#include "resource.h"

class CMyDlg : public CDialog
{

};

class CMyWinApp : public CWinApp {
public:
	virtual BOOL InitInstance();
};
BOOL CMyWinApp::InitInstance()
{
	CMyDlg* pdlg = new CMyDlg;
	pdlg->Create(IDD_DIALOG1);
	m_pMainWnd = pdlg;
	pdlg->ShowWindow(SW_SHOW);
	return TRUE;
}
CMyWinApp theApp;




