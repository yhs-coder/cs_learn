
// MFCSingleDocWizardView.cpp: CMFCSingleDocWizardView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCSingleDocWizard.h"
#endif

#include "MFCSingleDocWizardDoc.h"
#include "MFCSingleDocWizardView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCSingleDocWizardView

IMPLEMENT_DYNCREATE(CMFCSingleDocWizardView, CView)

BEGIN_MESSAGE_MAP(CMFCSingleDocWizardView, CView)
END_MESSAGE_MAP()

// CMFCSingleDocWizardView 构造/析构

CMFCSingleDocWizardView::CMFCSingleDocWizardView() noexcept
{
	// TODO: 在此处添加构造代码

}

CMFCSingleDocWizardView::~CMFCSingleDocWizardView()
{
}

BOOL CMFCSingleDocWizardView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCSingleDocWizardView 绘图

void CMFCSingleDocWizardView::OnDraw(CDC* /*pDC*/)
{
	CMFCSingleDocWizardDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMFCSingleDocWizardView 诊断

#ifdef _DEBUG
void CMFCSingleDocWizardView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCSingleDocWizardView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCSingleDocWizardDoc* CMFCSingleDocWizardView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCSingleDocWizardDoc)));
	return (CMFCSingleDocWizardDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCSingleDocWizardView 消息处理程序
