// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGFoliageTypes.generated.h"

USTRUCT()
struct FHashableVectorWrapper
{
	GENERATED_BODY()

	FHashableVectorWrapper(const FVector& InLoc)
		: Location(InLoc) {}

	FHashableVectorWrapper() = default;
	
	UPROPERTY(VisibleAnywhere, SaveGame)
	FVector Location = FVector::ZeroVector;
	
	bool operator<(const FVector &V) const;
	FORCEINLINE bool operator<(const FHashableVectorWrapper& Other) const
	{
		return *this < Other.Location;
	}
	
	FORCEINLINE bool operator== (const FVector &V) const
	{
		return Location.Equals( V );
	}
	
	FORCEINLINE bool operator== (const FHashableVectorWrapper &V) const
	{
		return *this == V.Location;
	}
};

uint32 GetTypeHash(const FHashableVectorWrapper& Loc);

USTRUCT()
struct FFoliageRemovalDataKey
{
	GENERATED_BODY()

	UPROPERTY(SaveGame)
	FIntVector CellCoord;

	UPROPERTY(SaveGame)
	TObjectPtr<const class UFoliageType> FoliageType;

	bool operator==(const FFoliageRemovalDataKey&) const;
};

FORCEINLINE uint32 GetTypeHash( const FFoliageRemovalDataKey& saveDataKey )
{
	return HashCombine( GetTypeHash( saveDataKey.CellCoord ), GetTypeHash( saveDataKey.FoliageType ) );
}

/**
 * A struct that can be used to uniquely identify a foliage instance accross the network. Used for replication. 
 */
USTRUCT()
struct FFoliageInstanceStableId
{
	GENERATED_BODY()
	
	inline operator bool() const
	{
		return InstanceHash != 0 && FoliageType;
	}

	UPROPERTY()
	uint32 InstanceHash = 0;

	UPROPERTY()
	class UFoliageType* FoliageType = nullptr;

	UPROPERTY()
	FIntVector FoliageCell = {};
};

/// A map per foliage cell per foliage type parameterized over @ValueType
template< typename ValueType >
using TPerCellPerTypeMap = TMap< FIntVector, TMap< const UFoliageType*, ValueType > >;