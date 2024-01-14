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
	AfxMessageBox("�ĵ��ദ���WM_COMMAND��Ϣ");
	str = "hello world";	// ���յ�������
	//UpdateAllViews(NULL);	// ˢ�º�����ĵ������this��������������ͼ����

	
	// ��ȡm_viewList��Ա�ĵ�������GetFirstViewPosition����ָ����m_viewList����ͷ�ڵ��ǰһ��λ��
	POSITION pos = this->GetFirstViewPosition();	  // GetFirstxxxPosition ��ȡ����������
	CView* pView = this->GetNextView(pos);			  // GetNextXXX �õ���һ����ͼ�����
	this->UpdateAllViews(pView);					  // ˢ�º�����ĵ������(this)������ ����pViewָ�����ͼ����
}


class CMyView : public CView
{
	// ֧�ֶ�̬��������
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
	AfxMessageBox("��ͼ�ദ���WM_COMMAND��Ϣ");
}

int CMyView::OnCreate(LPCREATESTRUCT pcs)
{
	return CView::OnCreate(pcs);	  // ���ĵ���������ͼ�����������
}

void CMyView::OnDraw(CDC* pDc){
	
	//pDc->TextOut(100, 100, "������ͼ�ര��");
	// ��ͼ������ȡ���ڲ����ĵ�������Ա
	//CMyDoc* pDoc =  (CMyDoc*)this->m_pDocument;
	// �ȼ���GetDocument()
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

	CSplitterWnd split;	// �������ܴ���
};
BEGIN_MESSAGE_MAP(CMyFrameWnd, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	//ON_COMMAND(ID_NEW, OnNew)
END_MESSAGE_MAP()

void CMyFrameWnd::OnNew()
{
	AfxMessageBox("����ദ���WM_COMMAND��Ϣ");
}

BOOL CMyFrameWnd::OnCreateClient(LPCREATESTRUCT pcs, CCreateContext* pContext)
{
	// �����������ܴ���
	split.CreateStatic(this, 1, 2);

	// ����������ͼ����
	split.CreateView(0, 0, RUNTIME_CLASS(CMyView), CSize(200), pContext);
	split.CreateView(0, 1, pContext->m_pNewViewClass, CSize(200), pContext);
	// ָ�����ͼ����
	m_pViewActive = (CView*)split.GetPane(0, 0);
	return TRUE;
}


void CMyFrameWnd::OnPaint()
{
	PAINTSTRUCT ps = { 0 };
	HDC hdc = ::BeginPaint(this->m_hWnd, &ps);
	::TextOut(hdc, 200, 200, "���ǿ�ܴ��ڿͻ���", strlen("���ǿ�ܴ��ڿͻ���"));
	::EndPaint(this->m_hWnd, &ps);
}

int CMyFrameWnd::OnCreate(LPCREATESTRUCT pcs)
{
	// ��֤���ø��ദ��WM_CREAT��Ϣ���Ƿ񻹻ᶯ̬������ͼ����
	// ������OnDraw��ʾ����
	// return 0;

	// �ø��ദ����Ϣ,��̬������ͼ����󣬴�����ͼ����
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
	AfxMessageBox("Ӧ�ó����ദ���WM_COMMAND��Ϣ");
}


BOOL CMyWinApp::InitInstance()
{
	CMyFrameWnd* pFrame = new CMyFrameWnd;
	CMyDoc* pDoc = new CMyDoc;

	CCreateContext cct;
	cct.m_pCurrentDoc = pDoc;						// �ĵ�������ַ	
	cct.m_pNewViewClass = RUNTIME_CLASS(CMyView);	// ��ȡCMyView��̬�����ĵ�ַ��&CMyView::classCMyView	
	pFrame->LoadFrame(IDR_MENU1, WS_OVERLAPPEDWINDOW, NULL, &cct);
	m_pMainWnd = pFrame;
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	return TRUE;
}
CMyWinApp theApp;

