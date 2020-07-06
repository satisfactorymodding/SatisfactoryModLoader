// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/World.h"
#include "Array.h"
#include "GameFramework/Actor.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGSubsystem.h"
#include "FGSaveInterface.h"
#include "FGResourceSinkSubsystem.generated.h"

DECLARE_LOG_CATEGORY_EXTERN( LogResourceSink, Log, All );

/**
 * Subsystem to handle the resource sink and the rewards from sinked items
 */
UCLASS( Blueprintable, hidecategories = ( Actor, Input, Replication, Rendering, "Actor Tick" ) )
class FACTORYGAME_API AFGResourceSinkSubsystem : public AFGSubsystem, public IFGSaveInterface
{
	GENERATED_BODY()

public:
	AFGResourceSinkSubsystem();

	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;
	// End AActor interface

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override {}
	virtual bool NeedTransform_Implementation() override { return false; }
	virtual bool ShouldSave_Implementation() const override { return true; }
	// End IFSaveInterface

	/** Get the resource sink subsystem, this should always return something unless you call it really early. */
	static AFGResourceSinkSubsystem* Get( UWorld* world );

	/** Get the resource sink subsystem from a world context, this should always return something unless you call it really early. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|ResourceSink", DisplayName = "GetResourceSinkSubsystem", Meta = ( DefaultToSelf = "worldContext" ) )
	static AFGResourceSinkSubsystem* Get( UObject* worldContext );

	virtual void DisplayDebug( class UCanvas* canvas, const class FDebugDisplayInfo& debugDisplay, float& YL, float& YPos ) override;

	/** Add the resource sink points of the given item. Points are added to a thread safe queue and are added to the system later in the game thread
	*	Will only add points if the item can be discarded and is valued to at least 1 point. 
	*	Returns if the item could be sunk or not.
	*/
	bool AddPoints_ThreadSafe( TSubclassOf<class UFGItemDescriptor> item );

	/** Returns the total number of accumulated points for all resource sinks */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|ResourceSink" )
	FORCEINLINE int64 GetNumTotalPoints() const { return mTotalResourceSinkPoints; }
	
	/** Returns an array with the global point per minute history. Sorted from old to new */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|ResourceSink" )
	FORCEINLINE TArray<int32> GetGlobalPointHistory() const { return mGlobalPointHistory; }

	/** Returns the number of available resource sink coupons */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|ResourceSink" )
	FORCEINLINE int32 GetNumCoupons() const { return mNumResourceSinkCoupons; }
	
	/** Returns the number of points left until you receive the next coupon */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|ResourceSink" )
	int32 GetNumPointsToNextCoupon() const;
	
	/** Returns the percentage (normalized value) of your progression towards the next coupon */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|ResourceSink" )
	float GetProgressionTowardsNextCoupon() const;

	/** Return the item descriptor class that we use as coupon */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|ResourceSink" )
	FORCEINLINE class TSubclassOf< class UFGItemDescriptor > GetCouponClass() const { return mCouponClass; }

	/** Returns the number of coupons this schematic costs  */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|ResourceSink" )
	int32 GetCostOfSchematics( TArray< TSubclassOf< class UFGSchematic > > schematics ) const;
	
	/** Does the given player inventory contain enough coupons to purchase the given schematics */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|ResourceSink" )
	bool CanAffordResourceSinkSchematics( UFGInventoryComponent* playerInventory, TArray< TSubclassOf< class UFGSchematic > > schematics ) const;

	/** Purchase the the given schematics. The cost of the schematics in coupons will be removed from the given player inventory
	* Returns true if we could afford all schematics and none of them are already purchased
	*/
	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "FactoryGame|ResourceSink", meta = ( DeprecatedFunction, DeprecationMessage = "Use PurchaseResourceSinkSchematics() from resource sink shop instead" ) )
	bool PurchaseResourceSinkSchematics( class UFGInventoryComponent* playerInventory, TArray< TSubclassOf< class UFGSchematic > > schematics );

	/** Add resource sink coupons to the resource sink subsystem */
	void AddResourceSinkCoupons( int32 numCoupons );

	/** Remove resource sink coupons from the resource sink subsystem
	* Returns how many coupons that were removed
	*/
	int32 RemoveResourceSinkCoupons( int32 numCoupons );

	int32 GetResourceSinkPointsForItem( TSubclassOf< class UFGItemDescriptor > itemDescriptor );

