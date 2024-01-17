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
	pDC->TextOut(100, 100, "������ͼ����");
}

// �ӿ�ܴ���
class CMyChild : public CMDIChildWnd {
	DECLARE_DYNCREATE(CMyChild)
};
IMPLEMENT_DYNCREATE(CMyChild, CMDIChildWnd)

// ����ܴ�����Ķ���
class CMyFrameWnd : public CMDIFrameWnd
{
	// ��Ҫ�Լ���������ܴ�����Ķ���
};


class CMyWinApp : public CWinApp {
	// ��Ҫ�Լ�����Ӧ�ó�����Ķ���
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
	   
	//�������ĵ�ģ�������
	CMultiDocTemplate* pTemplate = new CMultiDocTemplate(
		IDR_MENU2,
		RUNTIME_CLASS(CMyDoc),
		RUNTIME_CLASS(CMyChild),
		RUNTIME_CLASS(CMyView)
	);
	AddDocTemplate(pTemplate);
	// �����ĵ�����󣬴����ӿ������󣬴����ӿ�ܴ��ڣ�������ͼ����󣬴�����ͼ�ര�ڣ����ĵ���������ͼ��������
	OnFileNew();
	OnFileNew();
	OnFileNew();
	 

	return TRUE;
}

CMyWinApp theApp;


