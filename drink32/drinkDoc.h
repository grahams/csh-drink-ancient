// drinkDoc.h : interface of the CDrinkDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRINKDOC_H__A0616FCD_84BA_11D3_B3AF_444553540000__INCLUDED_)
#define AFX_DRINKDOC_H__A0616FCD_84BA_11D3_B3AF_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CDrinkDoc : public COleDocument
{
protected: // create from serialization only
	CDrinkDoc();
	DECLARE_DYNCREATE(CDrinkDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrinkDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDrinkDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDrinkDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRINKDOC_H__A0616FCD_84BA_11D3_B3AF_444553540000__INCLUDED_)
