// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGFoliageRemovalSubsystem.h"
#include "FGUseableInterface.h"
#include "GameFramework/Actor.h"
#include "FGFoliagePickup.generated.h"

// <FL> [PuschkeN] UI state for toggling auto pickup on/off
UENUM(BlueprintType)
enum class EAutoPickupToggleUIState : uint8
{
	Idle,
	TogglingOnPossible,		// "hold [button] to toggle on" UI is shown
	TogglingOn,				// player is holding the button to toggle on, progress bar is shown
	TogglingOffPossible,	// "hold [button] to toggle off" UI is shown
	TogglingOff,			// player is holding the button to toggle off, progress bar is shown
};
// </FL>
// 
// <FL> [PuschkeN] Delegate for blueprint events for toggling auto pickup on/off
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FAutoPickupToggleDelegate, bool, AutoPickupActive );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FAutoPickupToggleUIStateDelegate, EAutoPickupToggleUIState, UIState );
// </FL>

UCLASS(abstract,notplaceable,transient)
class FACTORYGAME_API AFGFoliagePickup : public AActor, public IFGUseableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFGFoliagePickup();

	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;
	// End AActor interface

	//~ Begin IFGUseableInterface
	virtual void UpdateUseState_Implementation( class AFGCharacterPlayer* byCharacter, const FVector& atLocation, class UPrimitiveComponent* componentHit, FUseState& out_useState ) override;
	virtual void OnUse_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override {}
	virtual void OnUseStop_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override {}
	virtual bool IsUseable_Implementation() const override;
	virtual void StartIsLookedAt_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state  ) override;
	virtual FText GetLookAtDecription_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) const override;
	virtual void StopIsLookedAt_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual void RegisterInteractingPlayer_Implementation( class AFGCharacterPlayer* player ) override {}
	virtual void UnregisterInteractingPlayer_Implementation( class AFGCharacterPlayer* player ) override {}
	//~ End IFGUseableInterface

	UFUNCTION( NetMulticast, Unreliable )
	void BroadcastPickup( class UStaticMesh* fromStaticMesh, FVector atLocation );

	UFUNCTION( BlueprintCosmetic, BlueprintImplementableEvent, Category = "Foliage" )
	void PlayPickupEffect( class UFGFoliageResourceUserData* foliageUserData, FVector atLocation );

	/** Set the mesh and it's translation */
	void SetPickupData( class UHierarchicalInstancedStaticMeshComponent* component, int32 instanceId, AFGCharacterPlayer* byCharacter );

	/** gets the pickup component, duhh */
	FORCEINLINE TWeakObjectPtr< class UHierarchicalInstancedStaticMeshComponent > GetPickupComponent() const { return mPickupComponent; }

	/** gets the pickup component's instance, duhh */
	FORCEINLINE int32 GetPickupInstance() const { return mInstanceId; }

	/** Returns the character owning this pick up */
	UFUNCTION( BlueprintPure, Category = "Foliage" )
	class AFGCharacterPlayer* GetOwnerCharacter() const;

	/** Returns true if we are currently capable of picking up foliage */
	UFUNCTION( BlueprintPure, Category = "Foliage" )
	bool CanPickUpFoliageCurrently() const;

	// <FL> PuschkeN Toggling auto pickup on/off

	/** Broadcast when auto pickup is toggled on/off */
	UPROPERTY( BlueprintAssignable )
	FAutoPickupToggleDelegate mOnAutoPickupToggled;

	/** Broadcast when the state of the auto pickup toggle UI changes */
	UPROPERTY( BlueprintAssignable )
	FAutoPickupToggleUIStateDelegate mOnAutoPickupToggleUIStateChanged;

	// </FL>

private:
	void DoPickup();

	void Input_Use( const struct FInputActionValue& actionValue );
	// <FL> PuschkeN Toggling foliage auto pickup on/off
	void Input_ToggleAutoPickup_Started();
	void Input_ToggleAutoPickup_Triggered();
	void Input_ToggleAutoPickup_Canceled();
	void ToggleAutoPickUp();
	void OnAutoPickUpToggleDelayCompleted();
	// </FL>

protected:
	/** Sends to the server that something should be removed up at a specific location */
	UFUNCTION(Server, Reliable)
	void Server_PickUpFoliage( class AFGCharacterPlayer* byCharacter, FFoliageInstanceStableId StableId, const FVector& instanceLocation );

	/** Add the item to the player inventory */
	bool AddToPlayerInventory( class AFGCharacterPlayer* character, class UHierarchicalInstancedStaticMeshComponent* meshComponent, uint32 seed );

	/** Returns true if the player has space for the items in the component */
	bool HasPlayerSpaceFor( class AFGCharacterPlayer* character, class UHierarchicalInstancedStaticMeshComponent* meshComponent, uint32 seed );

	/**
	 * The minimum number of seconds between each pickup when the pickup key is held down 
	 */
	UPROPERTY( EditDefaultsOnly )
	float mPickupRepeatInterval = 0.5f;

	/**
	 * The number of seconds until the 'hold to toggle auto pickup' widget appears.
	 */
	UPROPERTY( EditDefaultsOnly )
	float mAutoPickUpToggleDelay = 0.5f;

protected:
	/** The mesh that should be outlining */
	UPROPERTY()
	class UStaticMesh* mPickupMesh;

	/** ID of instance we want to pickup */
	int32 mInstanceId;

	/** The component we want to pickup from */
	TWeakObjectPtr< class UHierarchicalInstancedStaticMeshComponent > mPickupComponent;
	
	bool mIsPickupActive = false;
	float mEarliestNextPickupTime = 0.0;

	// <FL> ZimmermannA, PuschkeN foliage auto pickup
	EAutoPickupToggleUIState mAutoPickupToggleUIState = EAutoPickupToggleUIState::Idle;
	bool mCurrentAutoPickupToggleInputPossible = false;
	bool mIsAutoPickupActive = false;
	FTimerHandle mAutoPickupToggleDelayTimerHandle;
	// </FL>
};
