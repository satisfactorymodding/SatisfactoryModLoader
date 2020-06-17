// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "../../Plugins/Wwise/Source/AkAudio/Classes/AkAudioEvent.h"
#include "Engine/World.h"
#include "Array.h"
#include "GameFramework/Actor.h"
#include "SubclassOf.h"
#include "UObject/Class.h"
#include "FGCharacterBase.h"
#include "AI/FGAggroTargetInterface.h"
#include "FGInventoryComponent.h"
#include "FGUseableInterface.h"
#include "FGRadiationInterface.h"
#include "Equipment/FGEquipment.h"
#include "FGHUD.h"
#include "FGOutlineComponent.h"

#include "FGCharacterPlayer.generated.h"

// Callbacks used by the replication graph to build dependency lists
DECLARE_MULTICAST_DELEGATE_TwoParams( FOnPersistentEquipmentSpawned, class AFGCharacterPlayer*, class IFGReplicationDependencyActorInterface* );
DECLARE_MULTICAST_DELEGATE_TwoParams( FOnEquipmentEquipped, class AFGCharacterPlayer*, class AFGEquipment* );
DECLARE_MULTICAST_DELEGATE_TwoParams( FOnEquipmentUnequipped, class AFGCharacterPlayer*, class AFGEquipment* );
DECLARE_MULTICAST_DELEGATE_TwoParams( FOnFoliagePickupSpawned, class AFGCharacterPlayer*, class AFGFoliagePickup* );

UENUM( BlueprintType )
enum class ECameraMode : uint8
{
	ECM_None,
	ECM_FirstPerson,
	ECM_ThirdPerson,
};

/** structure that holds variables per input whether it's allowed or not. NOTE: True if input is disabled. */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FDisabledInputGate
{
	GENERATED_USTRUCT_BODY()

public:
	FDisabledInputGate();

	FORCEINLINE FDisabledInputGate( bool disabled ) :
		mBuildGun( disabled ),
		mDismantle( disabled ),
		mFlashLight( disabled ),
		mResourceScanner( disabled ),
		mOpenCodex( disabled ),
		mInventory( disabled ),
		mToggleMap( disabled ),
		mHotbar( disabled ),
		mJump( disabled ),
		mChat( disabled ),
		mUse( disabled ),
		mVehicleRecording( disabled )
	{}

	UPROPERTY( EditAnywhere, BlueprintReadWrite, category = "Input" )
	uint8 mBuildGun : 1;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, category = "Input" )
	uint8 mDismantle : 1;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, category = "Input" )
	uint8 mFlashLight : 1;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, category = "Input" )
	uint8 mResourceScanner : 1;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, category = "Input" )
	uint8 mOpenCodex : 1;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, category = "Input" )
	uint8 mInventory : 1;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, category = "Input" )
	uint8 mToggleMap : 1;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, category = "Input" )
	uint8 mHotbar : 1;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, category = "Input" )
	uint8 mJump : 1;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, category = "Input" )
	uint8 mChat : 1;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, category = "Input" )
	uint8 mUse : 1;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, category = "Input" )
	uint8 mVehicleRecording : 1;

public:
	FORCEINLINE ~FDisabledInputGate() = default;
};
FORCEINLINE FDisabledInputGate::FDisabledInputGate() : FDisabledInputGate( false ) {}

/**
* not dead, cant revive
*/
UCLASS()
class FACTORYGAME_API UFGUseState_ReviveInvalid_PlayerNotDead : public UFGUseState
{
	GENERATED_BODY()
public:
	UFGUseState_ReviveInvalid_PlayerNotDead();

public:
	FORCEINLINE ~UFGUseState_ReviveInvalid_PlayerNotDead() = default;
};
FORCEINLINE UFGUseState_ReviveInvalid_PlayerNotDead::UFGUseState_ReviveInvalid_PlayerNotDead() { mIsUsableState = false; }

/**
* Revive valid
*/
UCLASS()
class FACTORYGAME_API UFGUseState_ReviveValid : public UFGUseState
{
	GENERATED_BODY()
public:
	UFGUseState_ReviveValid();

public:
	FORCEINLINE ~UFGUseState_ReviveValid() = default;
};
FORCEINLINE UFGUseState_ReviveValid::UFGUseState_ReviveValid() { mIsUsableState = true; }

/**
 * Base class for all player characters in the game.
 */
