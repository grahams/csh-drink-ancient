// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "drink.h"

#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

extern CDrinkApp theApp;


IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	// TODO: add member initialization code here
	
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	if( theApp.Current_Machine != NULL )
	{
		cs.cx = (theApp.Current_Machine->NumberSlots() * 47 ) + 14;
		if( cs.cx < theApp.Current_Machine->GetImageWidth() + 18 )
		{
			cs.cx = theApp.Current_Machine->GetImageWidth() + 18;
		}
		cs.lpszName = (LPCSTR) (LPCTSTR) theApp.Current_Machine->GetMachineName();		
	}
	else
	{
		cs.lpszName = "foodrink";
	}
	cs.cy = 480;
	cs.style = WS_CAPTION | WS_CHILD | WS_CLIPSIBLINGS | WS_MINIMIZEBOX | WS_SYSMENU;
	return CMDIChildWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers

void CChildFrame::OnSize(UINT nType, int cx, int cy)
{
   // Get a pointer to the parent window
   CWnd* pWnd = this;

   // Resize the window
   if (pWnd != NULL)
      pWnd->SetWindowPos(0, 0, 0, 640, 480, 
         SWP_NOMOVE | SWP_NOZORDER);

	CMDIChildWnd::OnSize(nType, 640, 480);

}