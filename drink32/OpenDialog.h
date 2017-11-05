#if !defined(AFX_OPENDIALOG_H__17BA5B21_931D_11D3_B3AF_444553540000__INCLUDED_)
#define AFX_OPENDIALOG_H__17BA5B21_931D_11D3_B3AF_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// OpenDialog.h : header file
//
#include "MetaFailedDialog.h"

/////////////////////////////////////////////////////////////////////////////
// COpenDialog dialog

class COpenDialog : public CDialog
{
// Construction
public:
	CTreeCtrl & Tree();
	BOOL OnInitDialog();
	COpenDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COpenDialog)
	enum { IDD = Drink_Open };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COpenDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COpenDialog)
	afx_msg void OnOpenOK();
	afx_msg void OnOpenCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void BuildMachine( CString name );
	HTREEITEM root;
	CMetaFailedDialog metafailed;
};
enum mode
{
	IDLE = 0,
	MACHINE,
	MACHINENAME,
	MACHINEIMAGE,
	SERVER,
	SLOT,
	LOCATION,
	NAME,
	IMAGE
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPENDIALOG_H__17BA5B21_931D_11D3_B3AF_444553540000__INCLUDED_)
