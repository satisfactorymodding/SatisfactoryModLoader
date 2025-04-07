// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "UObject/Package.h"
#include "Engine/ActorChannel.h"
#include "Engine/LocalPlayer.h"
#include "Engine/NetConnection.h"
#include "Misc/ConfigCacheIni.h"
#include "ReplicationGraph.h"
#include "FGReplicationGraph.generated.h"

FACTORYGAME_API DECLARE_LOG_CATEGORY_EXTERN( LogFactoryReplicationGraph, Display, All );
FACTORYGAME_API DECLARE_LOG_CATEGORY_EXTERN( LogConveyorFrequencyNodes, Display, All );

enum class EClassRepPolicy : uint8
{
	CRP_NotRouted,						// Doesn't map to any node. Used for special case actors that handled by special case nodes (UShooterReplicationGraphNode_PlayerStateFrequencyLimiter)
	CRP_RelevantAllConnections,			// Routes to mAlwaysRelevantNode or mAlwaysRelevantStreamingLevelNode node
	CRP_ConditionalRelevant,			// Routes to mConditionalRelevantNode that runs IsNetRelevantFor() on each actor. Expects each actor to be relevant for all connections 

	// Spatialized routes into the grid node
	CRP_Spatialize_Static,				// Routes to mGridNode: these actors don't move and don't need to be updated every frame.
	CRP_Spatialize_Dynamic,				// Routes to mGridNode: these actors move frequently and are updated once per frame.
	CRP_Spatialize_Dormancy,			// Routes to mGridNode: While dormant we treat as static. When flushed/not dormant dynamic. Note this is for things that "move while not dormant".
	CRP_Spatialize_Prioritized_Dynamic, // Routes to mPrioritizedGridNode: These actors use the SpatializedDynamicFequency node, which uses each connections view location and rot to prioritize actors
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
	virtual void NotifyActorDormancyChange( AActor* Actor, ENetDormancy OldDormancyState ) override;
	virtual void AddNetworkActor(AActor* Actor) override;
	// ~ end UReplicationGraph implementation

	/** Sets the class replication info for a class */
	void InitClassReplicationInfo( struct FClassReplicationInfo& classInfo, UClass* inClass, bool isSpatialized, int32 NetServerMaxTickRate );

	UPROPERTY()
	TArray<UClass*> mSpatializedClasses;

	UPROPERTY()
	TArray<UClass*> mNonSpatializedClasses;

	UPROPERTY()
	TArray<UClass*> mAlwaysRelevantClasses;

	/** Grid Node that divides the map into grids and determines if an actor should send network updates to a connection depending on the different pre-defined grids. */
	UPROPERTY()
	UReplicationGraphNode_GridSpatialization2D* mGridNode;

	/** Grid Node that is dedicated for more Dynamic actors ie. Pawns / Characters */
	UPROPERTY()
	UReplicationGraphNode_GridSpatialization2D* mPrioritizedGridNode;

	/** Node that holds a list of actors that are always Net Relevant. */
	UPROPERTY()
	UFGReplicationGraphNode_AlwaysRelevantWithDormancy* mAlwaysRelevantNode;

	UPROPERTY()
	class UFGReplicationGraphNode_ConditionallyAlwaysRelevant* mConditionalRelevancyNode;

	/** Node holds all player states and cycles through them so they do not all attempt replication every frame */
	UPROPERTY()
	UFGReplicationGraphNode_PlayerStateFrequencyLimiter* mPlayerStateNode;

	UPROPERTY()
	TArray<FConnectionAlwaysRelevant_NodePair> mAlwaysRelevantForConnectionList;

	/** Maps the actors that need to be always relevant across streaming levels */
	TMap<FName, FActorRepListRefView> mAlwaysRelevantStreamingLevelActors;

	/**
	 * Registers the default replication policy for the specified actor
	 * If the actor is not explicitly registered in the replication graph, it will be assumed to be ConditionallyRelevant, which
	 * should be good enough for a lot of use cases but if you want spatialization or per-connection relevancy, you can override that
	 */
	static void RegisterCustomClassRepPolicy( TSoftClassPtr<AActor> inActor, EClassRepPolicy inRepPolicy );
protected:
	static TMap<TSoftClassPtr<AActor>, EClassRepPolicy> CustomClassRepPolicies;
	 
	/** Class types of equipment who's dependency to the pawn shouldn't be removed if they're unequipped. */
	UPROPERTY()
	TSet<UClass*> mPersistentDependencyClasses;

	// Actor Dependencies
	/** Callback on when a train replication actor is added to the game so we can add the vehicles in the consist as dependencies. */
	void OnTrainReplicationActorAdded( class AFGTrainReplicationActor* replicationActor );
	void OnTrainReplicationActorRemoved( class AFGTrainReplicationActor* replicationActor );

	// Called from Elevator Floor stops when added/removed to bind replication dependency to their owning Elevator
	void OnElevatorChildAdded( AActor* dependantActor, class AActor* elevator );
	void OnElevatorChildRemoved( AActor* dependantActor, class AActor* elevator  );

	/**
	 * Callback for when a locomotive is possessed or unpossessed by a player controller so we can add a dependency.
	 * Note: Locomotive nor controller can be null.
	 */
	void OnLocomotivePossessedBy( class AFGLocomotive* locomotive, AController* controller );
	void OnLocomotiveUnPossessed( class AFGLocomotive* locomotive, AController* controller );
	
