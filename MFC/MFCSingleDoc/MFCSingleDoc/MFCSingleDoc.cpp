#include <afxwin.h>
#include "resource.h"

class CMyDoc : public CDocument
{
	DECLARE_DYNCREATE(CMyDoc)
};
IMPLEMENT_DYNCREATE(CMyDoc, CDocument)

class CMyView : public CView
{
	DECLARE_DYNCREATE(CMyView)
public:
	virtual void OnDraw(CDC* pDC);
};
IMPLEMENT_DYNCREATE(CMyView, CView)

void CMyView::OnDraw(CDC* pDC)
{
	pDC->TextOutA(100, 100, "我是视图窗口");
}

class CMyFrameWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(CMyFrameWnd)
};
IMPLEMENT_DYNCREATE(CMyFrameWnd, CFrameWnd)

class CMyWinApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
};
BOOL CMyWinApp::InitInstance()
{
	// 创建单文档模板类对象
	CSingleDocTemplate* pTemplate = new CSingleDocTemplate(
		IDR_MENU1,
		RUNTIME_CLASS(CMyDoc),
		RUNTIME_CLASS(CMyFrameWnd),
		RUNTIME_CLASS(CMyView)
	);

	// 调用
	AddDocTemplate(pTemplate);
	OnFileNew();
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}
CMyWinApp theApp;