UCLASS( config = Game )
class FACTORYGAME_API AFGCharacterPlayer : public AFGCharacterBase, public IFGAggroTargetInterface, public IFGUseableInterface, public IFGRadiationInterface
{
	GENERATED_BODY()
public:
	AFGCharacterPlayer( const FObjectInitializer& ObjectInitializer );

	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	// Begin AActor Interface
	virtual void PostActorCreated() override;
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type endPlayReason ) override;
	virtual void Tick( float deltaTime ) override;


	virtual void Destroyed() override;
	// End AActor Interface

	// Begin Pawn Interface
	virtual bool IsLocallyControlled() const override;
	virtual void PossessedBy( AController* newController ) override;
	virtual void UnPossessed() override;
	virtual void OnRep_Controller() override;
	virtual void AddControllerPitchInput( float Val ) override;
	virtual void Jump() override;
	virtual void OnJumped_Implementation()override;

	virtual bool CanJumpInternal_Implementation() const;
	// End Pawn Interface

	// Begin ACharacter Interface
	virtual void OnEndCrouch( float HalfHeightAdjust, float ScaledHalfHeightAdjust );
	// End ACharacter Interface

	// Begin AFGCharacterBase interface
	virtual void Died( AActor* died ) override;
	virtual const FFootstepEffect& GetFootstepEffect( const FHitResult& hitResult ) const override;
	virtual void OnTakeDamage( AActor* damagedActor, float damageAmount, const class UDamageType* damageType, class AController* instigatedBy, AActor* damageCauser ) override;
	// End AFGCharacterBase interface

	// Begin ACharacter interface
	virtual void OnMovementModeChanged( EMovementMode PrevMovementMode, uint8 PreviousCustomMode = 0 ) override;
	// End ACharacter interface

	// Begin IFGUseableInterface
	virtual void UpdateUseState_Implementation( class AFGCharacterPlayer* byCharacter, const FVector& atLocation, class UPrimitiveComponent* componentHit, FUseState& out_useState ) const override;
	virtual void OnUse_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual void OnUseStop_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual bool IsUseable_Implementation() const override;
	virtual void StartIsLookedAt_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual FText GetLookAtDecription_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) const override;
	virtual void StopIsLookedAt_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual void RegisterInteractingPlayer_Implementation( class AFGCharacterPlayer* player ) override {}
	virtual void UnregisterInteractingPlayer_Implementation( class AFGCharacterPlayer* player ) override {}
	// End IFGUseableInterface

	// Begin IFGRadiationInterface
	virtual void ReceiveRadiation_Implementation( float amount, float duration, FVector direction, TSubclassOf< class UFGDamageType > damageType );
	// End IFGRadiationInterface

	// Begin IFGAggroTargetInterface
	virtual void RegisterIncomingAttacker_Implementation( class AFGEnemyController* forController ) override;
	virtual void UnregisterAttacker_Implementation( class AFGEnemyController* forController ) override;
	virtual AActor* GetActor_Implementation() override;
	virtual float GetEnemyTargetDesirability_Implementation( class AFGEnemyController* forController ) override;
	virtual bool ShouldAutoregisterAsTargetable_Implementation() const override;
	virtual class UPrimitiveComponent* GetTargetComponent_Implementation() override;
	virtual bool IsAlive_Implementation() const override;
	virtual FVector GetAttackLocation_Implementation() const override;
	// End IFGAggroTargetInterface

	//~Begin IFGSaveInterface
	virtual bool ShouldSave_Implementation() const override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	//~End IFGSaveInterface

	/** Blueprint function that ticks visual things not needed on dedicated server */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCosmetic, Category = "Character" )
	void TickVisuals( float dt );

	/** Must be called on the owning client for the client to be able to switch the weapon */
	UFUNCTION( BlueprintCallable, Category = "Equipment" )
	void EquipEquipment( AFGEquipment* equipment );

	/** Must be called on the owning client to unequip one equipment */
	UFUNCTION( BlueprintCallable, Category = "Equipment" )
	void UnequipEquipment( AFGEquipment* equipment );

	/**
	 * Set/clear override the active equipment in a slot.
	 * This must be called on both server and client (simulated)
	 * @param The equipment, cannot be null and must have a valid slot set.
	 */
	void SetOverrideEquipment( AFGEquipment* equipment );
	void ClearOverrideEquipment( AFGEquipment* equipment );

	/** @return - The equipments you have equipped */
	UFUNCTION( BlueprintPure, Category = "Equipment" )
	TArray< AFGEquipment* > GetActiveEquipments() const;

	/** @return - The attachments you have equipped */
	UFUNCTION( BlueprintPure, Category = "Equipment" )
	TArray< class AFGEquipmentAttachment* > GetActiveAttachments() const;

	/** @return - The current desired state for the cross hair polled by the HUD. */
	UFUNCTION( BlueprintNativeEvent, Category = "HUD" )
	ECrosshairState GetActiveCrosshairState();

	/** @return The inventory component for the given equipment slot. */
	UFUNCTION( BlueprintPure, Category = "Equipment" )
	class UFGInventoryComponentEquipment* GetEquipmentSlot( EEquipmentSlot slot ) const;

	/** @return The active equipment in the given equipment slot; nullptr if nothing is equipped. */
	UFUNCTION( BlueprintPure, Category = "Equipment" )
	class AFGEquipment* GetEquipmentInSlot( EEquipmentSlot slot ) const;

	/** @return The item given equipment slot; nullptr if nothing is equipped. */
	UFUNCTION( BlueprintPure, Category = "Equipment" )
	FInventoryItem GetActiveEquipmentItem( EEquipmentSlot slot ) const;

	/** Get Buildgun */
	UFUNCTION( BlueprintPure, Category = "BuildGun" )
	FORCEINLINE AFGBuildGun* GetBuildGun() const{ return mBuildGun; }

	/** Can equip the build gun */
	bool CanEquipBuildGun() const;

	/** Can equip the build gun specifically to dismantle */
	bool CanEquipBuildGunForDismantle() const;

	/** Is the build gun equipped */
	UFUNCTION( BlueprintPure, Category = "Equipment" )
	bool IsBuildGunEquipped() const;

	/** Equips/unequips buildgun */ 
	UFUNCTION( BlueprintCallable, Category = "Equipment" )
	void ToggleBuildGun();

	/** Instantly goes to build mode for selected recipe */
	UFUNCTION( BlueprintCallable, Category = "Equipment" )
	void HotKeyRecipe( TSubclassOf< class UFGRecipe > recipe );

	/** Instantly goes to dismantle mode */
	UFUNCTION( BlueprintCallable, Category = "Equipment" )
	void HotKeyDismantle();

	/** Returns Mesh1P subobject **/
	UFUNCTION( BlueprintPure, Category = "Mesh" )
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return GetMesh(); }

	/** Returns Mesh3P subobject */
	virtual USkeletalMeshComponent* GetMesh3P() const override;

	/** Returns 1p or 3p mesh */
	virtual USkeletalMeshComponent* GetMainMesh() const override;

	/** Switches between camera modes */
	UFUNCTION()
	void ToggleCameraMode();

	/** Start focus aiming */
	UFUNCTION( BlueprintNativeEvent, Category = "Camera" )
	void StartFocusAim();

	/** Stop focus aiming */
	UFUNCTION( BlueprintNativeEvent, Category = "Camera" )
	void StopFocusAim();

	/** Starts the free rotate mode */
	UFUNCTION( BlueprintNativeEvent, Category = "Camera" )
	void StartFreeRotate3P();

	/** Stops the free rotate mode */
	UFUNCTION( BlueprintNativeEvent, Category = "Camera" )
	void StopFreeRotate3P();

	/** Starts the free rotate mode */
	UFUNCTION( BlueprintNativeEvent, Category = "Camera" )
	void CameraZoomIn();

	/** Stops the free rotate mode */
	UFUNCTION( BlueprintNativeEvent, Category = "Camera" )
	void CameraZoomOut();

	/** Do stuff needed for first person mode */
	UFUNCTION( BlueprintNativeEvent, Category = "Camera" )
	void SetFirstPersonMode();

	/** Do stuff needed for third person mode */
	UFUNCTION( BlueprintNativeEvent, Category = "Camera" )
	void SetThirdPersonMode();

	/** Get current camera mode */
	UFUNCTION( BlueprintPure, Category = "Camera" )
	FORCEINLINE ECameraMode GetCameraMode() const { return mCurrentCameraMode; }

	/** Set camera mode */
	UFUNCTION( BlueprintCallable, Category = "Camera" )
	void SetCameraMode( ECameraMode newCameraMode );

	/** Set the camera mode to the one specified in mPlayerPreferredCameraMode */
	UFUNCTION( BlueprintCallable, Category = "Camera" )
	void UsePreferredCameraMode();

	/** Are we in first person mode? */
	UFUNCTION( BlueprintPure, Category = "Camera" )
	bool IsFirstPerson() const;

	/** Start and stop sprinting, called when player presses/releases Left Shift, as standard. */
	void SprintPressed();
	void SprintReleased();

	/** Start and stop crouch, called when player presses/releases Left Ctrl, as standard. */
	UFUNCTION( BlueprintCallable, Category = "Crouch" )
	void CrouchPressed();
	UFUNCTION( BlueprintCallable, Category = "Crouch" )
	void CrouchReleased();

	/** Updates the camera with crouch settings */
	void TickCameraOffset( float dt );

	/** Cycles hand equipments in equipment slots */
	void CycleHandEquipmentPressedUp();

	/** Cycles hand equipments in equipment slots */
	void CycleHandEquipmentPressedDown();

	/** Cycles hand equipments in equipment slots */
	UFUNCTION( Reliable, Server, WithValidation )
	void Server_CycleHandEquipmentPressed( int32 dir );

	/** Actually cycle the equipment */
	void DoCycleEquipment( int32 dir );

	UFUNCTION(BlueprintPure, Category = "Outline")
	FORCEINLINE UFGOutlineComponent* GetOutline() const { return mOutlineComponent; }

	/** The vehicle we are currently driving */
	UFUNCTION( BlueprintPure, Category = "Vehicle" )
	FORCEINLINE bool IsDrivingVehicle() const { return mDrivenVehicle != nullptr; }

	/** The vehicle we are currently driving */
	UFUNCTION( BlueprintPure, Category = "Vehicle" )
	FORCEINLINE class AFGDriveablePawn* GetDrivenVehicle() const { return mDrivenVehicle; }

	/**
	 * Start and StopDriving is called on server and then client when mDrivenVehicle is replicated.
	 * Use these to prepare the pawn for driving, e.g. unequip/re-equip equipments, setting physics state.
	 */
	void StartDriving( class AFGDriveablePawn* vehicle );
	void StopDriving( class AFGDriveablePawn* vehicle );

	/** See if we have spawned our initial gear, if not, spawn it here */
	void TrySpawnInitialGear();

	UFUNCTION( BlueprintNativeEvent, Category = "Inventory" )
	void SpawnInitialGear();

	/** Picked up an item */
	void OnPickUpItem();

	/** 
	* Picks up an item. Is currently being called from item's OnUse(), and was needed in order to 
	* route it through a client owned actor for the pickup action to become reliable. 
	*/
	void PickUpItem( class AFGItemPickup* itemPickup );

	//** The target of a pickup, this is only set if the pickup has a collection time */
	void SetPickupToCollect( class AFGItemPickup* itemPickup );

	FORCEINLINE class AFGFoliagePickup* GetFoliagePickupProxy() { return mFoliagePickupProxy; }

	/** @return This players inventory. */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	FORCEINLINE class UFGInventoryComponent* GetInventory() const { return mInventory; }

	/** @return This players trash inventory. */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	FORCEINLINE class UFGInventoryComponent* GetTrashSlot() const { return mTrashSlot; }

	/** @return This players belt inventory. */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	FORCEINLINE class UFGInventoryComponentBeltSlot* GetBeltSlot() const { return mBeltSlot; }

	/** @return This players resource scanner. */
	UFUNCTION( BlueprintPure, Category = "Equipment" )
	FORCEINLINE AFGResourceScanner* GetResourceScanner() const { return mResourceScanner; }

	/** @return This players resource miner. */
	UFUNCTION( BlueprintPure, Category = "Equipment" )
	FORCEINLINE class AFGResourceMiner* GetResourceMiner() const { return mResourceMiner; }

	UFUNCTION( BlueprintPure, Category = "FactoryGame|Character" )
	FORCEINLINE class USkeletalMeshComponent* Get3PMesh() const{ return mMesh3P; }

	/** @todo This should move to the replicator object... Toggles the switch on the server. */
	UFUNCTION( Reliable, Server, WithValidation )
	void Server_ToggleSwitchControl( class AFGBuildableRailroadSwitchControl* switchControl );

	/** Ticks drown damage. Tests drown interval and applies drown damage when appropriate */
	void TickDrownDamage( float delta );

	/** Ticks healt regen */
	void TickHealthGeneration( float delta );

	/** returns the foliage pickup proxy, duh */
	class AFGFoliagePickup* GetFoliagePickupData() { return mFoliagePickupProxy; }

	/** returns currently cached use state, duh */
	FUseState* GetCachedUseState() { return &mCachedUseState; }

	/** returns ladder we are currently on */
	UFUNCTION( BlueprintCallable, Category = "Movement" )
	class UFGLadderComponent* GetCurrentLadderComponent();

	/** Gets the camera bobbing animation we want to use when sprinting ( can vary with equipment ) */
	UFUNCTION( BlueprintCallable, Category = "Movement" )
	TSubclassOf< class UCameraShake > GetDesiredSprintHeadBobShake();

	/** Gets the camera bobbing animation we want to use when walking ( can vary with equipment ) */
	UFUNCTION( BlueprintCallable, Category = "Movement" )
	TSubclassOf< class UCameraShake > GetDesiredWalkHeadBobShake();

	/**Gets a precasted movement component. We should be able to optimzie this by ensuring that this component is the right type when assigning it and then do a free cast here ans have it faster. So making this way of fetching it now. Even though it's not really faster atm, it can be optimized later.*/
	class UFGCharacterMovementComponent* GetFGMovementComponent();

	/** Setter for mWantsSprintBobbing */
	UFUNCTION( BlueprintCallable, Category = "Movement" ) 
	void SetWantSprintBobbing( bool wantBobbing );

	/** Getter for mWantsSprintBobbing */
	UFUNCTION( BlueprintPure, Category = "Movement" ) 
	FORCEINLINE bool GetWantSprintBobbing() { return mWantsSprintBobbing; }

	/** Getter for the world location of the Camera component */
	FORCEINLINE FVector GetCameraComponentWorldLocation() { return mCameraComponent->GetComponentToWorld().GetLocation(); }

	/** Where to drop a inventory item if we drop one */
	UFUNCTION( BlueprintNativeEvent, Category = "Inventory" )
	FVector GetInventoryDropLocation( const class UFGInventoryComponent* component, FInventoryStack stack );

	/** Name of the inventory component for the arms */
	static const FName ArmsInvComponentName;

	/** Name of the inventory component for the back */
	static const FName BackInvComponentName;

	/** Adds or removes an amount of radiation */
	UFUNCTION( BlueprintCallable, Category = "Radiation" )
	void AddRadiationImmunity( float toAdd );

	/** Sets an amount of radiation */
	UFUNCTION( BlueprintCallable, Category = "Radiation" )
	void SetRadiationImmunity( float newImmunity );


	//Cheats
	virtual void ClientCheatFly_Implementation() override;
	virtual void CheatJump();
	virtual void StopCheatJump();
	virtual void CheatCrouch();
	virtual void StopCheatCrouch();
	virtual void CheatToggleGhostFly();
	virtual void CheatToggleGhostFly( bool ghostModeActive );
	virtual bool CheatToggleGhostFlyIsActive();
	virtual bool CheatToggleFlyModeIsActive();
	virtual void CheatToggleFlyMode();
	virtual void CheatTeleport();
	//End cheats

	/** Called when a slide has started*/
	void OnSlideStart();

	/** Called when a slide has started, local only */
	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|Movment" )
	void OnSlideStartLocal();

	/** Called when a slide has ended*/
	void OnSlideEnd();

	/** Called when a slide has ended, local only*/
	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|Movment" )
	void OnSlideEndLocal();

	/** Called when a slide has ended, simulated proxies only */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCosmetic, Category = "FactoryGame|Movment" )
	void OnSlideEndSimulated();

	/** Called when a slide has started, simulated proxies only */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCosmetic, Category = "FactoryGame|Movment" )
	void OnSlideStartSimulated();

	UFUNCTION( Unreliable, NetMulticast )
	void Multicast_PlayJumpEffects( bool boostJump );

	/** Called when a slide has started, simulated proxies only */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCosmetic, Category = "FactoryGame|Movment" )
	void PlayJumpEffects( bool boostJump );


	UFUNCTION( NetMulticast, Reliable, WithValidation, Category = "Hyper Tubes" )
	void Client_HyperTubeStart( AActor* tubeStart, float startTime, float pipeVelocity, float pipeProgress );
	UFUNCTION( NetMulticast, Reliable, WithValidation, Category = "Hyper Tubes" )
	void Client_HyperTubeEnd( FVector point, FVector velocity, float startTime );

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent( class UInputComponent* InputComponent ) override;
	// End of APawn interface

	/** Called when we unlock more inventory slots */
	UFUNCTION()
	void OnInventorySlotsUnlocked( int32 newUnlockedSlots );

	/** Called when we unlock more arms slots */
	UFUNCTION()
	void OnArmsSlotsUnlocked( int32 newUnlockedSlots );

	void CheckAndAddPositionToSafeList( UWorld * world, FVector currentPos );

	// Begin AFGCharacterBase interface
	virtual float AdjustDamage( AActor* damagedActor, float damageAmount, const class UDamageType* damageType, class AController* instigatedBy, AActor* damageCauser ) override;
	virtual void DoRagdoll_Internal() override;
	// End AFGCharacterBase interface

	/** Sets what mesh is visible on us ( 1p or 3p ) */
	UFUNCTION( BlueprintCallable, Category = "Camera" )
	void SetMeshVisibility( bool isFirstPerson );

	/** Blueprint accessor for when an item was picked up, called on client/server/remote */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, BlueprintCosmetic, Category = "Character" )
	void PlayPickupEffects();

	/** For playing 1P events */
	virtual class UAkAudioEvent* GetFootstepEvent( int32 footDown ) const override;

	UFUNCTION( BlueprintNativeEvent, Category = "Input" )
	void OnDisabledInputGateChanged(FDisabledInputGate newValue);

	/** SERVER ONLY: Drops the contents of the player on the ground */
	void SpawnDeathCrate();

	/** Setup the players inventories, including equipment slots. */
	void SetupInventory();

	UFUNCTION()
	void OnItemAddedToInventory( TSubclassOf<UFGItemDescriptor> itemClass, int32 numAdded );

	/** Hand out the starting resources. */
	void AddDefaultInventoryItems();

	/** Equip the existing equipment, useful when exiting a car, loading games a similar */
	void ReEquipExistingEquipment();

	/** Equip the existing equipment, useful when exiting a car, loading games a similar */
	void UnEquipAllEquipment();

	/** Update which actor we can interact with at our location. */
	void UpdateBestUsableActor();

	/** Called when the use input action is triggered. */
	void OnUsePressed();

	/** Called when we release the use button */
	void OnUseReleased();

	/** Called on both server and client when we want to use something. */
	void OnUse();

	/** Called on both server and client when we want to use something. */
	void OnUseStop();

	/** Checks if what we hit can be picked up */
	bool CanBePickedUp( const FHitResult& hitResult );

	/** Handles moving forward/backward */
	void MoveForward( float Val );

	/** Handles strafing movement, left and right */
	void MoveRight( float Val );

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate( float Rate );

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate( float Rate );

	/** Returns Camera subobject **/
	UFUNCTION( BlueprintPure, Category = "Camera" )
	FORCEINLINE class UCameraComponent* GetCameraComponent() const { return mCameraComponent; }

	/** Returns spring arm subobject **/
	UFUNCTION( BlueprintPure, Category = "Camera" )
	FORCEINLINE class USpringArmComponent* GetSpringArmComponent() const { return mSpringArmComponent; }

	/** Set the best usable actor */
	void SetBestUsableActor( class AActor* newBestUsableActor );

	/** Returns distance we want to be able to use stuff from */
	UFUNCTION( BlueprintPure, Category = "Use" )
	float GetUseDistance();

	/** snaps the camera spring arm to its desired location, so no interp */
	UFUNCTION( BlueprintImplementableEvent, Category = "Camera" )
	void SnapSpringArmToDesiredLocation();

	/** Callback for the revive timer */
	void OnReviveTimerComplete();

	/** returns the progress of reviving a player 0..1 */
	UFUNCTION( BlueprintPure, Category="Revive" )
	float GetReviveProgress();

	/** called when a revive process is complete. Called on the player being revived. */
	UFUNCTION( BlueprintImplementableEvent, Category = "Revive" )
	void OnReviveComplete();

	/** Takes care of client side stuff when revived (eg. Enabling player input) */
	UFUNCTION( Client, Reliable, WithValidation, Category = "Revive" )
	void Client_Revived();

	/** returns the progress of reviving a player 0..1 */
	UFUNCTION( BlueprintPure, Category = "Use" )
	float GetPickupProgress();

	/** Called when we start receiving radiation. */
	UFUNCTION( BlueprintImplementableEvent, Category = "Radiation" )
	void OnReceiveRadiationStart();

	/** Called when we have updated radiation intensity. */
	UFUNCTION( BlueprintImplementableEvent, Category = "Radiation" )
	void OnRadiationIntensityUpdated( float radiationIntensity, float radiationImmunity );

	/** Called when we stop receiving radiation. */
	UFUNCTION( BlueprintImplementableEvent, Category = "Radiation" )
	void OnReceiveRadiationStop();

	UFUNCTION()
	void StartReceivingRadiation();

	UFUNCTION()
	void StopReceivingRadiation();

	/** Called when we respawn but didn't get a death crate, so we can find our last death location. */
	UFUNCTION( BlueprintImplementableEvent, Category = "Death" )
	void OnSpawnDeathMarker();

	/** Returns accumulated normalized radiation intensity at the the players location **/
	UFUNCTION( BlueprintPure, Category = "Radiation" )
	FORCEINLINE float GetRadiationIntensity() const { return mRadiationIntensity; }

	/** Returns accumulated radioation immunity **/
	UFUNCTION( BlueprintPure, Category = "Radiation" )
	FORCEINLINE float GetRadiationImmunity() const { return mRadiationImmunity; }

	/** Returns the angle from the players view to the accumulated radiation damage **/
	UFUNCTION( BlueprintPure, Category = "Radiation" )
	FORCEINLINE float GetRadiationDamageAngle() const { return mRadiationDamageAngle; }

	bool IsInRadioActiveZone()
	{
		return mInRadioactiveZone;
	}

	/** Start the pending removal of the character */
	virtual void TornOff() override;

	/** Returns the arm bone location offset we want to use depending on crouch/stand state **/
	UFUNCTION( BlueprintPure, Category = "Movement" )
	FORCEINLINE float GetArmBoneLocation() const { return mArmBoneLocation; }

	void DebugBuildablesInFrustum();



