// ChildFrm.h : interface of the CChildFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDFRM_H__A0616FCB_84BA_11D3_B3AF_444553540000__INCLUDED_)
#define AFX_CHILDFRM_H__A0616FCB_84BA_11D3_B3AF_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	afx_msg void OnWindowPosChanged( WINDOWPOS* lpwndpos );
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	LPWINDOWPOS Wind;
	afx_msg void OnWindowPosChanging(LPWINDOWPOS lpWndPos);
	afx_msg void OnSizing( UINT nSide, LPRECT lpRect);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//{{AFX_MSG(CChildFrame)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDFRM_H__A0616FCB_84BA_11D3_B3AF_444553540000__INCLUDED_)
