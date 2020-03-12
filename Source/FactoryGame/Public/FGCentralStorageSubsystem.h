// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/World.h"
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGSubsystem.h"
#include "FGCentralStorageSubsystem.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE( FCentralStorageAddedOrRemovedDelegate );


/**
 * Handles the central storage system in the game.
 */
UCLASS( Blueprintable )
class FACTORYGAME_API AFGCentralStorageSubsystem : public AFGSubsystem
{
	GENERATED_BODY()
public:
	/** Called when a central storage has been removed */
	UPROPERTY( BlueprintAssignable, Category = "Central Storage", DisplayName = "OnCentralStorageAddedOrRemoved" )
	FCentralStorageAddedOrRemovedDelegate CentralStorageAddedOrRemoved;

public:
	/** Get the central storage, this should always return something unless you call it really early. */
	static AFGCentralStorageSubsystem* Get( UWorld* world );

	/** Get the central storage from a world context, this should always return something unless you call it really early. */
	UFUNCTION( BlueprintPure, Category = "Central Storage", DisplayName = "GetCentralStorage", Meta = ( DefaultToSelf = "worldContext" ) )
	static AFGCentralStorageSubsystem* Get( UObject* worldContext );

public:
	AFGCentralStorageSubsystem();

	/** @return True if we've at least 1 central storage built; false if 0. */
	UFUNCTION( BlueprintPure, Category = "Central Storage" )
	bool IsCentralStorageBuilt() const { return mCentralStorages.Num() > 0; }

	/** @return All central storages built; empty if none built. */
	UFUNCTION( BlueprintCallable, Category = "Central Storage" )
	FORCEINLINE TArray< class AFGCentralStorageContainer* > GetCentralStorageContainers() { return mCentralStorages; }

	/** @return Number of items available across all the central storages. */
	UFUNCTION( BlueprintCallable, Category = "Central Storage" )
	int32 GetNumItemsFromCentralStorage( TSubclassOf< class UFGItemDescriptor > itemClass );

	/**
	 * Removes the number of specified items across all central storages.
	 *
	 * @param itemClass - Type of items to remove.
	 * @param num - Number of items to remove. Must be >= 0. If count is more than the items available, a partial remove is done and a warning is raised.
	 */
	UFUNCTION( BlueprintCallable, BlueprintAuthorityOnly, Category = "Central Storage" )
	void RemoveItemsFromCentralStorage( TSubclassOf< class UFGItemDescriptor > itemClass, int32 num );

	/** Called by the central storage when built/destroyed. */
	void AddCentralStorage( class AFGCentralStorageContainer* centralStorage );
	void RemoveCentralStorage( class AFGCentralStorageContainer* centralStorage );

private:
	/** All the central storages built. */
	UPROPERTY()
	TArray< class AFGCentralStorageContainer* > mCentralStorages;

public:
	FORCEINLINE ~AFGCentralStorageSubsystem() = default;
};
