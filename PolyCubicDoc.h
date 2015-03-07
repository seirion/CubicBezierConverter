// PolyCubicDoc.h : interface of the CPolyCubicDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_POLYCUBICDOC_H__0C6AA14B_2AE1_4A2B_B19D_7399A43876D3__INCLUDED_)
#define AFX_POLYCUBICDOC_H__0C6AA14B_2AE1_4A2B_B19D_7399A43876D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define DRAW_NONE	0
#define DRAW_ING	1
#define DRAW_DONE	2

class CPolyCubicDoc : public CDocument
{
protected: // create from serialization only
	CPolyCubicDoc();
	DECLARE_DYNCREATE(CPolyCubicDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPolyCubicDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	void DrawDevide(CDC* pDC, COLORREF color);
	void Devide();
	int GetCoefficient(int n, int k);
	double Power(double u, int k);
	int Factorial( int value);
	CPoint GetBezierPoint( double u);
	CPoint GetBezierPoint2( double u);
	CPoint GetBezierPoint3( double u);
	void DrawBezier(CDC *pDC, COLORREF color);
	void Init();

	//////////////////////////////////////////////////////////////////////////
	
	int m_PointNum;
	CPoint m_Point[6];
	int m_DrawMode;
	BOOL m_Devide;
	CPoint m_DevidePoint[7];

	virtual ~CPolyCubicDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPolyCubicDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POLYCUBICDOC_H__0C6AA14B_2AE1_4A2B_B19D_7399A43876D3__INCLUDED_)
