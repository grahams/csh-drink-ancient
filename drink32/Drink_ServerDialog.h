#if !defined(AFX_DRINK_SERVERDIALOG_H__91607661_B01B_11D3_B3AF_444553540000__INCLUDED_)
#define AFX_DRINK_SERVERDIALOG_H__91607661_B01B_11D3_B3AF_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Drink_ServerDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Drink_ServerDialog dialog

class Drink_ServerDialog : public CDialog
{
// Construction
public:
	CButton & server();
	BOOL OnInitDialog();
	Drink_ServerDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Drink_ServerDialog)
	enum { IDD = Drink_Server_Dialog };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Drink_ServerDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Drink_ServerDialog)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString Server;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRINK_SERVERDIALOG_H__91607661_B01B_11D3_B3AF_444553540000__INCLUDED_)
