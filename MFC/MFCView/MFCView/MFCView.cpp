#include <afxwin.h>
#include "resource.h"
class CMyView : public CView
{
	DECLARE_MESSAGE_MAP()
protected:
	void OnDraw(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnNew();
};

void CMyView::OnNew()
{
	AfxMessageBox("视图类处理了WM_COMMAND消息");
}

void CMyView::OnPaint()
{
	PAINTSTRUCT ps = { 0 };
	HDC hdc = ::BeginPaint(this->m_hWnd, &ps);
	::TextOut(hdc, 200, 200, "CMyView::OnPaint", strlen("CMyView::OnPaint"));
	::EndPaint(this->m_hWnd, &ps);
}

BEGIN_MESSAGE_MAP(CMyView, CView)
	ON_WM_PAINT()
	ON_COMMAND(ID_NEW, OnNew)
END_MESSAGE_MAP()

void CMyView::OnDraw(CDC* pDC)
{
	pDC->TextOutA(100, 100, "CMyView::OnDraw");
}

class CMyFrameWnd : public CFrameWnd {
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT pcs);
};

int CMyFrameWnd::OnCreate(LPCREATESTRUCT pcs)
{
	CMyView* pView = new CMyView;
	//pView->Create(NULL, "MFCView", WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(0, 0, 150, 150), this, 1001);
	// 如果视图窗口ID大于等于AFX_IDW_PANE_FIRST，就将视图窗口平铺（覆盖）整个框架窗口，即设置成框架窗口客户区的大小
	pView->Create(NULL, "MFCView", WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(0, 0, 150, 150), this, AFX_IDW_PANE_FIRST);
	this->m_pViewActive = pView;
	return CFrameWnd::OnCreate(pcs);
}

void CMyFrameWnd::OnPaint()
{
	PAINTSTRUCT ps = { 0 };
	HDC hdc = ::BeginPaint(this->m_hWnd, &ps);
	::TextOut(hdc, 100, 100, "框架窗口客户区", strlen("框架窗口客户区"));
	::EndPaint(this->m_hWnd, &ps);
}


BEGIN_MESSAGE_MAP(CMyFrameWnd, CFrameWnd)
	ON_WM_PAINT()
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
	pFrame->Create(NULL, "MFCVIew", WS_OVERLAPPEDWINDOW,CFrameWnd::rectDefault, NULL, (CHAR*)IDR_MENU1);
	m_pMainWnd = pFrame;
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	return TRUE;
}
CMyWinApp theApp;