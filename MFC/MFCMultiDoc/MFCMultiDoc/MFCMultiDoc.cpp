#include <afxwin.h>
#include "resource.h"
class CMyDoc : public CDocument
{
	DECLARE_DYNCREATE(CMyDoc)
};

IMPLEMENT_DYNCREATE(CMyDoc, CDocument)

class CMyView : CView
{
	DECLARE_DYNCREATE(CMyView)
public:
	virtual void OnDraw(CDC* pDC);
};
IMPLEMENT_DYNCREATE(CMyView, CView)
void CMyView::OnDraw(CDC* pDC)
{
	pDC->TextOut(100, 100, "我是视图窗口");
}

// 子框架窗口
class CMyChild : public CMDIChildWnd {
	DECLARE_DYNCREATE(CMyChild)
};
IMPLEMENT_DYNCREATE(CMyChild, CMDIChildWnd)

// 主框架窗口类的对象
class CMyFrameWnd : public CMDIFrameWnd
{
	// 需要自己创建主框架窗口类的对象
};


class CMyWinApp : public CWinApp {
	// 需要自己创建应用程序类的对象
public:
	virtual BOOL InitInstance();
};

BOOL CMyWinApp::InitInstance()
{
	CMyFrameWnd* pFrame = new CMyFrameWnd;
	pFrame->LoadFrame(IDR_MENU1);
	m_pMainWnd = pFrame;
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	   
	//创建多文档模板类对象
	CMultiDocTemplate* pTemplate = new CMultiDocTemplate(
		IDR_MENU2,
		RUNTIME_CLASS(CMyDoc),
		RUNTIME_CLASS(CMyChild),
		RUNTIME_CLASS(CMyView)
	);
	AddDocTemplate(pTemplate);
	// 创建文档类对象，创建子框架类对象，创建子框架窗口，创建视图类对象，创建视图类窗口，将文档类对象和视图类对象关联
	OnFileNew();
	OnFileNew();
	OnFileNew();
	 

	return TRUE;
}

CMyWinApp theApp;