	/** Callback on when actor dependencies for character players that should always exist for the pawn is spawned */
	void AddPersistentDependencyActor( class AFGCharacterPlayer* pawn, class IFGReplicationDependencyActorInterface* depedencyActor );

	/** Callback to handle when a player equips any equipment and add it to the pawns dependency list */
	void OnCharacterPlayerEquip( class AFGCharacterPlayer* pawn, class AFGEquipment* equipment );
	
	/** Callback to handle when a player unequips any equipment and removes it to the pawns dependency list */
	void OnCharacterPlayerUnequip( class AFGCharacterPlayer* pawn, class AFGEquipment* equipment );

	/** Callback on when the foliage pickup proxy has spawned for a player */
	void OnCharacterPlayerFoliagePickupSpawned( class AFGCharacterPlayer* pawn, class AFGFoliagePickup* foliagePickup );

	/** Called when the pawn controlled by the given player controller changes */
	void OnPlayerControllerPawnChanged( class APlayerController* playerController, APawn* oldPawn, APawn* newPawn );

	/** Whether the given mapping is spatialized in any way */
	FORCEINLINE bool IsSpatialized( EClassRepPolicy mapping ) { return mapping >= EClassRepPolicy::CRP_Spatialize_Static; }

	/** Gets the mapping to be used for the given class */
	EClassRepPolicy GetMappingPolicy( UClass* inClass );

	TClassMap<EClassRepPolicy> mClassRepPolicies;

	// The size in uunits of each grid cell
	float mGridCellSize = 50000.f; // [Dylan] Was 100000.f
	
	// Essentially "Min X" for replication. This is just an initial value. The system will reset itself if actors appears outside of this.
	float mSpatialBiasX = -400000.f;
	
	// Essentially "Min Y" for replication. This is just an initial value. The system will reset itself if actors appears outside of this.
	float mSpatialBiasY = -400000.f;

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

	UReplicationGraphNode_AlwaysRelevant_ForConnection* GetAlwaysRelevantNodeForConnection( UNetConnection* Connection );
};



UCLASS()
class FACTORYGAME_API UFGReplicationGraphNode_AlwaysRelevantWithDormancy : public UReplicationGraphNode_ActorList
{
	GENERATED_BODY()
public:
	// Begin UReplicationGraphNode_ActorList interface
	virtual void NotifyAddNetworkActor( const FNewReplicatedActorInfo& ActorInfo ) override;
	virtual bool NotifyRemoveNetworkActor( const FNewReplicatedActorInfo& ActorInfo, bool bWarnIfNotFound = true ) override;
	// End UReplicationGraphNode_ActorList interface

	void AddActor(const FNewReplicatedActorInfo& ActorInfo, FGlobalActorReplicationInfo& ActorRepInfo);
	void RemoveActor(const FNewReplicatedActorInfo& ActorInfo);
protected:
	UPROPERTY()
	UReplicationGraphNode_DormancyNode* mDormancyNode;
	
	void OnActorDormancyChanged(AActor* Actor, FGlobalActorReplicationInfo& GlobalInfo, ENetDormancy NewValue, ENetDormancy OldValue);
	
	UReplicationGraphNode_DormancyNode* GetDormancyNode();
};

UCLASS()
class FACTORYGAME_API UFGReplicationGraphNode_ConditionallyAlwaysRelevant : public UReplicationGraphNode_ActorList
{
	GENERATED_BODY()
public:
	// ~ begin UReplicationGraphNode_AlwaysRelevant_ForConnection implementation
	virtual void GatherActorListsForConnection( const FConnectionGatherActorListParameters& Params ) override;
	virtual void NotifyAddNetworkActor( const FNewReplicatedActorInfo& ActorInfo ) override;
	virtual bool NotifyRemoveNetworkActor( const FNewReplicatedActorInfo& ActorInfo, bool bWarnIfNotFound = true ) override;
	virtual void NotifyResetAllNetworkActors() override;
	// ~ end UReplicationGraphNode_AlwaysRelevant_ForConnection implementation

private:
	FActorRepListRefView mAllReplicationActors;
};

/** This is a specialized node for handling PlayerState replication in a frequency limited fashion. It tracks all player states but only returns a subset of them to the replication driver each frame. */
UCLASS()
class FACTORYGAME_API UFGReplicationGraphNode_PlayerStateFrequencyLimiter : public UReplicationGraphNode
{
	GENERATED_BODY()

	UFGReplicationGraphNode_PlayerStateFrequencyLimiter();

	virtual void NotifyAddNetworkActor( const FNewReplicatedActorInfo& Actor ) override { }
	virtual bool NotifyRemoveNetworkActor( const FNewReplicatedActorInfo& ActorInfo, bool bWarnIfNotFound = true ) override { return false; }

	virtual void GatherActorListsForConnection( const FConnectionGatherActorListParameters& Params ) override;

	virtual void PrepareForReplication() override;

	virtual void LogNode( FReplicationGraphDebugInfo& DebugInfo, const FString& NodeName ) const override;

	/** How many actors we want to return to the replication driver per frame. Will not suppress ForceNetUpdate. */
	int32 TargetActorsPerFrame = 1;

private:

	TArray<FActorRepListRefView> ReplicationActorLists;
	FActorRepListRefView ForceNetUpdateReplicationActorList;
};

UCLASS()
class FACTORYGAME_API UFGReplicationGraphNode_AlwaysRelevant_ForConnection : public UReplicationGraphNode_AlwaysRelevant_ForConnection
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
