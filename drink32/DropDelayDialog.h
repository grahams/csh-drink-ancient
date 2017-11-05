#if !defined(AFX_DROPDELAYDIALOG_H__2685D262_9089_11D3_B3AF_444553540000__INCLUDED_)
#define AFX_DROPDELAYDIALOG_H__2685D262_9089_11D3_B3AF_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DropDelayDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDropDelayDialog dialog

class CDropDelayDialog : public CDialog
{
// Construction
public:
	CButton & Delay();
	BOOL OnInitDialog();
	CDropDelayDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDropDelayDialog)
	enum { IDD = Drink_DropDelay_Dialog };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDropDelayDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDropDelayDialog)
	afx_msg void OnDrop();
	afx_msg void OnDropCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	unsigned long int Drop_Delay;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DROPDELAYDIALOG_H__2685D262_9089_11D3_B3AF_444553540000__INCLUDED_)
