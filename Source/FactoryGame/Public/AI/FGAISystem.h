// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/World.h"
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "Tickable.h"
#include "AISystem.h"
#include "FGAISystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FAggroTargetAddedSignature, TScriptInterface<class IFGAggroTargetInterface>, aggroTarget );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FAggroTargetRemovedSignature, TScriptInterface<class IFGAggroTargetInterface>, aggroTarget );

USTRUCT()
struct FACTORYGAME_API FSpawnerInfo
{
	GENERATED_BODY()

	FSpawnerInfo() : 
		Spawner( nullptr ),
		WithinSpawnRange( false ),
		DistanceSq( -1.0f )
	{
	}

	UPROPERTY()
	class AFGCreatureSpawner* Spawner;

	UPROPERTY()
	bool WithinSpawnRange;

	UPROPERTY()
	float DistanceSq;

public:
	FORCEINLINE ~FSpawnerInfo() = default;
};

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

	//Begin aactor
	virtual void DisplayDebug( class UCanvas* canvas, const class FDebugDisplayInfo& debugDisplay, float& YL, float& YPos );
	//End aactor

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

	/** Activates spawners one at a time */
	void TickSpawnerActivationList();

	/** Add a spawner to the pending activation list **/
	void AddPendingActiveSpawner( class AFGCreatureSpawner* inSpawner );
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

	/** Gets the default value set in AISystem */
	float GetDefaultActivateSpawnerDistance() { return mActivateSpawnerDistance; }

	/** Find the closest player sq for a creature */
	float FindClosestPlayerSq( class AActor* actor ) const;

	/** Gets the keep alive distance */
	float GetKeepAliveDistance() { return mKeepAliveDistanceToPlayer; }
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

	void UpdatePotentialSpawners( class AFGCreatureSpawner* inSpawner, bool withinSpawnRange, float closeSqDistance );

	void ManagePotentialSpawners();
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
	/** Distance for when we should activate a spawner, this distance is used if the spawner does not specify a custom distance */
	UPROPERTY( EditDefaultsOnly, Category = "AI" )
	float mActivateSpawnerDistance;

	/* Indicates if we also want to disable pawn movement when we disable the AI */
	UPROPERTY( EditDefaultsOnly, Category = "AI" )
	bool mDisablePawnMovement;

	/** Cached list of all aggro targets, not guaranteed to have the same order */
	UPROPERTY( )
	TArray< class TScriptInterface< class IFGAggroTargetInterface > > mAllAggroTargets;

	/** Cached list of all enemies, used for optimizing enemies depending on distance */
	UPROPERTY()
	TArray< class AFGCreature* > mAllCreatures;

	/** Cached list of all players, used for checking distance to all enemies */
	UPROPERTY()
	TArray< class AFGCharacterPlayer* > mAllPlayers;

	/** Cached list of all enemy spawners. Used to spawn enemies based on distance to player */
	UPROPERTY()
	TArray< class AFGCreatureSpawner* > mAllCreatureSpawners;

	/** Actors that have been given pardon from being targeted by enemies */
	UPROPERTY()
	TArray< AActor* > mPardonedActors;

	/** Cached list of creature spawners that are trying to activate*/
	UPROPERTY()
	TArray< class AFGCreatureSpawner* > mPendingActiveSpawners;
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

	/** Spawners that want to spawn */
	UPROPERTY()
	TArray< FSpawnerInfo > mPotentialSpawnersInfo;

	/** Total weight of spawners that can be active, by default one creature will add 1.0f to a spawners weight */
	UPROPERTY( EditDefaultsOnly, Category = "AI" )
	float mMaxSpawnWeight;

	/** Minimum distance to a spawner for it to be able to spawn. */
	UPROPERTY( EditDefaultsOnly, Category = "AI" )
	float mMinSpawnDistance;

	/** If a creature is withing this distance to an active player then it should not despawn */
	UPROPERTY( EditDefaultsOnly, Category = "AI" )
	float mKeepAliveDistanceToPlayer;

	/** Handle to the last async trace performed */
	FTraceHandle mLastAsyncTraceHandle;

public:
	FORCEINLINE ~UFGAISystem() = default;
};
