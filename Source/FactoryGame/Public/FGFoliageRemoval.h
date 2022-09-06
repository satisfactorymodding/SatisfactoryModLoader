// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "GameFramework/Actor.h"
#include "FGSaveInterface.h"
#include "Replication/FGStaticReplicatedActor.h"
#include "FGFoliageRemovalSubsystem.h"
#include "FGFoliageRemoval.generated.h"


/** Legacy removals. Kept for save compatibility. */
USTRUCT()
struct FRemovedInstance
{
	GENERATED_BODY()

	/** Stored in world space */
	UPROPERTY( SaveGame, NotReplicated ) 
	FTransform Transform;
};

/** Legacy removals. Kept for save compatibility. */
USTRUCT()
struct FRemovedInstanceArray
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY( SaveGame, NotReplicated )
	TArray< FRemovedInstance >	Items;
};

/**
* New foliage removal system.
*/

/**
* 8 bit index replication. Used for removals into foliage types/level with < 256 instances.
*/
USTRUCT()
struct FByteRemovalIndex : public FFastArraySerializerItem
{
	GENERATED_USTRUCT_BODY()

	using IndexType = uint8;

	static constexpr int BitCount = sizeof( IndexType ) * 8;

	static constexpr int MaxCount = 1 << BitCount;

	/**
	 * Index into the foliage removal cache in the subsystem
	 */
	UPROPERTY()
	uint8 Index = 0;
};

/**
* 8 bit index replication array.
*/
USTRUCT()
struct FByteRemovalIndices : public FFastArraySerializer
{
	GENERATED_USTRUCT_BODY()

	using ItemType = FByteRemovalIndex;

	UPROPERTY()
	TArray< FByteRemovalIndex > Items;
	
	UPROPERTY( NotReplicated )
	class AFGFoliageRemoval* FoliageRemoval;

	bool NetDeltaSerialize( FNetDeltaSerializeInfo& DeltaParms );

	void AddReplicatedIndex( uint32 index );

	int GetReplicatedIndexCount() const { return Items.Num(); }

	template< typename ArrayType >
	friend bool FoliageRemovalNetDeltaSerialize( FNetDeltaSerializeInfo& deltaParams, ArrayType& fastArray );
};

template<>
struct TStructOpsTypeTraits< FByteRemovalIndices > : public TStructOpsTypeTraitsBase2< FByteRemovalIndices >
{
	enum
	{
		WithNetDeltaSerializer = true
	};
};

/**
* 16 bit index replication. Used for removals into foliage types/level with < 65536 instances.
*/
USTRUCT()
struct FShortRemovalIndex : public FFastArraySerializerItem
{
	GENERATED_USTRUCT_BODY()

	using IndexType = uint16;

	static constexpr int BitCount = sizeof( IndexType ) * 8;

	static constexpr int MaxCount = 1 << BitCount;

	/**
	 * Index into the foliage removal cache in the subsystem
	 */
	UPROPERTY()
	uint16 Index = 0;
};

/**
 * 16 bit index replication array.
 */
USTRUCT()
struct FShortRemovalIndices : public FFastArraySerializer
{
	GENERATED_USTRUCT_BODY()

	using ItemType = FShortRemovalIndex;

	UPROPERTY()
	TArray< FShortRemovalIndex > Items;
	
	UPROPERTY( NotReplicated )
	class AFGFoliageRemoval* FoliageRemoval;

	bool NetDeltaSerialize( FNetDeltaSerializeInfo& DeltaParms );

	void AddReplicatedIndex( uint32 index );

	int GetReplicatedIndexCount() const { return Items.Num(); }

	template< typename ArrayType >
	friend bool FoliageRemovalNetDeltaSerialize( FNetDeltaSerializeInfo& deltaParams, ArrayType& fastArray );
};

template<>
struct TStructOpsTypeTraits< FShortRemovalIndices > : public TStructOpsTypeTraitsBase2< FShortRemovalIndices >
{
	enum
	{
		WithNetDeltaSerializer = true
	};
};

