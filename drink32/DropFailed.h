#if !defined(AFX_DROPFAILED_H__3B250CC1_A698_11D3_B3AF_444553540000__INCLUDED_)
#define AFX_DROPFAILED_H__3B250CC1_A698_11D3_B3AF_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DropFailed.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDropFailed dialog

class CDropFailed : public CDialog
{
// Construction
public:
	CDropFailed(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDropFailed)
	enum { IDD = Drink_Drop_Failed };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDropFailed)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDropFailed)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DROPFAILED_H__3B250CC1_A698_11D3_B3AF_444553540000__INCLUDED_)