public:
	// Callbacks used by the replication graph to build dependency lists
	/** Event for when equipment that is should always be replicated on the player is spawned */
	static FOnPersistentEquipmentSpawned OnPersistentEquipmentSpawned;
	
	/** Event on when new equipment has been equipped */
	static FOnEquipmentEquipped OnEquipmentEquipped;

	/** Event on when equipment has been unequipped */
	static FOnEquipmentUnequipped OnEquipmentUnequipped;

	/** Event when the foliage pickup proxy has spawned */
	static FOnFoliagePickupSpawned OnFoliagePickupSpawned;

	/** The best usable actor nearby. */
	UFUNCTION( BlueprintPure, Category = "Use" )
	FORCEINLINE	class AActor* GetBestUsableActor() { return mBestUsableActor; }

	/** Update what crosshair to show */
	void UpdateHUDCrosshair();

	/** Gets sliding status */
	UFUNCTION( BlueprintPure, Category = "Use" )
	bool IsSliding() const;

	/** Gets mTryToUnSlide */
	inline bool IsTryingToUnslide(){ return mTryToUnSlide; }
private:
	/**
	 * Spawn a new equipment.
	 * @param equipmentClass Class to spawn.
	 * @param owner Optionally pass an owner, only use this in combination with persistent equipments.
	 */
	AFGEquipment* SpawnEquipment( TSubclassOf< AFGEquipment > equipmentClass, AActor* owner = nullptr );

	template< typename T >
	T* SpawnEquipment( TSubclassOf< AFGEquipment > equipmentClass, AActor* owner = nullptr )
	{
		check( equipmentClass->IsChildOf( T::StaticClass() ) );
		return Cast<T>( SpawnEquipment( equipmentClass, owner ) );
	}

	/* Spawns the attachment for this equipment */
	AFGEquipmentAttachment* SpawnAttachmentForEquipment( AFGEquipment* equipment );
	/* Spawns the secondary attachment for this equipment */
	AFGEquipmentAttachment* SpawnSecondaryAttachmentForEquipment( AFGEquipment* equipment );

	/** Custom ticks */
	void UpdateHeadBob();

	void NotifyGameStatePlayerAdded();

	UFGGameUI* GetGameUI();

	/** Update the UI with status if we are in radioactive zone or not*/
	void UpdateGameUIRadiationStatus();

	/** Update the UI with radiation intensity*/
	void UpdateGameUIRadiationIntensity();

	UFUNCTION( BlueprintPure, Category = "General" )
	int32 GetTotalPlayerInventorySlots() const;

	UFUNCTION( BlueprintPure, Category = "General" )
	int32 GetTotalPlayerArmEquipmentSlots() const;

	/** Server function that are called from public clients of the same name */
	UFUNCTION( Reliable, Server, WithValidation )
	void Server_EquipEquipment( AFGEquipment* newEquipment );
	UFUNCTION( Reliable, Server, WithValidation )
	void Server_UnequipEquipment( AFGEquipment* newEquipment );
	UFUNCTION( Server, Reliable, WithValidation, Category = "Revive" )
	void Server_RevivePlayer( AFGCharacterPlayer* playerToRevive );
	UFUNCTION( Reliable, Server, WithValidation, Category = "Use" )
	void Server_OnUse();
	UFUNCTION( Reliable, Server, WithValidation, Category = "Use" )
	void Server_OnUseReleased();
	UFUNCTION( Reliable, Server, WithValidation )
	void Server_PickUpItem( class AFGItemPickup* itemPickup );


	/** Called when slide status changes so we can change capsule size accordingly */
	void OnSlideStatusUpdated();


	/** OnReps */
	UFUNCTION()
	void OnRep_ActiveEquipments();
	UFUNCTION()
	void OnRep_ActiveAttachments();
	UFUNCTION()
	void OnRep_DrivenVehicle();
	UFUNCTION()
	void OnRep_PickupCounter();
	UFUNCTION()
	void OnRep_InRadioactiveZone();
	UFUNCTION()
	void OnRep_RadiationIntensity();
	UFUNCTION()
	void OnRep_IsSliding();
	
	/** Migrate number of inventory and arm equipment slots saved before BU3 to unlock subsystem */
	void MigrateNumSavedSlots();

	/** Check if we have items picked up that isn't registered as picked up. Fixes issues on old saves before we saved picked up items */
	void CheckItemPickedUp();

