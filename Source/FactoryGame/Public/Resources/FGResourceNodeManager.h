// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "FactoryGame.h"
#include "FGSubsystem.h"
#include "FGResourceNode.h"
#include "FGGameState.h"
#include "Engine/DataAsset.h"
#include "FGResourceNodeManager.generated.h"

class AFGResourceNodeFrackingCore;
class AFGResourceNodeFrackingSatellite;

struct FResourceNodeInfo
{
	TSubclassOf< UFGResourceDescriptor > mResourceDescriptor;
	EResourcePurity mPurity = RP_MAX;
	int32 mTotalThroughput = 0;

	friend bool operator<( const FResourceNodeInfo& lhs, const FResourceNodeInfo& rhs )
	{
		if(lhs.mResourceDescriptor == rhs.mResourceDescriptor)
		{
			if(lhs.mPurity == rhs.mPurity)
			{
				return lhs.mTotalThroughput < rhs.mTotalThroughput;
			}
			return lhs.mPurity < rhs.mPurity;
		}
		if(lhs.mResourceDescriptor == nullptr)
		{
			return true;
		}
		if(rhs.mResourceDescriptor == nullptr)
		{
			return false;
		}
		return lhs.mResourceDescriptor->GetName() < rhs.mResourceDescriptor->GetName();
	}
};

USTRUCT( BlueprintType )
struct FNodeMeshOverrides
{
	GENERATED_BODY()

	/** The static mesh for node. */
	UPROPERTY( EditDefaultsOnly )
	TObjectPtr< UStaticMesh > mMesh;

	/** The materials for node. */
	UPROPERTY( EditDefaultsOnly )
	TArray<TObjectPtr< UMaterialInterface >> mMaterials;

	/** Mesh offset relative to the node position, mostly z offset to compensate different meshes heights */
	UPROPERTY( EditDefaultsOnly )
	FVector mPositionOffset = FVector::ZeroVector;

	/** Turn on update of player position custom primitive vector parameter. Used for effect on SAM static mesh */
	UPROPERTY( EditDefaultsOnly )
	bool mUpdatePlayerPositionParameter = false;
};

UCLASS( BlueprintType )
class FACTORYGAME_API UFGResourceNodeData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY( EditDefaultsOnly )
	TSubclassOf< UFGResourceDescriptor > mResourceDescriptor;

	UPROPERTY( EditDefaultsOnly )
	TMap<ENodeMeshType, FNodeMeshOverrides> mNodeMeshOverrides;
};

UCLASS( BlueprintType )
class FACTORYGAME_API AFGResourceNodeUtilities : public AActor
{
	GENERATED_BODY()
public:
	UFUNCTION( CallInEditor )
	void PerformNodeToMeshAssignment();
	void CreateDefaultNodeListFromWorld();

	TArray< AFGResourceNodeBase* > mAllResourceNodesInWorld;
	TArray< AFGNodeMeshActor* > mAllNodeMeshesInWorld;
};

/**
 * A Manager that handles Resource Node related tasks such as the Randomised Node Game Mode.
 */
UCLASS( Blueprintable, Abstract )
class AFGResourceNodeManager : public AFGSubsystem
{
	GENERATED_BODY()

public:
	static AFGResourceNodeManager* Get( UWorld* world );

	static void CreateListOfMeshesFromWorld( const UWorld* world, TArray< AFGNodeMeshActor* >& out_meshActors );
	static void PairNodesWithMeshes( const TArray< AFGResourceNodeBase* >& nodeArray,
	                                 const TArray< AFGNodeMeshActor* >& meshArray );
	static void PairDepositsWithNodes( const UWorld* world, const TArray< AFGResourceNodeBase* >& nodeArray );
	static void PairDestructiblesWithNodes( const UWorld* world, const TArray< AFGResourceNodeBase* >& nodeArray );

	static FNodeMeshOverrides* GetNodeMeshOverrides( TSubclassOf< UFGResourceDescriptor > resourceDescriptor, ENodeMeshType nodeMeshType );

	void ApplyRandomizationSettings( ENodeRandomizationMode randomizationMode, ENodePuritySettings puritySettings, const int32 seed );
	void CheckForcedRandomizationSettings( AFGGameState* gameState );

protected:
	UPROPERTY( EditDefaultsOnly )
	TMap< ENodeRandomizationMode, float > mNodeCountMultiplier;

private:
	static void TryPairNodeWithMesh( AFGNodeMeshActor* mesh, const TArray< AFGResourceNodeBase* >& nodeArray );
	static AFGResourceNodeBase* GetClosestNode( const FVector& location, float cutoff, EResourceNodeType nodeType,
	                                            const TArray< AFGResourceNodeBase* >& nodeArray );
	void SetNewSeedInternal( const int32 newSeed );
	static TSet< TSubclassOf< UFGResourceDescriptor > > GetResourceDescriptors( const FGameplayTag& gameplayTag );
	static FGameplayTag GetResourceDescriptorTag( ENodeRandomizationMode randomizationMode );
	static uint32 PurityToThroughput( EResourcePurity purity );
	static EResourcePurity ThroughputToPurity( int32 throughput );

	float GetDistributionMultiplier( ENodeRandomizationMode randomizationMode );
	void DistributeThroughput( AFGResourceNodeFrackingCore* frackingCore, int32 totalThroughput ) const;
	uint32 GetThroughput( AFGResourceNodeFrackingCore* frackingCore ) const;

	void CreateDefaultNodeListFromWorld( const UWorld* world );
	void ModifyNodeDistribution( TArray< FResourceNodeInfo >& nodePool, const TSet< TSubclassOf< UFGResourceDescriptor > >& resourcesSubset,
	                             float resourcesSubsetMultiplier );
	EResourcePurity GetPurityOverride( EResourcePurity purity, ENodePuritySettings puritySettings ) const;
	void Shuffle( TArray< FResourceNodeInfo >& nodePool );

	
	TArray< AFGResourceNode* > mResourceNodes;
	TArray< AFGResourceNode* > mGeysers;
	TMultiMap< AFGResourceNodeFrackingCore*, AFGResourceNodeFrackingSatellite* > mFrackingSatellite;
	TArray< AFGResourceNodeFrackingCore* > mFrackingCore;
	
	TArray< FResourceNodeInfo > mNodePool;
	TArray< FResourceNodeInfo > mFrackingNodePool;

	/** This Stream or just a seed is the only thing that needs to be saved for the Random Nodes Game Mode to work. */
	FRandomStream mSeedStream;
	
};
