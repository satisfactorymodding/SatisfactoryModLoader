// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Creature/FGCreature.h"
#include "FGSubsystem.h"
#include "Misc/EnumRange.h"
#include "NavMesh/RecastNavMesh.h"
#include "FGCreatureSubsystem.generated.h"

extern TAutoConsoleVariable< int32 > CVarCreatureDisable;
DECLARE_MULTICAST_DELEGATE_OneParam( FOnSpawnerRegistered, AFGCreatureSpawner* spawner );
DECLARE_MULTICAST_DELEGATE_OneParam( FOnSpawnerUnregistered, AFGCreatureSpawner* spawner );

/** Used as a wrapper for spawners with additional information. */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FSpawnerInfo
{
	GENERATED_BODY()

	UPROPERTY( BlueprintReadOnly )
	class AFGCreatureSpawner* Spawner;

	UPROPERTY( BlueprintReadOnly )
	float PlayerDistanceSq;
};

UENUM( BlueprintType )
enum class EPlayerHostilityMode : uint8
{
	// Default hostility against players
	PHM_Default		UMETA( displayName = "Default" ),

	// Passive mode, creature will ignore
	PHM_Passive		UMETA( displayName = "Passive" ),

	// Creature will only fight if attacked
	PHM_Retaliate	UMETA( displayName = "Retaliate" ),
};

USTRUCT(BlueprintType)
struct FAgentGenerationProperties
{
	GENERATED_BODY()

	/** Name of the Nav Agent those settings will apply for. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName agentName = "None";

	/** Should the Tile Size be automatically computed at cell size x autoTileSize? (Epic recommends between 32 and 128, 128 being the fastest to generate the mesh in my testing) */
	UPROPERTY(EditAnywhere)
	bool autoTileSize = true;

	/** How many cell sizes do we set the tile size to? Recommended between 32 and 128. */
	UPROPERTY(EditAnywhere)
	float autoTileSizeMultiplier = 128;

	/** Good luck. This is all the nifty nifty parameters you'll have to touch to optimize or make it worse. :> */
	UPROPERTY(EditAnywhere)
	FRecastNavMeshGenerationProperties navGenerationProperties;
};

/** Used to replace / disable certain creatures when spawning them. */
USTRUCT( BlueprintType )
struct FCreatureClassOverride
{
	GENERATED_BODY()

	FCreatureClassOverride()
		: CreatureClassToReplace( nullptr )
		, CreatureClassOverride( nullptr )
	{}
	
	FCreatureClassOverride( TSubclassOf< class AFGCreature > classToReplace, TSubclassOf< class AFGCreature > overrideClass )
		: CreatureClassToReplace( classToReplace )
		, CreatureClassOverride( overrideClass )
	{}

	UPROPERTY( EditDefaultsOnly )
	TSubclassOf< class AFGCreature > CreatureClassToReplace;

	UPROPERTY( EditDefaultsOnly )
	TSubclassOf< class AFGCreature > CreatureClassOverride;
};

/** Used to decide what to do with existing creatures when adding a creature class override for them. */
UENUM( BlueprintType )
enum class ECreatureReplaceAction : uint8
{
	NOTHING					UMETA( DisplayName = "Nothing" ),
	KILL					UMETA( DisplayName = "Kill" ),
	DESTROY					UMETA( DisplayName = "Destroy" ),
	// REPLACE				UMETA( DisplayName = "Replace" ), // TODO: Might be nice to implement this? My idea for it is that it would respawn the creature in the same spot, but ofc respecting creature class overrides, so it could be replaced by another class.
};

/**
 * 
 */
UCLASS( config = Game, defaultconfig, Blueprintable, meta = ( DisplayName = "Creature Subsystem" ) )
class FACTORYGAME_API AFGCreatureSubsystem : public AFGSubsystem
{
	GENERATED_BODY()
public:
	AFGCreatureSubsystem();

	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void Tick( float dt ) override;
	// End AActor interface

	const TArray< class AFGCreature* >& GetAllCreatures() const { return mAllCreatures; }
	const TArray< FSpawnerInfo >& GetAllSpawners() const { return mAllSpawners; }

