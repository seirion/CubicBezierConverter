             // PolyCubicDoc.cpp : implementation of the CPolyCubicDoc class
//

#include "stdafx.h"
#include "PolyCubic.h"

#include "PolyCubicDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPolyCubicDoc

IMPLEMENT_DYNCREATE(CPolyCubicDoc, CDocument)

BEGIN_MESSAGE_MAP(CPolyCubicDoc, CDocument)
	//{{AFX_MSG_MAP(CPolyCubicDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPolyCubicDoc construction/destruction

CPolyCubicDoc::CPolyCubicDoc()
{
	// TODO: add one-time construction code here
	Init();

}

CPolyCubicDoc::~CPolyCubicDoc()
{
}

BOOL CPolyCubicDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	Init();
	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPolyCubicDoc serialization

void CPolyCubicDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPolyCubicDoc diagnostics

#ifdef _DEBUG
void CPolyCubicDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPolyCubicDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPolyCubicDoc commands

void CPolyCubicDoc::Init()
{
	m_DrawMode = DRAW_NONE;
	m_PointNum = 0;
	m_Devide = FALSE;
}

void CPolyCubicDoc::DrawBezier(CDC *pDC, COLORREF color)
{
	int i;
	const int size = 200;
	for( i = 0; i <= size; i++)
	{
		pDC->SetPixel(GetBezierPoint((double)i/size), color);
	}
}

CPoint CPolyCubicDoc::GetBezierPoint( double u)
{
	CPoint point;
	double x, y;
	int k;
	int n = m_PointNum-1;
	int coeff;
	
	x = 0;
	y = 0;
	for( k = 0; k < m_PointNum; k++)
	{
		coeff = GetCoefficient(n,k);
		x += m_Point[k].x      *coeff*        Power(u,k)*      Power(1-u, n-k);
		y += m_Point[k].y      *coeff*        Power(u,k)*      Power(1-u, n-k);
	}

	point.x = (int)(x+0.5);
	point.y = (int)(y+0.5);
	return point;
}

CPoint CPolyCubicDoc::GetBezierPoint2( double u)
{
	CPoint point;
	double x, y;
	int k;
	int n = 3;
	int coeff;
	
	x = 0;
	y = 0;
	for( k = 0; k < 4; k++)
	{
		coeff = GetCoefficient(n,k);
		x += m_DevidePoint[k].x      *coeff*        Power(u,k)*      Power(1-u, n-k);
		y += m_DevidePoint[k].y      *coeff*        Power(u,k)*      Power(1-u, n-k);
	}

	point.x = (int)(x+0.5);
	point.y = (int)(y+0.5);
	return point;
}

CPoint CPolyCubicDoc::GetBezierPoint3( double u)
{
	CPoint point;
	double x, y;
	int k;
	int n = 3;
	int coeff;
	
	x = 0;
	y = 0;
	for( k = 0; k < 4; k++)
	{
		coeff = GetCoefficient(n,k);
		x += m_DevidePoint[k+3].x      *coeff*        Power(u,k)*      Power(1-u, n-k);
		y += m_DevidePoint[k+3].y      *coeff*        Power(u,k)*      Power(1-u, n-k);
	}

	point.x = (int)(x+0.5);
	point.y = (int)(y+0.5);
	return point;
}


int CPolyCubicDoc::Factorial(int value)
{
	if( value <= 1 ) return 1;
	int i;
	int result = 1;
	for( i = value; i >= 2; i--)
		result = result * i;
	return result;


}

double CPolyCubicDoc::Power(double u, int k)
{
	if( k <= 0 ) return 1;
	if( u == 0 ) return 1;
	double result = 1;
	for( int i = 0; i < k; i++)
	{
		result = result * u;
	}

	return result;
}

int CPolyCubicDoc::GetCoefficient(int n, int k)
{
	int r = 1;
	for( int i = n; i > k; i--)
	{
		r = r*i;
	}

	return r/Factorial(n-k);
}

//////////////////////////////////////////////////////////////////////////

