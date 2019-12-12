// Copyright 2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/World.h"
#include "Array.h"
#include "UnrealString.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "ReplicationGraph.h"
#include "../FGProductionIndicatorComponent.h"
#include "FGReplicationGraph.generated.h"

enum class EClassRepPolicy : uint8
{
	CRP_NotRouted,						// Doesn't map to any node. Used for special case actors that handled by special case nodes (UShooterReplicationGraphNode_PlayerStateFrequencyLimiter)
	CRP_RelevantAllConnections,			// Routes to an mAlwaysRelevantNode or mAlwaysRelevantStreamingLevelNode node
	
	// Spatialized routes into the grid node
	CRP_Spatialize_Static,				// Routes to mGridNode: these actors don't move and don't need to be updated every frame.
	CRP_Spatialize_Dynamic,				// Routes to mGridNode: these actors move frequently and are updated once per frame.
	CRP_Spatialize_Dormancy,			// Routes to mGridNode: While dormant we treat as static. When flushed/not dormant dynamic. Note this is for things that "move while not dormant".
	CRP_Deferred_Spatialize_Static,				// Deferred replication on initial load. Then Routes to mGridNode: these actors don't move and don't need to be updated every frame.
	CRP_Deferred_Spatialize_Dynamic,				// Deferred replication on initial load. Then Routes to mGridNode: these actors move frequently and are updated once per frame.
	CRP_Deferred_Spatialize_Dormancy,			// Deferred replication on initial load. Then Routes to mGridNode: While dormant we treat as static. When flushed/not dormant dynamic. Note this is for things that "move while not dormant".
};

USTRUCT()
struct FConnectionAlwaysRelevant_NodePair
{
	GENERATED_BODY()

	FConnectionAlwaysRelevant_NodePair() { }
	FConnectionAlwaysRelevant_NodePair( UNetConnection* InConnection, UReplicationGraphNode_AlwaysRelevant_ForConnection* InNode ) : NetConnection( InConnection ), Node( InNode ) { }
	bool operator==( const UNetConnection* InConnection ) const { return InConnection == NetConnection; }

	UPROPERTY()
	UNetConnection* NetConnection = nullptr;

	UPROPERTY()
	UReplicationGraphNode_AlwaysRelevant_ForConnection* Node = nullptr;
};

class UReplicationGraphNode_GridSpatialization2D;
class UReplicationGraphNode_ActorList;
class UReplicationGraphNode_AlwaysRelevant_ForConnection;

UCLASS(Transient, config=Engine)
class FACTORYGAME_API UFGReplicationGraph : public UReplicationGraph
{
public:
	GENERATED_BODY()

	// ~ begin UReplicationGraph implementation
	virtual void ResetGameWorldState() override;
	virtual void InitConnectionGraphNodes( UNetReplicationGraphConnection* connectionManager ) override;
	virtual void InitGlobalActorClassSettings() override;
	virtual void InitGlobalGraphNodes() override;
	virtual void RouteAddNetworkActorToNodes( const FNewReplicatedActorInfo& ActorInfo, FGlobalActorReplicationInfo& GlobalInfo ) override;
	virtual void RouteRemoveNetworkActorToNodes( const FNewReplicatedActorInfo& ActorInfo ) override;
	virtual int32 ServerReplicateActors( float DeltaSeconds ) override;
	virtual void NotifyActorDormancyChange( AActor* Actor, ENetDormancy OldDormancyState ) override;
	// ~ end UReplicationGraph implementation

	/** Sets the class replication info for a class */
	void InitClassReplicationInfo( FClassReplicationInfo& classInfo, UClass* inClass, bool isSpatialized, int32 NetServerMaxTickRate );

	UPROPERTY()
	TArray<UClass*> mSpatializedClasses;

	UPROPERTY()
	TArray<UClass*> mNonSpatializedClasses;

	UPROPERTY()
	TArray<UClass*> mAlwaysRelevantClasses;

	/** Grid Node that divides the map into grids and determines if an actor should send network updates to a connection depending on the different pre-defined grids. */
	UPROPERTY()
	UReplicationGraphNode_GridSpatialization2D* mGridNode;

	/** Node that holds a list of actors that are always Net Relevant. */
	UPROPERTY()
	UReplicationGraphNode_ActorList* mAlwaysRelevantNode;

	UPROPERTY()
	TArray<FConnectionAlwaysRelevant_NodePair> mAlwaysRelevantForConnectionList;

	/** Maps the actors that need to be always relevant across streaming levels */
	TMap<FName, FActorRepListRefView> mAlwaysRelevantStreamingLevelActors;

protected:
	 