	void RegisterSpawner( class AFGCreatureSpawner* spawner );
	void UnregisterSpawner( class AFGCreatureSpawner* spawner );

	void RegisterCreature( class AFGCreature* creature );
	void UnregisterCreature( class AFGCreature* creature );

	void RegisterFlyingBabyCrab( class AFGFlyingBabyCrab* babyCrab );
	void UnregisterFlyingBabyCrab( class AFGFlyingBabyCrab* babyCrab );

	/** Used to force spawners which have players near them to spawn. */
	void ForceTriggerSpawnersInRange();

	UFUNCTION( BlueprintPure, Category = "AI" )
	bool CanCreaturesAttackEachother() const { return mCreaturesCanAttackEachother; }

	UFUNCTION( BlueprintCallable, Category = "AI" )
	void SetCreaturesCanAttackEachother( bool canAttack ) { mCreaturesCanAttackEachother = canAttack; }

	/** Whether or not the specified creature is protected and can not be targeted by other creatures. */
	UFUNCTION( BlueprintPure, Category = "AI" )
	bool IsProtectedCreature( TSubclassOf< class AFGCreature > creatureClass ) const;

	void SetCreatureStressEnabled( bool enabled );

	/** Whether or not creature stress gain is enabled. */
	UFUNCTION( BlueprintPure, Category = "AI" )
	bool IsCreatureStressEnabled() const { return mEnableCreatureStress; }

	/** Get the creature subsystem in the current world, can be nullptr, e.g. on game ending (destroy) or game startup. */
	static AFGCreatureSubsystem* Get( UWorld* world );

	/** Get the creature subsystem in the current world, can be nullptr, e.g. on game ending (destroy) or game startup. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame", DisplayName = "GetCreatureSubsystem", meta = ( DefaultToSelf = "WorldContext" ) )
	static AFGCreatureSubsystem* Get( UObject* worldContext );

	TSubclassOf< class UFGNoise > GetNoiseClassFromFName( const FName& name ) const;
	TSubclassOf< class UFGNoise > GetNoiseClassFromStimulus( const struct FAIStimulus& stimulus ) const;

	/** Use this function to override certain creature classes when spawning them. */
	UFUNCTION( BlueprintCallable, Category = "Creatures" )
	void AddCreatureClassOverride( TSubclassOf< AFGCreature > classToReplace, TSubclassOf< AFGCreature > overrideClass, ECreatureReplaceAction replaceAction = ECreatureReplaceAction::NOTHING );
	void AddCreatureClassOverride( const FCreatureClassOverride& creatureOverride, ECreatureReplaceAction replaceAction = ECreatureReplaceAction::NOTHING );

	/** Used to remove any potential active creature class overrides. */
	UFUNCTION( BlueprintCallable, Category = "Creatures" )
	void RemoveCreatureClassOverride( TSubclassOf< AFGCreature > creatureClass, bool updateScannableState = true );

	AFGCreature* BeginSpawningCreature( TSubclassOf< AFGCreature > creatureClass, const FTransform& spawnTransform );

	/** Set whether or not arachnid creatures should be able to spawn and what to do with existing creatures considered arachnid. */
	UFUNCTION( BlueprintCallable, Category = "Creatures" )
	void SetArachnidCreaturesDisabled( bool disabled, ECreatureReplaceAction replaceAction = ECreatureReplaceAction::DESTROY );

	/** Whether or not arachnid creatures are disabled. */
	UFUNCTION( BlueprintPure, Category = "Creatures" )
	bool GetArachnidCreaturesDisabled() const { return mArachnidCreaturesDisabled; }
	
	/** Used to override a class when spawning a creature. Could be used for easter eggs or removing / replacing creatures. */
	UFUNCTION( BlueprintPure, Category = "Creatures" )
	TSubclassOf< AFGCreature > GetOverriddenCreatureClass( TSubclassOf< AFGCreature > creatureClass ) const;

protected:
	/** Used to override what creature will spawn. Can be used for easter eggs and whatnot. */
	UFUNCTION( BlueprintNativeEvent, Category = "Creatures" )
	TSubclassOf< AFGCreature > OverrideSpawnedCreatureClass( TSubclassOf< AFGCreature > creatureClassToSpawn ) const;
	
private:
	/** Called whenever a level is added to the world */
	UFUNCTION()
	void OnLevelAddedToWorld( ULevel* inLevel, UWorld* inWorld );
	
