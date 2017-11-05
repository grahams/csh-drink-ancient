// OpenDialog.cpp : implementation file
//

#include "stdafx.h"
#include <afxinet.h>
#include "drink.h"
#include "OpenDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COpenDialog dialog
extern CDrinkApp theApp;


COpenDialog::COpenDialog(CWnd* pParent /*=NULL*/)
	: CDialog(COpenDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(COpenDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void COpenDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COpenDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COpenDialog, CDialog)
	//{{AFX_MSG_MAP(COpenDialog)
	ON_BN_CLICKED(IDOK, OnOpenOK)
	ON_BN_CLICKED(IDCANCEL, OnOpenCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COpenDialog message handlers

void COpenDialog::OnOpenOK() 
{
	// TODO: Add your control notification handler code here
	// find the current selection...
	// single out that server data, and create a drinkmachine with it in it.
	HTREEITEM item;
	
	item = Tree().GetSelectedItem();
	if( Tree().GetParentItem( item ) == root )
	{
		Tree().SelectItem( item );
		BuildMachine( Tree().GetItemText( item ) );
		CDialog::OnOK();
	}
	else if( item == root )
	{
		// This selection wont work. try again.
		
	}
	else
	{
		item = Tree().GetParentItem( item );
		Tree().SelectItem( item );
		BuildMachine( Tree().GetItemText( item ) );
		CDialog::OnOK();
	}
}

BOOL COpenDialog::OnInitDialog()
{
	// load from server.
	char *string;
	CInternetSession session;
	CHttpConnection* pServer = NULL;
	CHttpFile* pFile = NULL;
	CString ServerName;
	CString Object;
	INTERNET_PORT port;
	DWORD ServiceType;
	TV_INSERTSTRUCT tvstruct;
	LPTV_INSERTSTRUCT Node;
	HTREEITEM parent;
	if(!AfxParseURL(theApp.GetMetaServer(), ServiceType, ServerName, Object, port) ||
		ServiceType != INTERNET_SERVICE_HTTP)
	{
		// bad URL try again...
		pFile->Close();
		metafailed.DoModal();
		return( FALSE );
	}
	pServer = session.GetHttpConnection(ServerName, port);

	pFile = pServer->OpenRequest(CHttpConnection::HTTP_VERB_GET,
		Object, NULL, 1, NULL, NULL, INTERNET_FLAG_EXISTING_CONNECT);
	pFile->AddRequestHeaders(_T("Accept: text/*\r\nUser-Agent: Win32Drink Client\r\n"));
	pFile->SendRequest();
	DWORD dwRet;
	pFile->QueryInfoStatusCode(dwRet);
	if( dwRet != 200 )
	{
		// if status not equal to 200 then abort.
		// bad URL try again.
		pFile->Close();
		metafailed.DoModal();
		return( FALSE );
	}
	tvstruct.hParent = NULL;
	tvstruct.hInsertAfter = TVI_FIRST;
	tvstruct.item.iImage = 0;
	tvstruct.item.iSelectedImage = 0;
	tvstruct.item.pszText = ( LPTSTR )( LPCTSTR )theApp.GetMetaServer();
	tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
	root = parent = Tree().InsertItem(&tvstruct);

	TCHAR sz[1024];
	mode Mode = IDLE;
	while (pFile->ReadString(sz, 1023))
	{
		switch( Mode )
		{
			case IDLE:
				if( strstr( sz, "<MACHINE>" ) )
				{
					Mode = MACHINE;
					Node = new TV_INSERTSTRUCT;
				}
				else
				{
					// discard this line.
				}
				break;

			case MACHINE:
				if( strstr( sz, "<SERVER>" ) )
				{
					Mode = SERVER;
				}
				else if( strstr( sz, "<MACHINENAME>" ) )
				{
					Mode = MACHINENAME;
				}
				else if( strstr( sz, "<SLOT>" ) )
				{
					Mode = SLOT;
				}
				else if( strstr( sz, "<LOCATION>" ) )
				{
					Mode = LOCATION;
				}
				else if( strstr( sz, "</MACHINE>" ) )
				{
					Mode = IDLE;
				}
				else
				{
				}
				break;

			case SLOT:
				if( strstr( sz, "<NAME>" ) )
				{
					Mode = NAME;
					Node = new TV_INSERTSTRUCT;
				}
				else if( strstr( sz, "<IMAGE>" ) )
				{
					Mode = IMAGE;
				}
				else if( strstr( sz, "</SLOT>" ) )
				{
					Mode = MACHINE;
				}
				else
				{
				}
				break;

			case SERVER:
				if( strstr( sz, "</SERVER>" ) )
				{
					Mode = MACHINE;
				}
				else
				{
					// server URL is sz - whitespace.
				}
				break;

			case LOCATION:
				if( strstr( sz, "</LOCATION>" ) )
				{
					Mode = MACHINE;
				}
				else
				{
					// machine location is sz - whitespace.
				}
				break;

			case NAME:
				if( strstr( sz, "</NAME>" ) )
				{
					Mode = SLOT;
					Node->hParent = parent;
					Node->hInsertAfter = TVI_LAST;
					Node->item.iImage = 0;
					Node->item.iSelectedImage = 0;
					Node->item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
					Tree().InsertItem(Node);
					Tree().Expand( parent, TVE_EXPAND );
				}
				else
				{
					// slot name is sz - whitespace.
					string = (char *)malloc( strlen( sz ) -1);
					strncpy( string, sz, strlen( sz ) -1);
					string[ strlen( sz ) -1] = '\0';
					Node->item.pszText = string;
				}
				break;

			case IMAGE:
				if( strstr( sz, "</IMAGE>" ) )
				{
					Mode = SLOT;
				}
				else
				{
					// name of slot image is sz - whitespace.
				}
				break;

			case MACHINENAME:
				if( strstr( sz, "</MACHINENAME>" ) )
				{
					Mode = MACHINE;
					Node->hParent = root;
					Node->hInsertAfter = parent;
					Node->item.iImage = 0;
					Node->item.iSelectedImage = 0;
					Node->item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
					Tree().Expand( parent, TVE_EXPAND );
					parent = Tree().InsertItem(Node);
				}
				else
				{
					// machine name is sz - whitespace.
					string = (char *)malloc( strlen( sz ) -1);
					strncpy( string, sz, strlen( sz ) -1);
					string[ strlen( sz ) -1] = '\0';
					Node->item.pszText = string;
				}
				break;

			default:
				break;
		}
	}
	return( TRUE );
}

CTreeCtrl & COpenDialog::Tree()
{
	return *(CTreeCtrl*) GetDlgItem(Drink_OpenTree);
}

void COpenDialog::OnOpenCancel() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

void COpenDialog::BuildMachine(CString name)
{
	CInternetSession session;
	CHttpConnection* pServer = NULL;
	CHttpFile* pFile = NULL;
	CString ServerName;
	CString Object;
	INTERNET_PORT port;
	DWORD ServiceType;
	DrinkMachine * newMachine;
	DrinkSlot * slot;


	if(!AfxParseURL(theApp.GetMetaServer(), ServiceType, ServerName, Object, port) ||
		ServiceType != INTERNET_SERVICE_HTTP)
	{
		// bad URL try again...
		metafailed.DoModal();
		return;
	}
	pServer = session.GetHttpConnection(ServerName, port);

	pFile = pServer->OpenRequest(CHttpConnection::HTTP_VERB_GET,
		Object, NULL, 1, NULL, NULL, INTERNET_FLAG_EXISTING_CONNECT);
	pFile->AddRequestHeaders(_T("Accept: text/*\r\nUser-Agent: Win32Drink Client\r\n"));
	pFile->SendRequest();
	DWORD dwRet;
	pFile->QueryInfoStatusCode(dwRet);
	if( dwRet != 200 )
	{
		// if status not equal to 200 then abort.
		// bad URL try again.
		metafailed.DoModal();
		return;
	}


	TCHAR sz[1024];
	mode Mode = IDLE;
	while (pFile->ReadString(sz, 1023))
	{
		switch( Mode )
		{
			case IDLE:
				if( strstr( sz, "<MACHINE>" ) )
				{
					Mode = MACHINE;
				}
				else
				{
					// discard this line.
				}
				break;

			case MACHINE:
				if( strstr( sz, "<SERVER>" ) )
				{
					Mode = SERVER;
				}
				else if( strstr( sz, "<MACHINENAME>" ) )
				{
					Mode = MACHINENAME;
				}
				else if( strstr( sz, "<IMAGE>" ) )
				{
					Mode = MACHINEIMAGE;
				}
				else if( strstr( sz, "<SLOT>" ) )
				{
					Mode = SLOT;
					slot = new DrinkSlot;
				}
				else if( strstr( sz, "<LOCATION>" ) )
				{
					Mode = LOCATION;
				}
				else if( strstr( sz, "</MACHINE>" ) )
				{
					Mode = IDLE;
					// save our Drink Machine
					theApp.AddMachine( newMachine );
					theApp.Current_Machine = newMachine;
				}
				else
				{
				}
				break;

			case MACHINEIMAGE:
				if( strstr( sz, "</IMAGE>" ) )
				{
					Mode = MACHINE;
				}
				else
				{
					sz[strlen( sz ) -1] = '\0';
					newMachine->SetImageURL( CString( sz ) );
				}

			case SLOT:
				if( strstr( sz, "<NAME>" ) )
				{
					Mode = NAME;
				}
				else if( strstr( sz, "<IMAGE>" ) )
				{
					Mode = IMAGE;
				}
				else if( strstr( sz, "</SLOT>" ) )
				{
					Mode = MACHINE;
					newMachine->AddSlot( slot );
				}
				else
				{
				}
				break;

			case SERVER:
				if( strstr( sz, "</SERVER>" ) )
				{
					Mode = MACHINE;
				}
				else
				{
					sz[strlen( sz ) -1] = '\0';
					newMachine->SetMachineURL( CString( sz ) );
				}
				break;

			case LOCATION:
				if( strstr( sz, "</LOCATION>" ) )
				{
					Mode = MACHINE;
				}
				else
				{
					sz[strlen( sz ) -1] = '\0';
					newMachine->SetLocation( CString( sz ) );
				}
				break;

			case NAME:
				if( strstr( sz, "</NAME>" ) )
				{
					Mode = SLOT;
				}
				else
				{
					sz[strlen( sz ) -1] = '\0';
					slot->SetName( CString( sz ) );
				}
				break;

			case IMAGE:
				if( strstr( sz, "</IMAGE>" ) )
				{
					Mode = SLOT;
				}
				else
				{
					sz[strlen( sz ) -1] = '\0';
					slot->SetImageURL( CString( sz ) );
				}
				break;

			case MACHINENAME:
				if( strstr( sz, "</MACHINENAME>" ) )
				{
					Mode = MACHINE;
				}
				else
				{
					if( strstr( sz, (LPCSTR) (LPCTSTR)name ) )
					{
						// this is our machine.
						newMachine = new DrinkMachine;
						newMachine->SetMachineName( name );
					}
					else
					{
						Mode = IDLE;
					}
				}
				break;

			default:
				break;
		}
	}

}
