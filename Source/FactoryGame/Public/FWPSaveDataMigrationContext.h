// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Equipment/FGAmmoType.h"
#include "FGActorSaveHeaderTypes.h"
#include "SaveCustomVersion.h"
#include "UObject/Object.h"
#include "FWPSaveDataMigrationContext.generated.h"

USTRUCT()
struct FWPCellIdentifier
{
	GENERATED_BODY()
	
	FWPCellIdentifier(FName inGridName, FName inCellname)
		: GridName( inGridName )
		, CellName( inCellname )
		{}

	FWPCellIdentifier() = default;
	FWPCellIdentifier(const FWPCellIdentifier&) = default;
	FWPCellIdentifier(FWPCellIdentifier&&) = default;

	FWPCellIdentifier& operator=(const FWPCellIdentifier&) = default;
	FWPCellIdentifier& operator=(FWPCellIdentifier&&) = default;

	bool IsPersistentLevel() const
	{
		return GridName.IsNone() && CellName.IsNone();
	}

	UPROPERTY()
	FName GridName;

	UPROPERTY()
	FName CellName;
};

USTRUCT()
struct FWPGridValidationData
{
	GENERATED_BODY()
	
	UPROPERTY()
	int32 CellSize = 0;
	
	UPROPERTY()
	uint32 GridHash = 0;
	
	UPROPERTY()
	TMap<FName, uint32> CellHashes;
};

FORCEINLINE FArchive& operator<<(FArchive& ar, FWPGridValidationData& data)
{
	ar << data.CellSize;
	ar << data.GridHash;
	ar << data.CellHashes;
	return ar;
}

/**
 * 
 */
USTRUCT()
struct FWorldPartitionValidationData
{
	GENERATED_BODY()
	
	UPROPERTY()
	TMap<FName, FWPGridValidationData> Grids;
};

FORCEINLINE FArchive& operator<<(FArchive& ar, FWorldPartitionValidationData& data)
{
	ar << data.Grids;
	return ar;
}


struct FUninitializedObjectHeader {};

struct FObjectSaveData
{
	int32 SaveVersion = FSaveCustomVersion::LatestVersion;
	bool ShouldMigrateObjectRefsToPersistent = false;
	TArray< uint8 > Data;

	void Reset()
	{
		Data.Reset();
	}
	
	friend FArchive& operator<<(FArchive& Ar, FObjectSaveData& saveData) 
	{
		if( Ar.IsSaving() || ( Ar.IsLoading() && Ar.CustomVer( FSaveCustomVersion::GUID ) >= FSaveCustomVersion::IntroducedWorldPartition ) )
		{
			Ar << saveData.SaveVersion;
			Ar << saveData.ShouldMigrateObjectRefsToPersistent;	
		}
		else
		{
			// [Dylan 11/06/2024] Before we introduce actor custom version we should just use the archives custom version as a best approximation. The lack of this was causing migration issues from older saves
			if( Ar.IsLoading() )
			{
				int32 saveCustomVersion = Ar.CustomVer(  FSaveCustomVersion::GUID  );
				saveData.SaveVersion = saveCustomVersion;
			}
		}
		Ar << saveData.Data;
		return Ar;
	}
};

struct FGenericObjectSaveHeader
{
	TVariant<FUninitializedObjectHeader, FActorSaveHeader, FObjectSaveHeader> Header = {};

	const FObjectBaseSaveHeader& GetBaseHeader() const
	{
		return const_cast<FGenericObjectSaveHeader&>(*this).GetBaseHeader();;
	}

	FObjectBaseSaveHeader& GetBaseHeader()
	{
		if(Header.IsType<FActorSaveHeader>())
		{
			return Header.Get<FActorSaveHeader>().ObjectHeader;
		}
		
		return Header.Get<FObjectSaveHeader>().BaseHeader;
	}

	FObjectSaveHeader& GetObjectHeader()
	{
		return Header.Get<FObjectSaveHeader>();
	}

	FActorSaveHeader& GetActorHeader()
	{
		return Header.Get<FActorSaveHeader>();
	}

	bool IsActor() const
	{
		return Header.IsType<FActorSaveHeader>();
	}

	UClass* ResolveClass() const
	{
		return GetBaseHeader().ResolveClass();
	}

