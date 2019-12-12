// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "GameFramework/Actor.h"
#include "FGCreature.h"
#include "../FGSaveInterface.h"
#include "FGCreatureSpawner.generated.h"

/** Data we need to know/save about spawns in this spawner */
USTRUCT()
struct FSpawnData
{
	GENERATED_BODY();

	FSpawnData() :
		SpawnLocation( FVector( 0, 0, 0 ) ),
		Creature( nullptr ),
		WasKilled( false ),
		KilledOnDayNr( -1 )
	{}

	/** Location where we want to spawn */
	UPROPERTY( SaveGame )
	FVector SpawnLocation;

	/** Reference to creature */
	UPROPERTY( SaveGame )
	class AFGCreature* Creature;

	/** We save if the creature was killed so we know if we want to respawn the creature when in range of the spawner */
	UPROPERTY( SaveGame )
	bool WasKilled;

	/** What day we were killed ( -1 if we haven't been killed yet ) */
	UPROPERTY( SaveGame )
	int32 KilledOnDayNr;
};

UCLASS()
class FACTORYGAME_API AFGCreatureSpawner : public AActor, public IFGSaveInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFGCreatureSpawner();

	// BEGIN AActor interface
	virtual void BeginPlay() override;

	/** Moved in the editor, on done, calculate spawn locations */
	#if WITH_EDITOR
	virtual void PostEditMove( bool bFinished ) override;
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

	/** Get all spawn locations that's been calculated */
	void GetSpawnLocations( TArray<FVector>& out_spawnLocations ) const;

	/** Get the creature that we will spawn */
	FORCEINLINE TSubclassOf< class AFGCreature > GetCreatureToSpawn() const { return mCreatureClass; }

	/** Radius that we will spawn creatures within */
	FORCEINLINE float GetSpawnRadius() const { return mSpawnRadius; }

	/** Height that we will search for ground within */
	FORCEINLINE float GetSpawnHalfHeight() const { return mSpawnHalfHeight; }

	/** Gets all splines assigned to this spawner */
	UFUNCTION( BlueprintPure, Category = "Spawning" )
	FORCEINLINE TArray< class AFGSplinePath* > GetSplines() { return mSplines; }

	/** Sets active state of a spawner */
	void SetSpawnerActive( bool active );

	/** Is this spawner within active distance? */
	UFUNCTION( BlueprintPure, Category = "Spawning" )
	FORCEINLINE bool IsSpawnerActive() { return mIsActive; }

	/**  Server only - Handles logic for creating creatures when the spawners becomes active */
	UFUNCTION( BlueprintNativeEvent, Category = "Spawning" )
	void SpawnCreatures();

	/** Server only - Handles logic for destroying creatures when the spawners becomes active */
	UFUNCTION( BlueprintNativeEvent, Category = "Spawning" )
	void DestroyCreatures();

	/** Returns true if all conditions for resetting the WasKilled status of an entry in SpawnData are met */
	bool ShouldResetKillStatus( FSpawnData spawnData, int32 newDayNr );

	/** Goes through all spawndata and sets correct WasKilled depending on how many days have passed */
	void UpdateKillStatus( int32 newDayNr ); 

	/** Should this creature exist at this time? ( day/night ) */
	bool IsTimeForCreature();

	/** If all conditions are met ( day/night spawning, reset kill status when days have passed etc ) we spawn creatures */
	void TrySpawnCreatures();

	/** Called when a creature died, need to be UFUNCTION as it's bound as a delegate */
	UFUNCTION()
	virtual void CreatureDied( AActor* thisActor );

	/**
	* Calculates the locations of the spawn locations of the enemies
	* @returns false if we didn't manage to fit all the enemies is the radius
	**/
	UFUNCTION( BlueprintCallable, Category = "Spawning", meta = ( CallInEditor = "true" ) )
	bool CalculateSpawningLocations();
protected:
	/** Randoms a location within range of this actor, and randoms new locations trying to find a unused location numRetries times */
	bool TryFindNonOverlappingLocation( const TArray<FVector2D>& usedSpawnLocations, float spawnRadius, int32 maxRetries, FVector2D& out_location );

	/** Check through usedLocations so that location isn't overlapping another location (using mCreatureClass radius) */
	bool IsLocationNonOverlapping( const FVector2D& location, const TArray< FVector2D >& usedLocations ) const;
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

	/** Within what radius do you want to spawn the enemies (the won't go outside of this radius) */
	UPROPERTY( EditAnywhere, Category = "Spawning" )
	float mSpawnRadius;

	/** How much up/down our spawner tries to search for a placeable location */
	UPROPERTY( EditAnywhere, Category = "Spawning" )
	float mSpawnHalfHeight;

	/** Indicates if we have spawned our enemies */
	UPROPERTY( SaveGame )
	bool mIsActive;

	/** Structure for keeping all data saved about enemies spawned */
	UPROPERTY( SaveGame )
	TArray< FSpawnData > mSpawnData;

	/** Path splines that enemies in this spawner should set to follow */
	UPROPERTY( EditAnywhere, Category = "Spawning" )
	TArray< class AFGSplinePath* > mSplines;
private:
	UPROPERTY( SaveGame )
	int32 mRandomSeed;
public: 
	/** How many days should pass before creatures start to respawn ( -1 means never ) */
	UPROPERTY( EditInstanceOnly, Category = "Spawning" )
	int32 mRespawnTimeIndays;
};
