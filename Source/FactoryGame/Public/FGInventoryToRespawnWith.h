// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Containers/Map.h"
#include "Containers/Array.h"
#include "Equipment/FGEquipment.h"
#include "FGInventoryComponent.h"

#include "FGInventoryToRespawnWith.generated.h"

// This struct only exists to work around an issue where UnrealHeaderTool won't let me use TArrays in TMaps.
USTRUCT()
struct FACTORYGAME_API FArrayOfInventoryStacksHolder final
{
	GENERATED_BODY()

	UPROPERTY( SaveGame )
	TArray< FInventoryStack > mArrayOfInventoryStacks;
};

USTRUCT()
struct FACTORYGAME_API FInventoryToRespawnWith final
{
	GENERATED_BODY()

	bool IsAnyInventoryStackRadioactive( TArray<int>& out_RadioActiveItemStackIndices ) const
	{
		for( int i = 0; i < mInventoryStacks.Num(); i++ )
		{
			if( UFGItemDescriptor::GetRadioactiveDecay( mInventoryStacks[i].Item.GetItemClass() ) > 0.0f )
			{
				out_RadioActiveItemStackIndices.Push( i );
			}
		}
		for( int i = 0; i < mCentralStoragePendingInventoryStacks.Num(); i++ )
		{
			if( UFGItemDescriptor::GetRadioactiveDecay( mCentralStoragePendingInventoryStacks[i].Item.GetItemClass() ) > 0.0f )
			{
				out_RadioActiveItemStackIndices.Push( i );
			}
		}
		
		return !out_RadioActiveItemStackIndices.IsEmpty();
	}
	
	// Inventory
	UPROPERTY( SaveGame )
	TArray< FInventoryStack > mInventoryStacks;
	// Inventory to upload to Central Storage.
	UPROPERTY( SaveGame )
	TArray< FInventoryStack > mCentralStoragePendingInventoryStacks;
	// Equipment
	UPROPERTY( SaveGame )
	TMap< EEquipmentSlot, FArrayOfInventoryStacksHolder > mEquipmentPairs;

	// Additional data you are willing to persist until the respawn. Objects in question should implement IFGSaveGameInterface and be parented to the level or to the player state
	UPROPERTY( SaveGame )
	TMap< FString, UObject* > mMetadata;
};