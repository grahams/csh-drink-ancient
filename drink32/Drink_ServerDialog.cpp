// Drink_ServerDialog.cpp : implementation file
//

#include "stdafx.h"
#include "drink.h"
#include "Drink_ServerDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Drink_ServerDialog dialog
extern CDrinkApp theApp;


Drink_ServerDialog::Drink_ServerDialog(CWnd* pParent /*=NULL*/)
	: CDialog(Drink_ServerDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(Drink_ServerDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Drink_ServerDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Drink_ServerDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP

	DDX_Text(pDX, Drink_ServerEdit, Server);
	DDV_MaxChars(pDX, Server, 512);
}


BEGIN_MESSAGE_MAP(Drink_ServerDialog, CDialog)
	//{{AFX_MSG_MAP(Drink_ServerDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Drink_ServerDialog message handlers

BOOL Drink_ServerDialog::OnInitDialog()
{
	CString temp;

	Server = theApp.GetMetaServer();

	server().SetWindowText( Server );

	CDialog::OnInitDialog();
	return( TRUE );
}

CButton & Drink_ServerDialog::server()
{
	return *(CButton*) GetDlgItem(Drink_ServerEdit);
}


void Drink_ServerDialog::OnOK() 
{
	// TODO: Add extra validation here

	UpdateData();

	theApp.SetMetaServer( Server );

	CDialog::OnOK();
}
