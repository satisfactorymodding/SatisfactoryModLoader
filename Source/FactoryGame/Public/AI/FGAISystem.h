// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/World.h"
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "Tickable.h"
#include "FGAggroTargetInterface.h"
#include "AISystem.h"
#include "FGAISystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FAggroTargetAddedSignature, TScriptInterface<class IFGAggroTargetInterface>, aggroTarget );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FAggroTargetRemovedSignature, TScriptInterface<class IFGAggroTargetInterface>, aggroTarget );

/**
 * @todoai: Expose tick to BP here, as it might be interesting for modders to use
 */
UCLASS(Blueprintable)
class FACTORYGAME_API UFGAISystem : public UAISystem, public FTickableGameObject
{
	GENERATED_BODY()
public:
	/** ctor */
	UFGAISystem( const FObjectInitializer& ObjectInitializer );

	// BEGIN UAISystemBase interface	
	virtual void InitializeActorsForPlay( bool bTimeGotReset ) override;
	// END UAISystemBase interface

	// BEGIN FTickableGameObject interface
	virtual void Tick( float DeltaTime ) override;
	virtual bool IsTickable() const override;
	virtual TStatId GetStatId() const override{ RETURN_QUICK_DECLARE_CYCLE_STAT( UFGAISystem, STATGROUP_AI ); }
	// END FTickableGameObject interface

	bool GetDisablePawnMovement() { return mDisablePawnMovement; }

	/** Get the current FGAI system */
	static UFGAISystem* GetCurrentFG( UWorld* world );

	/** Get the current FGAI system */
	static UFGAISystem* GetCurrentFGSafe( UWorld* world );

	/** Check spawners proximity to players */
	void TickSpawners( float dt );

	/**
	 * Addes this aggro target as a global aggro target
	 */
	UFUNCTION(BlueprintCallable, Category="FactoryGame|AI|Aggro")
	static void AddToTargetableList( TScriptInterface<class IFGAggroTargetInterface> aggroTarget );

	/**
	* Removes this aggro target as a global aggro target
	*/
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|AI|Aggro" )
	static void RemoveFromTargetableList( TScriptInterface<class IFGAggroTargetInterface> aggroTarget );

	/** Get all available aggro targets */
	UFUNCTION( BlueprintPure, Category="FactoryGame|AI|Aggro")
	const TArray< class TScriptInterface< IFGAggroTargetInterface > >& GetAggroTargetList() const;

	/** Removes all actors from the pardoned list */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|AI|Aggro" )
	void ClearAllPardonedActors();

	/** Give pardon to a actor */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|AI|Aggro" )
	void PardonActor( AActor* inActor );

	/** removes pardon from an actor */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|AI|Aggro" )
	void UnpardonActor( AActor* inActor );

	/** Is this actor pardoned from being targeted? */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|AI|Aggro" ) 
	bool IsActorPardoned( AActor* inActor );
public:
	/** Called whenever a aggro target is added */
	UPROPERTY(BlueprintAssignable,Category="AI|AggroTargets")
	FAggroTargetAddedSignature mOnAggroTargetAdded;

	/** Called whenever a aggro target is removed */
	UPROPERTY(BlueprintAssignable, Category="AI|AggroTargets")
	FAggroTargetRemovedSignature mOnAggroTargetRemoved;
protected:
	/** Adds a aggro target to the targetable list */
	void AddToTargetableListImp( TScriptInterface<class IFGAggroTargetInterface> aggroTarget );

	/** Removes a aggro target to the targetable list */
	void RemoveFromTargetableListImp( TScriptInterface<class IFGAggroTargetInterface> aggroTarget );

	/** Used to keep track of when aggro targets is spawned */
	virtual void OnActorSpawned( AActor* spawnedActor ) override;

	/** Called when a aggro target is destroyed */
	UFUNCTION()
	void AggroTargetDestroyed( AActor* destroyedActor );

	/** Called when a creature is destroyed */
	UFUNCTION()
	void CreatureDestroyed( AActor* destroyedEnemy );

	/** Called when a player is destroyed */
	UFUNCTION()
	void PlayerDestroyed( AActor* destroyedPlayer );

	/** Find the closest player sq for a creature */
	float FindClosestPlayerSq( class AActor* actor, class AFGCharacterPlayer*& out_closestPlayer ) const;
public:
	/** distance for disabling an enemys AI  */
	UPROPERTY(EditDefaultsOnly,Category="AI")
	float mDisableAIDistance;

	/** distance when we switch movement mode on creatures to PHYS_NavWalking  */
	UPROPERTY( EditDefaultsOnly, Category = "AI" )
	float mNavWalkingDistance;

	/** distance when we completely remove ticking on mesh  */
	UPROPERTY( EditDefaultsOnly, Category = "AI" )
	float mMeshTickEnableDistance;

	/** distance when we switch tick mode on mesh to Tick Only when Rendered  */
	UPROPERTY( EditDefaultsOnly, Category = "AI" )
	float mMeshUpdateDistance;
protected:
	/** Distance for when we should activate a spawner */
	UPROPERTY( EditDefaultsOnly, Category = "AI" )
	float mActivateSpawnerDistance;

	/* Indicates if we also want to disable pawn movement when we disable the AI */
	UPROPERTY( EditDefaultsOnly, Category = "AI" )
	bool mDisablePawnMovement;

	/** Cached list of all aggro targets, not guaranteed to have the same order */
	TArray< class TScriptInterface< IFGAggroTargetInterface > > mAllAggroTargets;

	/** Cached list of all enemies, used for optimizing enemies depending on distance */
	TArray< class AFGCreature* > mAllCreatures;

	/** Cached list of all players, used for checking distance to all enemies */
	TArray< class AFGCharacterPlayer* > mAllPlayers;

	/** Cached list of all enemy spawners. Used to spawn enemies based on distance to player */
	TArray< class AFGCreatureSpawner* > mAllCreatureSpawners;

	/** Actors that have been given pardon from being targeted by enemies */
	TArray< AActor* > mPardonedActors;
private:
	/** Iterator for current index in the creatures array */
	int32 mCreatureIterator; 

	/** Iterator for current index in the creature spawner array */
	int32 mSpawnerIterator;

	/** How many creatures can we iterate over per tick */
	UPROPERTY( EditDefaultsOnly, Category = "AI" )
	int32 mMaxCreatureIterationsPerTick;

	/** How many spawners can we iterate over per tick */
	UPROPERTY( EditDefaultsOnly, Category = "AI" )
	int32 mMaxSpawnerIterationsPerTick; 
};
