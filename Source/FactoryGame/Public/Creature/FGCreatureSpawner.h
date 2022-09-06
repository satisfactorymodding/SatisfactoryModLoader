// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "GameFramework/Actor.h"
#include "Creature/FGCreature.h"
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
	UFUNCTION( BlueprintNativeEvent, Category = "Spawner ")
	TSubclassOf< class AFGCreature > GetCreatureToSpawn() const;

	FORCEINLINE float GetSpawnDistanceOverride() const { return mSpawnDistanceOverride; }
	FORCEINLINE float GetDespawnDistanceOverride() const { return mDespawnDistanceOverride; }

	/** Radius that we will spawn creatures within */
	FORCEINLINE float GetSpawnRadius() const { return mSpawnRadius; }

	/** Height that we will search for ground within */
	FORCEINLINE float GetSpawnHalfHeight() const { return mSpawnHalfHeight; }

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

	/** Whether or not this spawner is ready to spawn creatures. */
	UFUNCTION( BlueprintPure, Category = "Spawning" )
	bool IsReadyToSpawn();

	/**  Server only - Handles logic for creating creatures when the spawners becomes active */
	void SpawnCreatures();

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
	void PopulateSpawnData();

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
	
protected:
	virtual void OnSpawningFinished();

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

	/** The number of enemies to spawn, used offline */
	UPROPERTY( EditAnywhere, Category = "Spawning" )
	FInt32Interval mNumberOfCreatures;

	/** Can creatures spawn during day? */
	UPROPERTY( EditAnywhere, Category = "Spawning" )
	bool mCanSpawnDuringDay;

	/** Can creatures spawn during night? */
	UPROPERTY( EditAnywhere, Category = "Spawning" )
	bool mCanSpawnDuringNight;

	/** Within what radius do you want to spawn the enemies (the won't go outside of this radius) */
	UPROPERTY( EditAnywhere, Category = "Spawning" )
	float mSpawnRadius;

	/** How much up/down our spawner tries to search for a placeable location */
	UPROPERTY( EditAnywhere, Category = "Spawning" )
	float mSpawnHalfHeight;

	/** Whether or not we are actively spawning. */
	UPROPERTY( SaveGame )
	bool mIsActive;

	/** Structure for keeping all data saved about enemies spawned */
	UPROPERTY( SaveGame )
	TArray< FSpawnData > mSpawnData;

	/** Path splines that enemies in this spawner should set to follow */
	UPROPERTY( EditAnywhere, Category = "Spawning" )
	TArray< class AFGSplinePath* > mSplines;

	/** cached value to see if spawner is near a base */
	UPROPERTY( SaveGame )
	bool mCachedIsNearBase;

	/** Is this spawner a monster closet? (spawning one creature at a time ) */
	UPROPERTY( EditAnywhere, Category = "Spawning" )
	bool mIsMonsterCloset;

	/** Delay in seconds when next creature spawns after current creature died */
	UPROPERTY( EditAnywhere, Category = "Spawning" )
	float mMonsterClosetSpawnDelay;

	/** Timer handle for monster closet spawning */
	UPROPERTY()
	FTimerHandle mMonsterClosetTimerHandle;

	/** Used to override the spawn distance of the creature. */
	UPROPERTY( EditAnywhere, Category = "Spawning" )
	float mSpawnDistanceOverride;

	/** Used to override the despawn distance of the creature. */
	UPROPERTY( EditAnywhere, Category = "Spawning" )
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

	/** Async overlap check is done and result is passed in here */
	UFUNCTION()
	void ReceiveOnTraceCompleted( const TArray< FOverlapResult > & Results );

	/** Does an async overlap in order to find a nearby base. */
	void TraceForNearbyBase();

	/** Function bound to mOverlapDelegate */
	void OnTraceCompleted( const FTraceHandle& Handle, FOverlapDatum& Data );

	FTraceHandle LastTraceHandle;

	/** Delegate fired when we're done with the async check for overlapping actors */
	FOverlapDelegate mOverlapDelegate;
};
