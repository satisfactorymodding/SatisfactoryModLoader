#pragma once

#include "CoreTypes.h"
#include "HAL/UnrealMemory.h"
#include "Math/UnrealMathUtility.h"
#include "Containers/UnrealString.h"
#include "Serialization/MemoryArchive.h"

/**
* A special 64bit version of the FObjectReader. Epic implemented a 64bit writer but no templatized support for 64bit reading
* Because the reader uses the default allocator (32bit) there was no convienient way around this. As such this is a carbon copy
* of Epics FObjectReader but with 64bit support
 */
class FFGMemoryReader64 : public FMemoryArchive
{
public:
	/**
	   * Returns the name of the Archive.  Useful for getting the name of the package a struct or object
	 * is in when a loading error occurs.
	 *
	 * This is overridden for the specific Archive Types
	 **/
	virtual FString GetArchiveName() const override
	{
		return TEXT("FFGMemoryReader64");
	}

	virtual int64 TotalSize() override
	{
		return FMath::Min((int64)Bytes.Num(), LimitSize);
	}

	void Serialize( void* Data, int64 Num )
	{
		if (Num && !IsError())
		{
			// Only serialize if we have the requested amount of data
			if (Offset + Num <= TotalSize())
			{
				FMemory::Memcpy( Data, &Bytes[Offset], Num );
				Offset += Num;
			}
			else
			{
				SetError();
			}
		}
	}

	explicit FFGMemoryReader64( const TArray<uint8, TSizedDefaultAllocator<64> >& InBytes, bool bIsPersistent = false )
		: Bytes    (InBytes)
		, LimitSize(INT64_MAX)
	{
		this->SetIsLoading(true);
		this->SetIsPersistent(bIsPersistent);
	}

	/** With this method it's possible to attach data behind some serialized data. */
	void SetLimitSize(int64 NewLimitSize)
	{
		LimitSize = NewLimitSize;
	}

private:
	const TArray<uint8, TSizedDefaultAllocator<64> >& Bytes;
	int64                LimitSize;
};

/**
 * 64bit FArchive Proxy to transparently load compressed data from an array. Basically a copy paste of epics version but modified to be 64bits
 */
class FACTORYGAME_API FArchiveLoadCompressedProxy64 : public FArchive
{
public:
	FArchiveLoadCompressedProxy64(const TArray<uint8, TSizedDefaultAllocator<64>>& InCompressedData, FName CompressionFormat, ECompressionFlags InCompressionFlags=COMPRESS_NoFlags);

	/** Destructor, freeing temporary memory. */
	virtual ~FArchiveLoadCompressedProxy64();

	/**
	 * Serializes data from archive. This function is called recursively and determines where to serialize
	 * from and how to do so based on internal state.
	 *
	 * @param	Data	Pointer to serialize to
	 * @param	Count	Number of bytes to read
	 */
	virtual void Serialize( void* Data, int64 Count );

	/**
	 * Seeks to the passed in position in the stream. This archive only supports forward seeking
	 * and implements it by serializing data till it reaches the position.
	 */
	virtual void Seek( int64 InPos );

	/**
	 * @return current position in uncompressed stream in bytes.
	 */
	virtual int64 Tell();

private:
	/**
	 * Flushes tmp data to array.
	 */
	void DecompressMoreData();

	/** Array to write compressed data to.						*/
	const TArray<uint8, TSizedDefaultAllocator<64>>&	CompressedData;
	/** Current index into compressed data array.				*/
	int64			CurrentIndex;
	/** Pointer to start of temporary buffer.					*/
	uint8*			TmpDataStart;
	/** Pointer to end of temporary buffer.						*/
	uint8*			TmpDataEnd;
	/** Pointer to current position in temporary buffer.		*/
	uint8*			TmpData;
	/** Whether to serialize from temporary buffer of array.	*/
	bool			bShouldSerializeFromArray;
	/** Number of raw (uncompressed) bytes serialized.			*/
	int64			RawBytesSerialized;
	/** Compression method										*/
	FName			CompressionFormat;
	/** Flags used for compression.								*/
	ECompressionFlags CompressionFlags;
};

/**
 * 64 bit FArchive Proxy to transparently write out compressed data to an array. Basically a copy paste of epics version but modified to be 64bits
 */
class FACTORYGAME_API FArchiveSaveCompressedProxy64 : public FArchive
{
	/**
	 * This enum and the following constructor is a workaround for VC compiler bug that prevents using attributes
	 * on constructors without inline implementation. This should be removed when the deprecated ctor is removed.
	 */
	enum EVS2015Redirector
	{
		Redirect
	};
	FArchiveSaveCompressedProxy64(EVS2015Redirector, TArray<uint8, TSizedDefaultAllocator<64>>& InCompressedData, ECompressionFlags InCompressionFlags);

public:
	FArchiveSaveCompressedProxy64( TArray<uint8, TSizedDefaultAllocator<64>>& InCompressedData, FName InCompressionFormat, ECompressionFlags InCompressionFlags=COMPRESS_None);

	/** Destructor, flushing array if needed. Also frees temporary memory. */
	virtual ~FArchiveSaveCompressedProxy64();

	/**
	 * Flushes tmp data to array.
	 */
	virtual void Flush();

	/**
	 * Serializes data to archive. This function is called recursively and determines where to serialize
	 * to and how to do so based on internal state.
	 *
	 * @param	Data	Pointer to serialize to
	 * @param	Count	Number of bytes to read
	 */
	virtual void Serialize( void* Data, int64 Count );

	/**
	 * Seeking is only implemented internally for writing out compressed data and asserts otherwise.
	 * 
	 * @param	InPos	Position to seek to
	 */
	virtual void Seek( int64 InPos );

	/**
	 * @return current position in uncompressed stream in bytes.
	 */
	virtual int64 Tell();

private:
	/** Array to write compressed data to.					*/
	TArray<uint8, TSizedDefaultAllocator<64>>&	CompressedData;
	/** Current index in array.								*/
	int64				CurrentIndex;
	/** Pointer to start of temporary buffer.				*/
	uint8*			TmpDataStart;
	/** Pointer to end of temporary buffer.					*/
	uint8*			TmpDataEnd;
	/** Pointer to current position in temporary buffer.	*/
	uint8*			TmpData;
	/** Whether to serialize to temporary buffer of array.	*/
	bool			bShouldSerializeToArray;
	/** Number of raw (uncompressed) bytes serialized.		*/
	int64		RawBytesSerialized;
	/** Format to use for compression.						*/
	FName  CompressionFormat;
	/** Flags to use for compression.						*/
	ECompressionFlags CompressionFlags;
};