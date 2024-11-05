// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "GameFramework/Actor.h"
#include "FGCreature.h"
#include "FGInventoryComponent.h"
#include "FGSaveInterface.h"
#include "FGCreatureSpawner.generated.h"

extern TAutoConsoleVariable< int32 > CVarCreatureSpawnerDebug;

/** Data we need to know/save about spawns in this spawner */
USTRUCT()
struct FACTORYGAME_API FSpawnData
{
	GENERATED_BODY();

	FSpawnData() :
		Creature( nullptr ),
		WasKilled( false ),
		NumTimesKilled( 0 ),
		KilledOnDayNr( -1 ),
		WaitingForSpawnLocation( false ),
		SpawnLocationWaitTimeStamp( -1.0f )
	{}

	/** Reference to creature */
	UPROPERTY( SaveGame )
	class AFGCreature* Creature;

	/** We save if the creature was killed so we know if we want to respawn the creature when in range of the spawner */
	UPROPERTY( SaveGame )
	bool WasKilled;

	/** How many times this creature has been killed. */
	UPROPERTY( SaveGame )
	int32 NumTimesKilled;

	/** What day we were killed ( -1 if we haven't been killed yet ) */
	UPROPERTY( SaveGame )
	int32 KilledOnDayNr;

	/** Whether or not this spawn data is currently waiting on a projected spawn location. */
	bool WaitingForSpawnLocation;

	/** Timestamp of when the spawn data first started waiting for a valid spawn location. */
	float SpawnLocationWaitTimeStamp;
};

UCLASS()
class FACTORYGAME_API AFGCreatureSpawner : public AActor, public IFGSaveInterface
{
	GENERATED_BODY()
public:	
	AFGCreatureSpawner();

	// BEGIN AActor interface
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type endPlayReason ) override;
	virtual void Tick(float DeltaSeconds) override;
	#if WITH_EDITOR
	/** Moved in the editor, on done, calculate spawn locations */
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	#endif
	// END AActor interface

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override; 
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	/** Get the creature that we will spawn */
	UFUNCTION( BlueprintPure, Category = "Spawner" )
	TSubclassOf< class AFGCreature > GetCreatureToSpawn() const;

	/** Gets the default creature class*/
	UFUNCTION( BlueprintPure, Category = "Spawner" )
	FORCEINLINE TSubclassOf< class AFGCreature > GetCreatureClass() const { return mCreatureClass; }

	/** Gets the arachnid override creature class*/
	UFUNCTION( BlueprintPure, Category = "Spawner" )
	FORCEINLINE TSubclassOf< class AFGCreature > GetCreatureClassArachnidOverride() const { return mCreatureClassArachnidOverride; }

	/** Gets the creatures that belong to this spawner. */
	UFUNCTION( BlueprintPure, Category = "Spawner" )
	TArray< AFGCreature* > GetCreatures() const;

	/** Appends the creatures of this spawner to the specified array*/
	UFUNCTION( BlueprintCallable, Category = "Spawner" )
	TArray< AFGCreature* > AppendCreatures( TArray< AFGCreature* >& out_creatures );

	FORCEINLINE float GetSpawnDistanceOverride() const { return mSpawnDistanceOverride; }
	FORCEINLINE float GetDespawnDistanceOverride() const { return mDespawnDistanceOverride; }

	/** Radius that we will spawn creatures within */
	FORCEINLINE float GetSpawnRadius() const { return mSpawnRadius; }

	/** Gets all splines assigned to this spawner */
	UFUNCTION( BlueprintPure, Category = "Spawning" )
	FORCEINLINE TArray< class AFGSplinePath* > GetSplines() { return mSplines; }

	/** Is this spawner currently spawning creatures. */
	UFUNCTION( BlueprintPure, Category = "Spawning" )
	FORCEINLINE bool IsSpawnerActive() const { return mIsActive; }

	/** Whether or not a creature can be spawned according to the specified spawn data. */
	bool CanSpawnCreature( const FSpawnData& spawnData ) const;
	
	FORCEINLINE bool CanSpawnDuringDay() const { return mCanSpawnDuringDay; }
	FORCEINLINE bool CanSpawnDuringNight() const { return mCanSpawnDuringNight; }

	/** Returns the number of creatures belonging to this spawner which do not exist and can be spawned. */
	UFUNCTION( BlueprintPure, Category = "Spawning" )
	int32 GetNumUnspawnedCreatures() const;

	/** Gets the total amount of creatures this spawner can spawn. */
	UFUNCTION( BlueprintPure, Category = "Spawning" )
	int32 GetTotalNumCreatures() const;

	/** Whether or not this spawner is ready to spawn creatures. */
	UFUNCTION( BlueprintPure, Category = "Spawning" )
	bool IsReadyToSpawn();

	/**  Server only - Handles logic for creating creatures when the spawners becomes active */
	void SpawnCreatures();

	/** Server only - Finishes creature spawning and sets spawner as inactive. */
	void StopSpawning();

	/**  Server only - Handles logic for actually spawning a single creature */
	void SpawnSingleCreature();

	/** Server only - Handles logic for destroying creatures when the spawners becomes active */
	void DestroyCreatures();

	/** Returns true if all conditions for resetting the WasKilled status of an entry in SpawnData are met */
	bool ShouldResetKillStatus( const FSpawnData& spawnData, int32 newDayNr );

	/** Goes through all spawndata and sets correct WasKilled depending on how many days have passed */
	void UpdateKillStatus( int32 newDayNr ); 

	/** Should this creature exist at this time? ( day/night ) */
	bool IsTimeForCreature() const;
	
	/** Called when a creature died, need to be UFUNCTION as it's bound as a delegate */
	UFUNCTION()
	virtual void CreatureDied( AActor* thisActor );

	/** Populates the spawndata array. */
	bool PopulateSpawnData();

	/** The distance at which this spawner will activate */
	UFUNCTION( BlueprintPure, Category = "Spawning" )
	float GetSpawnDistance() const;

	/** Returns the cached value for isNearBase */
	UFUNCTION( BlueprintPure, Category = "Spawning" ) 
	FORCEINLINE bool IsNearBase() const { return mCachedIsNearBase; }

	/** Returns the cached value for isNearBase */
	UFUNCTION()
	FORCEINLINE bool VisualizeSpawnDistance() const { return mVisualizeSpawnDistance; }

	/** Update if this spawner is scannable. Checks if near base and if it has any alive untamed creatures */
	void UpdateScannableState();

	/** Try and recouple creatures that are in this instances mSpawnData but has no spawner set */
	void TryRecoupleCreatureAndSpawner();

