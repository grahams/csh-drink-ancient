// drinkView.cpp : implementation of the CDrinkView class
//

#include "stdafx.h"
#include "drink.h"

#include "drinkDoc.h"
#include "CntrItem.h"
#include "drinkView.h"
#include "drinkbutton.h"
#include <process.h>
#include "afxinet.h"
#include "GifStream.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrinkView
extern CDrinkApp theApp;


IMPLEMENT_DYNCREATE(CDrinkView, CView)

BEGIN_MESSAGE_MAP(CDrinkView, CView)
	//{{AFX_MSG_MAP(CDrinkView)
	ON_WM_DESTROY()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_COMMAND(ID_OLE_INSERT_NEW, OnInsertObject)
	ON_COMMAND(ID_CANCEL_EDIT_CNTR, OnCancelEditCntr)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_APP_EXIT, OnAppExit)
	ON_COMMAND(Drink_MainSelect, OnSelect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrinkView construction/destruction

CDrinkView::CDrinkView()
{
	abort = 0;
	machine_number = 0;
	m_pSelection = NULL;
	// TODO: add construction code here
}

CDrinkView::~CDrinkView()
{
	for( int i=0; i < buttons.GetSize(); i++ )
	{
		delete buttons[i];
	}
	buttons.RemoveAll();
}

BOOL CDrinkView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDrinkView drawing

void CDrinkView::OnDraw(CDC* pDC)
{
	CDrinkDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
	// TODO: also draw all OLE items in the document

	// Draw the selection at an arbitrary position.  This code should be
	//  removed once your real drawing code is implemented.  This position
	//  corresponds exactly to the rectangle returned by CDrinkCntrItem,
	//  to give the effect of in-place editing.

	// TODO: remove this code when final draw code is complete.

	if (m_pSelection == NULL)
	{
		POSITION pos = pDoc->GetStartPosition();
		m_pSelection = (CDrinkCntrItem*)pDoc->GetNextClientItem(pos);
	}
	if (m_pSelection != NULL)
		m_pSelection->Draw(pDC, CRect(10, 10, 210, 210));
}

void CDrinkView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: remove this code when final selection model code is written
	m_pSelection = NULL;    // initialize selection

}

void CDrinkView::OnDestroy()
{
	// Deactivate the item on destruction; this is important
	// when a splitter view is being used.
   CView::OnDestroy();
   COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
   if (pActiveItem != NULL && pActiveItem->GetActiveView() == this)
   {
      pActiveItem->Deactivate();
      ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
   }
}


/////////////////////////////////////////////////////////////////////////////
// OLE Client support and commands

BOOL CDrinkView::IsSelected(const CObject* pDocItem) const
{
	// The implementation below is adequate if your selection consists of
	//  only CDrinkCntrItem objects.  To handle different selection
	//  mechanisms, the implementation here should be replaced.

	// TODO: implement this function that tests for a selected OLE client item

	return pDocItem == m_pSelection;
}

void CDrinkView::OnInsertObject()
{
	// Invoke the standard Insert Object dialog box to obtain information
	//  for new CDrinkCntrItem object.
	COleInsertDialog dlg;
	if (dlg.DoModal() != IDOK)
		return;

	BeginWaitCursor();

	CDrinkCntrItem* pItem = NULL;
	TRY
	{
		// Create new item connected to this document.
		CDrinkDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pItem = new CDrinkCntrItem(pDoc);
		ASSERT_VALID(pItem);

		// Initialize the item from the dialog data.
		if (!dlg.CreateItem(pItem))
			AfxThrowMemoryException();  // any exception will do
		ASSERT_VALID(pItem);

		// If item created from class list (not from file) then launch
		//  the server to edit the item.
		if (dlg.GetSelectionType() == COleInsertDialog::createNewItem)
			pItem->DoVerb(OLEIVERB_SHOW, this);

		ASSERT_VALID(pItem);

		// As an arbitrary user interface design, this sets the selection
		//  to the last item inserted.

		// TODO: reimplement selection as appropriate for your application

		m_pSelection = pItem;   // set selection to last inserted item
		pDoc->UpdateAllViews(NULL);
	}
	CATCH(CException, e)
	{
		if (pItem != NULL)
		{
			ASSERT_VALID(pItem);
			pItem->Delete();
		}
		AfxMessageBox(IDP_FAILED_TO_CREATE);
	}
	END_CATCH

	EndWaitCursor();
}

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the container (not the server) causes the deactivation.
void CDrinkView::OnCancelEditCntr()
{
	// Close any in-place active item on this view.
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL)
	{
		pActiveItem->Close();
	}
	ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
}

// Special handling of OnSetFocus and OnSize are required for a container
//  when an object is being edited in-place.
void CDrinkView::OnSetFocus(CWnd* pOldWnd)
{
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL &&
		pActiveItem->GetItemState() == COleClientItem::activeUIState)
	{
		// need to set focus to this item if it is in the same view
		CWnd* pWnd = pActiveItem->GetInPlaceWindow();
		if (pWnd != NULL)
		{
			pWnd->SetFocus();   // don't call the base class
			return;
		}
	}

	CView::OnSetFocus(pOldWnd);
}