// 반으로 나누기
void CPolyCubicDoc::Devide()
{
	
	if( m_PointNum == 5 )
	{
		m_DevidePoint[0] = m_Point[0]; 

		m_DevidePoint[1].x = (int)((-m_Point[0].x + 4*m_Point[1].x)/3); 
		m_DevidePoint[1].y = (int)((-m_Point[0].y + 4*m_Point[1].y)/3);

		m_DevidePoint[2].x = (int)(( 11*m_Point[0].x     +     28*m_Point[1].x    +     18*m_Point[2].x -
									  4*m_Point[3].x     -      5*m_Point[4].x )        /48 +0.5);
		m_DevidePoint[2].y = (int)(( 11*m_Point[0].y     +     28*m_Point[1].y    +     18*m_Point[2].y -
									  4*m_Point[3].y     -      5*m_Point[4].y )        /48 +0.5);


		m_DevidePoint[3].x = (int)(( m_Point[0].x      +       4*m_Point[1].x     +     6*m_Point[2].x +
								   4*m_Point[3].x      +       m_Point[4].x )     /     16 + 0.5);
		m_DevidePoint[3].y = (int)(( m_Point[0].y      +       4*m_Point[1].y     +     6*m_Point[2].y +
								   4*m_Point[3].y      +       m_Point[4].y )     /     16 + 0.5);

		//////////////////////////////////////////////////////////////////////////
		m_DevidePoint[1].x = (m_DevidePoint[0].x + m_DevidePoint[1].x + 1)/2;
		m_DevidePoint[1].y = (m_DevidePoint[0].y + m_DevidePoint[1].y + 1)/2;

		m_DevidePoint[2].x = (m_DevidePoint[2].x + m_DevidePoint[3].x +1)/2;
		m_DevidePoint[2].y = (m_DevidePoint[2].y + m_DevidePoint[3].y +1)/2;
		//////////////////////////////////////////////////////////////////////////

		m_DevidePoint[6] = m_Point[4]; 

		m_DevidePoint[5].x = (int)((-m_Point[4].x + 4*m_Point[3].x)/3+0.5); 
		m_DevidePoint[5].y = (int)((-m_Point[4].y + 4*m_Point[3].y)/3+0.5);

		m_DevidePoint[4].x = (int)(( 11*m_Point[4].x     +     28*m_Point[3].x    +     18*m_Point[2].x -
									  4*m_Point[1].x     -      5*m_Point[0].x )        /48 +0.5);
		m_DevidePoint[4].y = (int)(( 11*m_Point[4].y     +     28*m_Point[3].y    +     18*m_Point[2].y -
									  4*m_Point[1].y     -      5*m_Point[0].y )        /48 +0.5);
		//////////////////////////////////////////////////////////////////////////
		m_DevidePoint[5].x = (m_DevidePoint[5].x + m_DevidePoint[6].x +1)/2;
		m_DevidePoint[5].y = (m_DevidePoint[5].y + m_DevidePoint[6].y +1)/2;

		m_DevidePoint[4].x = (m_DevidePoint[3].x + m_DevidePoint[4].x +1)/2;
		m_DevidePoint[4].y = (m_DevidePoint[3].y + m_DevidePoint[4].y +1)/2;
	}
	//////////////////////////////////////////////////////////////////////////	
	else // m_PointNum == 6
	{
		m_DevidePoint[0] = m_Point[0];

		m_DevidePoint[1].x = (int)((-2*m_Point[0].x + 5*m_Point[1].x)/3); 
		m_DevidePoint[1].y = (int)((-2*m_Point[0].y + 5*m_Point[1].y)/3);

		m_DevidePoint[2].x = (int)(( -7*m_Point[0].x     -     15*m_Point[1].x    +     10*m_Point[2].x +
			      50*m_Point[3].x    +45*m_Point[4].x    +     13*m_Point[5].x )        /96);
		m_DevidePoint[2].y = (int)(( -7*m_Point[0].y     -     15*m_Point[1].y    +     10*m_Point[2].y +
			      50*m_Point[3].y    +45*m_Point[4].y    +     13*m_Point[5].y )        /96);


		m_DevidePoint[3].x = (int)(( m_Point[0].x      +       5*m_Point[1].x     +     10*m_Point[2].x +
								   10*m_Point[3].x      +       5*m_Point[4].x + m_Point[5].x)/32);
		m_DevidePoint[3].y = (int)(( m_Point[0].y      +       5*m_Point[1].y     +     10*m_Point[2].y +
								   10*m_Point[3].y      +       5*m_Point[4].y + m_Point[5].y)/32);

		//////////////////////////////////////////////////////////////////////////
		m_DevidePoint[1].x = (m_DevidePoint[0].x + m_DevidePoint[1].x + 1)/2;
		m_DevidePoint[1].y = (m_DevidePoint[0].y + m_DevidePoint[1].y + 1)/2;

		m_DevidePoint[2].x = (m_DevidePoint[2].x + m_DevidePoint[3].x +1)/2;
		m_DevidePoint[2].y = (m_DevidePoint[2].y + m_DevidePoint[3].y +1)/2;

		m_DevidePoint[2].x = m_DevidePoint[3].x - (m_DevidePoint[2].x - m_DevidePoint[3].x );
		m_DevidePoint[2].y = m_DevidePoint[3].y - (m_DevidePoint[2].y - m_DevidePoint[3].y );

		//////////////////////////////////////////////////////////////////////////

		m_DevidePoint[6] = m_Point[5]; 

		m_DevidePoint[5].x = (int)((-2*m_Point[5].x + 5*m_Point[4].x)/3); 
		m_DevidePoint[5].y = (int)((-2*m_Point[5].y + 5*m_Point[4].y)/3);

		m_DevidePoint[4].x = (int)(( -7*m_Point[5].x     -     15*m_Point[4].x    +     10*m_Point[3].x +
			      50*m_Point[2].x    +45*m_Point[1].x    +     13*m_Point[0].x )        /96);
		m_DevidePoint[4].y = (int)(( -7*m_Point[5].y     -     15*m_Point[4].y    +     10*m_Point[3].y +
			      50*m_Point[2].y    +45*m_Point[1].y    +     13*m_Point[0].y )        /96);

		//////////////////////////////////////////////////////////////////////////
		m_DevidePoint[5].x = (m_DevidePoint[6].x + m_DevidePoint[5].x + 1)/2;
		m_DevidePoint[5].y = (m_DevidePoint[6].y + m_DevidePoint[5].y + 1)/2;

		m_DevidePoint[4].x = (m_DevidePoint[4].x + m_DevidePoint[3].x +1)/2;
		m_DevidePoint[4].y = (m_DevidePoint[4].y + m_DevidePoint[3].y +1)/2;

		m_DevidePoint[4].x = m_DevidePoint[3].x - (m_DevidePoint[4].x - m_DevidePoint[3].x );
		m_DevidePoint[4].y = m_DevidePoint[3].y - (m_DevidePoint[4].y - m_DevidePoint[3].y );

	}
}

void CPolyCubicDoc::DrawDevide(CDC *pDC, COLORREF color)
{
	int i;
	const int size = 100;
	for( i = 0; i < size; i++)
	{
		pDC->SetPixel(GetBezierPoint2((double)i/size), color);
		pDC->SetPixel(GetBezierPoint3((double)i/size), color);
	}
}
