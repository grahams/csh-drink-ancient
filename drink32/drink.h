// drink.h : main header file for the DRINK application
//

#if !defined(AFX_DRINK_H__A0616FC5_84BA_11D3_B3AF_444553540000__INCLUDED_)
#define AFX_DRINK_H__A0616FC5_84BA_11D3_B3AF_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "LoginDialog.h"	// Added by ClassView
#include "OptionsDialog.h"
#include "DrinkMachine.h"
#include "Drink_ServerDialog.h"	// Added by ClassView

/////////////////////////////////////////////////////////////////////////////
// CDrinkApp:
// See drink.cpp for the implementation of this class
//



class CDrinkApp : public CWinApp
{
public:
	CString GetMetaServer();
	void SetMetaServer( CString server );
	void RemoveMachine( unsigned int macnum );
	void AddMachine(  DrinkMachine *machine );
	 ~CDrinkApp();
	unsigned int GetNumberMachines();
	DrinkMachine * GetMachine( unsigned int number);
	DrinkMachine * currentMachine();
	DrinkMachine * Current_Machine;
	CLoginDialog LoginWindow;
	COptionsDialog OptionsDialog;
	CDrinkApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrinkApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDrinkApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	afx_msg void OnFileOpen();
	DrinkMachine * Open(UINT machine);
	afx_msg void OnLogin();
	afx_msg void OnOptions();
	afx_msg void OnLogout();
	afx_msg void OnLogoutAll();
	afx_msg void OnNewLogin();

private:
	CString Current_MetaServer;
	Drink_ServerDialog Server;
	unsigned int Current_Machinenumber;
	CTypedPtrArray<CObArray, DrinkMachine *> machines;

};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRINK_H__A0616FC5_84BA_11D3_B3AF_444553540000__INCLUDED_)