/**
* 32 bit index replication. Used for removals into foliage types/level with >= 65536 instances.
*/
USTRUCT()
struct FLongRemovalIndex : public FFastArraySerializerItem
{
	GENERATED_USTRUCT_BODY()

	using IndexType = uint32;

	static constexpr int BitCount = sizeof( IndexType ) * 8;

	static constexpr int64 MaxCount = 1ll << BitCount;

	/**
	 * Index into the foliage removal cache in the subsystem
	 */
	UPROPERTY()
	uint32 Index = 0;
};

/**
* 32 bit index replication array.
*/
USTRUCT()
struct FLongRemovalIndices : public FFastArraySerializer
{
	GENERATED_USTRUCT_BODY()

	using ItemType = FLongRemovalIndex;

	UPROPERTY()
	TArray< FLongRemovalIndex > Items;
	
	UPROPERTY( NotReplicated )
	class AFGFoliageRemoval* FoliageRemoval;

	bool NetDeltaSerialize( FNetDeltaSerializeInfo& DeltaParms );

	void AddReplicatedIndex( uint32 index );

	int GetReplicatedIndexCount() const { return Items.Num(); }

	template< typename ArrayType >
	friend bool FoliageRemovalNetDeltaSerialize( FNetDeltaSerializeInfo& deltaParams, ArrayType& fastArray );
};

template<>
struct TStructOpsTypeTraits< FLongRemovalIndices > : public TStructOpsTypeTraitsBase2< FLongRemovalIndices >
{
	enum
	{
		WithNetDeltaSerializer = true
	};
};

/**
 * Contains all removals into one foliage type/level component. The 
 */
UCLASS(notplaceable)
class FACTORYGAME_API AFGFoliageRemoval : public AFGStaticReplicatedActor, public IFGSaveInterface
{
	GENERATED_BODY()
public:	
	// Begin built in networking functions
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual bool IsNetRelevantFor( const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation ) const override;
	// End built in networking functions

	/** Ctor */
	AFGFoliageRemoval();

	// Begin AActor interface
	virtual void PostActorCreated() override;
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	// End AActor interface

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	/**
	 * Get one of the components that this removal applies to
	 */
	UHierarchicalInstancedStaticMeshComponent* GetAnyMeshComponent() const;

	/**
	 * Remove all foliage that this foliage removal has removed
	 */
	void ApplyInitialRemovals_Server( bool firstLoad );

	/**
	 * Remove a foliage instance, transform, component and id known
	 */
	bool RemoveFoliageInstanceById( int32 instanceId, class UHierarchicalInstancedStaticMeshComponent* component );

	/**
	 * Remove a foliage instance, transform and optionally component known
	 */
	bool RemoveFoliageInstanceFromComponent( const FTransform& transform, class UHierarchicalInstancedStaticMeshComponent* component );

	/**
	 * Remove a foliage instance, transform and optionally component known
	 */
	class UHierarchicalInstancedStaticMeshComponent* RemoveFoliageInstanceByTransform( const FTransform& transform );

	bool RemoveFoliageInstanceByData( FoliageInstanceData& foliageInstanceData );

	bool RemoveFoliageInstances( TArray< int32 >& instanceIds, class UHierarchicalInstancedStaticMeshComponent* component, TArray< FVector >& out_removedLocations );

	bool AddRemoval( const FVector& location, const TArray< FoliageInstanceData* >& foliageInstanceDataResult, const FoliageTypeData* foliageTypeData );

	struct FoliageTypeData* GetFoliageTypeData() const { return mFoliageTypeData; }

	int FindInstanceIndexByTransform( const FTransform& transform );

	void Debug_PrintReplicationProgress() const;

	// Begin callbacks from IndexArrays when items are replicated
	void RemovedInstances_ItemAdded( int32 removalIndex );
	void RemovedInstances_ItemRemoved( int32 idx );
	void RemovedInstances_ItemChanged( int32 idx );
	void RemovedInstances_ReplicationFrameDone();
	// End callbacks

protected:
	friend struct FRemovalIndices;
	friend struct FRemovalIndex;

