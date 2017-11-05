// Drink_Meta_FailedDialog.cpp : implementation file
//

#include "stdafx.h"
#include "drink.h"
#include "Drink_MetaDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Drink_MetaDialog dialog


Drink_MetaDialog::Drink_MetaDialog(CWnd* pParent /*=NULL*/)
	: CDialog(Drink_MetaDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(Drink_MetaDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Drink_FailedDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Drink_MetaDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Drink_MetaDialog, CDialog)
	//{{AFX_MSG_MAP(Drink_MetaDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Drink_MetaDialog message handlers
