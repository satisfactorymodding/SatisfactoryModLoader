// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/StaticMesh.h"
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Resources/FGItemDescriptor.h"
#include "FGCrashSiteDebrisActor.h"
#include "FGCrashSiteDebris.generated.h"


/**
 * Debris meshes that can be spawned and how many.
 */
USTRUCT()
struct FDebrisMesh
{
	GENERATED_BODY()
public:
	FDebrisMesh();

	/** Mesh to spawn. */
	UPROPERTY( EditDefaultsOnly, Category = "Mesh" )
	class UStaticMesh* Mesh;

	/** How many to spawn, note that the upper limit is guaranteed while the lower limit is not. */
	UPROPERTY( EditDefaultsOnly, Category = "Mesh" )
	FInt32Interval Num;
};

/**
 * Debris actors that can be spawned and how many.
 */
USTRUCT()
struct FDebrisActor
{
	GENERATED_BODY()
public:
	FDebrisActor();

	/** Mesh to spawn. */
	UPROPERTY( EditDefaultsOnly, Category = "Actor" )
	TSubclassOf< AActor > ActorClass;

	/** How many to spawn, note that the upper limit is guaranteed while the lower limit is not. */
	UPROPERTY( EditDefaultsOnly, Category = "Actor" )
	FInt32Interval Num;
};

/**
 * Item drops that can be spawned and how many.
 */
USTRUCT()
struct FDebrisItemDrop
{
	GENERATED_BODY()
public:
	FDebrisItemDrop();

	/** Get the item class of this item drop */
	TSubclassOf< class UFGItemDescriptor > GetItemClass() const;

	/** If the items descriptor is cooked away, this is not valid */
	bool IsValid() const;

	/** How many items to spawn, note that the upper limit is guaranteed while the lower limit is not. */
	UPROPERTY( EditDefaultsOnly, Category = "Item" )
	FInt32Interval NumItems;
protected:
	/** Item to create pickup for. */
	UPROPERTY( EditDefaultsOnly, Category = "Item" )
	TSoftClassPtr< class UFGItemDescriptor > ItemClass;
};


/**
 * Struct containing the saved simulation for meshes.
 */
USTRUCT()
struct FSimulatedMeshTransform
{
	GENERATED_BODY()
public:
	FSimulatedMeshTransform();
	FSimulatedMeshTransform( class UStaticMesh* mesh, const FTransform& transform );

	UPROPERTY()
	class UStaticMesh* StaticMesh;

	UPROPERTY()
	FTransform MeshTransform;
};

/**
 * Struct containing the saved simulation for actors.
 */
USTRUCT()
struct FSimulatedActorTransform
{
	GENERATED_BODY()
public:
	FSimulatedActorTransform();
	FSimulatedActorTransform( TSubclassOf< AFGCrashSiteDebrisActor > actor, const FTransform& transform );

	UPROPERTY()
	TSubclassOf< AFGCrashSiteDebrisActor > ActorClass;

	UPROPERTY()
	FTransform ActorTransform;
};

/**
 * Struct containing the saved simulation for actors.
 */
USTRUCT()
struct FSimulatedItemDropTransform
{
	GENERATED_BODY()
public:
	FSimulatedItemDropTransform();

	UPROPERTY()
	FTransform ItemDropTransform;
};

/**
 * Actor for spawning debris around a crash site.
 */
UCLASS( Blueprintable )
class FACTORYGAME_API AFGCrashSiteDebris : public AActor
{
	GENERATED_BODY()
public:
	AFGCrashSiteDebris();
	~AFGCrashSiteDebris();

#if WITH_EDITOR
	virtual void OnConstruction( const FTransform& transform ) override;
	virtual void BeginPlay() override;
	virtual void Tick( float dt ) override;
	virtual void PostEditChangeChainProperty( struct FPropertyChangedChainEvent& PropertyChangedEvent ) override;
#endif

private:
#if WITH_EDITOR
	void OnPreBeginPIE( bool isSimulating );
	void OnEndPIE( bool wasSimulatingInEditor );

	void SpawnSimulation();
	void ResetSavedSimulation();
	void DestroySavedSimulation();
	void SpawnSavedSimulation();
#endif

private:
#if WITH_EDITORONLY_DATA
	/** Description of which meshes to spawn. */
	UPROPERTY( EditDefaultsOnly, Category = "Simulation" )
	TArray< FDebrisMesh > mDebrisMeshes;
	/** Description of which actors to spawn. */
	UPROPERTY( EditDefaultsOnly, Category = "Simulation" )
	TArray< FDebrisActor > mDebrisActors;

	/** Description of which parts to spawn. */
	UPROPERTY( EditDefaultsOnly, Category = "Item Drops" )
	TArray< FDebrisItemDrop > mItemDrops;
	/** How many item drops to place, debris must be resimulated when this is updated. */
	UPROPERTY( EditDefaultsOnly, Category = "Item Drops" )
	int32 mNumItemDrops;

	/** How far up to spawn the debris. */
	UPROPERTY( EditAnywhere, Category = "Simulation" )
	float mSpawnAltitude;
	/** If we want the debris to spread a bit more. */
	UPROPERTY( EditAnywhere, Category = "Simulation" )
	float mSpawnRadiusMultiplier;
	/** How much the parts should penetrate the ground. */
	UPROPERTY( EditAnywhere, Category = "Simulation", meta = ( UIMin = 0, UIMax = 0.5, ClampMin = 0, ClampMax = 1 ) )
	float mDebrisPenetrateGroundByPercentage;

	/** Maximum distance from the center debris can end up, debris outside this radius is destroyed. */
	UPROPERTY( EditAnywhere, Category = "Simulation" )
	float mDespawnRadius;

	/** If true debris will be respawned next simulation. */
	UPROPERTY( EditInstanceOnly, Category = "Simulation" )
	bool mRegenerateDebrisNextSimulation;

	/** true if we currently run a simulation on this actor. */
	bool mIsSIEActor;

	/** true if simulate in editor has ended. */
	bool mHasSIEEnded;

	/** true if we have unsaved simulation changes, UPROPERTY so value will be copied from the SIE actor. */
	bool mHasUnsavedSimulation;

	/**
	 * Keep track of active simulation spawned actors.
	 * Cannot be UPROPERTY as it crashes on keep simulation changes.
	 */
	TArray< TWeakObjectPtr< AActor > > mSimulatedDebrisActors;

	/** Actors spawned by this crash site. */
	UPROPERTY( VisibleInstanceOnly, Category = "Saved Simulation" )
	TArray< AActor* > mSavedSimulatedDebrisActors;
	UPROPERTY( VisibleInstanceOnly, Category = "Saved Simulation" )
	TArray< AActor* > mSavedSimulatedItemDropActors;

	/** Transforms saved during physics simulation. */
	UPROPERTY( VisibleInstanceOnly, Category = "Saved Simulation" )
	TArray< FSimulatedMeshTransform > mSavedMeshSimulationData;
	UPROPERTY( VisibleInstanceOnly, Category = "Saved Simulation" )
	TArray< FSimulatedActorTransform > mSavedActorSimulationData;
	UPROPERTY( VisibleInstanceOnly, Category = "Saved Simulation" )
	TArray< FSimulatedItemDropTransform > mSavedItemDropSimulationData;
#endif
};
