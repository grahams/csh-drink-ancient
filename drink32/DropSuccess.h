#if !defined(AFX_DROPSUCCESS_H__3B250CC2_A698_11D3_B3AF_444553540000__INCLUDED_)
#define AFX_DROPSUCCESS_H__3B250CC2_A698_11D3_B3AF_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DropSuccess.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDropSuccess dialog

class CDropSuccess : public CDialog
{
// Construction
public:
	CDropSuccess(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDropSuccess)
	enum { IDD = Drink_Drop_Successful };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDropSuccess)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDropSuccess)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DROPSUCCESS_H__3B250CC2_A698_11D3_B3AF_444553540000__INCLUDED_)
