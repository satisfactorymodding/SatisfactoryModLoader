// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ReplicationGraph.h"
#include "FGProductionIndicatorComponent.h"
#include "FGReplicationGraph.generated.h"

DECLARE_LOG_CATEGORY_EXTERN( LogFactoryReplicationGraph, Display, All );
DECLARE_LOG_CATEGORY_EXTERN( LogConveyorFrequencyNodes, Display, All );

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
	CRP_Spatialize_Conveyor_Frequency	// Routes to mConveyorFrequencyNode: These actors use a custom frequency node to consider Viewer position and direction to throttle off screen conveyors
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

	/** Grid Node that is dedicated for more Dynamic actors ie. Pawns / Characters */
	UPROPERTY()
	UReplicationGraphNode_GridSpatialization2D* mPrioritizedGridNode;

	/** Grid Node that is dedicated to Actors that are static and should replicate frequency based on Viewer */
	UPROPERTY()
	UReplicationGraphNode_GridSpatialization2D* mConveyorFrequencyNode;

	/** Node that holds a list of actors that are always Net Relevant. */
	UPROPERTY()
	UReplicationGraphNode_ActorList* mAlwaysRelevantNode;

	UPROPERTY()
	UFGReplicationGraphNode_ConditionallyAlwaysRelevant* mConditionalRelevancyNode;

	/** Node holds all player states and cycles through them so they do not all attempt replication every frame */
	UPROPERTY()
	UFGReplicationGraphNode_PlayerStateFrequencyLimiter* mPlayerStateNode;

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

	void LogCurrentActorDependencyList( FGlobalActorReplicationInfo& actorInfo, FString& logMarker );

	UReplicationGraphNode_AlwaysRelevant_ForConnection* GetAlwaysRelevantNodeForConnection( UNetConnection* Connection );
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


// Grid Node for prioritizing Actors Close to the player and inside their view frustum. Based on the DynamicSpatialFrequency Node. Intended for Actors that don't move and have a heavy Networking footprint (Tex. Conveyors)
UCLASS()
class FACTORYGAME_API UFGReplicationGraphNode_ConveyorSpatialFrequency : public UReplicationGraphNode_GridCell
{
	GENERATED_BODY()
public:
	void InitializeFrequencyGrid( FVector2D origin, FVector2D cellSize, int32 subdivisions );

	virtual void GatherActorListsForConnection( const FConnectionGatherActorListParameters& Params ) override;
	virtual void TearDown() override;

	// Custom CSS Notifies. These will only be called if the cell has bShouldNotifyStaticActorChanges == true. This is an empty function on the base GridCell
	virtual void OnStaticActorPutIntoCell( const FNewReplicatedActorInfo& ActorInfo ) override;
	virtual void OnStaticActorRemovedFromCell( const FNewReplicatedActorInfo& ActorInfo ) override;

	// --------------------------------------------------------
	struct FSpatializationZone
	{
		// Init based on target frame rate
		FSpatializationZone( float InMinDotProduct, float InMinDistPct, float InMaxDistPct, float InMinRepHz, float InMaxRepHz, float TickRate ) :
			MinDotProduct( InMinDotProduct ), MinDistPct( InMinDistPct ), MaxDistPct( InMaxDistPct ),
			MinRepPeriod( HzToFrm( InMinRepHz, TickRate ) ), MaxRepPeriod( HzToFrm( InMaxRepHz, TickRate ) ) { }

		float MinDotProduct = 1.f;	// Must have dot product >= to this to be in this zone
		float MinDistPct = 0.f;		// Min distance as pct of per-connection culldistance, to map to MinRepPeriod
		float MaxDistPct = 1.f;		// Max distance as pct of per-connection culldistance, to map to MaxRepPeriod

		uint32 MinRepPeriod = 5;
		uint32 MaxRepPeriod = 10;

		static uint32 HzToFrm( float Hz, float TargetFrameRate )
		{
			return  Hz > 0.f ? ( uint32 )FMath::CeilToInt( TargetFrameRate / Hz ) : 0;
		}
	};

	// --------------------------------------------------------
	struct FConnectionSaturationInfo
	{
		FConnectionSaturationInfo( const FConnectionSaturationInfo& otherInfo )
		{
			RepGraphConnection = otherInfo.RepGraphConnection;
			CurrentRatePCT = otherInfo.CurrentRatePCT;
			MaxClientRate = otherInfo.MaxClientRate;
		}

