
// Graphic1View.h : interface of the CGraphic1View class
//

#pragma once


class CGraphic1View : public CView
{
protected: // create from serialization only
	CGraphic1View();
	DECLARE_DYNCREATE(CGraphic1View)

// Attributes
public:
	CGraphic1Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CGraphic1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Graphic1View.cpp
inline CGraphic1Doc* CGraphic1View::GetDocument() const
   { return reinterpret_cast<CGraphic1Doc*>(m_pDocument); }
#endif

