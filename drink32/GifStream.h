// GifStream.h: interface for the GifStream class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GIFSTREAM_H__F8875EA1_B6EA_11D3_B3AF_444553540000__INCLUDED_)
#define AFX_GIFSTREAM_H__F8875EA1_B6EA_11D3_B3AF_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class GifStream  
{
public:
	void LoadCache( CFile * stream, CString CacheFileName );
	UINT GetImageHeight();
	UINT GetImageWidth();
	COLORREF * GetColorTable();
	BYTE * GetImageData();
	int GetNextCode( CFile * stream, int &Code, BYTE &BlockRemaining, BYTE CodeBits );
	void LoadGif( CFile * stream, CString name );
	GifStream();
	virtual ~GifStream();

private:
	void Interleaved();
	void InitData();
	DWORD CodePointer[4096];
	BYTE CodeLength[4096];
	void Convert_Data(CString name);
	BYTE * Data;
	
	struct GIFHEADER
	{
		BYTE Signature[3];
		BYTE Version[3];

		WORD ScreenWidth;
		WORD ScreenHeight;

		BYTE Packed;
		BYTE BackgroundColor;
		BYTE AspectRatio;
	} GifHeader;

	struct COLORTABLEENTRY
	{
		BYTE Red;
		BYTE Green;
		BYTE Blue;
	};

	struct COLORTABLE
	{
		COLORTABLEENTRY ColorTableEntry[256];
	} GlobalColorTable, LocalColorTable;

	struct IMAGEDESC
	{
		BYTE Separator;
		WORD Left;
		WORD Top;
		WORD Width;
		WORD Height;
		BYTE Packed;
	} ImageDescriptor;

	struct CONTROL
	{
		BYTE trash[8];  // we dont give a damn about this data...
	} Control;

	struct TEXT
	{
		BYTE trash[17];  // we dont give a damn about this data...
	} Text;

	struct APP
	{
		BYTE trash[7];  // we dont give a damn about this data...
	} App;

	struct COMMENT
	{
		BYTE trash[4];  // we dont give a damn about this data...
	} Comment;



};

#endif // !defined(AFX_GIFSTREAM_H__F8875EA1_B6EA_11D3_B3AF_444553540000__INCLUDED_)
