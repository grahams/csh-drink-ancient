// DrinkButton.cpp : implementation file
//

#include "stdafx.h"
#include "drink.h"
#include "DrinkButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrinkButton

CDrinkButton::CDrinkButton()
{
	Bitmap = NULL;
}

CDrinkButton::~CDrinkButton()
{
	if( Bitmap != NULL )
	{
		free( Bitmap - 256 );
	}
}


BEGIN_MESSAGE_MAP(CDrinkButton, CButton)
	//{{AFX_MSG_MAP(CDrinkButton)
	ON_WM_DRAWITEM()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrinkButton message handlers

void CDrinkButton::DrawBevelRaised(CDC * pDC, CRect & rc)
{
	INT cxLeft;
	INT cy;
	INT cxRight;
	INT cx;
	INT cyTop;
	INT cyBottom;

	CPen penLight( PS_SOLID, 1, GetSysColor( COLOR_3DHILIGHT) );
	CPen penShadow( PS_SOLID, 1, GetSysColor( COLOR_3DSHADOW) );

	cx = cxLeft = rc.left;
	cy = cyTop = rc.top;
	cxRight = rc.right + 1;
	cyBottom = rc.bottom + 1;

	if( GetState() )
	{
		// if clicked, draw clicked...
		CPen *OldPen = pDC->SelectObject( &penShadow );
		for( UINT i = 0; i < 2; i++ )
		{
			pDC->MoveTo( cxLeft++, cy );
			pDC->LineTo( cxRight--, cy++ );
		}

		for( i=0; i < 2; i++ )
		{
			pDC->MoveTo( cx, cyTop++ );
			pDC->LineTo( cx++, cyBottom-- );
		}

		cxLeft = rc.left;
		cyTop = rc.top;
		cx = cxRight = rc.right - 1;
		cy = cyBottom = rc.bottom - 1;
		pDC->SelectObject( &penLight );

		for( i = 0; i < 1; i++ )
		{
			pDC->MoveTo( cxLeft++, cy );
			pDC->LineTo( cxRight--, cy-- );
		}
		for( i=0; i < 1; i++ )
		{
			pDC->MoveTo( cx, cyTop++ );
			pDC->LineTo( cx--, cyBottom-- );
		}
		pDC->SelectObject( OldPen );
	}
	else
	{
		// otherwise draw unclicked.
		CPen *OldPen = pDC->SelectObject( &penLight );

		for( UINT i = 0; i < 1; i++ )
		{
			pDC->MoveTo( cxLeft++, cy );
			pDC->LineTo( cxRight--, cy++ );
		}

		for( i=0; i < 1; i++ )
		{
			pDC->MoveTo( cx, cyTop++ );
			pDC->LineTo( cx++, cyBottom-- );
		}

		cxLeft = rc.left;
		cyTop = rc.top;
		cx = cxRight = rc.right - 1;
		cy = cyBottom = rc.bottom - 1;
		pDC->SelectObject( &penShadow );

		for( i = 0; i < 2; i++ )
		{
			pDC->MoveTo( cxLeft++, cy );
			pDC->LineTo( cxRight--, cy-- );
		}
		for( i=0; i < 2; i++ )
		{
			pDC->MoveTo( cx, cyTop++ );
			pDC->LineTo( cx--, cyBottom-- );
		}
		pDC->SelectObject( OldPen );
	}
}


void CDrinkButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your code to draw the specified item
	CDC *pDC = CDC::FromHandle( lpDrawItemStruct->hDC);
	
	CRect rc;

	this->GetClientRect( &rc );

	DrawBevelRaised( pDC, rc );
	DrawBitmap( pDC, rc );
}

void CDrinkButton::SetColorTable(COLORREF * Table)
{
	for( int i=0; i < 256; i++ )
	{
		ColorTable[i] = Table[i];
	}
	free( Table );
}

void CDrinkButton::SetBitmap(BYTE * bitmapptr)
{
	Bitmap = bitmapptr;
}

void CDrinkButton::SetWidth(UINT X)
{
	Width = X;
}

void CDrinkButton::SetHeight(UINT Y)
{
	Height = Y;
}

void CDrinkButton::DrawBitmap(CDC * pDC, CRect & rc)
{
	int i, j, k;
	int maxwidth, maxheight;
	if( Height < rc.Height() - 3 )
	{
		maxheight = Height;
	}
	else
	{
		maxheight = rc.Height() - 3;
	}
	if( Width < rc.Width() - 3 )
	{
		maxwidth = Width;
	}
	else
	{
		maxwidth = rc.Width() - 3;
	}
	if( GetState() )
	{
		k = 2;
	}
	else
	{
		k = 1;
	}

	for( i = 0; i < maxheight ; i++ )
	{
		for( j = 0; j < maxwidth; j++ )
		{
			// draw the scan line.
			pDC->SetPixel( j+k, i+k, ColorTable[ Bitmap[ ( i * Width ) + j ] ] );
		}
	}
}