	/**
	 * Helper function that finds the the closest foliage instance that's close to the location
	 *
	 */
	int32 FindInstanceByTransform( const FTransform& foliageTransform, const class UHierarchicalInstancedStaticMeshComponent* component ) const;

	/**
	 * Setup the component after a level has streamed in
	 *
	 * @param meshComponent - the new mesh that's associated with this foliage remover (must be valid)
	 */
	void LevelStreamedIn( bool firstLoad );

	void LevelStreamedOut();

private:
	/** Register with the foliage removal subsystem, retries if no one is created yet */
	UFUNCTION()
	void RegisterWithSubsystem();

	/** Unregister ourself from the foliage removal subsystem */
	void RemoveFromSubsystem();

	bool RemoveFoliageInstance_Internal( const FVector& location, int32 instanceId, class UHierarchicalInstancedStaticMeshComponent* component );

	bool RemoveFoliageInstances_Internal( const TArray< FVector >& locations, const TArray< int32 >& instanceIds, class UHierarchicalInstancedStaticMeshComponent* component );

	UFUNCTION()
	void OnRep_RemovalCount( int oldValue );

	/**
	 * If all initial removals have been replicated, removes them by id.
	 */
	void TryApplyInitialRemovals_Client();

protected:
	friend class AFGFoliageRemovalSubsystem;

	/** Deprecated in favor of mRemovalLocations and mRemovalIndices */
	UPROPERTY( SaveGame )
	FRemovedInstanceArray mRemovedInstances;

	/** CLIENT: The instances that should be removed this frame on client (populated every frame with the id's of the instances that has been replicated)*/
	TArray<FRemovedInstance> mClientInstancesToRemove;

	/**
	 * Contains the saved locations of all removals of a foliage type/level
	 */
	UPROPERTY( SaveGame )
	TSet< FVector > mRemovalLocations;

	/**
	 * Contains the replicated indices of removals into foliage type/level with < 256 instances.
	 */
	UPROPERTY( Replicated )
	FByteRemovalIndices mByteRemovalIndices;

	/**
	 * Contains the replicated indices of removals into foliage type/level with < 65536 instances.
	 */
	UPROPERTY( Replicated )
	FShortRemovalIndices mShortRemovalIndices;

	/**
	 * Contains the replicated indices of removals into foliage type/level with >= 65536 instances.
	 */
	UPROPERTY( Replicated )
	FLongRemovalIndices mLongRemovalIndices;

	/**
	 * Contains the number replicated indices of removals into the foliage type/level.
	 * The number is needed to decide when the first batch of removals (usually the saved ones) have been replicated, so that it can be removed cheaper.
	 */
	UPROPERTY( ReplicatedUsing = OnRep_RemovalCount )
	int mRemovalCount = 0;

	/** The name of the level that this actor removes foliage from, so that the foliage system can find it */
	UPROPERTY( SaveGame, Replicated )
	FName mLevelName;

	/** The name of mesh component to use the level */
	UPROPERTY( SaveGame, Replicated )
	FName mFoliageTypeName;

	struct FoliageTypeData* mFoliageTypeData = nullptr;

	/** ServerOnly: The bounds of the level we have foliage in (@todo: Can we remove this savegame tag?)*/
	UPROPERTY( SaveGame )
	FBox mLevelBounds;

	// Set to true when loaded so that we know that we need to go through and verify data in mRemovedInstances
	bool mIsLoaded = false;

	// Flag to indicate whether this removal actor is allowed to run apply. Needs to be setup by FoliageSubSystem first. 
	bool mMarkedByFoliageSubSystem = false;

	/**
	 * The client will use different methods of removal for the first batch (usually the saved ones), and all subsequent removals
	 */
	bool mHasAppliedInitialRemovals_Client = false;
};
