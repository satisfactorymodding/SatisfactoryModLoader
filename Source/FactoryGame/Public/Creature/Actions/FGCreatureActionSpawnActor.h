// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGCreatureActionAnimated.h"
#include "FGCreatureActionSpawnActor.generated.h"

USTRUCT( BlueprintType )
struct FFGCreatureActionSpawnData
{
	GENERATED_BODY()

	FFGCreatureActionSpawnData()
		: NumToSpawn( 1, 1 )
		, ShouldTriggerOnPerform( false )
	{}
	
	/** The types of actors to spawn, will be chosen at random. */
	UPROPERTY( EditDefaultsOnly )
	TArray< TSubclassOf< AActor > > ActorTypesToSpawn;

	/** How many actors to spawn when triggered. */
	UPROPERTY( EditDefaultsOnly )
	FInt32Interval NumToSpawn;

	/** Notifies which can trigger this spawn. */
	UPROPERTY( EditDefaultsOnly )
	TArray< TSubclassOf< class UFGAnimNotify > > NotifyTriggers;

	/** Whether or not this spawn should trigger immediately when the action is performed. */
	UPROPERTY( EditDefaultsOnly )
	bool ShouldTriggerOnPerform;
};

/**
 * 
 */
UCLASS( BlueprintType, Blueprintable )
class FACTORYGAME_API UFGCreatureActionSpawnActor : public UFGCreatureActionAnimated
{
	GENERATED_BODY()

public:
	UFGCreatureActionSpawnActor( const FObjectInitializer& ObjectInitializer );

	// Begin UFGAction Interface
	virtual void PerformAction_Implementation() override;
	// End UFGAction Interface

	// Begin UFGCreatureActionAnimatedBase Interface
	virtual void OnAnimNotify_Implementation( const UFGAnimNotify* Notify ) override;
	// End UFGCreatureActionAnimatedBase Interface

private:
	void TriggerSpawnData( const FFGCreatureActionSpawnData& data );

	void SpawnActor( const FFGCreatureActionSpawnData& data );
	
private:
	
	/** Spawn data which can be triggered. */
	UPROPERTY( EditDefaultsOnly, Category = "Spawning" )
	TArray< FFGCreatureActionSpawnData > mSpawnData;
};
