// DropSuccess.cpp : implementation file
//

#include "stdafx.h"
#include "drink.h"
#include "DropSuccess.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDropSuccess dialog


CDropSuccess::CDropSuccess(CWnd* pParent /*=NULL*/)
	: CDialog(CDropSuccess::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDropSuccess)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDropSuccess::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDropSuccess)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDropSuccess, CDialog)
	//{{AFX_MSG_MAP(CDropSuccess)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDropSuccess message handlers
