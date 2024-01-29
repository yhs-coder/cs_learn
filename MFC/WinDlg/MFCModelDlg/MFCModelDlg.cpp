#include <afxwin.h>
#include "resource.h"

// 模式对话框
class CMyDlg : public CDialog {
	DECLARE_MESSAGE_MAP()
	enum {
		IDD = IDD_DIALOG1
	};

public:
	CMyDlg() : CDialog(IDD) {}
	afx_msg void OnOK();

};
BEGIN_MESSAGE_MAP(CMyDlg, CDialog)
	ON_COMMAND(IDOK, OnOK)
END_MESSAGE_MAP()
void CMyDlg::OnOK() {
	CDialog::OnOK();
}


class CMyWinApp : public CWinApp {
public:
	virtual BOOL InitInstance();
};
BOOL CMyWinApp::InitInstance() {
	CMyDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();	// 内部会执行消息循环
	return FALSE;	// DoModal退出后，（没有必要）不再执行MFC库中安排的Run函数
}
CMyWinApp theApp;

