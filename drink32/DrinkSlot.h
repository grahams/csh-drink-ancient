// DrinkSlot.h: interface for the DrinkSlot class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRINKSLOT_H__F729CEE2_8CC3_11D3_B3AF_444553540000__INCLUDED_)
#define AFX_DRINKSLOT_H__F729CEE2_8CC3_11D3_B3AF_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class DrinkSlot: public CObject 
{
public:
	CString GetImageURL();
	void SetImageURL( CString URL );
	unsigned int RandomInclude();
	void SetRandomInclude( unsigned int include );
	void SetName( CString name );
	DrinkSlot( CString SlotName, bool Slot_Empty );
	bool IsEmpty();
	CString GetName();
	DrinkSlot();
	virtual ~DrinkSlot();

private:
	CString ImageURL;
	unsigned int randinclude;
	bool SlotEmpty;
	CString slotName;
};

#endif // !defined(AFX_DRINKSLOT_H__F729CEE2_8CC3_11D3_B3AF_444553540000__INCLUDED_)
