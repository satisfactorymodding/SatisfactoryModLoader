// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Resources/FGItemDescriptor.h"
#include "FGCrashSiteDebrisActor.h"
#include "FGSaveInterface.h"
#include "FGCrashSiteDebris.generated.h"

class AStaticMeshActor;
class AFGCrashSiteDebrisActor;
class UBoxComponent;

/**
 * Debris meshes that can be spawned and how many.
 */
USTRUCT()
struct FACTORYGAME_API FDebrisMesh
{
	GENERATED_BODY()

	/** Mesh to spawn. */
	UPROPERTY( EditDefaultsOnly, Category = "Mesh" )
	class UStaticMesh* Mesh;

	/** How many to spawn, note that the upper limit is guaranteed while the lower limit is not. */
	UPROPERTY( EditDefaultsOnly, Category = "Mesh" )
	FInt32Interval Num{0, 1};
};

/**
 * Debris actors that can be spawned and how many.
 */
USTRUCT()
struct FACTORYGAME_API FDebrisActor
{
	GENERATED_BODY()

	/** Mesh to spawn. */
	UPROPERTY( EditDefaultsOnly, Category = "Actor" )
	TSubclassOf< AFGCrashSiteDebrisActor > ActorClass;

	/** How many to spawn, note that the upper limit is guaranteed while the lower limit is not. */
	UPROPERTY( EditDefaultsOnly, Category = "Actor" )
	FInt32Interval Num{0, 1};
};

/**
 * Item drops that can be spawned and how many.
 */
USTRUCT()
struct FACTORYGAME_API FDebrisItemDrop
{
	GENERATED_BODY()

	/** Item to create pickup for. */
	UPROPERTY( EditDefaultsOnly, Category = "Item" )
	TSoftClassPtr< class UFGItemDescriptor > ItemClass;

	/** How many items to spawn, note that the upper limit is guaranteed while the lower limit is not. */
	UPROPERTY( EditDefaultsOnly, Category = "Item" )
	FInt32Interval NumItems{0, 10};
};

/**
 * Struct containing the saved simulation for meshes.
 */
USTRUCT()
struct FACTORYGAME_API FSimulatedMeshTransform
{
	GENERATED_BODY()

	UPROPERTY()
	class UStaticMesh* StaticMesh;

	UPROPERTY()
	FTransform MeshTransform;
};

/**
 * Struct containing the saved simulation for actors.
 */
USTRUCT()
struct FACTORYGAME_API FSimulatedActorTransform
{
	GENERATED_BODY()

	UPROPERTY()
	TSubclassOf< AFGCrashSiteDebrisActor > ActorClass;

	UPROPERTY()
	FTransform ActorTransform;
};

/**
 * Struct containing the saved simulation for actors.
 */
USTRUCT()
struct FACTORYGAME_API FSimulatedItemDropTransform
{
	GENERATED_BODY()

	UPROPERTY()
	FTransform ItemDropTransform;
};

/**
 * Actor for spawning debris around a crash site.
 */
UCLASS( Blueprintable )
class FACTORYGAME_API AFGCrashSiteDebris : public AActor, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	AFGCrashSiteDebris();

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

#if WITH_EDITOR

	// Begin UObject interface
	virtual void PreSave(FObjectPreSaveContext SaveContext) override;
	virtual void PreEditChange(FProperty* PropertyAboutToChange) override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	// End UObject interface
	
	// Begin AActor interface
	virtual void Tick( float dt ) override;
	virtual bool ShouldTickIfViewportsOnly() const override;
	// End AActor interface

	/** Resets and destroys saved simulation actors */
	UFUNCTION( BlueprintCallable, Category = "Simulation", meta = ( CallInEditor = "true" ) )
	void ResetSavedSimulation();

	/** Spawns the simulation in the world */
	UFUNCTION( BlueprintCallable, Category = "Simulation", meta = ( CallInEditor = "true" ) )
	void SpawnSimulation();

	/** Saves spawn simulation into the level */
	UFUNCTION( BlueprintCallable, Category = "Simulation", meta = ( CallInEditor = "true" ) )
	void SaveCurrentSimulation();

	/** Destroys current simulation without saving it */
	UFUNCTION( BlueprintCallable, Category = "Simulation", meta = ( CallInEditor = "true" ) )
	void DestroyCurrentSimulation();

	/** Caches debris spawn locations from the instanced mesh component */
	void CacheDebrisSpawnLocations();
#endif
private:
#if WITH_EDITOR
	/** Returns true if the component is within the simulation relevance distance, false otherwise */
	bool IsLocationWithinSimulationDistance( const FVector& location ) const;

	/** Makes the item transform face up */
	static FTransform OrientItemTransformUp( const FTransform& originalTransform, float boxExtent );

	/** Updates currently running simulation */
	void TickCurrentSimulation( float dt );
	
	/** Destroys actors belonging to the saved simulation in the current world */
	void DestroySavedSimulation();

	/** Spawns the actors from the saved simulation data in the correct world */
	void SpawnSavedSimulation();
#endif