public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = Camera )
	float mBaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = Camera )
	float mBaseLookUpRate;

	/** The default arms animation when we're idle. */
	UPROPERTY( EditDefaultsOnly, Category = Mesh )
	TSubclassOf< class UAnimInstance > mMesh1PAnimClass;

protected:
	/** Pawn mesh: 3rd person view */
	UPROPERTY( VisibleDefaultsOnly, Category = Mesh )
	class USkeletalMeshComponent* mMesh3P;

	/** As we have no foliage actor to actually put pickup code in, we use this actor as a proxy */
	UPROPERTY( EditDefaultsOnly, Category = "Use" )
	TSubclassOf< class AFGFoliagePickup > mFoliagePickupProxyClass;

	/** Actor that's used when trying to pickup foliage */
	UPROPERTY( Replicated, BlueprintReadOnly, Category = "Use" )
	class AFGFoliagePickup* mFoliagePickupProxy;

	/* This is the infamous build gun. */
	UPROPERTY( SaveGame, BlueprintReadOnly, Replicated, Category = "Equipment" )
	AFGBuildGun* mBuildGun;

	/*Reference to the resource scanner */
	UPROPERTY( SaveGame, Replicated )
	AFGResourceScanner* mResourceScanner;

	/* Reference to the resource miner */
	UPROPERTY( SaveGame, Replicated )
	class AFGResourceMiner* mResourceMiner;

	/** The best usable actor nearby. */
	UPROPERTY()
	class AActor* mBestUsableActor;

	/** Of the usable actor we are looking at, UPROPERTY to prevent the AdditionalData to be garbage collected */
	UPROPERTY( BlueprintReadOnly )
	FUseState mCachedUseState;

	/** Anim instance class to use in third person */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Character" )
	TSubclassOf< class UAnimInstance > mAnimInstanceClass;

	/** Anim instance class to use in first person */
	UPROPERTY( EditDefaultsOnly, Category = "Character" )
	TSubclassOf< class UAnimInstance > mAnimInstanceClass1P;

	/** time (in seconds) it takes to revive a fellow player */
	UPROPERTY( EditDefaultsOnly, Category = "Revive" )
	float mReviveDuration;

	/** The starting resources for the player */
	UPROPERTY( EditDefaultsOnly, Category = "Inventory" )
	TArray< FItemAmount > mStartingResources;

	/** The starting resources for the player if we are NOT in shipping */
	UPROPERTY( EditDefaultsOnly, Category = "Inventory" )
	TArray< FItemAmount > mStartingResourceForTesting;

	/** @todo: This should not be specified for each pawn */
	UPROPERTY(EditDefaultsOnly, Category = "Swimming")
	TSubclassOf< class UFGDamageType > mDrownDamageDamageType;

	/** The amount of damage to receive when drowning. */
	UPROPERTY( EditDefaultsOnly, Category = "Swimming" )
	float mDrownDamage;

	/** Time between each application of drowning damage (in seconds) */
	UPROPERTY( EditDefaultsOnly, Category = "Swimming" )
	float mDrownDamageInterval;

	/** The player that we are reviving */
	UPROPERTY( BlueprintReadOnly, Category = "Revive" )
	AFGCharacterPlayer* mPlayerToRevive;

	/** The pickup we are collecting */
	UPROPERTY( BlueprintReadOnly, Category = "Use" )
	class AFGItemPickup* mPickupToCollect;

	/** Default effects to play when a foot hits the ground when the material doesn't exist in m1PFootstepEffect */
	UPROPERTY( EditDefaultsOnly, Category = "Footstep" )
	FFootstepEffect m1PDefaultFootstepEffect;

	/** Effects to play when a foot hits the ground in first person */
	UPROPERTY( EditDefaultsOnly, Category = "Footstep" )
	TArray< FFootstepEffectSurface > m1PFootstepEffect;

	/** Effects to play when a foot hits the ground in first person */
	UPROPERTY( EditDefaultsOnly, Category = "Footstep" )
	TArray<class UAkAudioEvent*> m1PFootstepEvent;

	/** latest safe ground location check timer */
	float mLastSafeGroundCheckTimer;

	static const int32 MAX_SAFE_GROUND_POS_BUFFER_SIZE = 3;

	/** latest safe ground location positions */
	UPROPERTY( SaveGame )
	FVector mLastSafeGroundPositions[ MAX_SAFE_GROUND_POS_BUFFER_SIZE ];

	/** used for knowing which is the latest written safe ground position */
	UPROPERTY( SaveGame )
	int32 mLastSafeGroundPositionLoopHead = 0;
