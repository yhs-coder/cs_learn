#include <afxwin.h>
// MFC��Ϣӳ�����

class CMyFrameWnd : public CFrameWnd {
	// �������������
#if 0
	DECLARE_MESSAGE_MAP()
#else
 // DECLARE_MESSAGE_MAP()�ȼ���
protected:
	static const AFX_MSGMAP* PASCAL GetThisMessageMap();
	virtual const AFX_MSGMAP* GetMessageMap() const;
#endif

public:
	LRESULT OnCreate(WPARAM wParam, LPARAM lParam);
};

#if 0
// �������ʵ�ֺ�
BEGIN_MESSAGE_MAP(CMyFrameWnd, CFrameWnd)
	ON_MESSAGE(WM_CREATE, OnCreate)
END_MESSAGE_MAP()
#else
// ���Ϻ�չ��
// BEGIN_MESSAGE_MAP(theClass, baseClass) 
PTM_WARNING_DISABLE
const AFX_MSGMAP* CMyFrameWnd::GetMessageMap() const
{
	return GetThisMessageMap();
}
const AFX_MSGMAP* PASCAL CMyFrameWnd::GetThisMessageMap()
{
	typedef CMyFrameWnd ThisClass;
	typedef CFrameWnd TheBaseClass;
	__pragma(warning(push))
		__pragma(warning(disable: 4640)) /* message maps can only be called by single threaded message pump */
		static const AFX_MSGMAP_ENTRY _messageEntries[] =
	{
		// �ڴ˴��滻ON_MESSAGE(WM_CREATE, OnCreate)
		//#define ON_MESSAGE(message, memberFxn) 
	{   WM_CREATE, 0, 0, 0, AfxSig_lwl,
		(AFX_PMSG)(AFX_PMSGW)
		(static_cast<LRESULT(AFX_MSG_CALL CWnd::*)(WPARAM, LPARAM)>
		(OnCreate)) },

		// END_MESSAGE_MAP()չ��
		{0, 0, 0, 0, AfxSig_end, (AFX_PMSG)0 }
	};
	__pragma(warning(pop))
		static const AFX_MSGMAP messageMap =
	{ &TheBaseClass::GetThisMessageMap, &_messageEntries[0] };
	return &messageMap;
}
PTM_WARNING_RESTORE


#endif



LRESULT CMyFrameWnd::OnCreate(WPARAM wParam, LPARAM lParam)
{
	AfxMessageBox("WM_CREATE");
	return 0;
}

class CMyWinApp : public CWinApp {
public:
	virtual BOOL InitInstance();
};

BOOL CMyWinApp::InitInstance()
{
	CMyFrameWnd* pFrame = new CMyFrameWnd;
	pFrame->Create(NULL, "MFCBase");
	m_pMainWnd = pFrame;
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	return TRUE;
}

CMyWinApp theApp;	// ���Ƶ