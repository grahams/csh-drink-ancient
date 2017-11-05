// drinkView.h : interface of the CDrinkView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRINKVIEW_H__A0616FCF_84BA_11D3_B3AF_444553540000__INCLUDED_)
#define AFX_DRINKVIEW_H__A0616FCF_84BA_11D3_B3AF_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "drinkmachine.h"
#include "drinkdoc.h"
#include "afxtempl.h"
#include "DropFailed.h"	// Added by ClassView
#include "DropSuccess.h"	// Added by ClassView
#include "DropDialog.h"	// Added by ClassView
#include "DropAbortDialog.h"	// Added by ClassView
#include "DropDelayDialog.h"	// Added by ClassView
#include "GifStream.h"	// Added by ClassView

class CDrinkCntrItem;

class CDrinkView : public CView
{
protected: // create from serialization only
	CDrinkView();
	DECLARE_DYNCREATE(CDrinkView)

// Attributes
public:
	CDrinkDoc* GetDocument();
	// m_pSelection holds the selection to the current CDrinkCntrItem.
	// For many applications, such a member variable isn't adequate to
	//  represent a selection, such as a multiple selection or a selection
	//  of objects that are not CDrinkCntrItem objects.  This selection
	//  mechanism is provided just to help you get started.

	// TODO: replace this selection mechanism with one appropriate to your app.
	CDrinkCntrItem* m_pSelection;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrinkView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL IsSelected(const CObject* pDocItem) const;// Container support
	//}}AFX_VIRTUAL

// Implementation
public:
	void AbortDrop();
	unsigned int GetCurrent_Machine_Num();
	void SetMacNum( unsigned int num );
	void PlaceButton( DrinkSlot *slot, int i );
	void CreateChildControls();
	CString userersstr;
	virtual ~CDrinkView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	CTypedPtrArray<CObArray, CButton *> buttons;

// Generated message map functions
protected:
	//{{AFX_MSG(CDrinkView)
	afx_msg void OnDestroy();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnInsertObject();
	afx_msg void OnCancelEditCntr();
	afx_msg void OnAppExit();
	afx_msg void OnSelect();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	GifStream GifLoader;
	CDropDelayDialog Drop;
	CDropAbortDialog DropAbort;
	int abort;
	CDropSuccess DropSuccess;
	CDropFailed DropFail;
	unsigned int machine_number;
};

#ifndef _DEBUG  // debug version in drinkView.cpp
inline CDrinkDoc* CDrinkView::GetDocument()
   { return (CDrinkDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRINKVIEW_H__A0616FCF_84BA_11D3_B3AF_444553540000__INCLUDED_)
