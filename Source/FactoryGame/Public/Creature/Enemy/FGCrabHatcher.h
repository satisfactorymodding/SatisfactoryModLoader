// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGEnemy.h"
#include "FGCrabHatcher.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGCrabHatcher : public AFGEnemy
{
	GENERATED_BODY()
public:
	// Begin AActor Interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	virtual void Tick( float deltaTime ) override;
	// End AActor Interface
	
	/** Get for mThreatNearby */
	UFUNCTION( BlueprintPure, Category = "Crab Hatcher" )
	FORCEINLINE bool GetThreatNearby() { return mThreatNearby; }

	/** Set for mThreatNearby */
	UFUNCTION( BlueprintCallable, Category = "Crab Hatcher" )
	void SetThreatNearby( bool inNearby ) { mThreatNearby = inNearby; }

	/** Set for mDidSpawnCrabs */
	UFUNCTION( BlueprintCallable, Category = "Crab Hatcher" )
	void SetDidSpawnCrabs( bool inDidSPawn ) { mDidSpawnCrabs = inDidSPawn; }

	UFUNCTION( BlueprintPure, Category = "Crab Hatcher" )
	FORCEINLINE bool GetDidSpawnCrabs() { return mDidSpawnCrabs; }

	/** Set for mAnimationLength */
	UFUNCTION( BlueprintCallable, Category = "Crab Hatcher" )
	void SetAnimationLength( float animLength ) { mAnimationLength = animLength; }

	/** Call to BP to spawn the crab babies */
	UFUNCTION( BlueprintCallable, BlueprintImplementableEvent, Category = "Crab Hatcher" )
	void SpawnCrabs();

	/** Call to BP when expansion starts */
	UFUNCTION( BlueprintImplementableEvent, Category = "Crab Hatcher" )
	void StartExpanding();
protected:
	/** Indicates if a threat is nearby */
	UPROPERTY( Replicated )
	bool mThreatNearby;

	UFUNCTION()
	void OnRep_DidSpawnCrabs();
	/** Have crabs been spawned? */
	UPROPERTY( ReplicatedUsing=OnRep_DidSpawnCrabs )
	bool mDidSpawnCrabs;

	//bool mDidRespondToSpawnCrabBool = false; //[DavalliusA:Fri/31-05-2019] ugly hack, but unless I do this, the crab thatchers don't detect when the bool was already set on spawning. Meaning it was looking alive on clients. Even though I did a begin play test. So, hack it for now!
	bool mBeganPlaying = false; //[DavalliusA:Fri/31-05-2019] so we in the on rep don't play the death effects if we get the on rep before begin play... maybe there is a better way to cehck for this?

	/** Time enemy has been under threat */
	UPROPERTY( Replicated )
	float mThreatTimer;

	/** Time when timer reach it's end */
	UPROPERTY( EditDefaultsOnly, Category = "Crab Hatcher" )
	float mThreatTimerMax;

	/** Length of the animation to play */
	float mAnimationLength;

	bool mDidStartExpanding;
	

public:
	FORCEINLINE ~AFGCrabHatcher() = default;
};
