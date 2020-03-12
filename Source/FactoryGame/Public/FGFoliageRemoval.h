// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "UObject/Class.h"

#include "GameFramework/Actor.h"
#include "FGSaveInterface.h"
#include "Engine/NetSerialization.h"
#include "FGFoliageRemoval.generated.h"

/** Data about removed instances */
/** We can't send the id of the instance to clients, as that requires us to maintain a commandbuffer with all done commands to be able to get the same id's a server/client */
USTRUCT()
struct FACTORYGAME_API FRemovedInstance : public FFastArraySerializerItem
{
	GENERATED_BODY()
	
	FRemovedInstance() :
		Location( FVector::ZeroVector ),
		Transform( FTransform::Identity )
	{
	}

	FRemovedInstance( const FTransform& transform ) :
		Location( transform.GetLocation() ),
		Transform( transform )
	{
	}
	/** Stored in localspace. Compressed location to get the id of the item, @todo: Toy around with different FVector_NetQuantize and see what works best */
	UPROPERTY()
	FVector_NetQuantize10 Location;

	/** Stored in localspace */
	UPROPERTY( SaveGame, NotReplicated ) 
	FTransform Transform;

public:
	FORCEINLINE ~FRemovedInstance() = default;
};

/** Wrapper around the Items struct to enable custom delta serialization (we send a part of the data to the client every frame instead of sending it all in one frame) */
USTRUCT()
struct FACTORYGAME_API FRemovedInstanceArray : public FFastArraySerializer
{
	GENERATED_USTRUCT_BODY()

	/** Used to invoke the callback directly on the foliage removal instead of on FRemovedInstance */
	// @todogc: Investigate if we can move this into a TWeakObjectPointer to reduce strain on gc
	UPROPERTY( NotReplicated )
	class AFGFoliageRemoval* FoliageRemover;

	/** All the items that has been removed from the AFGFoliageRemoval */
	UPROPERTY( SaveGame )
	TArray<FRemovedInstance>	Items;

	// Begin TArray emulation
	FORCEINLINE int32 Num(){ return Items.Num(); }
	
	FORCEINLINE const FRemovedInstance& operator[]( int32 idx ) const{ return Items[idx]; }
	FORCEINLINE FRemovedInstance& operator[]( int32 idx ){ return Items[ idx ]; }
	
	FORCEINLINE void RemoveAt( int32 idx ){ Items.RemoveAt( idx ); }
	FORCEINLINE void RemoveAtSwap( int32 idx ){ Items.RemoveAtSwap( idx ); }
	FORCEINLINE void Empty(){ Items.Empty(); }
	// End TArray emulation
	
	// This does the delta sending of data
	bool NetDeltaSerialize( FNetDeltaSerializeInfo & DeltaParms );

public:
	FORCEINLINE ~FRemovedInstanceArray() = default;
};

/** Enables NetDeltaSerialize in FRemovedInstanceArray with template magic */
template<>
struct FACTORYGAME_API TStructOpsTypeTraits< FRemovedInstanceArray > : public TStructOpsTypeTraitsBase2< FRemovedInstanceArray >
{
	enum
	{
		WithNetDeltaSerializer = true
	};

public:
	FORCEINLINE ~TStructOpsTypeTraits< FRemovedInstanceArray >() = default;
};


UCLASS(notplaceable)
class FACTORYGAME_API AFGFoliageRemoval : public AActor, public IFGSaveInterface
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
	 * Remove all foliage that this foliage removal has removed
	 */
	void Apply();

	/**
	 * Remove a instance from the level
	 *
	 * SERVER ONLY
	 * @param foliageTransform - a transform for the instance
	 * @param localSpace - if true, then the foliageTransform is sent in localspace
	 * @param instanceId - optional, if this is set (not -1), then we can faster lookup the instance, sadly, it's not stable, so we won't be able to rely only on these
	 */
	UFUNCTION(BlueprintCallable, Category="Foliage")
	bool RemoveInstance( FTransform foliageTransform, bool localSpace = false, int32 instanceId = -1 );

	//removes multiple foliage instances at once
	bool RemoveInstances( TArray< FTransform > foliageTransforms, TArray< int32 > instanceIds );

	// Accessor to get mesh component
	FORCEINLINE class UHierarchicalInstancedStaticMeshComponent* GetMeshComponent() const{ return mMeshComponent; }
protected:
	friend struct FRemovedInstanceArray;
	
	// Begin callbacks from FRemovedInstanceArray when items are replicated
	void RemovedInstances_ItemAdded( int32 idx );
	void RemovedInstances_ItemRemoved( int32 idx );
	void RemovedInstances_ItemChanged( int32 idx );
	void RemovedInstances_ReplicationFrameDone();
	// End callbacks

	/**
	 * Helper function that finds the the closest foliage instance that's close to the location
	 *
	 * @param out_adjustedLocation - this will be the location the closest foliage was located at, only changed if we find a instance (ie, return != INDEX_NONE)
	 */
	int32 GetInstanceClosestTo( FVector foliageLocation, FVector& out_closestFoliageLocation, bool localSpace ) const;

	/**
	 * Builds a nice indice list that can be used with InstanceStaticMesh::RemoveInstances from a less packed TArray<FRemovedInstance> list.
	 */
	void BuildRemovalList( const TArray<FRemovedInstance>& instances, TArray<int32>& out_toRemove );

	/**
	 * Setup the component after a level has streamed in
	 *
	 * @param meshComponent - the new mesh that's associated with this foliage remover (must be valid)
	 */
	void LevelStreamedIn( class UHierarchicalInstancedStaticMeshComponent* meshComponent );

	/** Discard old invalid data from our mRemovedInstance, use sparingly as it iterates through all our data and verifies that it's correct, also dirties all items */
	void MakeSureDataIsValid();
private:
	/** Register with the foliage removal subsystem, retries if no one is created yet */
	UFUNCTION()
	void RegisterWithSubsystem();

	/** Unregister ourself from the foliage removal subsystem */
	void RemoveFromSubsystem();
protected:
	friend class AFGFoliageRemovalSubsystem;

	/** Instances to remove, has custom "ReplicatedUsing", so we get a notify for each instance replicated */
	UPROPERTY(SaveGame, Replicated)
	FRemovedInstanceArray mRemovedInstances;

	/** CLIENT: The instances that should be removed this frame on client (populated every frame with the id's of the instances that has been replicated)*/
	TArray<FRemovedInstance> mClientInstancesToRemove;

	/** This needs to be a UPROPERTY as it will become null:ed when the level this actor is associated with is streamed out */
	UPROPERTY() // @todogc: Investigate if we can change this to a TWeakObjectPtr to reduce strain on gc
	class UHierarchicalInstancedStaticMeshComponent* mMeshComponent;

	/** The name of the level that this actor removes foliage from, so that the foliage system can find it */
	UPROPERTY(SaveGame,Replicated)
	FName mLevelName;

	/** The name of mesh component to use the level */
	UPROPERTY(SaveGame,Replicated)
	FName mFoliageTypeName;

	/** ServerOnly: The bounds of the level we have foliage in (@todo: Can we remove this savegame tag?)*/
	UPROPERTY(SaveGame)
	FBox mLevelBounds;

	// Set to true when loaded so that we know that we need to go through and verify data in mRemovedInstances
	uint8 mIsLoaded:1;

	// Flag to indicate whether this removal actor is allowed to run apply. Needs to be setup by FoliageSubSystem first. 
	uint8 mMarkedByFoliageSubSystem:1;

public:
	FORCEINLINE ~AFGFoliageRemoval() = default;
};