	/** Called whenever a level is removed from the world */
	UFUNCTION()
	void OnLevelRemovedFromWorld( ULevel* inLevel, UWorld* inWorld );

	void DespawnCreaturesInlevel( ULevel* inLevel );
	
	UFUNCTION()
	void OnCreaturePersistenceUpdated( class AFGCreature* creature, bool isPersistent );
	
	/** Updates information about all the spawners, such as distance from nearest player. */
	void UpdateSpawners();

	/** Manages despawning of creatures. */
	void ManageCreatures();

	/** Wrapper function for managing activation of spawners. */
	void ManageSpawningNewCreatures();

	/** Manages flying baby crabs. */
	void ManageFlyingBabyCrabs( float dt );

	void PopulateNoiseClassArray();

	void HandleExistingCreatureReplacement( class AFGCreature* creatureToReplace, ECreatureReplaceAction replaceAction );

public:
	/** Called when a new spawner is registered */
	FOnSpawnerRegistered mOnSpawnerRegistered;

	/** Called when a existing spawner is unregistered */
	FOnSpawnerUnregistered mOnSpawnerUnregistered;

protected:
	/** Generation properties that will be enforced to the navigation meshes. */
	UPROPERTY( EditDefaultsOnly, Category = "Creatures" )
	TArray<FAgentGenerationProperties> mNavAgentGenerationProperties;
	
	/** Max creatures allowed to spawn at once. */
	UPROPERTY( EditDefaultsOnly, Category = "Creatures" )
	int32 mMaxNumCreatures;

	/** Whether or not creatures are able to attack other creatures at all. Uses creature family system to determine hostility. */
	UPROPERTY( EditDefaultsOnly, Category = "AI" )
	bool mCreaturesCanAttackEachother;

	/** Used to enable / disable creature stress gain. */
	bool mEnableCreatureStress;
	
	/** Protected creatures can never be targeted by other creatures. */
	UPROPERTY( EditDefaultsOnly, Category = "AI" )
	TArray< TSubclassOf< class AFGCreature > > mProtectedCreatures;
	
	/** All the spawners and information about them. */
	UPROPERTY( Transient, BlueprintReadOnly )
	TArray< FSpawnerInfo > mAllSpawners;

	/** All the creatures which currently exist. */
	UPROPERTY( Transient, BlueprintReadOnly )
	TArray< class AFGCreature* > mAllCreatures;

	/** List of creatures with pending reactivation, waiting for level streaming. */
	UPROPERTY( Transient )
	TArray< class AFGCreature* > mPersistentCreaturesPendingReactivation;
	
	/** All the flying baby crabs which currently exist. */
	UPROPERTY( Transient, BlueprintReadOnly )
	TArray< class AFGFlyingBabyCrab* > mAllFlyingBabyCrabs;

	/** All the persistent creatures which currently exist. */
	UPROPERTY( Transient, BlueprintReadOnly )
	TArray< class AFGCreature* > mAllPersistentCreatures;

	/** Every type of FGNoise that exists. */
	UPROPERTY( VisibleAnywhere, Category = "AI" )
	TArray< TSubclassOf< class UFGNoise > > mAllNoiseClasses;

	/** Default overrides for creature classes. */
	UPROPERTY( EditDefaultsOnly, Category = "Creatures" )
	TArray< FCreatureClassOverride > mDefaultCreatureClassOverrides;

	/** Overridden creature classes. */
	UPROPERTY( VisibleAnywhere, Category = "Creatures" )
	TArray< FCreatureClassOverride > mCreatureClassOverrides;

	/** Used to disable arachnid creatures from spawning. */
	UPROPERTY( EditAnywhere, Category = "Creatures" )
	bool mArachnidCreaturesDisabled;
};
