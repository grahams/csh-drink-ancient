// MetaFailedDialog.cpp : implementation file
//

#include "stdafx.h"
#include "drink.h"
#include "MetaFailedDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMetaFailedDialog dialog


CMetaFailedDialog::CMetaFailedDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CMetaFailedDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMetaFailedDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMetaFailedDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMetaFailedDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMetaFailedDialog, CDialog)
	//{{AFX_MSG_MAP(CMetaFailedDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMetaFailedDialog message handlers
