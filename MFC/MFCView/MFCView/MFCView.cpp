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
	AfxMessageBox("��ͼ�ദ����WM_COMMAND��Ϣ");
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
	// �����ͼ����ID���ڵ���AFX_IDW_PANE_FIRST���ͽ���ͼ����ƽ�̣����ǣ�������ܴ��ڣ������óɿ�ܴ��ڿͻ����Ĵ�С
	pView->Create(NULL, "MFCView", WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(0, 0, 150, 150), this, AFX_IDW_PANE_FIRST);
	this->m_pViewActive = pView;
	return CFrameWnd::OnCreate(pcs);
}

void CMyFrameWnd::OnPaint()
{
	PAINTSTRUCT ps = { 0 };
	HDC hdc = ::BeginPaint(this->m_hWnd, &ps);
	::TextOut(hdc, 100, 100, "��ܴ��ڿͻ���", strlen("��ܴ��ڿͻ���"));
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