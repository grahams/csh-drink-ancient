// OptionsDialog.cpp : implementation file
//

#include "stdafx.h"
#include "drink.h"
#include "OptionsDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionsDialog dialog

extern CDrinkApp theApp;


COptionsDialog::COptionsDialog(CWnd* pParent /*=NULL*/)
	: CDialog(COptionsDialog::IDD, pParent)
{
	// place the existing values into the various boxes.

	
	//{{AFX_DATA_INIT(COptionsDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void COptionsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP

	DDX_Check(pDX, Drink_OptionsOpen, Auto_Open);
	DDV_MinMaxInt(pDX, Auto_Open, false, true );

   	DDX_Check(pDX, Drink_OptionsLogin, Auto_Login);
	DDV_MinMaxInt(pDX, Auto_Login, false, true );

   	DDX_Check(pDX, Drink_OptionsGamble, Gamble);
	DDV_MinMaxInt(pDX, Gamble, false, true );

	DDX_Check(pDX, Drink_OptionsSaveUser, Save_User);
	DDV_MinMaxInt(pDX, Save_User, false, true );

	DDX_Text(pDX, Drink_OptionsDelay, Drop_Delay);
	DDV_MinMaxInt(pDX, Drop_Delay, 0, 0x7fffffff );

	DDX_Text(pDX, Drink_OptionsServer, server);
	DDV_MaxChars(pDX, server, 512 );

}


BEGIN_MESSAGE_MAP(COptionsDialog, CDialog)
	//{{AFX_MSG_MAP(COptionsDialog)
	ON_BN_CLICKED(IDOK, OnOptionsOK)
	ON_BN_CLICKED(IDCANCEL, OnOptionsCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsDialog message handlers


void COptionsDialog::OnOptionsOK() 
{
	DrinkMachine *machine;
	unsigned int macnum;

	UpdateData();

	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;

	// Get the active MDI child window.
	CMDIChildWnd *pChild = (CMDIChildWnd *) pFrame->GetActiveFrame();

	// or CMDIChildWnd *pChild = pFrame->MDIGetActive();

	// Get the active view attached to the active MDI child
	// window.
	CDrinkView *pView = (CDrinkView *) pChild->GetActiveView();

	// set the macnum.
	macnum = pView->GetCurrent_Machine_Num();
	machine = theApp.GetMachine( macnum );

	// figure out which button it is, and try to drop that slot.
	for( unsigned int i = 0; i < buttons.GetSize() ; i++ )
	{
		machine->GetSlot( i )->SetRandomInclude( buttons[ i ]->GetState() );
	}



	
	
	// TODO: Add your control notification handler code here
	// set the current machines options to match the ones set here.
	theApp.currentMachine()->StoreUserPass( Save_User );
	theApp.currentMachine()->Set_Auto_Login( Auto_Login );
	theApp.currentMachine()->Set_Auto_Open( Auto_Open );
	theApp.currentMachine()->Set_Default_Delay( Drop_Delay );
	theApp.SetMetaServer( server );
	theApp.currentMachine()->Set_Gamble( Gamble );

	for( i=0; i < buttons.GetSize(); i++ )
	{
		delete buttons[i];
	}
	buttons.RemoveAll();
	CDialog::OnOK();

}


CButton & COptionsDialog::Delay()
{
	return *(CButton*) GetDlgItem(Drink_OptionsDelay);
}

CButton & COptionsDialog::AutoOpen()
{
	return *(CButton*) GetDlgItem(Drink_OptionsOpen);
}

CButton & COptionsDialog::AutoLogin()
{
	return *(CButton*) GetDlgItem(Drink_OptionsLogin);
}

CButton & COptionsDialog::gamble()
{
	return *(CButton*) GetDlgItem(Drink_OptionsGamble);
}


BOOL COptionsDialog::OnInitDialog()
{
	CButton * temp1;
	DrinkMachine *machine = NULL;
	unsigned int macnum = 0;

	CDialog::OnInitDialog();

	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;

	// Get the active MDI child window.
	CMDIChildWnd *pChild = (CMDIChildWnd *) pFrame->GetActiveFrame();

	// or CMDIChildWnd *pChild = pFrame->MDIGetActive();

	// Get the active view attached to the active MDI child
	// window.
	CDrinkView *pView = (CDrinkView *) pChild->GetActiveView();

	// set the macnum.
	macnum = pView->GetCurrent_Machine_Num();

	machine = theApp.GetMachine( macnum );


	for( int i=0; i < machine->NumberSlots(); i++ )
	{
		temp1 = new CButton;
		temp1->Create( machine->GetSlot( i )->GetName(), BS_AUTOCHECKBOX | WS_VISIBLE | WS_CHILD, CRect( 30, 30 + (30 * i), 300, 60 + (30 * i) ), this, Drink_OptionsSelect );
		temp1->SetCheck( machine->GetSlot( i )->RandomInclude() );
		buttons.Add( temp1 );
	}
	CString temp;

	

	temp.Format( "%lu", machine->Get_Default_Delay() );

	Delay().SetWindowText( temp );
	Server().SetWindowText( theApp.GetMetaServer() );
	SaveUser().SetCheck( machine->UserPassStored() );
	AutoOpen().SetCheck( machine->Get_Auto_Open() );
	AutoLogin().SetCheck( machine->Get_Auto_Login() );
	gamble().SetCheck( machine->Get_Gamble() );

	return( TRUE );
}


COptionsDialog::~COptionsDialog()
{
	for( int i=0; i < buttons.GetSize(); i++ )
	{
		delete buttons[i];
	}
	buttons.RemoveAll();
}



CButton & COptionsDialog::SaveUser()
{
	return *(CButton*) GetDlgItem(Drink_OptionsSaveUser);
}

void COptionsDialog::OnOptionsCancel() 
{
	for( int i=0; i < buttons.GetSize(); i++ )
	{
		delete buttons[i];
	}
	buttons.RemoveAll();
	CDialog::OnCancel();	
}

CButton & COptionsDialog::Server()
{
	return *(CButton*) GetDlgItem(Drink_OptionsServer);
}
