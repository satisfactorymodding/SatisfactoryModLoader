// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGSubsystem.h"
#include "FGCreatureSubsystem.generated.h"

/** Used as a wrapper for spawners with additional information. */
USTRUCT()
struct FACTORYGAME_API FSpawnerInfo
{
	GENERATED_BODY()

	UPROPERTY()
	class AFGCreatureSpawner* Spawner;
	
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
	
	void RegisterSpawner( class AFGCreatureSpawner* spawner );
	void UnregisterSpawner( class AFGCreatureSpawner* spawner );

	void RegisterCreature( class AFGCreature* creature );
	void UnregisterCreature( class AFGCreature* creature );

	UFUNCTION( BlueprintPure, Category = "AI" )
	ECreatureHostility GetCreatureHostility() const { return mCreatureHostilityMode; }

	UFUNCTION( BlueprintPure, Category = "AI" )
	bool CanCreaturesAttackEachother() const { return mCreaturesCanAttackEachother; }

	UFUNCTION( BlueprintCallable, Category = "AI" )
	void SetCreatureHostility( ECreatureHostility hostility );

	/** Whether or not the specified creature is protected and can not be targeted by other creatures. */
	UFUNCTION( BlueprintPure, Category = "AI" )
	bool IsProtectedCreature( TSubclassOf< class AFGCreature > creatureClass ) const;

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
	/** Max creatures allowed to spawn at once. */
	UPROPERTY( EditDefaultsOnly, Category = "Creatures" )
	int32 mMaxNumCreatures;

	/** Whether or not creatures are able to attack other creatures at all. Uses creature family system to determine hostility. */
	UPROPERTY( EditDefaultsOnly, Category = "AI" )
	bool mCreaturesCanAttackEachother;
	
	/** Protected creatures can never be targeted by other creatures. */
	UPROPERTY( EditDefaultsOnly, Category = "AI" )
	TArray< TSubclassOf< class AFGCreature > > mProtectedCreatures;
	
	/** All the spawners and information about them. */
	UPROPERTY( Transient )
	TArray< FSpawnerInfo > mAllSpawners;

	/** All the creatures which currently exist. */
	UPROPERTY( Transient )
	TArray< class AFGCreature* > mAllCreatures;

	/** All the persistent creatures which currently exist. */
	UPROPERTY( Transient )
	TArray< class AFGCreature* > mAllPersistentCreatures;

	/** How all creatures behave in terms of being hostile. */
	UPROPERTY( EditAnywhere, Category = "AI" )
	TEnumAsByte< ECreatureHostility > mCreatureHostilityMode;

	/** Every type of FGNoise that exists. */
	UPROPERTY( VisibleAnywhere, Category = "AI" )
	TArray< TSubclassOf< class UFGNoise > > mAllNoiseClasses;
};
