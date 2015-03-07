           // PolyCubicView.cpp : implementation of the CPolyCubicView class
//

#include "stdafx.h"
#include "PolyCubic.h"

#include "PolyCubicDoc.h"
#include "PolyCubicView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPolyCubicView

IMPLEMENT_DYNCREATE(CPolyCubicView, CView)

BEGIN_MESSAGE_MAP(CPolyCubicView, CView)
	//{{AFX_MSG_MAP(CPolyCubicView)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPolyCubicView construction/destruction

CPolyCubicView::CPolyCubicView()
{
	// TODO: add construction code here

}

CPolyCubicView::~CPolyCubicView()
{
}

BOOL CPolyCubicView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPolyCubicView drawing

void CPolyCubicView::OnDraw(CDC* pDC)
{
	CPolyCubicDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	const int size = 3;
	if( pDoc->m_DrawMode == DRAW_NONE) return;
	
	CPen blackPen, redPen, bluePen, grayPen, *pOldPen;
	blackPen.CreatePen(PS_SOLID, 1, RGB(0,0,0));
	redPen.CreatePen(PS_SOLID, 1, RGB(255,0,0));
	bluePen.CreatePen(PS_SOLID, 1, RGB(0,0,255));
	grayPen.CreatePen(PS_SOLID, 1, RGB(127,127,127));
	pOldPen = (CPen *)pDC->SelectObject(&bluePen);

	int i;
	for( i = 0; i < pDoc->m_PointNum; i++)
	{
		pDC->MoveTo(pDoc->m_Point[i].x-size,pDoc->m_Point[i].y-size);
		pDC->LineTo(pDoc->m_Point[i].x+size,pDoc->m_Point[i].y+size);
		
		pDC->MoveTo(pDoc->m_Point[i].x-size,pDoc->m_Point[i].y+size);
		pDC->LineTo(pDoc->m_Point[i].x+size,pDoc->m_Point[i].y-size);
	}
	
	if( pDoc->m_DrawMode == DRAW_DONE)
	{
		pDC->SelectObject(&blackPen);
		pDoc->DrawBezier(pDC, RGB(0,0,0));
	}
	
	// 반으로 쪼개기
	if( pDoc->m_Devide )
	{
		pOldPen = (CPen *)pDC->SelectObject(&redPen);
		for( i = 0; i < 7; i++ )
		{
			pDC->MoveTo(pDoc->m_DevidePoint[i].x-size,pDoc->m_DevidePoint[i].y-size);
			pDC->LineTo(pDoc->m_DevidePoint[i].x+size,pDoc->m_DevidePoint[i].y+size);
			
			pDC->MoveTo(pDoc->m_DevidePoint[i].x-size,pDoc->m_DevidePoint[i].y+size);
			pDC->LineTo(pDoc->m_DevidePoint[i].x+size,pDoc->m_DevidePoint[i].y-size);
		}
		pDoc->DrawDevide(pDC, RGB(0,127,0));
	}

	// release pens
	pDC->SelectObject(pOldPen);
	blackPen.DeleteObject();
	redPen.DeleteObject();
	bluePen.DeleteObject();
	grayPen.DeleteObject();
}

/////////////////////////////////////////////////////////////////////////////
// CPolyCubicView printing

BOOL CPolyCubicView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPolyCubicView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPolyCubicView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPolyCubicView diagnostics

#ifdef _DEBUG
void CPolyCubicView::AssertValid() const
{
	CView::AssertValid();
}

void CPolyCubicView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPolyCubicDoc* CPolyCubicView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPolyCubicDoc)));
	return (CPolyCubicDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPolyCubicView message handlers

void CPolyCubicView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CPolyCubicDoc* pDoc = (CPolyCubicDoc*)GetDocument();
	if( pDoc->m_PointNum >= 6 ) return;
	pDoc->m_Point[pDoc->m_PointNum] = point;
	pDoc->m_PointNum++;
	pDoc->m_DrawMode = DRAW_ING;
	Invalidate();
	CView::OnLButtonDown(nFlags, point);
}

void CPolyCubicView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CPolyCubicDoc* pDoc = (CPolyCubicDoc*)GetDocument();
	pDoc->m_DrawMode = DRAW_DONE;
	Invalidate();
	CView::OnRButtonDown(nFlags, point);
}

void CPolyCubicView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CView::OnKeyDown(nChar, nRepCnt, nFlags);

	if( nChar == '1')
	{
		CPolyCubicDoc* pDoc = (CPolyCubicDoc*)GetDocument();
		if( pDoc->m_PointNum > 4 )
		{
			pDoc->Devide();
			pDoc->m_Devide = TRUE;
			Invalidate();
		}
	}
}
