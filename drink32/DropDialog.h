#if !defined(AFX_DROPDIALOG_H__2685D261_9089_11D3_B3AF_444553540000__INCLUDED_)
#define AFX_DROPDIALOG_H__2685D261_9089_11D3_B3AF_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DropDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDropDialog dialog

class CDropDialog : public CDialog
{
// Construction
public:
	CDropDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDropDialog)
	enum { IDD = Drink_Drop_Dialog };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDropDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDropDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DROPDIALOG_H__2685D261_9089_11D3_B3AF_444553540000__INCLUDED_)