private:
	/** Handle the points added to the point queue and adds them to the system */
	void HandleQueuedPoints();

	/** Handle the items added to the item queue and plays messages */
	void HandleQueuedFailedItems();

	/** Init and load the coupon class that we use for buying resource sink schematics. Defined in project settings */
	void InitCouponClass();
	
	/** Calculate the current coupon level and gives more coupons if we reached a new level */
	void CalculateLevel();

	/** Returns the required poins to reach the given point level */
	int64 GetRequiredPointsForLevel( int32 level ) const;

	/** Sums up how many points we accumulated the last interval and adds it to the history data */
	void CalculateAccumulatedPointsPastInterval();

	/** Used to trigger cyber coupon events from non-game thread */
	UFUNCTION()
	void TriggerCyberCoupon();

private:
	/** The cached schematic manager */
	UPROPERTY( Transient )
	class AFGSchematicManager* mSchematicManager;

	/** The coupon class that we use for buying resource sink schematics */
	UPROPERTY( Transient )
	TSubclassOf< class UFGItemDescriptor > mCouponClass;

	/** The total number of resource sink points we have accumulated in total */
	UPROPERTY( SaveGame, Replicated )
	int64 mTotalResourceSinkPoints;

	/** The number of resource sink points we have accumulated the last interval */
	int32 mAccumulatedPointsPastInterval;

	/** Thread safe queue where we store the points that have been given by resource sinks during the factory tick */
	TQueue<int32, EQueueMode::Mpsc> mQueuedPoints;

	/** Thread safe queue where we store the failed items that have been tried to be sinked and failed by resource sinks during the factory tick */
	TQueue<TSubclassOf<UFGItemDescriptor>, EQueueMode::Mpsc> mQueuedFailedItems;

	/** The number of data points for the global resource sink subsystem history */
	int32 mGlobalHistorySize;

	/** The current point level we have reached, this value only increases and isn't not affected by printing coupons  */
	UPROPERTY( SaveGame, Replicated )
	int32 mCurrentPointLevel;

	/** The number of coupons we have to our disposal to print and use */
	UPROPERTY( SaveGame, Replicated )
	int32 mNumResourceSinkCoupons;

	/** The data for the global points history of the resource sink subsystem */
	UPROPERTY( SaveGame, Replicated )
	TArray<int32> mGlobalPointHistory;

	/** The timer handle that is used to trigger updates of the global points history of the resource sink subsystem */
	FTimerHandle mCalculateHistoryTimer;
//MODDING EDIT:
public:
	/** Cached points per itemdescriptor */
	UPROPERTY( Transient )
	TMap< TSubclassOf< class UFGItemDescriptor >, int32 > mResourceSinkPoints;
private:
	/** Cached number of points we need to reach to unlock a new coupon */
	TArray<int64> mRewardLevels;
	
	/** The number of points we need to reach to unlock a new coupon after we have reached the defined reward levels */
	int64 mOverflowDeltaPoints;

	/** The messages that should play if the player tries to sink a item that you can't sink */
	UPROPERTY( Transient )
	TMap<TSubclassOf<class UFGItemDescriptor>, TSubclassOf<class UFGMessageBase>> mFailedItemSinkMessages;
	
	/** The items that the player tried to sink that you can't sink that is also present in mFailedItemSinkMessages */
	UPROPERTY( SaveGame )
	TArray<TSubclassOf<class UFGItemDescriptor>> mItemsFailedToSink;

	/** Have we ever tried to sink any item that you can't sink that is not present in mFailedItemSinkMessages */
	UPROPERTY( SaveGame )
	bool mAnyGenericItemsFailedToSink;

	/** Have we sunken a item of the coupon class, Used to give a schematic */
	UPROPERTY( SaveGame )
	bool mIsCouponEverSunk;

public:
	FORCEINLINE ~AFGResourceSinkSubsystem() = default;
};