		FConnectionSaturationInfo() : RepGraphConnection(nullptr) {}

		// Init based on UNetReplicationGraphConnection
		FConnectionSaturationInfo( UNetReplicationGraphConnection* connection ) : RepGraphConnection( connection ) 
		{
			for( int32 i = 0; i < LoadBalanceFrameCount; ++i )
			{
				FramesSelfSaturated[ i ] = false;
				FramesExternalSaturated[ i ] = false;
			}

			MaxClientRate = connection->NetConnection->Driver->MaxClientRate;
			UE_LOG( LogGame, Log, TEXT("Initialized MaxClientRate == %i"), MaxClientRate );
		}

		UNetReplicationGraphConnection* RepGraphConnection;
		float MaxRatePCT = 0.65f; // Maximum % of the total budget
		float MinRatePCT = 0.15f; // Minimum % of the total budget
		float DefaultRatePCT = 0.3f;
		float CurrentRatePCT = 0.3f;
		int32 MaxClientRate = 15000; // Is copied from NetDriver on initialization

		static const int32 LoadBalanceFrameCount = 60;
		bool FramesSelfSaturated[ LoadBalanceFrameCount ];
		bool FramesExternalSaturated[ LoadBalanceFrameCount ];
	};

	// --------------------------------------------------------
	struct FSettings
	{
		FSettings() :MaxBitsPerFrame( 0 ), MaxNearestActors( -1 ), FrequencyGridSubdivisions( 18 )
		{ }

		FSettings( TArrayView<FSpatializationZone> InZoneSettings ) : ZoneSettings( InZoneSettings )
		{}

		FORCEINLINE float GetCullDistanceSquared() { return CullDistance * CullDistance; }

		TArrayView<FSpatializationZone> ZoneSettings;
		int64 MaxBitsPerFrame;
		int32 MaxNearestActors; // Only replicate the X nearest actors to a connection in this node. -1 = no limit.
		int32 FrequencyGridSubdivisions = 41;
		float CullDistance = 35000.f; // Potentially not great, this will be used to calc cull distance on Cells. As all actors in a cell will be culled together not per actor
		float SkipLowPriorityAtHz = 2.f; // At 2hz or lower we will skip low priority conveyors. They will be disregarded and not replicate at all
		int32 MaxAllowedRepPeriod = 120; // Anything over this amount of frames will be Zeroed and not replicate
	};

	static FSettings mDefaultSettings;	// Default settings used by all instance
	FSettings* mSettings;				// per instance override settings (optional)

	FSettings& GetSettings() { return mSettings ? *mSettings : mDefaultSettings; }

protected:

	// --------------------------------------------------------
	struct FConveyorFrequency_ZBucketNode
	{
		FConveyorFrequency_ZBucketNode()	
		{
			StartIndex = INDEX_NONE;
			EndIndex = INDEX_NONE;
			WorldMin = -MaxHalfHeight;
			WorldMax = MaxHalfHeight;
		}

		FConveyorFrequency_ZBucketNode( int32 startIndex, int32 endIndex, float worldMin, float worldMax ) :
			StartIndex( startIndex ),
			EndIndex( endIndex ),
			WorldMin( worldMin ),
			WorldMax( worldMax )
		{ }

		void Set( int32 newStartIndex, int32 newEndIndex, int32 newWorldMin, int32 newWorldMax )
		{
			StartIndex = newStartIndex;
			EndIndex = newEndIndex;
			WorldMin = newWorldMin;
			WorldMax = newWorldMax;
		}

		// Very similar to the Cell Replication Period (check there for the reasoning/comments if needed)
		void SetReplicationPeriod( int32 newRepPeriod, const uint32& frameNum )
		{
			if( newRepPeriod == BucketReplicationPeriod )
			{
				FramesTillReplicate = ( ( int32 )LastReplicationFrame + BucketReplicationPeriod ) - ( int32 )frameNum;
				return;
			}

			if( BucketReplicationPeriod == 0 )
			{
				LastReplicationFrame = frameNum - newRepPeriod;
			}

			BucketReplicationPeriod = newRepPeriod;

			FramesTillReplicate = ( ( int32 )LastReplicationFrame + BucketReplicationPeriod ) - ( int32 )frameNum;
		}

		// For sorting from -Max to +Max in the world
		bool operator<( const FConveyorFrequency_ZBucketNode& Other ) const
		{
			return GetCenterZ() < Other.GetCenterZ();
		}

