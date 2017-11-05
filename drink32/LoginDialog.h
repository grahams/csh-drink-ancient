#if !defined(AFX_LOGINDIALOG_H__780A2E61_8599_11D3_B3AF_444553540000__INCLUDED_)
#define AFX_LOGINDIALOG_H__780A2E61_8599_11D3_B3AF_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#include "drink.h"
// LoginDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLoginDialog dialog

class CLoginDialog : public CDialog
{
// Construction
public:
	void discard_UserPass();
	void save_UserPass();
	BOOL OnInitDialog();
	CLoginDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLoginDialog)
	enum { IDD = Drink_Login_Dialog };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoginDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString Username;
	CString Password;

	// Generated message map functions
	//{{AFX_MSG(CLoginDialog)
	afx_msg void OnLoginLogin();
	afx_msg void OnLoginCANCEL();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CButton & savebtn();
	BOOL Store_UserPass;
	CButton & EditPassword();
	CButton & EditUsername();
	CButton & SavePassword();
};



//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGINDIALOG_H__780A2E61_8599_11D3_B3AF_444553540000__INCLUDED_)
