// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGSubsystem.h"
#include "FGSaveInterface.h"
#include "Containers/Queue.h"
#include "Misc/EnumRange.h"
#include "FGResourceSinkSubsystem.generated.h"

FACTORYGAME_API DECLARE_LOG_CATEGORY_EXTERN( LogResourceSink, Log, All );

UENUM( BlueprintType )
enum class EResourceSinkTrack : uint8
{
	RST_Default		= 0			UMETA( DisplayName = "Default" ),
	RST_Exploration	= 1			UMETA( DisplayName = "Exploration" ),
	RST_MAX			= 2			UMETA( Hidden )
};

/** For now this just mirrors EResourceSinkTrack with an extra none. I know there have been talks about adding coupons besides from the tracks
  *	so will this as a separate enum for coupon source
  */	
UENUM( BlueprintType )
enum class ECouponSource : uint8
{
	CS_None					UMETA( DisplayName = "None" ), 
	CS_DefaultTrack			UMETA( DisplayName = "Default Track" ), 
	CS_ExplorationTrack		UMETA( DisplayName = "Exploration Track" )
};

ENUM_RANGE_BY_COUNT(EResourceSinkTrack, EResourceSinkTrack::RST_MAX);

USTRUCT()
struct FResourceSinkHistory
{
	GENERATED_BODY()

	FResourceSinkHistory(){}
	FResourceSinkHistory( int32 numValues )
	{
		Values.AddZeroed( numValues );
	}
	FResourceSinkHistory( TArray<int32> values ) :
		Values( values )
	{}

	UPROPERTY( SaveGame )
	TArray<int32> Values;
};

USTRUCT()
struct FResourceSinkValuePair32
{
	GENERATED_BODY()

	FResourceSinkValuePair32(){}
	FResourceSinkValuePair32( EResourceSinkTrack trackType, int32 value ) :
		TrackType( trackType ),
		Value( value )
	{}
	
	UPROPERTY()
	EResourceSinkTrack TrackType;

	UPROPERTY()
	int32 Value;
};