		FORCEINLINE bool IsValid() const
		{
			return ( StartIndex != INDEX_NONE && EndIndex != INDEX_NONE ) && ( StartIndex != EndIndex );
		}

		FORCEINLINE void ShiftIndices( int32 num, bool includeStart )
		{
			if( includeStart )
			{
				StartIndex += num;
			}
			EndIndex += num;
		}

		FORCEINLINE bool ShouldRebuild() const
		{
			return IsValid() && ( EndIndex - StartIndex >= NumActorsToSubdivide ) && ( FMath::Abs( WorldMax - WorldMin ) > MinZBucketHeight );
		}

		FORCEINLINE float GetCenterZ() const
		{
			return WorldMin + ( WorldMax - WorldMin ) / 2.f;
		}

		FORCEINLINE float GetHeight() const
		{
			return FMath::Abs( WorldMax - WorldMin );
		}

		FORCEINLINE int32 GetNum() const
		{
			if( IsValid() )
			{
				return EndIndex - StartIndex;
			}
			else
			{
				return 0;
			}
		}


		int32 StartIndex; // Index in the Cell Array that this bucket starts at (inclusive)
		int32 EndIndex; // The index at which this bucket ends (exclusive - The end index may be out of bounds and that's a-okay)
		float WorldMin; // Z-Location of the bottom of this bucket
		float WorldMax; // Z-Location of the top of this bucket

		// The RepPeriod of this Bucket
		int32 BucketReplicationPeriod = 0;
		int32 FramesTillReplicate = 0;
		int32 LastReplicationFrame = 0;

		// ZBucket globals
		inline static int32 NumActorsToSubdivide = 20; // A single bucket with more actors than this should attempt to split and redistribute to the new buckets
		inline static float MinZBucketHeight = 6000; // ZBuckets smaller than this will not attempt to further split (even if they are exceeding the max actors per z group)
		inline static int32 NumBucketsFromSplit = 3; // When exceeding maximum actors, how many should be created from subdivision?
		inline static float MaxHalfHeight = 150000.0; // World Size Half Height of the First Bucket (all future buckets will be a subdivision of this so never larger)
	};

	// --------------------------------------------------------
	struct FZBucketReplicationRange
	{
		FZBucketReplicationRange() :
			StartIndex( 0 ),
			EndIndex( 0 ),
			Period( 0 ),
			BucketIndex( INDEX_NONE )
		{ }

		FZBucketReplicationRange( int32 inMin, int32 inMax, int32 inPeriod, int32 inBucketIndex ) :
			StartIndex( inMin ),
			EndIndex( inMax ),
			Period( inPeriod ),
			BucketIndex( inBucketIndex )
		{ }

		bool operator<( const FZBucketReplicationRange& Other ) const
		{
			if( Other.Period > 0 && Period > 0 || Other.Period <= 0 && Period <= 0 )
			{
				return Period < Other.Period;
			}
			else
			{
				if( Period > 0 && Other.Period <= 0 )
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}

		int32 StartIndex;
		int32 EndIndex;
		int32 Period;
		int32 BucketIndex; // Used for debugging
	};

	// --------------------------------------------------------
	struct FFrequencyGrid2D_Cell
	{
		FFrequencyGrid2D_Cell() 
		{
			InitializeZBuckets();
		}
		FFrequencyGrid2D_Cell( FVector cellOrigin ) : CellOrigin( cellOrigin ) 
		{
			InitializeZBuckets();
		}

		~FFrequencyGrid2D_Cell()
		{
			for( int32 i = ZBuckets.Num() - 1; i >= 0; --i )
			{
				delete ZBuckets[i];
			}
			ZBuckets.Reset();
		}

		bool AddActor( AActor* actor );
		bool RemoveActor( AActor* actor );

		void SetDirty( int32 FrameNum )
		{
			MarkedDirtyFrameNum = FrameNum;
			IsDirty = true;
			ForceUpdate = true;
		}

		void InitializeZBuckets()
		{
			// Initialize a 0 size Zbucket
			ZBuckets.Add( new FConveyorFrequency_ZBucketNode(0, 0, -FConveyorFrequency_ZBucketNode::MaxHalfHeight, FConveyorFrequency_ZBucketNode::MaxHalfHeight ) );
		}

		void SplitBucket( FConveyorFrequency_ZBucketNode* zBucket );

