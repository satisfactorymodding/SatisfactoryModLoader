// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGSaveInterface.h"
#include "FGSubsystem.h"
#include "ItemAmount.h"
#include "FGCentralStorageSubsystem.generated.h"

DECLARE_LOG_CATEGORY_EXTERN( LogCentralStorage, Log, All );

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FCentralStorageAddedOrRemovedDelegate );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnCentralStorageNewItemAddedDelegate, TSubclassOf<class UFGItemDescriptor>, newItemDescriptor );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnCentralStorageItemAmountUpdatedDelegate, TSubclassOf<class UFGItemDescriptor>, newItemDescriptor, int32, newItemAmount );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnCentralStorageItemLimitReachedUpdated, TSubclassOf< class UFGItemDescriptor >, itemDescriptor, bool, itemLimitReached );


/**
 * Handles the central storage system in the game.
 */
UCLASS( Blueprintable )
class FACTORYGAME_API AFGCentralStorageSubsystem : public AFGSubsystem, public IFGSaveInterface
{
	GENERATED_BODY()
	
public:
	AFGCentralStorageSubsystem();

	/** Get the central storage, this should always return something unless you call it really early. */
	static AFGCentralStorageSubsystem* Get( UWorld* world );

	/** Get the central storage from a world context, this should always return something unless you call it really early. */
	UFUNCTION( BlueprintPure, Category = "Central Storage", DisplayName = "GetCentralStorage", Meta = ( DefaultToSelf = "worldContext" ) )
	static AFGCentralStorageSubsystem* Get( UObject* worldContext );
	
	// Begin AActor Interface
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	virtual void DisplayDebug( class UCanvas* canvas, const class FDebugDisplayInfo& debugDisplay, float& YL, float& YPos ) override;
	// End AActor Interface

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override {}
	virtual bool NeedTransform_Implementation() override { return false; }
	virtual bool ShouldSave_Implementation() const override { return true; }
	// End IFSaveInterface
	
	/** @return True if we've at least 1 central storage built; false if 0. */
	UFUNCTION( BlueprintPure, Category = "Central Storage" )
	bool IsCentralStorageBuilt() const { return mCentralStorages.Num() > 0; }

	/** @return All central storages built; empty if none built. */
	UFUNCTION( BlueprintCallable, Category = "Central Storage" )
	FORCEINLINE TArray< class AFGCentralStorageContainer* > GetCentralStorageContainers() { return mCentralStorages; }

	/** @return Number of items available across all the central storages. */
	UFUNCTION( BlueprintCallable, Category = "Central Storage" )
	int32 GetNumItemsFromCentralStorage( TSubclassOf< class UFGItemDescriptor > itemClass );

	UFUNCTION( BlueprintCallable, Category = "Central Storage" )
	void GetAllItemsFromCentralStorage( TArray<FItemAmount>& out_allItems );
	
	/**
	 * Tries to remove the number of specified items from the central storage. Returns how many items we could remove
	 *
	 * @param itemClass - Type of items to remove.
	 * @param numToRemove - Number of items to remove. Must be >= 0. If count is more than the items available, a partial remove is done and a warning is raised.
	 * @return Number of items that we could remove.
	 */
	int32 TryRemoveItemsFromCentralStorage( TSubclassOf< class UFGItemDescriptor > itemClass, const int32 numToRemove );
	
	/** Called by the central storage when built/destroyed. */
	void AddCentralStorage( class AFGCentralStorageContainer* centralStorage );
	void RemoveCentralStorage( class AFGCentralStorageContainer* centralStorage );

	/** If we can hold an item of the given class we upload it and remove it from the given inventory */ 
	bool UploadItemFromInventoryToCentralStorage( class UFGInventoryComponent* inventoryComponent, int32 slotIndexToRemoveFrom, TSubclassOf< class UFGItemDescriptor > inClass );

	/** Return true if we can add more of the given item descriptor class */ 
	UFUNCTION( BlueprintPure, Category = "Central Storage" )
	bool CanUploadItemsToCentralStorage( TSubclassOf<class UFGItemDescriptor> inClass ) const;

	/** Returns the total number of items we can store of the given item descriptor class */ 
	UFUNCTION( BlueprintPure, Category = "Central Storage" )
	int32 GetCentralStorageItemLimit(TSubclassOf< class UFGItemDescriptor > inClass) const;

	/** Returns the total number of item stacks we can store of any item descriptor class */ 
	UFUNCTION( BlueprintPure, Category = "Central Storage" )
	int32 GetCentralStorageItemStackLimit() const { return mItemStackLimit; }

	/** Returns how long it takes to upload an item to central storage in seconds */ 
	UFUNCTION( BlueprintPure, Category = "Central Storage", meta=( KeyWords="Upload Speed Time") )
	float GetCentralStorageTimeToUpload() const;

	UFUNCTION()
	void UpdateItemStackLimit();

	UFUNCTION( BlueprintCallable )
	void SortItemsInStorage();

protected:
	UFUNCTION()
	void OnRep_StorageUpdated() const;

	UFUNCTION( NetMulticast, Reliable )
	void Client_NewItemAddedToCentralStorage( TSubclassOf<UFGItemDescriptor> inClass );
	
private:
	void OnCentralStorageItemLimitReachedUpdated( TSubclassOf< class UFGItemDescriptor > itemDescriptor, bool itemLimitReached );

public:
	/** Called when a central storage has been removed */
	UPROPERTY( BlueprintAssignable, Category = "Central Storage", DisplayName = "OnCentralStorageAddedOrRemoved" )
	FCentralStorageAddedOrRemovedDelegate CentralStorageAddedOrRemoved;

	/** Called when a new item class has been added to the central storage */
	UPROPERTY( BlueprintAssignable, Category = "Central Storage" )
	FOnCentralStorageNewItemAddedDelegate mOnCentralStorageNewItemAddedDelegate;

	/** Called whenever an amount of an item in the central storage changes. */
	UPROPERTY( BlueprintAssignable, Category = "Central Storage" )
	FOnCentralStorageItemAmountUpdatedDelegate mOnCentralStorageItemAmountUpdatedDelegate;

	/** Called when we reached or went back under the item limit  */
	UPROPERTY( BlueprintAssignable, Category = "Central Storage" )
	FOnCentralStorageItemLimitReachedUpdated mOnCentralStorageItemLimitReachedUpdated;

private:
	/** All the central storages built. */
	UPROPERTY()
	TArray< class AFGCentralStorageContainer* > mCentralStorages;

	UPROPERTY( SaveGame, ReplicatedUsing=OnRep_StorageUpdated )
	TArray< FItemAmount > mStoredItems;

	/** The number of stacks per item we can store */
	UPROPERTY( Transient, Replicated )
	int32 mItemStackLimit;

	UPROPERTY( Transient )
	TMap< TSubclassOf<UFGItemDescriptor>, bool > mIsItemLimitReached;
	
};