#if !UE_BUILD_SHIPPING
	void DrawDebugInformation( float duration );
#endif

	/** Used to register the spawner as a navigation invoker to generate navmesh around it for the creature. */
	void RegisterAsNavigationInvoker( bool shouldRegister );

protected:
	/** For showing a preview of what will happen in the editor */
	UPROPERTY()
	class UFGCreatureSpawnerDebugComponent* mDebugComponent;

	UPROPERTY()
	class UBillboardComponent* mEditorSprite;

	UPROPERTY()
	class UCapsuleComponent* mCapsuleComponent;

	/** The creature we should spawn */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Spawning" )
	TSubclassOf< class AFGCreature > mCreatureClass;

	/** The creature to spawn in case arachnid creatures are disabled, and our normal creature is considered arachnid */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Spawning" )
	TSubclassOf< class AFGCreature > mCreatureClassArachnidOverride;

	/** The number of enemies to spawn, used offline */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Spawning" )
	FInt32Interval mNumberOfCreatures;

	/** Can creatures spawn during day? */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Spawning" )
	bool mCanSpawnDuringDay;

	/** Can creatures spawn during night? */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Spawning" )
	bool mCanSpawnDuringNight;

	/** Within what radius do you want to spawn the enemies (the won't go outside of this radius) */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Spawning" )
	float mSpawnRadius;

	/** Whether or not we are actively spawning. */
	UPROPERTY()
	bool mIsActive;

	/** Structure for keeping all data saved about enemies spawned */
	UPROPERTY( SaveGame )
	TArray< FSpawnData > mSpawnData;

	/** Path splines that enemies in this spawner should set to follow */
	UPROPERTY( EditAnywhere, Category = "Spawning" )
	TArray< class AFGSplinePath* > mSplines;

	/** For creatures with attached items, the item we attach to the creature will get chosen from this list at random. */
	UPROPERTY( EditAnywhere, Category = "Spawning" )
	TArray< FInventoryStack > mAttachedItemLootTable;

	/** cached value to see if spawner is near a base */
	UPROPERTY( SaveGame )
	bool mCachedIsNearBase;

	/** Used to override the spawn distance of the creature. */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Spawning" )
	float mSpawnDistanceOverride;

	/** Used to override the despawn distance of the creature. */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Spawning" )
	float mDespawnDistanceOverride;
	
private:
	int32 mRandomSeed;

	float mLastTraceTimeStamp;

	bool mHasScannableCreatures;

	bool mIsRegisteredAsNavigationInvoker;
	
public: 
	/** Should this spawner draw a sphere showing its spawn distance in editor */
	UPROPERTY( EditAnywhere, Category = "Spawning" )
	bool mVisualizeSpawnDistance;

	/** How many days should pass before creatures start to respawn ( -1 means never ) */
	UPROPERTY( EditInstanceOnly, Category = "Spawning" )
	int32 mRespawnTimeIndays;
	
	/** Does a call to the proximity system. */
	void TraceForNearbyBase();
};
