// InvalidLoginDialog.cpp : implementation file
//

#include "stdafx.h"
#include "drink.h"
#include "InvalidLoginDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInvalidLoginDialog dialog


CInvalidLoginDialog::CInvalidLoginDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CInvalidLoginDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInvalidLoginDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CInvalidLoginDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInvalidLoginDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInvalidLoginDialog, CDialog)
	//{{AFX_MSG_MAP(CInvalidLoginDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInvalidLoginDialog message handlers