		void PreReplication();
		int32 GetZBucketForActorIndex( int32 actorIndex ); // Return the index of the Z bucket for a given index in the actor array
		void OnActorChangedInBucket( int32 bucketIndex, int32 plusminus ); // plusminus here is used as a switch to indicate if an actor was added (+1) or removed (-1)
		FORCEINLINE int32 GetZBucketIndexForWorldZ( float zLoc ) const
		{
			zLoc = FMath::Clamp( zLoc, -FConveyorFrequency_ZBucketNode::MaxHalfHeight - KINDA_SMALL_NUMBER, FConveyorFrequency_ZBucketNode::MaxHalfHeight + KINDA_SMALL_NUMBER );
			for( int32 i = 0; i < ZBuckets.Num(); ++i )
			{
				if( zLoc >= ZBuckets[ i ]->WorldMin && zLoc < ZBuckets[ i ]->WorldMax )
				{
					return i;
				}
			}
			
			UE_LOG( LogConveyorFrequencyNodes, Verbose, TEXT("Failed to find appropriate ZBucket for world location: %f"), zLoc);
			return 0;
		}

		FVector CellOrigin;
		const float LowPrioConveyorMaxLength = 201.f; // Slightly over 200 so belts snapped to the grid that are 200 exactly fall into the low prio group
		const float LowPrioPipelineMaxLength = 499.f; // Larger than conveyors as pipes smaller than this cannot have flow indicators

		// All actors that belong in this cell. Added / Removed from Graph Notifies. Used to find the connection info for each actor
		TArray < AActor* > ActorList;
		TArray < AActor* > LowPriority_ActorList; // For very short conveyors we want to use more aggressive distance scaling, so track which ones

		TArray< FConveyorFrequency_ZBucketNode* > ZBuckets;
		int32 MarkedDirtyFrameNum = 0;
		bool IsDirty = false;
		bool ZBucketsDirty = false;
		bool ForceUpdate = false;
	};


	// --------------------------------------------------------
	struct FConveyorFrequency_SortedCell
	{
		FConveyorFrequency_SortedCell() { }
		FConveyorFrequency_SortedCell( FFrequencyGrid2D_Cell* InCell, int32 InReplicationPeriod, const uint32& InFrameNum )
			: Cell( InCell )
		{
			ForceUpdate = true; // When creating a new Cell, we should always force an update so that it gets replicated at least once
			SetReplicationPeriod( ReplicationPeriod, InFrameNum, true );
		}

		bool operator<( const FConveyorFrequency_SortedCell& Other ) const 
		{
			if( Other.ReplicationPeriod > 0 && ReplicationPeriod > 0 || Other.ReplicationPeriod <= 0 && ReplicationPeriod <= 0)
			{
				return FramesTillReplicate < Other.FramesTillReplicate;
			}
			else
			{
				if( ReplicationPeriod > 0 && Other.ReplicationPeriod <= 0 )
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}

		UPROPERTY()
		FFrequencyGrid2D_Cell* Cell = nullptr;

		void SetReplicationPeriod( int32 newRepPeriod, const uint32& frameNum, bool forceInit = false )
		{
			// Only skip the setting if this cell is not flagged ForceUpdate
			if( !forceInit && !ForceUpdate && newRepPeriod == ReplicationPeriod )
			{
				// Just update the frames until replication and return
				FramesTillReplicate = ( ( int32 )LastReplicationFrame + ReplicationPeriod ) - ( int32 )frameNum;
				return;
			}

			// if the replication period is currently 0, then this cell has not been updating and will potentially have a very old LastReplicationFrame
			// In this case, we don't want to just set the period as this cell will become over prioritized. Instead we will force the last update frame to 
			// the current minus the new rep period
			if( ReplicationPeriod == 0 )
			{
				LastReplicationFrame = frameNum - newRepPeriod;
			}

			if( !ForceUpdate )
			{
				ReplicationPeriod = newRepPeriod;
			}
			else
			{
				ReplicationPeriod = 1;
			}

			FramesTillReplicate = ( ( int32 )LastReplicationFrame + ReplicationPeriod ) - ( int32 )frameNum;

			// Scale if this cell is flagged to force update
			FramesTillReplicate -= ForceUpdate ? 10 : 0;
		}

		void CalculateZBucketRanges( int32 currentFrame )
		{
			ZRanges.Reset();
			TArray< FConveyorFrequency_ZBucketNode* >& bucketArr = Cell->ZBuckets;
			for( int32 i = 0; i < bucketArr.Num(); ++i )
			{
				if( !bucketArr[ i ]->IsValid() )
				{
					continue;
				}

				if( ForceUpdate )
				{
					ZRanges.Add( FZBucketReplicationRange( bucketArr[ i ]->StartIndex, bucketArr[ i ]->EndIndex, bucketArr[ i ]->BucketReplicationPeriod, i ) );
					continue;
				}

				if( bucketArr[ i ]->BucketReplicationPeriod > 0 )
				{
					//if( bucketArr[ i ]->BucketDelayExponent == 0 || (int32)FMath::Pow( 2, ReplicationCount ) % bucketArr[ i ]->BucketDelayExponent == 0 )
					//{
					if( bucketArr[ i ]->FramesTillReplicate <= 0 )
					{
						ZRanges.Add( FZBucketReplicationRange( bucketArr[ i ]->StartIndex, bucketArr[ i ]->EndIndex, bucketArr[ i ]->BucketReplicationPeriod, i ) );
					}
					//}
				}
			}

			// Sort them so we alwways start replication on the most relevant bucket (highest rep period)
			ZRanges.Sort();
		}

		TArray< FZBucketReplicationRange > ZRanges;
		int32 ReplicationPeriod = 0; // This is frame time so num frames to next replication. 0 = Do not replicate. 1 = Rep Every Frame etc.
		int32 FramesTillReplicate = 0;
		uint32 LastReplicationFrame = 0;
		int32 StartReplicationAtIndex = 0;
		int32 StartReplicationAtZBucket = 0;
		bool ForceUpdate = false;
	};

