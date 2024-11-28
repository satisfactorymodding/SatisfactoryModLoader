// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FGGiftRainSpawner.generated.h"

/** Spawn data for random gift bundle class selection. */
USTRUCT( BlueprintType )
struct FFGRandomGiftBundleSpawnData
{
	GENERATED_BODY()

	/** The type of gift bundle actor to spawn. */
	UPROPERTY( EditDefaultsOnly )
	TSubclassOf< class AFGFallingGiftBundle > Class = nullptr;

	/** The chance of this gift spawning. All weights are added up and the percentage chance of being selected is Weight / TotalWeight. Weight of <= 0 will never spawn.*/
	UPROPERTY( EditDefaultsOnly )
	int32 SpawnChanceWeight = 1;
};

/**
 * Actor responsible for spawning Falling Gift Bundles
 */
UCLASS( Abstract )
class FACTORYGAME_API AFGGiftRainSpawner : public AActor
{
	GENERATED_BODY()

public:
	AFGGiftRainSpawner();
	
	//~ Begin AActor interface
	virtual void BeginPlay() override;
	//~ End AActor interface
	
	/** Spawns a gift bundle with a randomly picked class (out of the GiftClasses list) at the specified location. */
	UFUNCTION( BlueprintCallable, Category = "Gift Rain Spawner" )
	class AFGFallingGiftBundle* SpawnRandomGiftAtLocation( const FVector& location );

	/** Spawns a gift bundle with a randomly picked class (out of the GiftClasses list) around the specified player. */
	UFUNCTION( BlueprintCallable, Category = "Gift Rain Spawner" )
	class AFGFallingGiftBundle* SpawnRandomGiftAroundPlayer( class AFGCharacterPlayer* player, float spawnDistance );

	/** Spawns a gift bundle with a randomly picked class (out of the GiftClasses list) around a player in the world. */
	UFUNCTION( BlueprintCallable, Category = "Gift Rain Spawner" )
	class AFGFallingGiftBundle* SpawnRandomGiftAroundAnyPlayer( float spawnDistance );

	/** Gets a list of gift bundle actors that this spawner has spawned. */
	UFUNCTION( BlueprintPure, Category = "Gift Rain Spawner" )
	const TArray< class AFGFallingGiftBundle* >& GetSpawnedGiftBundles() const { return mSpawnedGiftBundles; }
	
	/** Whether or not automatic gift spawning is enabled. */
	UFUNCTION( BlueprintPure, Category = "Gift Rain Spawner" )
	bool ShouldAutomaticallySpawnGifts() const;

	/** Enables / Disables the automatic gift spawning. */
	UFUNCTION( BlueprintCallable, Category = "Gift Rain Spawner" )
	void SetAutomaticGiftSpawningEnabled( bool enabled );

	/** Function returning the spawn interval for gifts in seconds. If <= 0 then no gift will spawn. */
	UFUNCTION( BlueprintPure, Category = "Gift Rain Spawner" )
	const FFloatInterval& GetGiftSpawnInterval() const { return mGiftSpawnInterval; }

	/** Sets the frequency of automatic gift spawns. */
	UFUNCTION( BlueprintCallable, Category = "Gift Rain Spawner" )
	void SetGiftSpawnIntervalMinMax( float intervalSecondsMin, float intervalSecondsMax );
	
	/** Sets the frequency of automatic gift spawns. */
	UFUNCTION( BlueprintCallable, Category = "Gift Rain Spawner" )
	void SetGiftSpawnInterval( const FFloatInterval& intervalSeconds );

	/** Returns the current automatic gift spawn limit. No automatic gifts will spawn if the number of spawned gifts exceed this value. */
	UFUNCTION( BlueprintPure, Category = "Gift Rain Spawner" )
	int32 GetAutomaticGiftSpawnLimit() const { return mAutomaticGiftSpawnLimit; }

	/** Sets the automatic gift spawn limit. No automatic gifts will spawn if the number of spawned gifts exceed this value. Set to <= 0 for unlimited spawns. */
	UFUNCTION( BlueprintCallable, Category = "Gift Rain Spawner" )
	void SetAutomaticGiftSpawnLimit( int32 newLimit );