private:
	/** Bound to mItemFilter to filter what items can be used in the inventory slots. */
	UFUNCTION()
	bool FilterInventoryClasses( TSubclassOf< UObject > object, int32 idx ) const;

	void InitializePreferredCameraMode();

	/** Character can unslide, no collision is blocking */
	void DoUnSlide();


	UFUNCTION()
	void OnUserSettingsUpdated();
private:
	friend class AFGPlayerController;
	friend class UFGInventoryComponentEquipment;

	/** Player camera */
	UPROPERTY( EditAnywhere )
	class UCameraComponent* mCameraComponent;

	/** Spring arm for camera */
	UPROPERTY( EditAnywhere )
	class USpringArmComponent* mSpringArmComponent;

	/** This is the equipment we hold in our hands.*/
	UPROPERTY( ReplicatedUsing = OnRep_ActiveEquipments )
	TArray< class AFGEquipment* > mActiveEquipments;

	/** Simulated on the client so they know what to unequip. */
	UPROPERTY()
	TArray< class AFGEquipment* > mClientActiveEquipments;

	/** @todo They should be in the inventory later on. But right now this is what you toggle with */
	UPROPERTY( Replicated )
	TArray< class AFGEquipmentAttachment* > mAllAttachments;

	/** Remote client representation of the equipment */
	UPROPERTY( ReplicatedUsing = OnRep_ActiveAttachments )
	TArray< class AFGEquipmentAttachment* > mActiveAttachments;

	/** Current camera mode for the character */
	UPROPERTY()
	ECameraMode mCurrentCameraMode;

	/** What camera mode were we in before we opened the  */
	UPROPERTY( EditDefaultsOnly, Category = "Camera" )
	ECameraMode mPlayerPreferredCameraMode;

	/** The players inventory. */
	UPROPERTY( SaveGame, Replicated )
	class UFGInventoryComponent* mInventory;

	/** The resource forms that are allowed in players inventory. */
	UPROPERTY( EditDefaultsOnly )
	TArray<EResourceForm> mAllowedResourceFormsInInventory;

	/** The belt slot inventory. */
	UPROPERTY( SaveGame, Replicated )
	class UFGInventoryComponentBeltSlot* mBeltSlot;

	/** The players inventory. */
	UPROPERTY( Replicated )
	class UFGInventoryComponent* mTrashSlot;

	/** Allow toggling of camera modes */
	UPROPERTY( EditDefaultsOnly, Category = "Camera" )
	bool mAllowCameraToggling;

	/** Maximum distance we use objects on */
	UPROPERTY( EditDefaultsOnly, Category = "Use" )
	float mUseDistance;

	/** keeps track of current drown damage interval time */
	float mTimeToApplyDrownDamage;

	/** Counter used for replicating to remote clients when something is picked up */
	UPROPERTY( ReplicatedUsing = OnRep_PickupCounter )
	int8 mPickupCounter;

	/** The player that is reviving me */
	UPROPERTY( Replicated )
	AFGCharacterPlayer* mReviver;

	/** Revive timer handle, duh. */
	FTimerHandle mReviveTimerHandle;

	/** Indicates if the player is sprinting and wants to use the sprint bobbing */
	bool mWantsSprintBobbing;

	/** Reference to the current head bob shake we should use */
	TSubclassOf< class UCameraShake > mCurrentHeadBobShake;

	/** Reference to the default walk head bob shake */
	UPROPERTY( EditDefaultsOnly, Category = "Movement" )
	TSubclassOf< class UCameraShake > mDefaultWalkHeadBobShake;

	/** Reference to the default sprint head bob shake */
	UPROPERTY( EditDefaultsOnly, Category = "Movement" )
	TSubclassOf< class UCameraShake > mDefaultSprintHeadBobShake;

	/** Vehicle currently driven by pawn. */
	UPROPERTY( ReplicatedUsing = OnRep_DrivenVehicle )
	class AFGDriveablePawn* mDrivenVehicle;
	/**
	 * Saved vehicle currently driven by pawn.
	 * Used by server to remember which vehicle we drove when saving.
	 * Used by client to remember which vehicle we drove when leaving the vehicle.
	 */
	UPROPERTY( SaveGame )
	class AFGDriveablePawn* mSavedDrivenVehicle;

	UPROPERTY()
	class UFGOutlineComponent* mOutlineComponent;

	// Health Generation
	UPROPERTY( EditDefaultsOnly, Category = "HealthGeneration" )
	float mHealthGenerationThreshold;
	UPROPERTY( EditDefaultsOnly, Category = "HealthGeneration" )
	float mHealthGenerationAmount;
	UPROPERTY( EditDefaultsOnly, Category = "HealthGeneration" )
	float mHealthGenerationInterval;
	UPROPERTY( EditDefaultsOnly, Category = "HealthGeneration" )
	float mHealthGenerationWaitTime;

	float mHealthGenerationTimer;
	float mLastDamageTakenTime;

	/** The minimum damage interval ( 0.2 = every 5 second, 10.0 = 10 times per second ) */
	float mRadiationMinDamageInterval;

	/** The maximum damage interval ( 0.2 = every 5 second, 10.0 = 10 times per second ) */
	float mRadiationMaxDamageInterval;

	/** How much damage we should apply during each damage event. Once per interval */
	float mRadiationDamagePerInterval;

	/** Counter to know when we should take damage from radiation" */
	float mRadiationCounter;

	/** Timer that keeps track of our exposure to radiation. */
	FTimerHandle mRadiationTimerHandle;

	/** The accumulated normalized radiation intensity of the players current location */
	UPROPERTY( ReplicatedUsing=OnRep_RadiationIntensity )
	float mRadiationIntensity;

	/** The angle from the players view to the accumulated radiation damage **/
	UPROPERTY( Replicated )
	float mRadiationDamageAngle;

	/** How much immunity do we have for radiation */
	UPROPERTY( Replicated )
	float mRadiationImmunity;
	
	/** Are we in a radioactive zone */
	UPROPERTY( ReplicatedUsing=OnRep_InRadioActiveZone )
	bool mInRadioactiveZone;

	/** Number of starting slots for players inventory */
	int32 mDefaultPlayerInventorySlots;

	/** Number of starting slots for players arm equipments */
	int32 mDefaultPlayerArmEquipmentSlots;

	/** Current offset when blending the camera between stand and crouch */
	float mCurrentCameraRelativeOffset;

	/** Z location offset for  the arms mesh  */
	float mArmBoneLocation;

	/** Current blend value */
	float mCameraOffsetBlend;

	/** How fast the blend is */
	UPROPERTY( EditDefaultsOnly, Category = "FactoryGame|Movement|Crouch" )
	float mCameraOffsetBlendSpeed;

	/** Replicated value of sliding status. Used to let non owning player know whats happening */
	UPROPERTY( replicatedUsing = OnRep_IsSliding )
	bool mReplicatedIsSliding;

	/** Keep track of what status was for mReplicatedIsSliding */
	bool mLastSlideStatus;

	/** New offset that we want to have */
	float mTargetCameraRelativeOffset;

	/* Old offset we are interpolating from */
	float mOldCameraRelativeOffset;

	float mSpringArmOffsetX; //Feched during begin play from the spring arm, and used to be able to restore it's valu later on

	/** New offset that we want to have */
	float mCurrentCameraPipeOffset = 0;


	/** Reprecentation of user setting */
	float mCameraMoveFeedback = 0;


	/** How fast the blend is for crouch and slide */
	UPROPERTY( EditDefaultsOnly, Category = "FactoryGame|Movement|Crouch" )
	float mCrouchSpeed;

	/** How fast the blend is from crouch/slide to stand */
	UPROPERTY( EditDefaultsOnly, Category = "FactoryGame|Movement|Crouch" )
	float mStandSpeed;

	/** How fast the blend is from slide to crouch */
	UPROPERTY( EditDefaultsOnly, Category = "FactoryGame|Movement|Crouch" )
	float mSlideToCrouchSpeed;

	/** Saving the default value of the crouch height since we manipulate it when sliding */
	float mDefaultCrouchHalfHeight;

	/** We are trying to raise capsule collision to default size after a slide has ended */
	bool mTryToUnSlide;

	/** If enable th einput vector will use the look direction as the forward vector */
	bool mIsUsingFull3DInput = false;
public:
	UPROPERTY( BlueprintReadWrite, Category = "FactoryGame|Movement|Crouch" )
	bool mNoUpdate;

public:
	FORCEINLINE ~AFGCharacterPlayer() = default;
};