	// --------------------------------------------------------
	struct FFrequencyGrid2D
	{
		FFrequencyGrid2D() 
		{
			++GridsCreated;
		}
		FFrequencyGrid2D( FVector2D origin, FVector2D gridSize, int32 subdivisions, UWorld* world ) : Origin(origin), GridSize(gridSize), Subdivisions(subdivisions) 
		{ 
			// The grid actually consumes a 3x3 area around a single GraphNode. This way Conveyors that actually fall outside the grid cell but have
			// a large net radius can be considered properly. Otherwise at the edge of a GraphNode we would have to clamp a lot of conveyors to contrain them
			// into the space of the actual GraphNode.

			CellSize = GridSize / Subdivisions;
			HalfGridSize = FVector2D( GridSize / 2.f );
			GridMin = FVector2D( Origin - HalfGridSize - CellSize );
			GridMax = FVector2D( Origin + HalfGridSize + CellSize );

			float halfSubdivisions = Subdivisions / 2.f;
			HalfCellSize = CellSize / 2.f;

			FVector newCellOrigin = FVector();
			for( int32 i = 0; i < Subdivisions; ++i )
			{
				for( int32 j = 0; j < Subdivisions; ++j )
				{
					newCellOrigin = FVector( Origin.X - ( ( j - halfSubdivisions ) * CellSize.X ) + HalfCellSize.X, Origin.Y - ( ( i - halfSubdivisions ) * CellSize.Y ) + HalfCellSize.Y, 0.f );
					FrequencyCells.Add( new FFrequencyGrid2D_Cell( newCellOrigin ) );
					if( world )
					{
						FString DebugString = FString::Printf( TEXT( "Cell [ %i, %i ]" ), j, i );
						//DrawDebugString( world, newCellOrigin + FVector( 0.f, 0.f, 500.f ), DebugString, nullptr, FColor::Emerald, -1.f, false, 1.f );
					}
				}
			}

			IsInitialized = true;
			GridID = GridsCreated;
			++GridsCreated;
		}

		~FFrequencyGrid2D()
		{
			UE_LOG( LogGame, Log, TEXT( "~FrequencyGrid2D Descructor: Num Fequency Cells: %i" ), FrequencyCells.Num() );

			//Delete all 'new' instanciated cells
			for( int i = FrequencyCells.Num() - 1; i >= 0; --i )
			{
				delete FrequencyCells[i];
			}
			FrequencyCells.Reset();
		}


		// Get the cell index for a given location
		int32 GetCellIndexForLocation( FVector location );
		FFrequencyGrid2D_Cell* GetCellForLocation( const FVector& location );

		// Takes a viewer Array for split screen support (realistically we won't have split screen... right?!)
		void GatherAndRankCellsForViewer( UFGReplicationGraphNode_ConveyorSpatialFrequency* GraphNode, UReplicationGraph* RepGraph, UNetConnection* NetConnection, FSettings& MySettings, const FNetViewerArray& Viewers, const int32 FrameNum, TArray< FConveyorFrequency_SortedCell*>& out_cells );

