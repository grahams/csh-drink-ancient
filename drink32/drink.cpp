// drink.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "drink.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "drinkDoc.h"
#include "drinkView.h"
#include "OpenDialog.h"
#include "InvalidLoginDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrinkApp

BEGIN_MESSAGE_MAP(CDrinkApp, CWinApp)
	//{{AFX_MSG_MAP(CDrinkApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(Grey_Login, OnNewLogin)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(Drink_Logout, CDrinkApp::OnLogout)
	ON_COMMAND(Drink_Logout_All, CDrinkApp::OnLogoutAll)
	ON_COMMAND(Drink_Options, CDrinkApp::OnOptions)
	ON_COMMAND(Drink_Login, CDrinkApp::OnLogin)
	ON_COMMAND(ID_FILE_OPEN, CDrinkApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrinkApp construction

CDrinkApp::CDrinkApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	Current_MetaServer = "http://www.csh.rit.edu/~schu/drink/metadrink.mac";
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDrinkApp object

CDrinkApp theApp;


/////////////////////////////////////////////////////////////////////////////
// CDrinkApp initialization

BOOL CDrinkApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_DRINKTYPE,
		RUNTIME_CLASS(CDrinkDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CDrinkView));
	pDocTemplate->SetContainerInfo(IDR_DRINKTYPE_CNTR_IP);
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Enable drag/drop open
//	m_pMainWnd->DragAcceptFiles();

	// Enable DDE Execute open
//	EnableShellOpen();
//	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	// create a dummy drinkmachine
	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;

	// Get the active MDI child window.
	CMDIChildWnd *pChild = (CMDIChildWnd *) pFrame->GetActiveFrame();

	// or CMDIChildWnd *pChild = pFrame->MDIGetActive();

	// Get the active view attached to the active MDI child
	// window.
	CDrinkView * view = (CDrinkView *) pChild->GetActiveView();
	CDrinkDoc * pDoc = (CDrinkDoc *) view->GetDocument();
	pDoc->OnCloseDocument();
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CDrinkApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CDrinkApp commands


void CDrinkApp::OnLogin()
{
	// setup login dialog.
	if( Current_Machine != NULL )
	{
		if( !( Current_Machine->LoggedIn() ) )
		{
			if( Current_Machine->UserPassStored() )
			{
				if( ! Current_Machine->Validate() )
				{
					LoginWindow.DoModal();
				}
			}
			else
			{
				LoginWindow.DoModal();	
			}
		}
	}
}


void CDrinkApp::OnOptions() 
{
	Current_Machinenumber =
	// TODO: Add your command handler code here
	OptionsDialog.DoModal();
}

void CDrinkApp::OnLogout() 
{
	// TODO: Add your command handler code here
	// log out of currently selected machine	
	if( Current_Machine != NULL )
	{
		if( Current_Machine->LoggedIn() )
		{
			//log out
			Current_Machine->LogOut();
		}
	}
}

void CDrinkApp::OnLogoutAll() 
{
	// TODO: Add your command handler code here
	// log out of all machines	
	for( int i = 0; i < machines.GetSize() ; i++ )
	{
		machines[ i ]->LogOut();
	}
}

void CDrinkApp::OnNewLogin() 
{
	// TODO: Add your command handler code here
	// log in. no machine is open, so open one first.
	OnFileOpen();
	if( Current_Machine != NULL )
	{
		LoginWindow.DoModal();
	}
	else
	{
	// open was canceled.
	}
	// another machine should now be open.
}

DrinkMachine * CDrinkApp::Open(UINT machine)
{
	return( NULL );	
}


void CDrinkApp::OnFileOpen()
{
	unsigned int macnum = 0;

	Current_Machine = NULL;
	COpenDialog opendialog;
	if( !Server.DoModal() )
	{
		return;
	}
	opendialog.DoModal();
	if( Current_Machine != NULL )
	{
		CWinApp::OnFileNew();
		CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;

		// Get the active MDI child window.
		CMDIChildWnd *pChild = (CMDIChildWnd *) pFrame->GetActiveFrame();

		// or CMDIChildWnd *pChild = pFrame->MDIGetActive();

		// Get the active view attached to the active MDI child
		// window.
		CDrinkView *pView = (CDrinkView *) pChild->GetActiveView();

		// set up view with current machine number.
		for( int i = 0; i < machines.GetSize(); i++ )
		{
			if( (*Current_Machine) == *(machines[i]) )
			{
				pView->SetMacNum( i );
			}
		}
		Current_Machine->UpdateDisplay( pView );
	}
	else
	{
		return;
	}
}

DrinkMachine * CDrinkApp::currentMachine()
{
	return( Current_Machine );
}

DrinkMachine * CDrinkApp::GetMachine(unsigned int number)
{
	return( machines[number] );
}

unsigned int CDrinkApp::GetNumberMachines()
{
	return( machines.GetSize() );
}

CDrinkApp::~CDrinkApp()
{
	for( int i=0; i < machines.GetSize(); i++ )
	{
		delete machines[i];
	}
	machines.RemoveAll();
}

void CDrinkApp::AddMachine(DrinkMachine * machine)
{
	machines.Add( machine );
}

void CDrinkApp::RemoveMachine(unsigned int macnum)
{
	delete machines[ macnum ];
	machines.RemoveAt( macnum );
}

void CDrinkApp::SetMetaServer(CString server)
{
	Current_MetaServer = server;
}

CString CDrinkApp::GetMetaServer()
{
	return( Current_MetaServer );
}