DECLARE_MULTICAST_DELEGATE_OneParam( FOnFirstItemSinkFailure, TSubclassOf<class UFGItemDescriptor> );

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

	void SetupRewardLevelData( EResourceSinkTrack ResourceSinkTrack, class UDataTable* rewardLevelsDataTable );
	void SetupPointData( EResourceSinkTrack ResourceSinkTrack, class UDataTable* pointsDataTable );

	virtual void DisplayDebug( class UCanvas* canvas, const class FDebugDisplayInfo& debugDisplay, float& YL, float& YPos ) override;

	/** Add the resource sink points of the given item. Points are added to a thread safe queue and are added to the system later in the game thread
	*	Will only add points if the item can be discarded and is valued to at least 1 point. 
	*	Returns true if the item could be sunk.
	*/
	bool AddPoints_ThreadSafe( TSubclassOf<class UFGItemDescriptor> item );

	/** Returns the total number of accumulated points for all resource sinks */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|ResourceSink" )
	int64 GetNumTotalPoints( EResourceSinkTrack resourceSinkTrack ) const;

	/** Returns an array with the global point per minute history. Sorted from old to new */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|ResourceSink" )
	TArray<int32> GetGlobalPointHistory( EResourceSinkTrack resourceSinkTrack ) const;

	/** Returns the number of available resource sink coupons */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|ResourceSink" )
	FORCEINLINE int32 GetNumCoupons() const { return mNumResourceSinkCoupons; }
	
	/** Returns the number of points left until you receive the next coupon for the given track */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|ResourceSink" )
	int64 GetNumPointsToNextCoupon( EResourceSinkTrack resourceSinkTrack ) const;
	
	/** Returns the percentage (normalized value) of your progression towards the next coupon */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|ResourceSink" )
	float GetProgressionTowardsNextCoupon( EResourceSinkTrack resourceSinkTrack ) const;

	/** Return the item descriptor class that we use as coupon */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|ResourceSink" )
	FORCEINLINE class TSubclassOf< class UFGItemDescriptor > GetCouponClass() const { return mCouponClass; }

	/** Returns the number of coupons this schematic costs  */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|ResourceSink" )
	int32 GetCostOfSchematics( TArray< TSubclassOf< class UFGSchematic > > schematics ) const;
	
	/** Does the given player inventory contain enough coupons to purchase the given schematics */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|ResourceSink" )
	bool CanAffordResourceSinkSchematics( class UFGInventoryComponent* playerInventory, TArray< TSubclassOf< class UFGSchematic > > schematics ) const;

	/** Returns true if we have earned one or more coupons on the given track since we last called this function */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|ResourceSink" )
	bool HasTrackGivenCouponSinceLastCheck( EResourceSinkTrack resourceSinkTrack );

	/** Purchase the the given schematics. The cost of the schematics in coupons will be removed from the given player inventory
	* Returns true if we could afford all schematics and none of them are already purchased
	*/
	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "FactoryGame|ResourceSink", meta = ( DeprecatedFunction, DeprecationMessage = "Use PurchaseResourceSinkSchematics() from resource sink shop instead" ) )
	bool PurchaseResourceSinkSchematics( class UFGInventoryComponent* playerInventory, TArray< TSubclassOf< class UFGSchematic > > schematics );

	/** Add resource sink coupons to the resource sink subsystem
	 * @param sendTelemetryData: Should be true for first time a coupone is created. Then we should send telemtry data.
	 * This should not be true when we return already createad coupons
	 */
	UFUNCTION( BlueprintCallable, Category="FactoryGame|ResourceSink" )
	void AddResourceSinkCoupons( int32 numCoupons, bool sendTelemetryData, ECouponSource couponSource = ECouponSource::CS_None );

	/** Remove resource sink coupons from the resource sink subsystem
	* Returns how many coupons that were removed
	* 
	*/
	int32 RemoveResourceSinkCoupons( int32 numCoupons );

	int32 GetResourceSinkPointsForItem( TSubclassOf< class UFGItemDescriptor > itemDescriptor );

	UFUNCTION( BlueprintPure, Category = "FactoryGame|ResourceSink" )
	bool FindResourceSinkPointsForItem( TSubclassOf< class UFGItemDescriptor > itemDescriptor, int32& out_numPoints, EResourceSinkTrack& out_itemTrack );

	// Called when we fail to sink an item the first time. Can be called once per item descriptor
	FOnFirstItemSinkFailure mOnFirstItemSinkFailure;
private:
	/** Handle the points added to the point queue and adds them to the system */
	void HandleQueuedPoints();

	/** Handle the items added to the item queue and plays messages */
	void HandleQueuedFailedItems();

	/** Init and load the coupon class that we use for buying resource sink schematics. Defined in project settings */
	void InitCouponClass();
	
	/** Calculate the current coupon level and gives more coupons if we reached a new level */
	void CalculateLevel();
	
	int32 GetCurrentPointLevel( EResourceSinkTrack resourceSinkTrack ) const;
	
	/** Returns the required poins to reach the given point level */
	int64 GetRequiredPointsForLevel( EResourceSinkTrack resourceSinkTrack, int32 level ) const;

	/** Sums up how many points we accumulated the last interval and adds it to the history data */
	void CalculateAccumulatedPointsPastInterval();

	/** Used to trigger cyber coupon events from non-game thread */
	UFUNCTION()
	void TriggerCyberCoupon();

	UFUNCTION()
	void TriggerCustomReward( TSubclassOf< class UFGItemDescriptor> item );

	int32 GetNumTotalCouponsFromSource( ECouponSource couponSource ) const;

