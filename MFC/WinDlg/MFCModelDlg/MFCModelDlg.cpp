#include <afxwin.h>
#include "resource.h"

// ģʽ�Ի���
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
	dlg.DoModal();	// �ڲ���ִ����Ϣѭ��
	return FALSE;	// DoModal�˳��󣬣�û�б�Ҫ������ִ��MFC���а��ŵ�Run����
}
CMyWinApp theApp;

