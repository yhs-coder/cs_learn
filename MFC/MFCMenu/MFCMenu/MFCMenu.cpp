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
	// 使用win32的api
	/*HMENU subMenu = ::GetSubMenu(menu.m_hMenu, 0);
	::TrackPopupMenu(subMenu, TPM_LEFTALIGN | TPM_TOPALIGN, pt.x, pt.y, 0, pWnd->m_hWnd, NULL);*/

	CMenu* pPopup = menu.GetSubMenu(0);	// 得到整个菜单中第一个菜单项
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_TOPALIGN, pt.x, pt.y, pWnd);
}


void CMyFrameWnd::OnInitMenuPopup(CMenu* pPopup, UINT nPos, BOOL i)
{
	// 使用CMenu对象的成员
	pPopup->CheckMenuItem(ID_NEW, MF_CHECKED);
	// 等价使用win32的api
	//::CheckMenuItem(pPopup->m_hMenu, ID_NEW, MF_CHECKED);
}

void CMyFrameWnd::OnNew()
{
	AfxMessageBox("框架类处理了新建菜单项被点击");
}

int CMyFrameWnd::OnCreate(LPCREATESTRUCT pcs)
{
	// 方法二： 在处理WM_CREATE消息时设置菜单
	menu.LoadMenu(IDR_MENU1);
	this->SetMenu(&menu);
	// this->SetMenu(&menu);不用面向对象的用法，使用win32 api等价于
	//::SetMenu(this->m_hWnd, menu.m_hMenu);
	return CFrameWnd::OnCreate(pcs);
}

BEGIN_MESSAGE_MAP(CMyFrameWnd, CFrameWnd)
	ON_WM_CREATE()
	//ON_COMMAND(ID_NEW, OnNew)	// 处理点击菜单项消息
	ON_WM_INITMENUPOPUP()		// 处理菜单项的状态信息
	ON_WM_CONTEXTMENU()			// 处理点击鼠标右键时弹出菜单的消息
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
	AfxMessageBox("应用程序类处理了新建菜单项被点击");
}

BEGIN_MESSAGE_MAP(CMyWinApp, CWinApp)
	ON_COMMAND(ID_NEW, OnNew)
END_MESSAGE_MAP()

BOOL CMyWinApp::InitInstance()
{
	CMyFrameWnd* pFrame = new CMyFrameWnd;
	// 将菜单设置到窗口
#if 0
	// 方法一：在Create函数中传参
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