		void AddActor( AActor* actor, int32 FrameNum )
		{
			check( IsInitialized )
			// @todo - Check multiple points and add to range of cells to better match conveyors actual long and winding nature?
			check( actor );

			int32 arrayIndex = GetCellIndexForLocation( actor->GetActorLocation() );

			checkf( arrayIndex >= 0 && arrayIndex < FrequencyCells.Num(), TEXT( "ConveyorFrequencyCell: Calculated Cell Index %i is out of bounds for Cell Count %i" ), arrayIndex, FrequencyCells.Num() );
			
			bool addedSomething = FrequencyCells[ arrayIndex ]->AddActor( actor );
			if( addedSomething )
			{
				FrequencyCells[ arrayIndex ]->SetDirty( FrameNum );
			}
		}

		void RemoveActor( AActor* actor, int32 FrameNum )
		{
			// For now just attempt to remove from all cells as we don't track whether or not an actor should be in a cell
			// Perhaps we will have actors in multiple cells as well so we don't want to run additional math to target specific cells
			for( FFrequencyGrid2D_Cell* gridCell : FrequencyCells )
			{
				bool removedSomething = gridCell->RemoveActor( actor );
				if( removedSomething )
				{
					gridCell->SetDirty( FrameNum );
				}
			}
		}

		TArray< FFrequencyGrid2D_Cell* > FrequencyCells;

		// Draw Visual Debug of cell locations
		void DrawDebug( UWorld* world, TArray<FConveyorFrequency_SortedCell*>& sortedCells );

		// Get the Current CellSize for this cell
		FORCEINLINE FVector2D GetCellSize() const { return CellSize; }
		// Get the Current Origin for this cell
		FORCEINLINE FVector2D GetOrigin() const { return Origin; }

		inline static int32 GridsCreated = 0;
		int32 GridID = 0;

	private:
		FVector2D Origin;
		FVector2D GridMin;
		FVector2D GridMax;
		FVector2D GridSize;
		FVector2D HalfGridSize;
		FVector2D CellSize;
		FVector2D HalfCellSize;
		int32 Subdivisions;
		bool IsInitialized = false;
	};

	// Per Node Grid
	FFrequencyGrid2D* FrequencyGrid;

	// Sorted Cell Lists (will be per connection, but for now, rebuild each gather)
	TMap< UNetConnection*, TArray<FConveyorFrequency_SortedCell*> > mConnectionToSortedCellList;

	// Track Bandwidth Saturation per connection so that we can allocate more budget per connection if other property replication isn't utilizing available budget
	TArray<FConnectionSaturationInfo> mConnectionSaturationInfo;

	// Working ints for adaptive load balancing. Does not count actors that rep every frame
	int32 mNumExpectedReplicationsThisFrame = 0;
	int32 mNumExpectedReplicationsNextFrame = 0;

	int32 CalcFrequencyForCell( FFrequencyGrid2D_Cell* GridCell, UReplicationGraph* RepGraph, UNetConnection* NetConnection, FSettings& MySettings, const FNetViewerArray& Viewers, const uint32 FrameNum, bool IsPlayerInCell );
	
	void CleanUpConnectionSaturationInfo( UReplicationGraph* RepGraph ) 
	{
		mConnectionSaturationInfo.RemoveAll( [&]( FConnectionSaturationInfo& connectionInfo ) {
			return !RepGraph->Connections.Contains( connectionInfo.RepGraphConnection ) || connectionInfo.RepGraphConnection->IsPendingKill();
		} );
	}

	FConnectionSaturationInfo& GetConnectionSaturationInfo( UNetReplicationGraphConnection* repGraphConnection )
	{
		int32 infoIndex = mConnectionSaturationInfo.IndexOfByPredicate( [&]( const FConnectionSaturationInfo& connection ) {
			return connection.RepGraphConnection == repGraphConnection;
		} );

		if( infoIndex == INDEX_NONE )
		{
			infoIndex = mConnectionSaturationInfo.Add( FConnectionSaturationInfo( repGraphConnection ) );
		}

		return mConnectionSaturationInfo[ infoIndex ];
	}

	// Has this Node Initialized its frequency grid
	bool mHasInitializedGrid;

	// For tracking the last frame we checked the GridCells for forceupdate (so that we only do this once per frame)
	uint32 mLastForceUpdateCheckFrameNum;
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
