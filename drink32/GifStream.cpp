// GifStream.cpp: implementation of the GifStream class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "drink.h"
#include "GifStream.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GifStream::GifStream()
{
	Data = NULL;
}

GifStream::~GifStream()
{
//	free( Data );
}


void GifStream::LoadGif(CFile * stream, CString name)
{
	BYTE MagicNumber;
	BYTE Type;
	BYTE CodeBits = 0;
	BYTE MinCodeBits = 0;
	BYTE BlockSize = 0;
	int Code;
	int NewCode;
	DWORD CurrentDataPointer = 0;
	// load the header
	stream->Read(&GifHeader, 13 );	
	// load the global color table.
	stream->Read(&GlobalColorTable, ( ( ( GifHeader.Packed >> 7) & 0x0001 ) << ( ( GifHeader.Packed & 0x0007 ) + 1 ) ) * 3 );

	
	// do alot...
	
	// load the next block, and see what it is...
ReadBlock:
	stream->Read(&MagicNumber, 1 );
	if( MagicNumber == 0x21 )
	{
		stream->Read(&Type, 1 );
		switch( Type )
		{
		case 0xFF:
			// read and ignore App
			App.trash[0] = MagicNumber;
			App.trash[1] = Type;
			stream->Read( App.trash + 2, sizeof( APP ) - 2 );
			goto ReadBlock;
		case 0xF9:
			// read and ignore Control
			Control.trash[0] = MagicNumber;
			Control.trash[1] = Type;
			stream->Read( Control.trash + 2, sizeof( CONTROL ) - 2 );
			goto ReadBlock;
		case 0x01:
			// read and ignore Text
			Text.trash[0] = MagicNumber;
			Text.trash[1] = Type;
			stream->Read( Text.trash + 2, sizeof( TEXT ) - 2 );
			goto ReadBlock;
		case 0xFE:
			// read and ignore Comment
			Comment.trash[0] = MagicNumber;
			Comment.trash[1] = Type;
			stream->Read( Comment.trash + 2, sizeof( COMMENT ) - 2 );
			goto ReadBlock;
		default:
			// this is bad.
			break;
		}
	}
	else if( MagicNumber == 0x2C )
	{
		// read image descriptor
		stream->Read( &(ImageDescriptor.Left), 9 );
		// read the local color table.
		stream->Read(&LocalColorTable, ( ( ( ImageDescriptor.Packed) & 0x0001 ) << ( ( ( ImageDescriptor.Packed & 0x00E0 ) >> 5 ) + 1 ) ) * 3 );
		// read the data, read the data, yessss master.
		stream->Read(&CodeBits, sizeof( CodeBits ) );
		MinCodeBits = CodeBits;

		CodeBits++;
		CurrentDataPointer = 256L;
		NewCode = (0x01 << MinCodeBits) + 2;
		InitData();
		Code = -1;
		Code = GetNextCode( stream, Code , BlockSize , CodeBits ); // clear the read buffer



		stream->Read(&BlockSize, sizeof( BlockSize ) );
		while( BlockSize != 0 )
		{
			// read a block
			while( GetNextCode( stream, Code, BlockSize, CodeBits ) && CurrentDataPointer <
								( ( ImageDescriptor.Height * ImageDescriptor.Width ) + 256 ) )
			{
				// figure out what the code is, and fill in corresponding locations in bitmap.
				if( Code == ( 0x01 << MinCodeBits ) )
				{
					// code table clear is indicatied. blow away the old table.
					NewCode = ( 0x01 << MinCodeBits ) + 2;
					CodeBits = MinCodeBits + 1;
				}
				else if( Code == ( 0x01 << MinCodeBits ) + 1 )
				{
					break;
					// data done. continue reading, but ignore remaining data.
				;
				}
				else if( Code +1 == NewCode )	// special case of trying to use a code before we have
												// filled it in in the lookup table. 
				{
					memcpy( &(Data[CurrentDataPointer]), &(Data[CodePointer[Code]]), CodeLength[Code] -1 );
					Data[CurrentDataPointer + CodeLength[Code] - 1] = Data[CurrentDataPointer];
					if( NewCode < 4096 )
					{
						// BuildNewCode

						// Point to the new code in the DataBuffer.
						CodePointer[NewCode] = CurrentDataPointer;
						// set the new codes length.
						CodeLength[NewCode] = CodeLength[Code] + 1;
						NewCode++;
					}
					else
					{
						// code table's full.
					}
					// update the CurrentPointer
					CurrentDataPointer += CodeLength[Code];
				}
				else if( Code < NewCode )	// all other codes are valid before we even got this far.
				{
					// store the data pointed to by code
					memcpy( &(Data[CurrentDataPointer]), &(Data[CodePointer[Code]]), CodeLength[Code] );

					if( NewCode < 4096 )
					{
						// BuildNewCode

						// Point to the new code in the DataBuffer.
						CodePointer[NewCode] = CurrentDataPointer;
						// set the new codes length.
						CodeLength[NewCode] = CodeLength[Code] + 1;
						NewCode++;
					}
					else
					{
						// code table's full.
					}
					// update the CurrentPointer
					CurrentDataPointer += CodeLength[Code];
				}
				else
				{
					// bad data.
				}

				if( NewCode > ( 0x01 << CodeBits ) )
				{
					CodeBits++;
				}
			}





			stream->Read(&BlockSize, sizeof( BlockSize ) );
		}


	}
	else 
	{
		// this is bad...
	}



	if( ImageDescriptor.Packed & 0x40 )
	{
		// need to de-interleave it
		Interleaved();
	}
	Convert_Data( name );
}

