#if !defined(AFX_DRINKBUTTON_H__2D5F7D61_C091_11D3_B3AF_444553540000__INCLUDED_)
#define AFX_DRINKBUTTON_H__2D5F7D61_C091_11D3_B3AF_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DrinkButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDrinkButton window

class CDrinkButton : public CButton
{
// Construction
public:
	CDrinkButton();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrinkButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetHeight( UINT Y );
	void SetWidth( UINT X );
	void SetBitmap( BYTE *bitmapptr );
	void SetColorTable( COLORREF *Table );
	void DrawBevelRaised( CDC *pDC, CRect& rc);
	virtual ~CDrinkButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDrinkButton)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	void DrawBitmap( CDC *pDC, CRect &rc );
	UINT Width;
	UINT Height;
	BYTE * Bitmap;
	COLORREF ColorTable[256];
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRINKBUTTON_H__2D5F7D61_C091_11D3_B3AF_444553540000__INCLUDED_)
