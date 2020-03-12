// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "SubclassOf.h"
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "FGBuildGun.h"
#include "../FGInventoryComponent.h"
#include "FGBuildGunDismantle.generated.h"

static const int MAX_DISMANTLE_LIMIT = 50;

USTRUCT()
struct FACTORYGAME_API FDismantleRefunds
{
	GENERATED_BODY()

	/** Ctor */
	FDismantleRefunds()
	{
		NumPendingActors = 0;
	}

	UPROPERTY()
	uint32 NumPendingActors;

	UPROPERTY()
	TArray<FInventoryStack> PeekDismantleRefund;

public:
	FORCEINLINE ~FDismantleRefunds() = default;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnDismantleRefundsChanged, class UFGBuildGunStateDismantle*, dismantleGun );
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnPendingDismantleActorListChanged );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnMultiDismantleStateChanged, bool, newState );


/**
 * Build guns dismantle state.
 */
UCLASS()
class FACTORYGAME_API UFGBuildGunStateDismantle : public UFGBuildGunState
{
	GENERATED_BODY()

public:
	UFGBuildGunStateDismantle();

	virtual void GetLifetimeReplicatedProps( TArray< class FLifetimeProperty > & OutLifetimeProps ) const override;

	// Begin UFGBuildGunState
	virtual void BeginState_Implementation() override;
	virtual void EndState_Implementation() override;
	virtual void TickState_Implementation( float deltaTime ) override;
	virtual void PrimaryFire_Implementation() override;
	virtual void SecondaryFire_Implementation() override;
	virtual void OnRecipeSampled_Implementation( TSubclassOf<class UFGRecipe> recipe ) override;
	// End UFGBuildGunState

	/** Toggle between whether the multi select should be in effect as actors are being highlighted */
	UFUNCTION( BlueprintCallable, Category = "BuildGunState|Dismantle" )
	void SetMultiDismantleState( bool isActive ) { mIsMultiSelectActive = isActive; Internal_OnMultiDismantleStateChanged( isActive ); }

	/** Gets the selected actor; null if none selected. */
	UFUNCTION( BlueprintPure, Category = "BuildGunState|Dismantle" )
	class AActor* GetSelectedActor() const;

	/** Returns the number of actors that are pending for dismantle */
	UFUNCTION( BlueprintPure, Category = "BuildGunState|Dismantle" )
	FORCEINLINE int32 GetNumPendingDismantleActors( bool includeAimedAtActor ) const { return mCurrentlySelectedActor != nullptr && includeAimedAtActor ? mPendingDismantleActors.Num() + 1 : mPendingDismantleActors.Num(); }

	/** Returns the maximum number of actors that can be selected for mass-dismantle */
	UFUNCTION( BlueprintPure, Category = "BuildGunState|Dismantle" )
	FORCEINLINE int32 GetMaxNumPendingDismantleActors() const { return MAX_DISMANTLE_LIMIT; }
	
	/** Returns true whether the limit for maximum number of actors pending dismantle has been reached */
	UFUNCTION( BlueprintPure, Category = "BuildGunState|Dismantle" )
	FORCEINLINE bool HasReachedMaxNumPendingDismantleActors() const { return GetNumPendingDismantleActors( false ) >= MAX_DISMANTLE_LIMIT; }

	UFUNCTION( BlueprintPure, Category = "BuildGunState|Dismantle" )
	TArray<FInventoryStack> GetPeekDismantleRefund() const;

	/** Can the selected actor be dismantled (Only call this on the server). */
	UFUNCTION( BlueprintPure, Category = "BuildGunState|Dismantle" )
	bool CanDismantle() const;

	/** What do we get by dismantling the actor (Only call this on the server). */
	UFUNCTION( BlueprintCallable, Category = "BuildGunState|Dismantle" )
	TArray< FInventoryStack > GetDismantleRefund() const;

	/** returns true if build gun delay is ok to start */
	virtual bool CanBeginBuildGunDelay() const override;

	/** Overriden for feedback purposes */	
	virtual void BeginBuildGunDelay() override;

	/** Overriden for feedback purposes */
	virtual void ResetBuildGunDelay() override;

	/** Give blueprint a chance to do effect when stopping dismantle */
	UFUNCTION( BlueprintImplementableEvent,Category = "BuildGunState" )
	void OnStopDismantle();

	/** Give blueprint a chance to do effect when starting dismantle */
	UFUNCTION( BlueprintImplementableEvent, Category = "BuildGunState" )
	void OnStartDismantle();
public:
	/** Delegate for when the refunds used to preview dismantle refunds have been updated on local machine */
	UPROPERTY( BlueprintAssignable, Category = "BuildGunState|Dismantle" )
	FOnDismantleRefundsChanged OnPeekRefundsChanged;

	UPROPERTY( BlueprintAssignable, Category = "BuildGunState|Dismantle" )
	FOnPendingDismantleActorListChanged OnPendingDismantleActorsChanged;

	UPROPERTY( BlueprintAssignable, Category = "BuildGunState|Dismantle" )
	FOnMultiDismantleStateChanged OnMultiDismantleStateChanged;

protected:
	void Internal_OnMultiDismantleStateChanged(bool newValue);

private:
	/** Client selects actor, then tells the server what to dismantle. This function does that! */
	UFUNCTION( Server, Reliable, WithValidation )
	void Server_DismantleActors( const TArray<class AActor*>& selectedActors );

	UFUNCTION( Server, Reliable, WithValidation )
	void Server_PeekAtDismantleRefund( const TArray<class AActor*>& selectedActors );

	UFUNCTION()
	virtual void OnRep_PeekDismantleRefund();

	/** Dismantle a given actor. Refunds that couldn't fit in inventory from dismantled actor will be appended to out_overflowRefunds. Will place overflow refunds on ground if dropRefundsOnDismantle is true. **/
	void Internal_DismantleActor( class AActor* actorToDismantle );

	/** Set the selected actor (Simulated on client). Deselects the actor is selected param is nullptr */
	void SetAimedAtActor( class AActor* selected );

	/** Adds dismantlable actors to the list of pending dismantles */
	void AddPendingDismantleActor( class AActor* selected );

	/** Clears the list of pending dismantable actors */
	void ClearPendingSelectedActors();

	/** Checks whether or not the replicated data for inventory peeking matches the state for client */
	bool DoesReplicatedPeekDataMatch() const;

	/** Sends server request to update the current dismantle refunds preview */
	void UpdatePeekDismantleRefunds();

	/** Validates the list of pending dismantle actors and removes any stale pointers */
	void ClearStaleDismantleActors();

private:
	/** State bool for whether multi-select is in effect */
	bool mIsMultiSelectActive;

	/** If true then this state won't broadcast when peek refunds have been updated. Used so that there won't be more than one broadcast per tick. */
	bool mDisablePeekDismantleRefundsBroadcast;

	/** Currently selected dismantable actor */
	UPROPERTY( Transient )
	class AActor* mCurrentlySelectedActor;

	/** The actor to dismantle (simulated locally on client). */
	UPROPERTY(Transient)
	TArray<class AActor*> mPendingDismantleActors;
	
	/** Cached dismantle refunds on server that is replicated */
	UPROPERTY(Transient, ReplicatedUsing = OnRep_PeekDismantleRefund )
	FDismantleRefunds mPeekDismantleRefund;

public:
	FORCEINLINE ~UFGBuildGunStateDismantle() = default;
};
