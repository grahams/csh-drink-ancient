#if !defined(AFX_DRINK_META_FAILEDDIALOG_H__D6D36001_B30D_11D3_B3AF_444553540000__INCLUDED_)
#define AFX_DRINK_META_FAILEDDIALOG_H__D6D36001_B30D_11D3_B3AF_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Drink_Meta_FailedDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Drink_Meta_FailedDialog dialog

class Drink_MetaDialog : public CDialog
{
// Construction
public:
	Drink_Meta_FailedDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Drink_Meta_FailedDialog)
	enum { IDD = Drink_Meta_FailedDialog };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Drink_Meta_FailedDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Drink_Meta_FailedDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRINK_META_FAILEDDIALOG_H__D6D36001_B30D_11D3_B3AF_444553540000__INCLUDED_)
