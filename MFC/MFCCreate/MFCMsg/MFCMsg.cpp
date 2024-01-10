#include <afxwin.h>
// MFC消息映射机制

class CMyFrameWnd : public CFrameWnd {
	// 类内添加声明宏
#if 0
	DECLARE_MESSAGE_MAP()
#else
 // DECLARE_MESSAGE_MAP()等价于
protected:
	static const AFX_MSGMAP* PASCAL GetThisMessageMap();
	virtual const AFX_MSGMAP* GetMessageMap() const;
#endif

public:
	LRESULT OnCreate(WPARAM wParam, LPARAM lParam);
};

#if 0
// 类外添加实现宏
BEGIN_MESSAGE_MAP(CMyFrameWnd, CFrameWnd)
	ON_MESSAGE(WM_CREATE, OnCreate)
END_MESSAGE_MAP()
#else
// 以上宏展开
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
		// 在此处替换ON_MESSAGE(WM_CREATE, OnCreate)
		//#define ON_MESSAGE(message, memberFxn) 
	{   WM_CREATE, 0, 0, 0, AfxSig_lwl,
		(AFX_PMSG)(AFX_PMSGW)
		(static_cast<LRESULT(AFX_MSG_CALL CWnd::*)(WPARAM, LPARAM)>
		(OnCreate)) },

		// END_MESSAGE_MAP()展开
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

CMyWinApp theApp;	// 爆破点