	/** Function used to block a certain gift bundle class from spawning. It will still be part of the weighted selection process, it just wont spawn if it gets randomly selected. */
	UFUNCTION( BlueprintCallable, Category = "Gift Rain Spawner" )
	void SetGiftBundleClassBlockedFromSpawning( TSubclassOf< class AFGFallingGiftBundle > giftBundleClass, bool blocked );

protected:
	/** Returns a gift bundle class to spawn when spawning a random gift bundle. Can be overridden to determine class manually. Otherwise it will grab a random class from the GiftClasses array. */
	UFUNCTION( BlueprintNativeEvent, Category = "Gift Rain Spawner" )
	TSubclassOf< class AFGFallingGiftBundle > GetGiftBundleClassToSpawn();

	/** Called whenever a new gift bundle actor is spawned. */
	virtual void OnGiftBundleSpawned_Native( class AFGFallingGiftBundle* giftBundle );

	/** Called whenever a new gift bundle actor is spawned. */
	UFUNCTION( BlueprintImplementableEvent, Category = "Gift Rain Spawner" )
	void OnGiftBundleSpawned( class AFGFallingGiftBundle* giftBundle );

	/** Called whenever a spawned gift bundle actor is destroyed. */
	UFUNCTION( BlueprintImplementableEvent, Category = "Gift Rain Spawner" )
	void OnGiftBundleDestroyed( class AFGFallingGiftBundle* giftBundle );

	void GetRelevantPlayerCharacters( TArray< class AFGCharacterPlayer* >& out_playerCharacters ) const;

private:
	UFUNCTION()
	void OnGiftBundleActorDestroyed( AActor* giftBundleActor );

	UFUNCTION()
	void OnGiftSpawnerTimerFinished();

	/** Function for controlling the automatic gift spawning timer. */
	void UpdateGiftSpawnerTimer();

	/** Attempts to destroy the oldest gift bundle which isn't near a player. Returns the amount of gifts that were destroyed. */
	int32 TryDestroyOldestGiftBundles( int32 numToDestroy ) const;
	
private:
	/** The different kind of gift bundle classes we want to spawn. Will be picked at random depending on their weights. */
	UPROPERTY( EditDefaultsOnly, Category = "Gift Rain Spawner" )
	TArray< FFGRandomGiftBundleSpawnData > mGiftClasses;

	/** How much additional height to add for the gift rain spawns. */
	UPROPERTY( EditDefaultsOnly, Category = "Gift Rain Spawner" )
	FFloatInterval mGiftRainSpawnHeightIncrease;

	/** List of spawned gift bundles. */
	UPROPERTY( Transient )
	TArray< class AFGFallingGiftBundle* > mSpawnedGiftBundles;

	/** List of gift bundle classes that are not allowed to spawn. Their weight will still be part of the random gift selection, they just won't spawn if they get selected. */
	UPROPERTY( Transient )
	TSet< TSubclassOf< class AFGFallingGiftBundle > > mBlockedGiftBundleSpawnClasses;

	/** Whether or not to enable automatic gift spawning. */
	UPROPERTY( EditDefaultsOnly, Category = "Gift Rain Spawner|Automatic Gift Spawning" )
	bool mEnableAutomaticGiftSpawning;
	
	/** How often to automatically spawn gifts around players (seconds). <= 0 to disable*/
	UPROPERTY( EditDefaultsOnly, Category = "Gift Rain Spawner|Automatic Gift Spawning" )
	FFloatInterval mGiftSpawnInterval;

	/** The spawn radius of automatic gift spawns around players. Min and Max distance. */
	UPROPERTY( EditDefaultsOnly, Category = "Gift Rain Spawner|Automatic Gift Spawning" )
	FFloatInterval mGiftSpawnRadius;

	/** If the amount of spawned gift bundles exceeds this value, then automatic gift spawning will stop. <= 0 means no limit. */
	UPROPERTY( EditDefaultsOnly, Category = "Gift Rain Spawner|Automatic Gift Spawning" )
	int32 mAutomaticGiftSpawnLimit;

	FTimerHandle mGiftSpawnTimerHandle;
};
