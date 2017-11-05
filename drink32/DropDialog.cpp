// DropDialog.cpp : implementation file
//

#include "stdafx.h"
#include "drink.h"
#include "DropDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDropDialog dialog


CDropDialog::CDropDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CDropDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDropDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDropDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDropDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDropDialog, CDialog)
	//{{AFX_MSG_MAP(CDropDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDropDialog message handlers
