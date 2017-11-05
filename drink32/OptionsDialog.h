#if !defined(AFX_OPTIONSDIALOG_H__780A2E62_8599_11D3_B3AF_444553540000__INCLUDED_)
#define AFX_OPTIONSDIALOG_H__780A2E62_8599_11D3_B3AF_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#include "afxtempl.h"
#include "dropsuccess.h"
// OptionsDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COptionsDialog dialog

class COptionsDialog : public CDialog
{
// Construction
public:
	CButton & Server();
	CButton & SaveUser();
	 ~COptionsDialog();
	COptionsDialog(CWnd* pParent = NULL);   // standard constructor
	BOOL OnInitDialog();

// Dialog Data
	//{{AFX_DATA(COptionsDialog)
	enum { IDD = Drink_Options_Dialog };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptionsDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COptionsDialog)
	afx_msg void OnOptionsOK();
	afx_msg void OnOptionsCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString server;

	CTypedPtrArray<CObArray, CButton *> buttons;

	CButton & Delay();
	CButton & AutoOpen();
	CButton & AutoLogin();
	CButton & gamble();
	
	
	unsigned long int Drop_Delay;
	int Gamble;
	int Auto_Login;
	int Save_User;
	int Auto_Open;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSDIALOG_H__780A2E62_8599_11D3_B3AF_444553540000__INCLUDED_)