	/**
	 * @brief 
	 * @return whether this actor was placed in level or not. Only makes sense as long as this object is indeed an actor. See @IsActor
	 */
	bool WasPlacedInLevel() const
	{
		if(Header.IsType<FActorSaveHeader>())
		{
			return Header.Get<FActorSaveHeader>().WasPlacedInLevel;
		}
		return false;
	}

	friend FArchive& operator<<(FArchive& ar, FGenericObjectSaveHeader& objectSaveData)
	{
		if( ar.IsLoading() )
		{
			bool isActor = false;
			ar << isActor;
			if(isActor)
			{
				objectSaveData.Header.Emplace<FActorSaveHeader>();
				ar << objectSaveData.Header.Get<FActorSaveHeader>();
			}
			else
			{
				objectSaveData.Header.Emplace<FObjectSaveHeader>();
				ar << objectSaveData.Header.Get<FObjectSaveHeader>();
			}
		}
		else
		{
			bool isActor = objectSaveData.Header.IsType<FActorSaveHeader>();
			ar << isActor;
			
			if(objectSaveData.Header.IsType<FActorSaveHeader>())
			{
				ar << objectSaveData.Header.Get<FActorSaveHeader>();
			}
			else
			{
				ar << objectSaveData.Header.Get<FObjectSaveHeader>();
			}
		}

		return ar;
	}
};

struct FUnpackedSaveData
{
	TArray< FGenericObjectSaveHeader > Headers;
	TArray< FObjectSaveData > SaveData;
	TArray< FObjectReferenceDisc > DestroyedActors;
};

class FACTORYGAME_API FWPSaveDataMigrationContext
{
public:
	using FPackedSaveDataMap = TMap< FString, TUniquePtr<struct FPerStreamingLevelSaveData> >;
	
	FWPSaveDataMigrationContext( const class AFGWorldSettings &InWorldSettings, const struct FSaveHeader& InSaveHeader );
	FWPSaveDataMigrationContext( const FWPSaveDataMigrationContext&) = delete;
	FWPSaveDataMigrationContext( FWPSaveDataMigrationContext&&) = delete;
	~FWPSaveDataMigrationContext();

	/**
	 * Migrates the save data from an unpacked save data struct and stores it into the internal state of this context.
	 */ 
	void MigrateUnpackedData( FUnpackedSaveData& UnpackedSaveData, const bool DataIsFromPersistentLevel );

	/**
	 * Validates World Partitioned save data against the latest world partition state. Makes all the necessary save version checks and
	 * if appropriate it reads all the data from the provided archive
	 * @return whether the save can be loaded or not. eg If this function returns false, then the save is considered invalid
	 */ 
	bool ValidateSaveData( FArchive& ReadAr );

	/**
	 * Performs migration on all the outdated save data in the save session and stores the result in the provided save session.
	 */ 
	void PerformSaveDataMigration( class UFGSaveSession& SaveSession );
	
	static void SaveValidationData( FArchive& WriteAr, class UFGSaveSession& SaveSession );
#if WITH_EDITOR
	static void CollectSaveGameValidationData(const struct FSpatialHashStreamingGrid& Grid, const class UWorldPartitionRuntimeLevelStreamingCell& Cell, class AFGWorldSettings& WorldSettings);
	static void CollectSaveGameValidationDataForPersistentLevel(const ULevel& Level, class AFGWorldSettings& WorldSettings);
#endif
	
private:
	void MigrateBlobs( const TArray<uint8> &TOCBlob, const TArray<uint8> &DataBlob, const bool DataIsFromPersistentLevel );
	void MigrateBlobs( const TArray<uint8, TSizedDefaultAllocator<64>> &TOCBlob, const TArray<uint8, TSizedDefaultAllocator<64>> &DataBlo0b, const bool DataIsFromPersistentLevel );
	void MigrateDestroyedActors( const TArray<FObjectReferenceDisc>& DestroyedActors );
	void RepackSaveData( class UFGSaveSession& SaveSession );

	TMap< FName, FUnpackedSaveData > PerLevelUnpackedSaveData;
	const AFGWorldSettings &WorldSettings;
	const struct FSaveHeader& SaveHeader;
	TSet< FName > InvalidatedCells;
	bool bIsFullMigration = false;
};
