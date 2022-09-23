// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGSubsystem.h"
#include "NavMesh/RecastNavMesh.h"
#include "FGCreatureSubsystem.generated.h"

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
enum ECreatureHostility
{
	// Default behavior for creature hostility.
	CH_Default			UMETA( displayName = "Default" ),

	// With passive hostility, creatures won't attack anything.
	CH_Passive			UMETA( displayName = "Passive" ),

	// Creatures will ignore players but can still attack eachother.
	CH_IgnorePlayers	UMETA( displayName = "Ignore Players" ),
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

#if WITH_EDITOR
	virtual void PostEditChangeProperty( FPropertyChangedEvent& PropertyChangedEvent ) override;
#endif

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
	ECreatureHostility GetCreatureHostility() const { return mCreatureHostilityMode; }

	UFUNCTION( BlueprintPure, Category = "AI" )
	bool CanCreaturesAttackEachother() const { return mCreaturesCanAttackEachother; }

	UFUNCTION( BlueprintCallable, Category = "AI" )
	void SetCreatureHostility( ECreatureHostility hostility );

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

private:
	UFUNCTION()
	void OnCreaturePersistenceUpdated( class AFGCreature* creature, bool isPersistent );
	
	/** Updates information about all the spawners, such as distance from nearest player. */
	void UpdateSpawners();

	/** Manages despawning of creatures. */
	void ManageCreatures();

	void PopulateNoiseClassArray();

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
	
	/** All the flying baby crabs which currently exist. */
	UPROPERTY( Transient, BlueprintReadOnly )
	TArray< class AFGFlyingBabyCrab* > mAllFlyingBabyCrabs;

	/** All the persistent creatures which currently exist. */
	UPROPERTY( Transient, BlueprintReadOnly )
	TArray< class AFGCreature* > mAllPersistentCreatures;

	/** How all creatures behave in terms of being hostile. */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "AI" )
	TEnumAsByte< ECreatureHostility > mCreatureHostilityMode;

	/** Every type of FGNoise that exists. */
	UPROPERTY( VisibleAnywhere, Category = "AI" )
	TArray< TSubclassOf< class UFGNoise > > mAllNoiseClasses;
};
