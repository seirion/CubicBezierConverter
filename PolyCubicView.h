// PolyCubicView.h : interface of the CPolyCubicView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_POLYCUBICVIEW_H__CF1B0011_B779_4EDE_A746_CA331D3AC20E__INCLUDED_)
#define AFX_POLYCUBICVIEW_H__CF1B0011_B779_4EDE_A746_CA331D3AC20E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPolyCubicView : public CView
{
protected: // create from serialization only
	CPolyCubicView();
	DECLARE_DYNCREATE(CPolyCubicView)

// Attributes
public:
	CPolyCubicDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPolyCubicView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPolyCubicView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPolyCubicView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in PolyCubicView.cpp
inline CPolyCubicDoc* CPolyCubicView::GetDocument()
   { return (CPolyCubicDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POLYCUBICVIEW_H__CF1B0011_B779_4EDE_A746_CA331D3AC20E__INCLUDED_)
