#if !defined(AFX_INVALIDLOGINDIALOG_H__F52DFEA2_94B5_11D3_B3AF_444553540000__INCLUDED_)
#define AFX_INVALIDLOGINDIALOG_H__F52DFEA2_94B5_11D3_B3AF_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// InvalidLoginDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInvalidLoginDialog dialog

class CInvalidLoginDialog : public CDialog
{
// Construction
public:
	CInvalidLoginDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInvalidLoginDialog)
	enum { IDD = Drink_LoginInvalid };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInvalidLoginDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInvalidLoginDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INVALIDLOGINDIALOG_H__F52DFEA2_94B5_11D3_B3AF_444553540000__INCLUDED_)
