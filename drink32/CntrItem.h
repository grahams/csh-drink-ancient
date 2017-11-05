// CntrItem.h : interface of the CDrinkCntrItem class
//

#if !defined(AFX_CNTRITEM_H__A0616FD2_84BA_11D3_B3AF_444553540000__INCLUDED_)
#define AFX_CNTRITEM_H__A0616FD2_84BA_11D3_B3AF_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CDrinkDoc;
class CDrinkView;

class CDrinkCntrItem : public COleClientItem
{
	DECLARE_SERIAL(CDrinkCntrItem)

// Constructors
public:
	CDrinkCntrItem(CDrinkDoc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE.
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer.

// Attributes
public:
	CDrinkDoc* GetDocument()
		{ return (CDrinkDoc*)COleClientItem::GetDocument(); }
	CDrinkView* GetActiveView()
		{ return (CDrinkView*)COleClientItem::GetActiveView(); }

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrinkCntrItem)
	public:
	virtual void OnChange(OLE_NOTIFICATION wNotification, DWORD dwParam);
	virtual void OnActivate();
	protected:
	virtual void OnGetItemPosition(CRect& rPosition);
	virtual void OnDeactivateUI(BOOL bUndoable);
	virtual BOOL OnChangeItemPosition(const CRect& rectPos);
	//}}AFX_VIRTUAL

// Implementation
public:
	~CDrinkCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	virtual void Serialize(CArchive& ar);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNTRITEM_H__A0616FD2_84BA_11D3_B3AF_444553540000__INCLUDED_)
