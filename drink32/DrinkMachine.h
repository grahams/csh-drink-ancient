// DrinkMachine.h: interface for the DrinkMachine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRINKMACHINE_H__F729CEE1_8CC3_11D3_B3AF_444553540000__INCLUDED_)
#define AFX_DRINKMACHINE_H__F729CEE1_8CC3_11D3_B3AF_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "drinkslot.h"
#include "drinkview.h"
#include <afxtempl.h>
#include "GifStream.h"	// Added by ClassView

class DrinkMachine: public CObject
{
public:
	void SetImageURL( CString URL );
	int GetImageHeight();
	int GetImageWidth();
	void SetImageWidth( UINT width );
	void SetImageHeight( UINT height );
	void SetImage( BYTE * Data );
	void SetColorTable( COLORREF * Table );
	COLORREF ColorTable[256];
	CString GetMachineURL( CString URL );
	void SetMachineURL( CString URL );
	CString GetLocation();
	void SetLocation( CString location );
	void AddSlot( DrinkSlot * slot );
	void UpdateDisplay( CDrinkView *view );
	BOOL operator==( DrinkMachine &other );
	void SetMachineName( CString name );
	CString GetMachineName();
	void SetDelay( unsigned long int delay );
	void SetView( CDrinkView * view );
	void StoreUserPass( int store );
	void Set_Default_Delay( unsigned long int delay );
	void Set_Gamble( int gamble );
	void Set_Auto_Open( int auto_open );
	void Set_Auto_Login( int auto_login );
	unsigned long int Get_Default_Delay();
	int Get_Gamble();
	int Get_Auto_Open();
	int Get_Auto_Login();
	bool Validate();
	int UserPassStored();
	bool Validate( CString username, CString password, int store_userpass);
	CString * GetPassword();
	CString * GetUsername();
	bool DropSlot( unsigned int Slot );
	DrinkSlot * GetSlot(unsigned int Slot);
	unsigned int NumberSlots();
	bool LogOut();
	bool LoggedIn();
	bool Login( CString Username, CString Password);
	DrinkMachine();
	virtual ~DrinkMachine();

private:
	GifStream GifLoader;
	CString ImageURL;
	UINT ImageWidth;
	UINT ImageHeight;
	BYTE * Image;
	CString MachineURL;
	CString Location;
	CString MachineName;
	unsigned long int Current_Delay;
	CDrinkView * View;
	unsigned long int Default_Delay;
	int Gamble;
	int Auto_Open;
	int Auto_Login;
	int Store_UserPass;
	bool loggedin;
	CString Password;
	CString Username;
protected:
	CTypedPtrArray<CObArray, DrinkSlot *> Slots;
};

#endif // !defined(AFX_DRINKMACHINE_H__F729CEE1_8CC3_11D3_B3AF_444553540000__INCLUDED_)