private:
#if WITH_EDITORONLY_DATA
	friend class FFGCrashSiteDebrisComponentVisualizer;
	friend class FFGDropPodToolsCommand;
	
	/** Component used for the visualization of item spawn locations */
	UPROPERTY( EditDefaultsOnly, Category = "Visualization" )
	UInstancedStaticMeshComponent* mItemMeshVisualizationComponent;

	/** Debug component for debug visualization */
	UPROPERTY( EditDefaultsOnly, Category = "Visualization" )
	class UFGCrashSiteDebrisDebugComponent* mDebugComponent;
	
	/** Description of which meshes to spawn. */
	UPROPERTY( EditDefaultsOnly, Category = "Simulation" )
	TArray< FDebrisMesh > mDebrisMeshes;
	/** Description of which actors to spawn. */
	UPROPERTY( EditDefaultsOnly, Category = "Simulation" )
	TArray< FDebrisActor > mDebrisActors;

	/** How many item drops to place, debris must be re-simulated when this is updated. */
	UPROPERTY( EditAnywhere, Category = "Simulation" )
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

	/** True if the simulation is currently running */
	UPROPERTY( VisibleInstanceOnly, Category = "Simulation", Transient )
	bool mIsSimulationRunning;

	/** Spawned FGCrashSiteDebris actors for the currently running simulation */
	UPROPERTY( VisibleInstanceOnly, Category = "Simulation", Transient, AdvancedDisplay )
	TArray< AFGCrashSiteDebrisActor*> mSimulatedDebrisCustomActors;

	/** Debris meshes that are simulated but will be attached to this component once the simulation is done */
	UPROPERTY( VisibleInstanceOnly, Category = "Simulation", Transient, AdvancedDisplay )
	TArray<AStaticMeshActor*> mSimulatedDebrisMeshes;

	/** Item boxes marking the item spawn locations for the current simulation */
	UPROPERTY( VisibleInstanceOnly, Category = "Simulation", Transient, AdvancedDisplay )
	TArray<AFGCrashSiteDebrisItemBox*> mSimulateItemBoxActors;

	/** Transforms saved during physics simulation. */
	UPROPERTY( VisibleInstanceOnly, Category = "Saved Simulation" )
	TArray< FSimulatedMeshTransform > mSavedMeshSimulationData;
	UPROPERTY( VisibleInstanceOnly, Category = "Saved Simulation" )
	TArray< FSimulatedActorTransform > mSavedActorSimulationData;
	UPROPERTY( VisibleInstanceOnly, Category = "Saved Simulation" )
	TArray< FSimulatedItemDropTransform > mSavedItemDropSimulationData;
	
	/** Legacy item pick up actors spawned by this crash site. */
	UPROPERTY( VisibleInstanceOnly, Category = "Saved Simulation" )
	TArray< TSoftObjectPtr<AActor> > mSavedSimulatedItemDropActors;
#endif

public:
	/** Drop pod linked to this crash site debris */
	UPROPERTY( EditInstanceOnly, Category = "Crash Site Debris" )
	TSoftObjectPtr<class AFGDropPod> mLinkedDropPod;
	
	/** Actors spawned by this crash site. */
	UPROPERTY( EditInstanceOnly, Category = "Saved Simulation" )
	TArray< TSoftObjectPtr<AActor>> mSavedSimulatedDebrisActors;

	/** New format item drop spawn transforms pulled by the drop pod actor to dynamically spawn the items */
	UPROPERTY( VisibleInstanceOnly, Category = "Saved Simulation" )
	TArray< FTransform > mSavedItemDropSpawnLocations;
};

UCLASS()
class FACTORYGAME_API AFGCrashSiteDebrisItemBox : public AActor
{
	GENERATED_BODY()
public:
	AFGCrashSiteDebrisItemBox();

	FORCEINLINE UBoxComponent* GetBoxComponent() const { return mBoxComponent; }

#if WITH_EDITOR
	FORCEINLINE UStaticMeshComponent* GetVisualizationMeshComponent() const { return mVisualizationComponent; }
#endif
private:
	UPROPERTY( EditAnywhere, Category = "Item Box" )
	class UBoxComponent* mBoxComponent;

#if WITH_EDITORONLY_DATA
	UPROPERTY( EditAnywhere, Category = "Item Box" )
	class UStaticMeshComponent* mVisualizationComponent;
#endif
};

UCLASS()
class FACTORYGAME_API UFGCrashSiteDebrisDebugComponent : public UActorComponent
{
	GENERATED_BODY()
public:
#if WITH_EDITORONLY_DATA
	UPROPERTY( EditAnywhere, Category = "Crash Site Debug Component" )
	class UTexture2D* mCrashSiteDebrisIcon;
	
	/** Sprite to draw when the crash site is not linked to this debris actor */
	UPROPERTY( EditAnywhere, Category = "Crash Site Debug Component" )
	class UTexture2D* mCrashSiteNotLinkedWarning;

	/** Mesh to use for item box visualization */
	UPROPERTY( EditAnywhere, Category = "Crash Site Debug Component" )
	class UStaticMesh* mItemBoxVisualizationMesh;
#endif
};