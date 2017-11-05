// DropAbortDialog.cpp : implementation file
//

#include "stdafx.h"
#include "drink.h"
#include "DropAbortDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDropAbortDialog dialog


CDropAbortDialog::CDropAbortDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CDropAbortDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDropAbortDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDropAbortDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDropAbortDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDropAbortDialog, CDialog)
	//{{AFX_MSG_MAP(CDropAbortDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDropAbortDialog message handlers