	/** Class types of equipment who's dependency to the pawn shouldn't be removed if they're unequipped. */
	UPROPERTY()
	TSet<UClass*> mPersistentDependencyClasses;

	// Actor Dependencies 
	/** Callback on when actor dependencies for character players that should always exist for the pawn is spawned */
	void AddPersistentDependencyActor( class AFGCharacterPlayer* pawn, class IFGReplicationDependencyActorInterface* depedencyActor );

	/** Callbacks for handling replication detail actors for manufacturers */
	void AddReplicationDependencyActor( class AActor* owner, class AFGReplicationDetailActor* replicationDetailActor );
	void RemoveReplicationDependencyActor( class AActor* owner, class AFGReplicationDetailActor* replicationDetailActor );
	void OnReplicationDetailActorStateChange( class IFGReplicationDetailActorOwnerInterface* owner, bool newState );

	/** Callback to handle when a player equips any equipment and add it to the pawns dependency list */
	void OnCharacterPlayerEquip( class AFGCharacterPlayer* pawn, class AFGEquipment* equipment );
	
	/** Callback to handle when a player unequips any equipment and removes it to the pawns dependency list */
	void OnCharacterPlayerUnequip( class AFGCharacterPlayer* pawn, class AFGEquipment* equipment );

	/** Callback on when the foliage pickup proxy has spawned for a player */
	void OnCharacterPlayerFoliagePickupSpawned( class AFGCharacterPlayer* pawn, class AFGFoliagePickup* foliagePickup );

	/** Callback to when a building registers (or unregisters) a player. Handles dormancy state changes for buildables in these cases. */
	void OnBuildableRegistedPlayerChanged( class AFGBuildable* buildable, class AFGCharacterPlayer* player, bool isInUse );

	/** Callback on when buildables production status changes. Handles any replication needed behavior for buildables when this happens. */
	void OnFactoryProductionStatusChanged( class AFGBuildable* buildable, EProductionStatus oldStatus, EProductionStatus newStatus );

	/** Whether the given mapping is spatialized in any way */
	FORCEINLINE bool IsSpatialized( EClassRepPolicy mapping ) { return mapping >= EClassRepPolicy::CRP_Spatialize_Static; }

	/** Gets the mapping to be used for the given class */
	EClassRepPolicy GetMappingPolicy( const UClass* inClass );

	TClassMap<EClassRepPolicy> mClassRepPolicies;

	// The size in uunits of each grid cell
	float mGridCellSize = 100000.f;
	
	// Essentially "Min X" for replication. This is just an initial value. The system will reset itself if actors appears outside of this.
	float mSpatialBiasX = -15000.f;
	
	// Essentially "Min Y" for replication. This is just an initial value. The system will reset itself if actors appears outside of this.
	float mSpatialBiasY = -15000.f;

	// How many buckets to spread dynamic, spatialized actors across. High number = more buckets = smaller effective replication frequency. This happens before individual actors do their own NetUpdateFrequency check.
	float mDynamicActorFrequencyBuckets = 4;

	//	[Dylan] - I Enabled this to stop the World->bInTick() crash. It doesn't blacklist all actors though. Only FGFoliageRemoval as spawning these during level stream was triggering a rebuild
	//		Rebuilds were causing a crash in world tick as the level was still being streamed and did not flush.
	//		Sidenote: This crash has been around for awhile with low counts. If a client joins for the first time while the server is streaming a level it will also trigger a rebuild and crash
	bool mDisableSpatialRebuild = true;

private:
	/** Actors that are only supposed to replicate to their owning connection, but that did not have a connection on spawn */
	UPROPERTY()
	TArray<AActor*> mActorsWithoutNetConnection;

	void LogCurrentActorDependencyList( FGlobalActorReplicationInfo& actorInfo, FString& logMarker );

	UReplicationGraphNode_AlwaysRelevant_ForConnection* GetAlwaysRelevantNodeForConnection( UNetConnection* Connection );
};

UCLASS()
class UFGReplicationGraphNode_AlwaysRelevant_ForConnection : public UReplicationGraphNode_AlwaysRelevant_ForConnection
{
public:
	GENERATED_BODY()

	// ~ begin UReplicationGraphNode_AlwaysRelevant_ForConnection implementation
	virtual void GatherActorListsForConnection( const FConnectionGatherActorListParameters& Params ) override;
	// ~ end UReplicationGraphNode_AlwaysRelevant_ForConnection implementation

	void OnLevelVisibilityAdd( FName levelName, UWorld* world );
	void OnLevelVisibilityRemove( FName levelName );

	void ResetWorldGameWorldState();

protected:
	// Stores levelstreaming actors
	TArray<FName, TInlineAllocator<64>> mAlwaysRelevantStremingLevels;

	bool mInitializedPlayerState = false;
};
