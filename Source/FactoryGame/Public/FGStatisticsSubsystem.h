// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGSubsystem.h"
#include "FGSaveInterface.h"
#include "ItemAmount.h"
#include "FGInventoryComponent.h"
#include "FGStatisticsSubsystem.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams( FOnItemPickedUp, class AFGPlayerState*, const FItemAmount& /*totalAmountPickuped*/ );
DECLARE_MULTICAST_DELEGATE_TwoParams( FOnItemManuallyCrafted, class AFGPlayerState*, const FItemAmount& /*totalAmountCrafted*/ );
DECLARE_MULTICAST_DELEGATE_ThreeParams( FOnBuildingBuilt, class AFGPlayerState*, TSubclassOf< class AActor >, int64 /*totalAmountBuilt*/ );
DECLARE_MULTICAST_DELEGATE_ThreeParams( FOnBuildingDismantled, class AFGPlayerState*, TSubclassOf< class AActor >, int64 /*totalAmountDismantled*/ );

/** Data to store the number of actors we built and dismantled with the buildgun. We map this struct to an actor class. A building or vehicle for example */
USTRUCT()
struct FActorBuiltData
{
	GENERATED_BODY()
	
	/** The total amount of built actors per player */
	UPROPERTY( SaveGame )
	TMap< class AFGPlayerState*, int64 > BuiltPerPlayer;

	/** The total amount of dismantled actors per player */
	UPROPERTY( SaveGame )
	TMap< class AFGPlayerState*, int64 > DismantledPerPlayer;
	
	/** The current amount of built actors that is in the world */
	UPROPERTY( SaveGame )
	int64 Current;

	/** The maximum amount of built actors that have been in the world, i.e highest number that ever been assigned to Current */
	UPROPERTY( SaveGame )
	int64 CurrentMax;

	/** The total amount of actors built in this world. Dismantle doesn't affect this number */
	UPROPERTY( SaveGame )
	int64 Total;

	/** The total amount of actors dismantled. */
	UPROPERTY( SaveGame )
	int64 TotalDismantled;
	
};

/**
 * 	Handles statistics of the game, such as the number of buildings built and enemies killed.
 * 	Mostly used for in-game dependencies and to trigger narrative messages.
 *	Note: Currently it's server only. Nothing is replicated and stat events should not trigger on client
 */
UCLASS( hidecategories = ( Actor, Input, Replication, Rendering, "Actor Tick", LOD, Cooking ) )
class FACTORYGAME_API AFGStatisticsSubsystem : public AFGSubsystem, public IFGSaveInterface
{
	GENERATED_BODY()

public:
	/** Get the Statistics Subsystem, this should always return something unless you call it really early. */
	static AFGStatisticsSubsystem* Get( UWorld* world );

	/** Get the Statistics Subsystem from a world context, this should always return something unless you call it really early. */
	UFUNCTION( BlueprintPure, Category = "Statistics", DisplayName = "GetStatisticsSubsystem", Meta = ( DefaultToSelf = "worldContext" ) )
    static AFGStatisticsSubsystem* Get( UObject* worldContext );

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override{}
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override{}
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override{}
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override{}
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override{}
	virtual bool NeedTransform_Implementation() override { return false; }
	virtual bool ShouldSave_Implementation() const override { return true; }
	// End IFSaveInterface

	UFUNCTION( BlueprintCallable, Category = "Statistics" )
	void Stat_ConsumableConsumed( TSubclassOf< class UFGConsumableDescriptor > consumable, int32 numConsumed = 1 );
	int32 Stat_GetNumConsumableConsumed( TSubclassOf< class UFGConsumableDescriptor > consumable );

	void Stat_CreatureKilled( TSubclassOf< class AFGCreature > creature, int32 numKilled = 1 );
	int32 Stat_GetNumCreatureKilled( TSubclassOf< class AFGCreature > creature );

    void Stat_ItemsManuallyCrafted( TSubclassOf< class UFGItemDescriptor > itemDescriptor, class AFGPlayerState* playerState, int32 numCrafted = 1 );
    int32 Stat_GetNumItemsManuallyCrafted( TSubclassOf< class UFGItemDescriptor > itemDescriptor, class AFGPlayerState* playerState );
    int32 Stat_GetNumItemsManuallyCrafted( TSubclassOf< class UFGItemDescriptor > itemDescriptor );

