#include <afxwin.h>
#include <afxext.h>
#include "resource.h"

class CMyDoc : public CDocument
{
	DECLARE_MESSAGE_MAP()
	
public:
	afx_msg void OnNew();
	CString str;
};
BEGIN_MESSAGE_MAP(CMyDoc, CDocument)
	ON_COMMAND(ID_NEW, OnNew)
END_MESSAGE_MAP()
void CMyDoc::OnNew()
{
	AfxMessageBox("文档类处理的WM_COMMAND消息");
	str = "hello world";	// 接收到的数据
	//UpdateAllViews(NULL);	// 刷新和这个文档类对象（this）关联的所有视图窗口

	
	// 获取m_viewList成员的迭代器，GetFirstViewPosition（）指的是m_viewList链表头节点的前一个位置
	POSITION pos = this->GetFirstViewPosition();	  // GetFirstxxxPosition 获取迭代器函数
	CView* pView = this->GetNextView(pos);			  // GetNextXXX 得到第一个视图类对象
	this->UpdateAllViews(pView);					  // 刷新和这个文档类对象(this)关联的 除了pView指向的视图窗口
}


class CMyView : public CView
{
	// 支持动态创建机制
	DECLARE_DYNCREATE(CMyView)
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnDraw(CDC* pDc);
	afx_msg int OnCreate(LPCREATESTRUCT pcs);
	afx_msg void OnNew();
};
IMPLEMENT_DYNCREATE(CMyView, CView)
BEGIN_MESSAGE_MAP(CMyView, CView)
	ON_WM_CREATE()
	//ON_COMMAND(ID_NEW, OnNew)
END_MESSAGE_MAP()

void CMyView::OnNew()
{
	AfxMessageBox("视图类处理的WM_COMMAND消息");
}

int CMyView::OnCreate(LPCREATESTRUCT pcs)
{
	return CView::OnCreate(pcs);	  // 将文档类对象和视图类对象建立关联
}

void CMyView::OnDraw(CDC* pDc){
	
	//pDc->TextOut(100, 100, "我是视图类窗口");
	// 视图类对象获取到内部的文档类对象成员
	//CMyDoc* pDoc =  (CMyDoc*)this->m_pDocument;
	// 等价于GetDocument()
	CMyDoc* pDoc = (CMyDoc*)this->GetDocument();
	pDc->TextOut(100, 100, pDoc->str);

}

class CMyFrameWnd : public CFrameWnd {
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT pcs);
	afx_msg void OnPaint();
	afx_msg void OnNew();

	virtual BOOL OnCreateClient(LPCREATESTRUCT pcs, CCreateContext* pContext);

	CSplitterWnd split;	// 不规则框架窗口
};
BEGIN_MESSAGE_MAP(CMyFrameWnd, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	//ON_COMMAND(ID_NEW, OnNew)
END_MESSAGE_MAP()

void CMyFrameWnd::OnNew()
{
	AfxMessageBox("框架类处理的WM_COMMAND消息");
}

BOOL CMyFrameWnd::OnCreateClient(LPCREATESTRUCT pcs, CCreateContext* pContext)
{
	// 创建不规则框架窗口
	split.CreateStatic(this, 1, 2);

	// 创建两个视图窗口
	split.CreateView(0, 0, RUNTIME_CLASS(CMyView), CSize(200), pContext);
	split.CreateView(0, 1, pContext->m_pNewViewClass, CSize(200), pContext);
	// 指定活动视图窗口
	m_pViewActive = (CView*)split.GetPane(0, 0);
	return TRUE;
}


void CMyFrameWnd::OnPaint()
{
	PAINTSTRUCT ps = { 0 };
	HDC hdc = ::BeginPaint(this->m_hWnd, &ps);
	::TextOut(hdc, 200, 200, "我是框架窗口客户区", strlen("我是框架窗口客户区"));
	::EndPaint(this->m_hWnd, &ps);
}

int CMyFrameWnd::OnCreate(LPCREATESTRUCT pcs)
{
	// 验证不让父类处理WM_CREAT消息，是否还会动态创建视图窗口
	// 最后调用OnDraw显示内容
	// return 0;

	// 让父类处理消息,动态创建视图类对象，创建视图窗口
	return CFrameWnd::OnCreate(pcs);
}



class CMyWinApp : public CWinApp
{
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL InitInstance();
	afx_msg void OnNew();
};

BEGIN_MESSAGE_MAP(CMyWinApp, CWinApp)
	ON_COMMAND(ID_NEW, OnNew)
END_MESSAGE_MAP()

void CMyWinApp::OnNew()
{
	AfxMessageBox("应用程序类处理的WM_COMMAND消息");
}


BOOL CMyWinApp::InitInstance()
{
	CMyFrameWnd* pFrame = new CMyFrameWnd;
	CMyDoc* pDoc = new CMyDoc;

	CCreateContext cct;
	cct.m_pCurrentDoc = pDoc;						// 文档类对象地址	
	cct.m_pNewViewClass = RUNTIME_CLASS(CMyView);	// 获取CMyView静态变量的地址，&CMyView::classCMyView	
	pFrame->LoadFrame(IDR_MENU1, WS_OVERLAPPEDWINDOW, NULL, &cct);
	m_pMainWnd = pFrame;
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	return TRUE;
}
CMyWinApp theApp;