void GifStream::Convert_Data(CString name)
{
	// take existing data, and transform it into a windows bitmap.
	// Write it out to file.
	CFile *CacheFile;
	tagBITMAPINFOHEADER InfoHeader;
	tagBITMAPFILEHEADER FileHeader;
	RGBQUAD	Palette[256];

	CacheFile = new CFile( (LPCTSTR) name, CFile::modeCreate | CFile::modeWrite | CFile::shareExclusive );

	FileHeader.bfType = 0x4d42;
	FileHeader.bfSize = sizeof( FileHeader ) + sizeof( InfoHeader ) + ( 256 * 4 ) +
					( ImageDescriptor.Height * ImageDescriptor.Width );
	FileHeader.bfReserved1 = 0x0000;
	FileHeader.bfReserved2 = 0x0000;
	FileHeader.bfOffBits = sizeof( FileHeader ) + sizeof( InfoHeader ) + ( 256 * 4 );

	InfoHeader.biSize = sizeof( InfoHeader );
	InfoHeader.biWidth = ImageDescriptor.Width;
	InfoHeader.biHeight = ImageDescriptor.Height;
	InfoHeader.biPlanes = 1;
	InfoHeader.biBitCount = 8;
	InfoHeader.biCompression = 0;
	InfoHeader.biSizeImage = ImageDescriptor.Height * ImageDescriptor.Width;
	InfoHeader.biXPelsPerMeter = 1000;
	InfoHeader.biYPelsPerMeter = 1000;
	InfoHeader.biClrUsed = 256;
	InfoHeader.biClrImportant = 256;
	for( int i = 0; i < 256; i++ )
	{
		Palette[i].rgbBlue = GlobalColorTable.ColorTableEntry[i].Blue;
		Palette[i].rgbGreen = GlobalColorTable.ColorTableEntry[i].Green;
		Palette[i].rgbRed = GlobalColorTable.ColorTableEntry[i].Red;
		Palette[i].rgbReserved = 0;
	}
	// write out to the file...
	CacheFile->Write( (void *)&(FileHeader.bfType), sizeof( FileHeader ) );
	CacheFile->Write( (void *)&(InfoHeader.biSize), sizeof( InfoHeader ) );
	CacheFile->Write( Palette, 256 * 4 );
	CacheFile->Write( ( Data + 256 ), ImageDescriptor.Height * ImageDescriptor.Width );
	CacheFile->Close();

}


void GifStream::InitData()
{
	Data = (BYTE *)malloc( ( ImageDescriptor.Height * ImageDescriptor.Width ) + 256 );
	for( int i = 0; i < 256; i++ )
	{
		Data[i] = i;
		CodeLength[i] = 1;
		CodePointer[i] = i;
	}
}