void CDrinkView::OnSize(UINT nType, int cx, int cy)
{	
}

/////////////////////////////////////////////////////////////////////////////
// CDrinkView diagnostics

#ifdef _DEBUG
void CDrinkView::AssertValid() const
{
	CView::AssertValid();
}

void CDrinkView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDrinkDoc* CDrinkView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrinkDoc)));
	return (CDrinkDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDrinkView message handlers


void CDrinkView::OnSelect()
{
	// figure out which button it is, and try to drop that slot.
	for( unsigned int i = 0; i < buttons.GetSize() ; i++ )
	{
		if( buttons[i]->GetState() )
		{
			Drop.DoModal();
			if( !abort )
			{
				// i'th button is clicked.
				if( !( theApp.GetMachine( machine_number )->DropSlot( i ) ) )
				{
					// warn about drop failed
					DropFail.DoModal();
				}
				else
				{
					// warn about drop succeeded
					DropSuccess.DoModal();
				}
			}
			else
			{
				abort = 0;
				DropAbort.DoModal();
			}
		}
	}

}



void CDrinkView::CreateChildControls()
{
}

void CDrinkView::OnAppExit() 
{
	// TODO: Add your command handler code here
	exit(0);	
}

void CDrinkView::PlaceButton( DrinkSlot * slot, int i)
{
	// find out if there is a cached version of our file.
	CString CacheFileName = slot->GetName();
	CacheFileName += ".BMP";
	CFile CacheFile;
	if( CacheFile.Open( (LPCTSTR) CacheFileName, CFile::modeRead ) )
	{

		GifLoader.LoadCache( &CacheFile, CacheFileName );
		CDrinkButton * temp;
		temp = new CDrinkButton;
		temp->SetBitmap( GifLoader.GetImageData() );
		temp->SetHeight( GifLoader.GetImageHeight() );
		temp->SetWidth( GifLoader.GetImageWidth() );
		temp->SetColorTable( GifLoader.GetColorTable() );
		temp->Create( "foo", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, CRect( 4 + ( 47 * i ), 4, 47 + (47 * i), 87 ), this, Drink_MainSelect);
		buttons.Add( temp );
	}
	else
	{
		// we need to go and get the copy from the server.

		CInternetSession session;
		CHttpConnection* pServer = NULL;
		CHttpFile* pFile = NULL;
		CString ServerName;
		CString Object;
		INTERNET_PORT port;
		DWORD ServiceType;

		if(!AfxParseURL(slot->GetImageURL(), ServiceType, ServerName, Object, port) ||
			ServiceType != INTERNET_SERVICE_HTTP)
		{
			// bad URL try again...
			CButton * temp;
			temp = new CButton;
			temp->Create( slot->GetName(), BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD, CRect( 4 + ( 47 * i ), 4, 47 + (47 * i), 87 ), this, Drink_MainSelect);
			buttons.Add( temp );
		}
		else
		{
			pServer = session.GetHttpConnection(ServerName, port);

			pFile = pServer->OpenRequest(CHttpConnection::HTTP_VERB_GET,
				Object, NULL, 1, NULL, NULL, INTERNET_FLAG_EXISTING_CONNECT);
			pFile->AddRequestHeaders(_T("Accept: image/gif\r\nUser-Agent: Win32Drink Client\r\n"));
			pFile->SendRequest();
			DWORD dwRet;
			pFile->QueryInfoStatusCode(dwRet);
			if( dwRet != 200 )
			{
				// if status not equal to 200 then abort.
				CButton * temp;
				temp = new CButton;
				temp->Create( slot->GetName(), BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD, CRect( 4 + ( 47 * i ), 4, 47 + (47 * i), 87 ), this, Drink_MainSelect);
				buttons.Add( temp );
			}
			else
			{
				// file is open and valid. load it.
				GifLoader.LoadGif( pFile, CacheFileName );
				CDrinkButton * temp;
				temp = new CDrinkButton;
				temp->SetBitmap( GifLoader.GetImageData() );
				temp->SetHeight( GifLoader.GetImageHeight() );
				temp->SetWidth( GifLoader.GetImageWidth() );
				temp->SetColorTable( GifLoader.GetColorTable() );
				temp->Create( "foo", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, CRect( 4 + ( 47 * i ), 4, 47 + (47 * i), 87 ), this, Drink_MainSelect);
				buttons.Add( temp );
			}
		}
		
		
		
		
		
		
	}


}


void CDrinkView::SetMacNum(unsigned int num)
{
	machine_number = num;
}

unsigned int CDrinkView::GetCurrent_Machine_Num()
{
	return( machine_number );
}

void CDrinkView::AbortDrop()
{
	abort = 1;
}
