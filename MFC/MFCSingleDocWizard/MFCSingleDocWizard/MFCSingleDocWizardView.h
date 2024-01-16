
// MFCSingleDocWizardView.h: CMFCSingleDocWizardView 类的接口
//

#pragma once


class CMFCSingleDocWizardView : public CView
{
protected: // 仅从序列化创建
	CMFCSingleDocWizardView() noexcept;
	DECLARE_DYNCREATE(CMFCSingleDocWizardView)

// 特性
public:
	CMFCSingleDocWizardDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CMFCSingleDocWizardView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // MFCSingleDocWizardView.cpp 中的调试版本
inline CMFCSingleDocWizardDoc* CMFCSingleDocWizardView::GetDocument() const
   { return reinterpret_cast<CMFCSingleDocWizardDoc*>(m_pDocument); }
#endif

