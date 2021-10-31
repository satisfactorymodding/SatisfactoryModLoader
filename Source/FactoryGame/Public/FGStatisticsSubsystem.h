// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGSubsystem.h"
#include "FGSaveInterface.h"
#include "FGStatisticsSubsystem.generated.h"

//[FreiholtzK:Sun/28-03-2021] Just added this delegate for prototype purposes. Should probably not be used in the future sincce it will broadcast alot. 
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnAnyStatisticsUpdated );

/** Data to store the number of actors we built and dismantled with the buildgun. We map this struct to an actor class. A building or vehicle for example */
USTRUCT()
struct FActorBuiltData
{
	GENERATED_BODY()

	/** The current amount of built actors that is in the world */
	UPROPERTY( SaveGame )
	int64 Current;

	/** The maximum amount of built actors that have been in the world */
	UPROPERTY( SaveGame )
	int64 CurrentMax;

	/** The total amount of actors built. Dismantle doesn't affect this number */
	UPROPERTY( SaveGame )
	int64 Total;

	/** The total amount of actors Dismantled. */
	UPROPERTY( SaveGame )
	int64 TotalDismantled;
	
};

/**
 * 	Handles statistics of the game. Number of buildings built, Enemies killed and so on
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

    void Stat_ItemsManuallyCrafted( TSubclassOf< class UFGItemDescriptor > itemDescriptor, int32 numCrafted = 1 );
    int32 Stat_GetNumItemsManuallyCrafted( TSubclassOf< class UFGItemDescriptor > itemDescriptor );

	void Stat_ActorBuilt( TSubclassOf< class AActor > actor, int32 numBuilt = 1 );
	void Stat_ActorDismantled( TSubclassOf< class AActor > actor, int32 numDismantled = 1 );
	int32 Stat_GetNumActorsBuilt_Current( TSubclassOf< class AActor > actor );
	int32 Stat_GetNumActorsBuilt_CurrentMax( TSubclassOf< class AActor > actor );
	int32 Stat_GetNumActorsBuilt_Total( TSubclassOf< class AActor > actor );
	int32 Stat_GetNumActorsBuilt_TotalDismantled( TSubclassOf< class AActor > actor );

	void GetStatisticsDebugData( TArray<FString>& out_debugData );

	FOnAnyStatisticsUpdated mOnAnyStatisticsUpdated;	

private:
	/** How many consumables we have consumed. Nut, berrys, medkit and similar. */
	UPROPERTY( SaveGame )
	TMap< TSubclassOf< class UFGConsumableDescriptor >, int32 > mConsumablesConsumedCount;

	/** How many creatures we have killed */
	UPROPERTY( SaveGame )
	TMap< TSubclassOf< class AFGCreature >, int32 > mCreaturesKilledCount;

	/** How many items we have manually crafted */
	UPROPERTY( SaveGame )
	TMap< TSubclassOf< class UFGItemDescriptor >, int32 > mItemsManuallyCraftedCount;

	/** How many actors of each class we have built/dismantled */
	UPROPERTY( SaveGame )
	TMap< TSubclassOf< class AActor >, FActorBuiltData > mActorsBuiltCount;
};
