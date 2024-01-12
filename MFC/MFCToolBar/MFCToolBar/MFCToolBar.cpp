#include <afxwin.h>
#include "resource.h"
#include <afxext.h>		// ����CToolBar��
class CMyFrameWnd : public CFrameWnd
{
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNew();
	afx_msg int OnCreate(LPCREATESTRUCT pcs);
	afx_msg void OnSet();

public:
	CToolBar toolbar;
};

void CMyFrameWnd::OnSet()
{
	AfxMessageBox("��ɫ��������ť�����");
}

int CMyFrameWnd::OnCreate(LPCREATESTRUCT pcs)
{
	toolbar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP);
	toolbar.LoadToolBar(IDR_TOOLBAR1);

	
	toolbar.EnableDocking(CBRS_ALIGN_ANY);
	this->EnableDocking(CBRS_ALIGN_ANY);
	this->DockControlBar(&toolbar);
	return CFrameWnd::OnCreate(pcs);
}

void CMyFrameWnd::OnNew()
{
	AfxMessageBox("�½��˵�����");
}



BEGIN_MESSAGE_MAP(CMyFrameWnd, CFrameWnd)
	ON_COMMAND(ID_SET,OnSet)	// ������
	ON_COMMAND(ID_NEW, OnNew)
	ON_WM_CREATE()
END_MESSAGE_MAP()
class CMyWinApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
};

BOOL CMyWinApp::InitInstance()
{
	CMyFrameWnd* pFrame = new CMyFrameWnd;
	pFrame->Create(NULL, "MFCToolBar", WS_OVERLAPPEDWINDOW, CFrameWnd::rectDefault, NULL,(CHAR*)IDR_MENU1);
	m_pMainWnd = pFrame;
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	return TRUE;
}
CMyWinApp theApp;

