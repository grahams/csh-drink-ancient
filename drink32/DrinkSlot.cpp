// DrinkSlot.cpp: implementation of the DrinkSlot class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "drink.h"
#include "DrinkSlot.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DrinkSlot::DrinkSlot()
{
	slotName = "None";
	SlotEmpty = true;
	randinclude = 0;
}

DrinkSlot::~DrinkSlot()
{

}

CString DrinkSlot::GetName()
{
	return( slotName );
}

bool DrinkSlot::IsEmpty()
{
	return( SlotEmpty );
}


DrinkSlot::DrinkSlot( CString SlotName, bool Slot_empty )
{
	slotName = SlotName;
	SlotEmpty = Slot_empty;
}

void DrinkSlot::SetName( CString name )
{
	slotName = name;	
}


void DrinkSlot::SetRandomInclude(unsigned int include)
{
	randinclude = include;
}

unsigned int DrinkSlot::RandomInclude()
{
	return( randinclude );
}

void DrinkSlot::SetImageURL(CString URL)
{
	ImageURL = URL;
}

CString DrinkSlot::GetImageURL()
{
	return( ImageURL );
}
