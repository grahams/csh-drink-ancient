// drinkDoc.cpp : implementation of the CDrinkDoc class
//

#include "stdafx.h"
#include "drink.h"

#include "drinkDoc.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrinkDoc

IMPLEMENT_DYNCREATE(CDrinkDoc, COleDocument)

BEGIN_MESSAGE_MAP(CDrinkDoc, COleDocument)
	//{{AFX_MSG_MAP(CDrinkDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Enable default OLE container implementation
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, COleDocument::OnUpdatePasteMenu)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE_LINK, COleDocument::OnUpdatePasteLinkMenu)
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_CONVERT, COleDocument::OnUpdateObjectVerbMenu)
	ON_COMMAND(ID_OLE_EDIT_CONVERT, COleDocument::OnEditConvert)
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, COleDocument::OnUpdateEditLinksMenu)
	ON_COMMAND(ID_OLE_EDIT_LINKS, COleDocument::OnEditLinks)
	ON_UPDATE_COMMAND_UI(ID_OLE_VERB_FIRST, COleDocument::OnUpdateObjectVerbMenu)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrinkDoc construction/destruction

CDrinkDoc::CDrinkDoc()
{
	// Use OLE compound files
	EnableCompoundFile();

	// TODO: add one-time construction code here

}

CDrinkDoc::~CDrinkDoc()
{
}

BOOL CDrinkDoc::OnNewDocument()
{
	if (!COleDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDrinkDoc serialization

void CDrinkDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}

	// Calling the base class COleDocument enables serialization
	//  of the container document's COleClientItem objects.
	COleDocument::Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CDrinkDoc diagnostics

#ifdef _DEBUG
void CDrinkDoc::AssertValid() const
{
	COleDocument::AssertValid();
}

void CDrinkDoc::Dump(CDumpContext& dc) const
{
	COleDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDrinkDoc commands
