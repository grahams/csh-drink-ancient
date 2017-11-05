// DropFailed.cpp : implementation file
//

#include "stdafx.h"
#include "drink.h"
#include "DropFailed.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDropFailed dialog


CDropFailed::CDropFailed(CWnd* pParent /*=NULL*/)
	: CDialog(CDropFailed::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDropFailed)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDropFailed::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDropFailed)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDropFailed, CDialog)
	//{{AFX_MSG_MAP(CDropFailed)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDropFailed message handlers