private:
	/** The coupon class that we use for buying resource sink schematics */
	UPROPERTY( Transient )
	TSubclassOf< class UFGItemDescriptor > mCouponClass;
	
	/** The total number of resource sink points we have accumulated in total 
	 *	The index in the array is matched to the EResourceSinkTrack integer value
	 */
	UPROPERTY( SaveGame, Replicated )
	TArray< int64 > mTotalPoints;
	UPROPERTY( SaveGame ) // DEPRECATED replaced by mTotalPoints. Still left for migration to new system
	int64 mTotalResourceSinkPoints;

	/** The number of resource sink points we have accumulated the last interval */
	TMap< EResourceSinkTrack, int32 > mAccumulatedPointsPastInterval;

	/** Thread safe queue where we store the points that have been given by resource sinks during the factory tick */
	TQueue<FResourceSinkValuePair32, EQueueMode::Mpsc> mQueuedPoints;
	
	/** Thread safe queue where we store the failed items that have been tried to be sinked and failed by resource sinks during the factory tick */
	TQueue<TSubclassOf<UFGItemDescriptor>, EQueueMode::Mpsc> mQueuedFailedItems;

	/** Used to keeps track if we have earned one or more coupons on the given track since we last called this function
	 *	At the start of the game it's equal to the current point level for each track. When HasTrackGivenCouponSinceLastCheck is called it's updated
	 *	to the current value. We can then compare the next time HasTrackGivenCouponSinceLastCheck is called if we have earned coupons or not
	 *	The index in the array is matched to the EResourceSinkTrack integer value
	 */
	UPROPERTY( Transient )
	TArray< int32 > mLastSeenPointLevel;

	/** The number of data points for the global resource sink subsystem history */
	int32 mGlobalHistorySize;
	
	/** The current point level we have reached, this value only increases and isn't affected by printing coupons 
	 *	The index in the array is matched to the EResourceSinkTrack integer value
	 */
	UPROPERTY( SaveGame, Replicated )
	TArray< int32 > mCurrentPointLevels;
	UPROPERTY( SaveGame ) // DEPRECATED replaced by mCurrentPointLevels. Still left for migration to new system
	int32 mCurrentPointLevel;

	/** The number of coupons we have to our disposal to print and use */
	UPROPERTY( SaveGame, Replicated )
	int32 mNumResourceSinkCoupons;
	
	/** The data for the global points history of the resource sink subsystem 
	 *	The index in the array is matched to the EResourceSinkTrack integer value
	 */
	UPROPERTY( SaveGame, Replicated )
	TArray< FResourceSinkHistory > mGlobalPointHistoryValues;
	UPROPERTY( SaveGame ) // DEPRECATED replaced by mGlobalPointHistoryValues. Still left for migration to new system
	TArray<int32> mGlobalPointHistory;

	/** The timer handle that is used to trigger updates of the global points history of the resource sink subsystem */
	FTimerHandle mCalculateHistoryTimer;

	/** Cached points per item descriptor */
	UPROPERTY( Transient ) 
	TMap< TSubclassOf< class UFGItemDescriptor >, FResourceSinkValuePair32 > mCachedResourceSinkPoints;
	
	/** Cached number of points we need to reach to unlock a new coupon */
	TMap< EResourceSinkTrack, TArray<int64> > mRewardLevels;
	
	/** The number of points we need to reach to unlock a new coupon after we have reached the defined reward levels */
	TMap< EResourceSinkTrack, int64 > mOverflowDeltaPoints;
	
	/** Items attempted to be sunk by the player but are unsinkable */
	UPROPERTY( SaveGame )
	TArray<TSubclassOf<class UFGItemDescriptor>> mItemsFailedToSink;

	/** Have we sunken a item of the coupon class, Used to give a schematic */
	UPROPERTY( SaveGame )
	bool mIsCouponEverSunk;

	/** Items with custom rewards that we want to check if we sink. Populated in begin play and should only contains unsunk items, and yes it's a horrible variable name */
	UPROPERTY( Transient )
	TSet<TSubclassOf<class UFGItemDescriptor> > mNotYetSunkenItemsWithCustomReward;

	/** Lists sunken item that have a special reward that we want to know if they been sunk or not, Used to give rewards */
	UPROPERTY( SaveGame )
	TSet<TSubclassOf<class UFGItemDescriptor> > mSunkenItemsWithCustomReward;

		
};
