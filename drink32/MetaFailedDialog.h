#if !defined(AFX_METAFAILEDDIALOG_H__FC5358E1_B578_11D3_B3AF_444553540000__INCLUDED_)
#define AFX_METAFAILEDDIALOG_H__FC5358E1_B578_11D3_B3AF_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MetaFailedDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMetaFailedDialog dialog

class CMetaFailedDialog : public CDialog
{
// Construction
public:
	CMetaFailedDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMetaFailedDialog)
	enum { IDD = Drink_Meta_FailedDialog };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMetaFailedDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMetaFailedDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_METAFAILEDDIALOG_H__FC5358E1_B578_11D3_B3AF_444553540000__INCLUDED_)
