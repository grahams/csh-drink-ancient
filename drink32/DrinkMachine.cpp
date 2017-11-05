// DrinkMachine.cpp: implementation of the DrinkMachine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "drink.h"
#include "DrinkMachine.h"
#include <afxinet.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


DrinkMachine::DrinkMachine()
{
	View = NULL;
//stubbed in. normally, this should go and get all this info from the registry.
	loggedin = false;
	Store_UserPass = false;
	Auto_Login = true;
	Auto_Open = false;
	Gamble = true;
	Default_Delay = 5;
	Image = NULL;
	ImageWidth = 0;
	ImageHeight = 0;
}

DrinkMachine::~DrinkMachine()
{
	for( int i=0; i < Slots.GetSize(); i++ )
	{
		delete Slots[i];
	}
	Slots.RemoveAll();
	if( Image != NULL )
	{
		free( Image - 256 );
	}
}

bool DrinkMachine::Login(CString Username, CString Password)
{
	return(TRUE);
	// log in
	// if successful, set loggedin, and return true
}

bool DrinkMachine::LoggedIn()
{
	return(loggedin);
}

bool DrinkMachine::LogOut()
{
	loggedin = false;
	return( !loggedin );
	if( !UserPassStored() )
	{
		Username = "";
		Password = "";
	}
}

unsigned int DrinkMachine::NumberSlots()
{
	return( Slots.GetSize() );
}

DrinkSlot * DrinkMachine::GetSlot(unsigned int Slot)
{
	return( Slots[Slot] );
}

bool DrinkMachine::DropSlot(unsigned int Slot)
{

	// replace this with the real thing.
	if( Slots[Slot]->RandomInclude() )
	{
		return( true );
	}
	else
	{
		return(false);
	}
}

CString * DrinkMachine::GetUsername()
{
	return( &Username );
}

CString * DrinkMachine::GetPassword()
{
	return( &Password );
}

bool DrinkMachine::Validate(CString username, CString password, int store_userpass)
{
	// todo, unstub this code.
	Store_UserPass = store_userpass;
	if( store_userpass )
	{
		Password = password;
		Username = username;
	}
	if( username == CString( "ers5174" ) && password == CString ( "foobar" ) )
	{
		loggedin = true;
		return( true );
	}
	else
	{
		loggedin = false;
		return( false );
	}
}

int DrinkMachine::UserPassStored()
{
	return( Store_UserPass );
}

bool DrinkMachine::Validate()
{
	// use Username and Password to try to login, and return results
	
	if( Username == CString( "ers5174" ) && Password == CString( "foobar" ) )
	{
		loggedin = true;
		return( true );
	}
	else
	{
		loggedin = false;
		return( false );
	}
}

int DrinkMachine::Get_Auto_Login()
{
	return( Auto_Login );
}

int DrinkMachine::Get_Auto_Open()
{
	return( Auto_Open );
}

int DrinkMachine::Get_Gamble()
{
	return( Gamble );
}

unsigned long int DrinkMachine::Get_Default_Delay()
{
	return( Default_Delay );
}


void DrinkMachine::Set_Auto_Login(int auto_login)
{
	Auto_Login = auto_login;
}

void DrinkMachine::Set_Auto_Open(int auto_open)
{
	Auto_Open = auto_open;
}

void DrinkMachine::Set_Gamble(int gamble)
{
	Gamble = gamble;
}

void DrinkMachine::Set_Default_Delay(unsigned long int delay)
{
	Default_Delay = delay;
}

void DrinkMachine::StoreUserPass(int store)
{
	Store_UserPass = store;
	if( !store )
	{
		Username = "";
		Password = "";
	}
}



void DrinkMachine::SetView(CDrinkView * view)
{
	View = view;
}

void DrinkMachine::SetDelay(unsigned long int delay)
{
	Current_Delay = delay;
}


CString DrinkMachine::GetMachineName()
{
	return( MachineName );
}

void DrinkMachine::SetMachineName(CString name)
{
	MachineName = name;
}

BOOL DrinkMachine::operator==(DrinkMachine &other)
{
	if( other.GetMachineName() == MachineName )
	{
		return( TRUE );
	}
	else
	{
		return( FALSE );
	}
}

void DrinkMachine::UpdateDisplay(CDrinkView * view)
{
	for( int i=0; i < Slots.GetSize(); i++ )
	{
		view->PlaceButton( Slots[i], i );
	}
}

void DrinkMachine::AddSlot(DrinkSlot * slot)
{
	Slots.Add( slot );
}

void DrinkMachine::SetLocation(CString location)
{
	Location = location;
}

CString DrinkMachine::GetLocation()
{
	return( Location );
}

void DrinkMachine::SetMachineURL(CString URL)
{
	MachineURL = URL;
}

CString DrinkMachine::GetMachineURL(CString URL)
{
	return( MachineURL );
}

void DrinkMachine::SetColorTable(COLORREF * Table)
{
	for( int i=0; i < 256; i++ )
	{
		ColorTable[i] = Table[i];
	}
	free( Table );
}

void DrinkMachine::SetImage(BYTE * Data)
{
	Image = Data;
}

void DrinkMachine::SetImageHeight(UINT height)
{
	ImageHeight = height;
}

void DrinkMachine::SetImageWidth(UINT width)
{
	ImageWidth = width;
}

int DrinkMachine::GetImageWidth()
{
	return( ImageWidth );
}

int DrinkMachine::GetImageHeight()
{
	return( ImageHeight );
}

void DrinkMachine::SetImageURL(CString URL)
{
	ImageURL = URL;
	CString CacheFileName = GetMachineName();
	CacheFileName += ".BMP";
	CFile CacheFile;
	if( CacheFile.Open( (LPCTSTR) CacheFileName, CFile::modeRead ) )
	{
		GifLoader.LoadCache( &CacheFile, CacheFileName );
		SetImage( GifLoader.GetImageData() );
		SetImageHeight( GifLoader.GetImageHeight() );
		SetImageWidth( GifLoader.GetImageWidth() );
		SetColorTable( GifLoader.GetColorTable() );
	}
	else
	{	
		// load the Image, and set all the details...
		CInternetSession session;
		CHttpConnection* pServer = NULL;
		CHttpFile* pFile = NULL;
		CString ServerName;
		CString Object;
		INTERNET_PORT port;
		DWORD ServiceType;

		if(!AfxParseURL(ImageURL, ServiceType, ServerName, Object, port) ||
			ServiceType != INTERNET_SERVICE_HTTP)
		{
			// bad URL no logo...
		}
		else
		{
			pServer = session.GetHttpConnection(ServerName, port);

			pFile = pServer->OpenRequest(CHttpConnection::HTTP_VERB_GET,
				Object, NULL, 1, NULL, NULL, INTERNET_FLAG_EXISTING_CONNECT);
			pFile->AddRequestHeaders(_T("Accept: image/gif\r\nUser-Agent: Win32Drink Client\r\n"));
			pFile->SendRequest();
			DWORD dwRet;
			pFile->QueryInfoStatusCode(dwRet);
			if( dwRet != 200 )
			{
				// if status not equal to 200 then no logo.
			}
			else
			{
				// file is open and valid. load it.
				GifLoader.LoadGif( pFile, CacheFileName );
				SetImage( GifLoader.GetImageData() );
				SetImageHeight( GifLoader.GetImageHeight() );
				SetImageWidth( GifLoader.GetImageWidth() );
				SetColorTable( GifLoader.GetColorTable() );
			}
		}
	}
}
