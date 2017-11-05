#if !defined(AFX_DROPABORTDIALOG_H__21989141_AC34_11D3_B3AF_444553540000__INCLUDED_)
#define AFX_DROPABORTDIALOG_H__21989141_AC34_11D3_B3AF_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DropAbortDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDropAbortDialog dialog

class CDropAbortDialog : public CDialog
{
// Construction
public:
	CDropAbortDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDropAbortDialog)
	enum { IDD = Drink_Drop_Abort };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDropAbortDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDropAbortDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DROPABORTDIALOG_H__21989141_AC34_11D3_B3AF_444553540000__INCLUDED_)
