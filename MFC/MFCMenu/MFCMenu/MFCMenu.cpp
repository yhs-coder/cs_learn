#include <afxwin.h>
#include "resource.h"
class CMyFrameWnd : public CFrameWnd
{
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT pcs);
	afx_msg void OnNew();
	afx_msg void OnInitMenuPopup(CMenu* pPopup, UINT nPos, BOOL i);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint pt);
public:
	CMenu menu;
};
void CMyFrameWnd::OnContextMenu(CWnd* pWnd, CPoint pt)
{
	// ʹ��win32��api
	/*HMENU subMenu = ::GetSubMenu(menu.m_hMenu, 0);
	::TrackPopupMenu(subMenu, TPM_LEFTALIGN | TPM_TOPALIGN, pt.x, pt.y, 0, pWnd->m_hWnd, NULL);*/

	CMenu* pPopup = menu.GetSubMenu(0);	// �õ������˵��е�һ���˵���
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_TOPALIGN, pt.x, pt.y, pWnd);
}


void CMyFrameWnd::OnInitMenuPopup(CMenu* pPopup, UINT nPos, BOOL i)
{
	// ʹ��CMenu����ĳ�Ա
	pPopup->CheckMenuItem(ID_NEW, MF_CHECKED);
	// �ȼ�ʹ��win32��api
	//::CheckMenuItem(pPopup->m_hMenu, ID_NEW, MF_CHECKED);
}

void CMyFrameWnd::OnNew()
{
	AfxMessageBox("����ദ�����½��˵�����");
}

int CMyFrameWnd::OnCreate(LPCREATESTRUCT pcs)
{
	// �������� �ڴ���WM_CREATE��Ϣʱ���ò˵�
	menu.LoadMenu(IDR_MENU1);
	this->SetMenu(&menu);
	// this->SetMenu(&menu);�������������÷���ʹ��win32 api�ȼ���
	//::SetMenu(this->m_hWnd, menu.m_hMenu);
	return CFrameWnd::OnCreate(pcs);
}

BEGIN_MESSAGE_MAP(CMyFrameWnd, CFrameWnd)
	ON_WM_CREATE()
	//ON_COMMAND(ID_NEW, OnNew)	// �������˵�����Ϣ
	ON_WM_INITMENUPOPUP()		// ����˵����״̬��Ϣ
	ON_WM_CONTEXTMENU()			// ����������Ҽ�ʱ�����˵�����Ϣ
END_MESSAGE_MAP()

class CMyWinApp : public CWinApp
{
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL InitInstance();
	afx_msg void OnNew();
};

void CMyWinApp::OnNew()
{
	AfxMessageBox("Ӧ�ó����ദ�����½��˵�����");
}

BEGIN_MESSAGE_MAP(CMyWinApp, CWinApp)
	ON_COMMAND(ID_NEW, OnNew)
END_MESSAGE_MAP()

BOOL CMyWinApp::InitInstance()
{
	CMyFrameWnd* pFrame = new CMyFrameWnd;
	// ���˵����õ�����
#if 0
	// ����һ����Create�����д���
	pFrame->Create(NULL, "MFCMenu", WS_OVERLAPPEDWINDOW, CFrameWnd::rectDefault, NULL, (CHAR*)IDR_MENU1);
#else
	pFrame->Create(NULL, "MFCMenu");
#endif
	m_pMainWnd = pFrame;
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	return TRUE;
}

CMyWinApp theApp;