int GifStream::GetNextCode(CFile * stream, int &Code, BYTE &BlockRemaining, BYTE CodeBits)
{
	static DWORD currentdword=0L;
	static BYTE bitsremaining = 0;
	
	BYTE DataByte;

	if( Code == -1 )
	{
		currentdword = 0L;
		bitsremaining = 0;
		return( 0 );
	}

	Code = 0;
	
	if( BlockRemaining == 0 && bitsremaining < CodeBits )
	{
		// no bits to be had. 
//		currentdword = 0L;
//		bitsremaining = 0;
		return( 0 );
	}
	else if( BlockRemaining == 1 && bitsremaining < CodeBits - 8 )
	{
		// not enough bits to be had.
		stream->Read(&DataByte, 1 );
		currentdword >>= 8;
		currentdword |= ( DataByte << 24 );
		bitsremaining += 8;
		BlockRemaining--;

//		currentdword = 0L;
//		bitsremaining = 0;
		return( 0 );
	}
	else if( bitsremaining >= CodeBits )
	{
		// bits left are already enough.
		Code = ( ( currentdword >> ( 32 - bitsremaining ) ) & ( ( 0x0001 << CodeBits ) - 1 ) );
		bitsremaining -= CodeBits;
		return( 1 );
	}
	else if( bitsremaining >= CodeBits - 8 )
	{
		// need to read 8 more bits, then we'll have enough.
		stream->Read(&DataByte, 1 );
		currentdword >>= 8;
		currentdword |= ( DataByte << 24 ); 
		bitsremaining += 8;
		BlockRemaining--;
		Code = ( ( currentdword >> ( 32 - bitsremaining ) ) & ( ( 0x0001 << CodeBits ) - 1 ) );
		bitsremaining -= CodeBits;
		return( 1 );
	}
	else
	{
		// we need 16 more bits to have enough, 8 more wont do.
		stream->Read(&DataByte, 1 );
		currentdword >>= 8;
		currentdword |= ( DataByte << 24 ); 
		bitsremaining += 8;
		BlockRemaining --;
		stream->Read(&DataByte, 1 );
		currentdword >>= 8;
		currentdword |= ( DataByte << 24 ); 
		bitsremaining += 8;
		BlockRemaining --;
		Code = ( ( currentdword >> ( 0x0020 - bitsremaining ) ) & ( ( 0x0001 << CodeBits ) - 1 ) );
		bitsremaining -= CodeBits;
		return( 1 );
	}
}

BYTE * GifStream::GetImageData()
{
	return( Data + 256L );
}

COLORREF * GifStream::GetColorTable()
{
	COLORREF *Table;
	Table = (COLORREF *)malloc( sizeof( COLORREF ) * 256 );
	for( int i=0; i < 256; i++ )
	{
		Table[i] = RGB( GlobalColorTable.ColorTableEntry[i].Red, GlobalColorTable.ColorTableEntry[i].Green,
					GlobalColorTable.ColorTableEntry[i].Blue );
	}
	return( Table );
}

UINT GifStream::GetImageWidth()
{
	return( ImageDescriptor.Width );	
}

UINT GifStream::GetImageHeight()
{
	return( ImageDescriptor.Height );
}

void GifStream::LoadCache(CFile * stream, CString CacheFileName)
{
	// read the CacheFile from the disk.
	tagBITMAPINFOHEADER InfoHeader;
	tagBITMAPFILEHEADER FileHeader;
	RGBQUAD	Palette[256];

	stream->Read( (void *)&(FileHeader.bfType), sizeof( FileHeader ) );
	stream->Read( (void *)&(InfoHeader.biSize), sizeof( InfoHeader ) );
	stream->Read( Palette, 256 * 4 );

	ImageDescriptor.Width = InfoHeader.biWidth;
	ImageDescriptor.Height = InfoHeader.biHeight;
	for( int i = 0; i < 256; i++ )
	{
		GlobalColorTable.ColorTableEntry[i].Blue = Palette[i].rgbBlue;
		GlobalColorTable.ColorTableEntry[i].Green = Palette[i].rgbGreen;
		GlobalColorTable.ColorTableEntry[i].Red = Palette[i].rgbRed;
	}
	// write out to the file...
	Data = ( BYTE * )malloc( ( InfoHeader.biHeight * InfoHeader.biWidth ) + 256 );
	stream->Read( ( Data + 256 ), InfoHeader.biHeight * InfoHeader.biWidth );
	stream->Close();

}

void GifStream::Interleaved()
{
	BYTE *InterData;
	BYTE *temp1, *temp2;
	InterData = (BYTE *)malloc( ( ImageDescriptor.Height * ImageDescriptor.Width ) + 256 ); 
	temp1 = &(Data[256]);
	temp2 = &(InterData[256]);
	

	for( unsigned int i = 0, j = 0; i < GetImageHeight(); i += 8, j++ )
	{
		memcpy( &(temp2[(i * GetImageWidth() )] ), &(temp1[( j * GetImageWidth() )] ), GetImageWidth() );
	}
	for( i = 4; i < GetImageHeight(); i += 8, j++ )
	{
		memcpy( &(temp2[i * GetImageWidth()] ), &(temp1[j * GetImageWidth()] ), GetImageWidth() );
	}
	for( i = 2; i < GetImageHeight(); i += 4, j++ )
	{
		memcpy( &(temp2[i * GetImageWidth()] ), &(temp1[j * GetImageWidth()] ), GetImageWidth() );
	}
	for( i = 1; i < GetImageHeight(); i += 2, j++ )
	{
		memcpy( &(temp2[i * GetImageWidth()] ), &(temp1[j * GetImageWidth()] ), GetImageWidth() );
	}
	free( Data );
	Data = InterData;
}
