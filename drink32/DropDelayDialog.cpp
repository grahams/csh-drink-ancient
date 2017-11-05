// DropDelayDialog.cpp : implementation file
//

#include "stdafx.h"
#include "drink.h"
#include "DropDelayDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDropDelayDialog dialog

extern CDrinkApp theApp;


CDropDelayDialog::CDropDelayDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CDropDelayDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDropDelayDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	

}


void CDropDelayDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDropDelayDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP

	DDX_Text(pDX, Drink_DropDelay, Drop_Delay);
	DDV_MinMaxInt(pDX, Drop_Delay, 0, 0x7fffffff );

}


BEGIN_MESSAGE_MAP(CDropDelayDialog, CDialog)
	//{{AFX_MSG_MAP(CDropDelayDialog)
	ON_BN_CLICKED(DelayDialog_Drop, OnDrop)
	ON_BN_CLICKED(Drink_DropCancel, OnDropCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDropDelayDialog message handlers

void CDropDelayDialog::OnDrop() 
{
	DrinkMachine *machine;
	unsigned int macnum;
	
	// TODO: Add your control notification handler code here
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

	machine->SetDelay( Drop_Delay );	
	CDialog::OnOK();
}


BOOL CDropDelayDialog::OnInitDialog()
{
	CString temp;
	DrinkMachine *machine = NULL;
	unsigned int macnum = 0;

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
	

	temp.Format( "%lu", machine->Get_Default_Delay() );

	Delay().SetWindowText( temp );
	return( TRUE );

}

CButton & CDropDelayDialog::Delay()
{
	return *(CButton*) GetDlgItem(Drink_DropDelay);
}

void CDropDelayDialog::OnDropCancel() 
{
	// TODO: Add your control notification handler code here
	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;

	// Get the active MDI child window.
	CMDIChildWnd *pChild = (CMDIChildWnd *) pFrame->GetActiveFrame();

	// or CMDIChildWnd *pChild = pFrame->MDIGetActive();

	// Get the active view attached to the active MDI child
	// window.
	CDrinkView *pView = (CDrinkView *) pChild->GetActiveView();


	pView->AbortDrop();
	CDialog::OnCancel();
}
