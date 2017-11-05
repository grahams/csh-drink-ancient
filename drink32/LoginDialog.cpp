// LoginDialog.cpp : implementation file
//

#include "stdafx.h"
#include "drink.h"
#include "LoginDialog.h"
#include "InvalidLoginDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoginDialog dialog

extern CDrinkApp theApp;


CLoginDialog::CLoginDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLoginDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CLoginDialog::DoDataExchange(CDataExchange* pDX)
{

	//{{AFX_DATA_MAP(CLoginDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_Text(pDX, Drink_LoginUsername, Username);
   DDV_MaxChars(pDX, Username, 50);
	
	DDX_Text(pDX, Drink_LoginPassword, Password);
	DDV_MaxChars(pDX, Password, 50);

	DDX_Check( pDX, Drink_LoginSave, Store_UserPass );
	DDV_MinMaxInt( pDX, Store_UserPass, false, true );

	CDialog::DoDataExchange(pDX);

}


BEGIN_MESSAGE_MAP(CLoginDialog, CDialog)
	//{{AFX_MSG_MAP(CLoginDialog)
	ON_WM_CHAR()
	ON_BN_CLICKED(Drink_LoginOK, OnLoginLogin)
	ON_BN_CLICKED(Drink_LoginCANCEL, OnLoginCANCEL)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoginDialog message handlers

BEGIN_EVENTSINK_MAP(CLoginDialog, CDialog)
    //{{AFX_EVENTSINK_MAP(CLoginDialog)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()


CButton & CLoginDialog::EditUsername()
{
	return *(CButton*) GetDlgItem(Drink_LoginUsername);
}

CButton & CLoginDialog::EditPassword()
{
	return *(CButton*) GetDlgItem(Drink_LoginPassword);
}

CButton & CLoginDialog::SavePassword()
{
	return *(CButton*) GetDlgItem(Drink_LoginSave);
}


BOOL CLoginDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	EditUsername().SetWindowText( *(theApp.currentMachine()->GetUsername()) );
	EditPassword().SetWindowText( *(theApp.currentMachine()->GetPassword()) );
	SavePassword().SetCheck( theApp.currentMachine()->UserPassStored() );

	EditUsername().EnableWindow(TRUE);
	EditPassword().EnableWindow(TRUE);
	//EditUsername().SetWindowText("I am a nom-nom" );
	return( TRUE );
}

void CLoginDialog::OnLoginLogin() 
{
	CInvalidLoginDialog message;
	// TODO: Add your control notification handler code here
	// validate Username and Password
   // Call the inherited handler
	UpdateData();
	if( !(theApp.currentMachine()->Validate( Username, Password, Store_UserPass ) ) )
	{
		// login invalid
		message.DoModal();
	}
	else
	{
		CDialog::OnOK();
	}
}

void CLoginDialog::OnLoginCANCEL() 
{
		// TODO: Add your control notification handler code here
	UpdateData();

	theApp.currentMachine()->StoreUserPass( Store_UserPass ); 
	CDialog::OnCancel();	
}




CButton & CLoginDialog::savebtn()
{
	return( *(CButton*) GetDlgItem( Drink_LoginSave ) );
}

void CLoginDialog::save_UserPass()
{
	Store_UserPass = true;
}

void CLoginDialog::discard_UserPass()
{
	Store_UserPass = false;
	Password = "";
	Username = "";
}