	void Stat_ActorBuilt( TSubclassOf< class AActor > actor, class AFGPlayerState* playerState, int32 numBuilt = 1 );
	void Stat_ActorDismantled( TSubclassOf< class AActor > actor, class AFGPlayerState* playerState, int32 numDismantled = 1 );
	int32 Stat_GetNumActorsBuilt_Current( TSubclassOf< class AActor > actor );
	int32 Stat_GetNumActorsBuilt_CurrentMax( TSubclassOf< class AActor > actor );
	int32 Stat_GetNumActorsBuilt_Total( TSubclassOf< class AActor > actor );
	int32 Stat_GetNumActorsBuilt_TotalDismantled( TSubclassOf< class AActor > actor );
	int32 Stat_GetNumActorsBuilt_BuiltPerPlayer( TSubclassOf< class AActor > actor, class AFGPlayerState* playerState );
	int32 Stat_GetNumActorsBuilt_DismantledPerPlayer( TSubclassOf< class AActor > actor, class AFGPlayerState* playerState );

	void Stat_ItemsPickedUp( TSubclassOf< class UFGItemDescriptor > itemDescriptor, class AFGPlayerState* playerState, int32 numPickedup = 1 );
	void Stat_ItemsPickedUp( const TArray< FInventoryStack >& inventoryStacks, class AFGPlayerState* playerState );
	int32 Stat_GetNumItemsPickedUp( TSubclassOf< class UFGItemDescriptor > itemDescriptor, class AFGPlayerState* playerState );
	
	void GetStatisticsDebugData( TArray<FString>& out_debugData );

	/* Called from FGbackground thread after processing the current frame. */
	void UpdateProducedItems( const TMap< TSubclassOf< UFGItemDescriptor >, uint64 >& ProducedItems );

	/* Last world time the produced items got updated. */
	float LastTimeUpdated = 0;

	/* Update frequency for items per X update.*/
	float mUpdateRateFrequency = 60.f;

	/* Cached version of mItemsProduced to compute the delta later on.*/
	TMap< TSubclassOf< UFGItemDescriptor >, uint64 > mLastUpdateValues;

	/* Map with items per min, int64 instead of unsigned 64 because of blueprint compatibility
	 * the likelihood of constructing more then a int64_max per min is hiiiiiiiiiiiiiiiiiiiiiiiiiiiiighly unlikely */	
	TMap< TSubclassOf< UFGItemDescriptor >, int64 > mItemsProducedPerFrequencyMap;
	
	FOnItemPickedUp mOnItemPickedUp;	
	FOnItemManuallyCrafted mOnItemManuallyCrafted;	
	FOnBuildingBuilt mOnBuildingBuilt;	
	FOnBuildingDismantled mOnBuildingDismantled;

private:
	/** How many consumables we have consumed. Nut, berrys, medkit and similar. */
	UPROPERTY( SaveGame )
	TMap< TSubclassOf< class UFGConsumableDescriptor >, int32 > mConsumablesConsumedCount;

	/** How many creatures we have killed */
	UPROPERTY( SaveGame )
	TMap< TSubclassOf< class AFGCreature >, int32 > mCreaturesKilledCount;

	/** How many items we have manually crafted */
	UPROPERTY( SaveGame )
	TMap< AFGPlayerState*, FMappedItemAmount > mItemsManuallyCraftedCount;

	/** How many actors of each class we have built/dismantled */
	UPROPERTY( SaveGame )
	TMap< TSubclassOf< class AActor >, FActorBuiltData > mActorsBuiltCount;

	UPROPERTY( SaveGame )
	TMap< TSubclassOf< UFGItemDescriptor >, uint64 > mItemsProduced;

	/** How many items we picked up. This only handles placed items in the world. Not player dropped items */
	UPROPERTY( SaveGame )
	TMap< AFGPlayerState*, FMappedItemAmount > mItemsPickedUp;
};
