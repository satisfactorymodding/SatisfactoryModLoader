// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CameraAnimationCameraModifier.h"
#include "Buildables/FGBuildablePipeHyperJunction.h"
#include "Creature/FGCreature.h"
#include "Equipment/FGEquipment.h"
#include "FGActorRepresentationInterface.h"
#include "FGCharacterBase.h"
#include "FGCharacterMovementComponent.h"
#include "FGHUD.h"
#include "FGInventoryComponent.h"
#include "FGInventoryComponentEquipment.h"
#include "FGInventoryToRespawnWith.h"
#include "FGOutlineComponent.h"
#include "FGRadiationInterface.h"
#include "FGUseableInterface.h"
#include "FGCinematicPlayerSettings.h"
#include "PlayerCustomizationData.h"
#include "Curves/CurveFloat.h"
#include "FGCharacterPlayer.generated.h"

class AFGBuildablePortal;
class AFGStartingPod;

// Callbacks used by the replication graph to build dependency lists
DECLARE_MULTICAST_DELEGATE_TwoParams( FOnPersistentEquipmentActivated, class AFGCharacterPlayer*, class IFGReplicationDependencyActorInterface* );
DECLARE_MULTICAST_DELEGATE_TwoParams( FOnEquipmentEquipped, class AFGCharacterPlayer*, class AFGEquipment* );
DECLARE_MULTICAST_DELEGATE_TwoParams( FOnEquipmentUnequipped, class AFGCharacterPlayer*, class AFGEquipment* );
DECLARE_MULTICAST_DELEGATE_TwoParams( FOnFoliagePickupSpawned, class AFGCharacterPlayer*, class AFGFoliagePickup* );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnBestUseableActorUpdated, bool, IsValid, AActor*, BestUseableActor );
DECLARE_DYNAMIC_DELEGATE_RetVal( bool, FCanPickBestUsableActorDelegate );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnReviveStarted, bool, isReviver );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnReviveEnded, bool, isReviveCompleted );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnPickupToCollectStateUpdated, bool, isActive );
DECLARE_DELEGATE_OneParam( FOnEquipmentSpawned, class AFGEquipment* );

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FDeathGameUIDelegate );

//Callbacks used to expose various lifecycle events of the player character to the mods, since these very frequently are the subject of interest
DECLARE_MULTICAST_DELEGATE_TwoParams( FOnPlayerInputInitializedDelegate, class AFGCharacterPlayer*, class UInputComponent* );
DECLARE_MULTICAST_DELEGATE_OneParam( FSimpleCharacterPlayerDelegate, class AFGCharacterPlayer* );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FFGOnActiveMenuUpdated, bool, isActive );


UENUM( BlueprintType )
enum class EPlayerKeepInventoryMode : uint8
{
	// Looses all items on death.
	Keep_Nothing		UMETA( displayName = "Keep Nothing" ),
	
	// Keeps only Equipment on death.
	Keep_Equipment		UMETA( displayName = "Keep Equipment" ),

	// Looses Nothing on death.
	Keep_Everything		UMETA( displayName = "Keep Everything" ),
};

/** structure that holds variables per input whether it's allowed or not. NOTE: True if input is disabled. */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FDisabledInputGate
{
	GENERATED_USTRUCT_BODY()

public:
	FDisabledInputGate() : FDisabledInputGate( false )
	{}

	explicit FDisabledInputGate( const bool disabled ) :
		mJump( disabled ),
		mCrouch( disabled ),
		mOpenSearch( disabled ),
		mChat( disabled ),
		mInventory( disabled ),
		mDismantle( disabled ),
		mUse( disabled ),
		mVehicleRecording( disabled ),
		mEmote( disabled ),
		mPhotoMode( disabled ),
		mFlashLight( disabled ),
		mOpenCodex( disabled ),
		mResourceScanner( disabled ),
		mBuildGun( disabled ),
		mHotbar( disabled ),
		mToggleMap( disabled )
	{}

	UPROPERTY( EditAnywhere, BlueprintReadWrite, category = "Input" )
	uint8 mJump : 1;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, category = "Input" )
    uint8 mCrouch : 1;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, category = "Input" )
	uint8 mOpenSearch : 1;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, category = "Input" )
	uint8 mChat : 1;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, category = "Input" )
	uint8 mInventory : 1;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, category = "Input" )
	uint8 mDismantle : 1;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, category = "Input" )
	uint8 mUse : 1;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, category = "Input" )
	uint8 mVehicleRecording : 1;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, category = "Input" )
	uint8 mEmote : 1;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, category = "Input" )
	uint8 mPhotoMode : 1;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, category = "Input" )
	uint8 mFlashLight : 1;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, category = "Input" )
	uint8 mOpenCodex : 1;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, category = "Input" )
	uint8 mResourceScanner : 1;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, category = "Input" )
	uint8 mBuildGun : 1;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, category = "Input" )
	uint8 mHotbar : 1;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, category = "Input" )
	uint8 mToggleMap : 1;
};

/**
* not dead, cant revive
*/
UCLASS()
class FACTORYGAME_API UFGUseState_ReviveInvalid_PlayerNotDead final : public UFGUseState
{
	GENERATED_BODY()
public:
	UFGUseState_ReviveInvalid_PlayerNotDead() : Super() { mIsUsableState = false; }
};

/**
* Revive valid
*/
UCLASS()
class FACTORYGAME_API UFGUseState_ReviveValid final : public UFGUseState
{
	GENERATED_BODY()
public:
	UFGUseState_ReviveValid() : Super() { mIsUsableState = true; }
};

USTRUCT( BlueprintType )
struct FACTORYGAME_API FFGActorPlayerPerceptionInfo
{
	GENERATED_BODY()

	FFGActorPlayerPerceptionInfo()
		: Actor( nullptr )
		, AggroLevel( 0.0f )
		, HasCalledInfoAddedEvent( false )
	{}

	/** The actor which is perceiving us. */
	UPROPERTY( BlueprintReadOnly )
	class AActor* Actor;
	
	/** Value representing the current aggro level of the creature. */
	UPROPERTY( BlueprintReadOnly )
	float AggroLevel;

private:
	friend class AFGCharacterPlayer;

	// Hack for clients to be able call the InfoAdded event in case a creature wasn't spawned when the struct was replicated.
	bool HasCalledInfoAddedEvent;
};

class UFGPipeConnectionComponentBase;

/** A single entry in the junction output choice history */
USTRUCT( BlueprintType )
struct FFGPipeHyperConnectionHistoryEntry
{
	GENERATED_BODY()

	/** The connection the player is expected to enter through */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Pipe Hyper" )
	UFGPipeConnectionComponentBase* ConnectionEnteredThrough{};

	/** The connection the player is expected to transit to */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Pipe Hyper" )
	UFGPipeConnectionComponentBase* PickedOutputConnection{};
};

/** Structs that holds the data about the currently pending teleportation of the player */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FFGPlayerPortalData
{
	GENERATED_BODY()

	/** True if we actually have a teleport pending */
	UPROPERTY( BlueprintReadOnly, Category = "Portal" )
	bool Valid;

	/** The portal player has entered through */
	UPROPERTY( BlueprintReadOnly, NotReplicated, Category = "Portal" )
	class AFGBuildablePortalBase* SourcePortal;

	/** The portal player has exited from */
	UPROPERTY( BlueprintReadOnly, NotReplicated, Category = "Portal" )
	class AFGBuildablePortalBase* DestinationPortal;

	/** The portal exit location for us */
	UPROPERTY( BlueprintReadOnly, Category = "Portal" )
	FTransform PortalExitTransform;

	/** The velocity player will have when exiting the portal */
	UPROPERTY( BlueprintReadOnly, Category = "Portal" )
	FVector PortalExitVelocity = FVector::ZeroVector;

	/** The rotation of the player exiting the portal */
	UPROPERTY( BlueprintReadOnly, Category = "Portal" )
	FVector PortalExitDirection;
	
	/** World time at which we have entered the portal */
	UPROPERTY( BlueprintReadOnly, Category = "Portal" )
	double PortalEnterWorldTime;

	/** Minimum time it should take for the player to teleport */
	UPROPERTY( BlueprintReadOnly, Category = "Portal" )
	double MinPortalTime;

	/** Maximum time it should take for the player to teleport */
	UPROPERTY( BlueprintReadOnly, Category = "Portal" )
	double MaxPortalTime;

	/** Distance traveled between teleports, in kms */
	UPROPERTY( BlueprintReadOnly, Category = "Portal" )
	double TotalPortalDistance;
	
	/** Indicator for whenever we have completed level streaming locally */
	uint8 bLocalLevelStreamingComplete : 1;
	/** Whenever we have completed level streaming on the client */
	uint8 bClientLevelStreamingComplete : 1;

	/** World time at which we have exited the portal */
	UPROPERTY( BlueprintReadOnly, Category = "Portal" )
	float PortalExitWorldTime;

	FFGPlayerPortalData();
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnActorPerceptionInfoAdded, const FFGActorPlayerPerceptionInfo&, perceptionInfo );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnActorPerceptionInfoRemoved, const FFGActorPlayerPerceptionInfo&, perceptionInfo );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnCreaturePerceptionStateChanged, const FFGActorPlayerPerceptionInfo&, perceptionInfo, ECreatureState, newState );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnActiveEquipmentChangedInSlot, EEquipmentSlot, Slot );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnPendingJunctionStateChanged, const FFGPendingHyperJunctionInfo&, newJunctionInfo );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnPendingJunctionOutputChanged, const FFGPipeHyperConnectionHistoryEntry&, newOutputConnection );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams( FFGOnPlayerDeathCrateSpawned, EPlayerKeepInventoryMode, keepInventoryMode, FInventoryToRespawnWith&, inout_itemsToRespawnWith, TArray<FInventoryStack>&, inout_droppedItems  );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FFGOnCameraModeModeChanged, ECameraMode, newCameraMode );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FFGOnPlayerPortalStateChanged, FFGPlayerPortalData, newValue );

// Flags to what actions to bind when calling BindActions
UENUM( meta = ( Bitflags, UseEnumValuesAsMaskValuesInEditor = "true" ) )
enum class EActionsToBind : uint8
{
	None = 0,
	
	Movement = 0x1,
	Camera = 0x2,
	Actions = 0x4,
	Cheats = 0x8,
	
	All = 0xFF
};

ENUM_CLASS_FLAGS( EActionsToBind )

// Flags representing each type of mapping context on the player
UENUM( meta = ( Bitflags, UseEnumValuesAsMaskValuesInEditor = "true" ) )
enum class EPlayerMappingContextCategory : uint8
{
	None = 0,
	
	Movement = 0x1,
	Actions = 0x2,
	EquipmentHandling = 0x4,
	EquipmentActions = 0x8,
	Interface = 0x10,

	Cheats = 0x20,

	// <FL> [KajtaziT]
	GamepadDefault = 0x80, // essential gamepad controls

	All = 0xFF
};

ENUM_CLASS_FLAGS( EPlayerMappingContextCategory )

USTRUCT( BlueprintType )
struct FPlayerMappingContext
{
	GENERATED_BODY()
	
	UPROPERTY( EditDefaultsOnly )
	EPlayerMappingContextCategory ContextCategory;

	UPROPERTY( EditDefaultsOnly )
	TObjectPtr< UInputMappingContext > MappingContext;

	UPROPERTY( EditDefaultsOnly )
	int32 Priority;
};

/**
 * Base class for all player characters in the game.
 */
UCLASS( config = Game )
class FACTORYGAME_API AFGCharacterPlayer final : public AFGCharacterBase, public IFGUseableInterface, public IFGRadiationInterface, public IFGActorRepresentationInterface
{
	GENERATED_BODY()
public:
	explicit AFGCharacterPlayer( const FObjectInitializer& ObjectInitializer );

	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	
	// Begin AActor Interface
	virtual void PostActorCreated() override;
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type endPlayReason ) override;
	virtual void Tick( float deltaTime ) override;

	virtual bool CanBeBaseForCharacter( APawn* Pawn ) const override;

	virtual void Destroyed() override;
	// End AActor Interface

	// Begin Pawn Interface
	virtual bool IsLocallyControlled() const override;
	virtual void PossessedBy( AController* newController ) override;
	virtual void UnPossessed() override;
	virtual void OnRep_Controller() override;
	virtual void AddControllerPitchInput( float Val ) override;
	virtual void Jump() override;
	virtual void OnJumped_Implementation() override;
	virtual FVector GetPawnViewLocation() const override;
	virtual bool CanJumpInternal_Implementation() const override;
	virtual bool ShouldTakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) const override;
	virtual FRotator GetViewRotation() const override;
	virtual void OnPlayerStateChanged(APlayerState* NewPlayerState, APlayerState* OldPlayerState) override;
	// End Pawn Interface

	// Begin ACharacter Interface
	virtual void OnStartCrouch( float HeightAdjust, float ScaledHeightAdjust ) override;
	virtual void OnEndCrouch( float HeightAdjust, float ScaledHeightAdjust ) override;
	// End ACharacter Interface

	// Begin AFGCharacterBase interface
	virtual void Died( AActor* died ) override;
	virtual const FFootstepEffect& GetFootstepEffect( const FHitResult& hitResult ) const override;
	virtual void OnTakeDamage( AActor* damagedActor, float damageAmount, const class UDamageType* damageType, class AController* instigatedBy, AActor* damageCauser ) override;
	// End AFGCharacterBase interface

	// Begin ACharacter interface
	virtual void OnMovementModeChanged( EMovementMode PrevMovementMode, uint8 PreviousCustomMode = 0 ) override;
	virtual bool CanCrouch() const override;
	// End ACharacter interface

	// Begin IFGUseableInterface
	virtual void UpdateUseState_Implementation( class AFGCharacterPlayer* byCharacter, const FVector& atLocation, class UPrimitiveComponent* componentHit, FUseState& out_useState ) override;
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
	virtual void ReceiveRadiation_Implementation( float amount, float duration, FVector direction, TSubclassOf< UFGDamageType > damageType ) override;
	virtual bool CanReceiveRadiation_Implementation() const override;
	// End IFGRadiationInterface
	
	//~Begin IFGSaveInterface
	virtual bool ShouldSave_Implementation() const override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreSaveGame_Implementation(int32 saveVersion, int32 gameVersion) override;
	//~End IFGSaveInterface

	// Begin IFGActorRepresentationInterface
	UFUNCTION() virtual bool AddAsRepresentation() override;
	UFUNCTION() virtual bool UpdateRepresentation() override;
	bool UpdateRepresentation_Local();
	UFUNCTION() virtual bool RemoveAsRepresentation() override;
	UFUNCTION() virtual bool IsActorStatic() override;
	UFUNCTION() virtual FVector GetRealActorLocation() override;
	UFUNCTION() virtual FRotator GetRealActorRotation() override;
	UFUNCTION() virtual class UTexture2D* GetActorRepresentationTexture() override;
	UFUNCTION() virtual FText GetActorRepresentationText() override;
	UFUNCTION() virtual void SetActorRepresentationText( const FText& newText ) override;
	UFUNCTION() virtual FLinearColor GetActorRepresentationColor() override;
	UFUNCTION() virtual void SetActorRepresentationColor( FLinearColor newColor ) override;
	UFUNCTION() virtual ERepresentationType GetActorRepresentationType() override;
	UFUNCTION() virtual bool GetActorShouldShowInCompass() override;
	UFUNCTION() virtual bool GetActorShouldShowOnMap() override;
	UFUNCTION() virtual EFogOfWarRevealType GetActorFogOfWarRevealType() override;
	UFUNCTION() virtual float GetActorFogOfWarRevealRadius() override;
	UFUNCTION() virtual ECompassViewDistance GetActorCompassViewDistance() override;
	UFUNCTION() virtual void SetActorCompassViewDistance( ECompassViewDistance compassViewDistance ) override;
	UFUNCTION()	virtual UMaterialInterface* GetActorRepresentationCompassMaterial() override;
	// End IFGActorRepresentationInterface
	
	/** Whether or not the player is currently inside the starting pod. */
	UFUNCTION( BlueprintPure, Category = "Player", meta = ( DeprecatedFunction, DeprecationMessage = "Use Is Playing Intro Sequence instead" ) )
	bool IsInStartingPod() const;

	/** Blueprint function that ticks visual things not needed on dedicated server */
	UFUNCTION( BlueprintCosmetic, Category = "Character" )
	void TickVisuals( float dt );

	/** Used by an actor to tell the player that they are being seen by it. Can be removed manually by calling Unregister, alternatively will be removed automatically if the actor is destroyed. */
	UFUNCTION( BlueprintCallable, Category = "AI" )
	void RegisterPerceivingActor( class AActor* actor );

	/** Used by an actor to tell the player that they are no longer being by it. */
	UFUNCTION( BlueprintCallable, Category = "AI" )
	void UnregisterPerceivingActor( class AActor* actor );

	/** Called on server whenever a creature which is perceiving us gets a state update. */
	UFUNCTION()
	void OnPerceivingCreatureStateChange( class AFGCreatureController* creatureController, ECreatureState previousState, ECreatureState newState );

	/** Gets the list of perception info for creatures that perceive us. */
	UFUNCTION( BlueprintPure, Category = "UI" )
	const TArray< FFGActorPlayerPerceptionInfo >& GetActorPerceptionInfoArray() const { return mActorPerceptionInfo; }

	/** Returns the data about the current portal travel the player is in */
	UFUNCTION( BlueprintPure, Category = "UI" )
	FFGPlayerPortalData GetPortalData() const { return mPortalData; }
	
	/** Used to get the perception info for a creature. */
	const FFGActorPlayerPerceptionInfo* GetPerceptionInfoForActor( class AActor* actor ) const;
	
	/** Must be called on the owning client for the client to be able to switch the weapon */
	UFUNCTION( BlueprintCallable, Category = "Equipment" )
	void EquipEquipment( AFGEquipment* equipment );

	/** Must be called on the owning client to unequip one equipment */
	UFUNCTION( BlueprintCallable, Category = "Equipment" )
	void UnequipEquipment( AFGEquipment* equipment );

	/** Shows or hides the active equipment (holster/unholster) */
	UFUNCTION( BlueprintCallable, Category = "Equipment" )
	void ToggleEquipment();

	/**
	 * Set/clear override the active equipment in a slot.
	 * This must be called on both server and client (simulated)
	 * @param equipment cannot be null and must have a valid slot set.
	 */
	void SetOverrideEquipment( AFGEquipment* equipment );
	void ClearOverrideEquipment( AFGEquipment* equipment );

	UFUNCTION( Server, Reliable )
	void Server_SetOverrideEquipment( AFGEquipment* equipment );

	UFUNCTION( Server, Reliable )
	void Server_ClearOverrideEquipment( AFGEquipment* equipment );

	UFUNCTION( NetMulticast, Reliable )
	void Multicast_SetOverrideEquipment( AFGEquipment* equipment );

	UFUNCTION( NetMulticast, Reliable )
	void Multicast_ClearOverrideEquipment( AFGEquipment* equipment );

	/** @return - The equipments you have equipped */
	UFUNCTION( BlueprintPure, Category = "Equipment" )
	TArray< AFGEquipment* > GetActiveEquipments() const;

	/** @return - The current desired state for the cross hair polled by the HUD. */
	UFUNCTION( Category = "HUD" )
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

	/** Can equip build gun for paint mode (logic behind a recipe gate) */
	bool CanEquipBuildGunForPaint() const;

	/** Is the build gun equipped */
	UFUNCTION( BlueprintPure, Category = "Equipment" )
	bool IsBuildGunEquipped() const;

	/** True if the player is currently traveling in a portal */
	UFUNCTION( BlueprintPure, Category = "Portal" )
	bool IsInPortal() const;

	/** Equips/unequips buildgun */ 
	UFUNCTION( BlueprintCallable, Category = "Equipment" )
	void ToggleBuildGun();

	/** Equips buildgun and goes to menu state */
	// not yet exposed to blueprints
	void EquipBuildGunAndGoToMenuState();

	/** Unequips buildgun */
	UFUNCTION( BlueprintCallable, Category = "Equipment" )
	bool UnequipBuildGun();

	/** Equip the build gun and go into painting state */
	UFUNCTION( BlueprintCallable, Category = "Equipment" )
	void ToggleBuildGunPaint();

	/** Instantly goes to build mode for selected recipe, If already set we unequip the build gun */
	UFUNCTION( BlueprintCallable, Category = "Equipment" )
	void HotKeyRecipe( TSubclassOf< class UFGRecipe > recipe );

	/** Instantly goes to dismantle mode. If already set we unequip the build gun */
	UFUNCTION( BlueprintCallable, Category = "Equipment" )
	void HotKeyDismantle();

	/** Instantly goes to build mode for selected customization recipe. If already set we unequip build gun */
	UFUNCTION( BlueprintCallable, Category = "Equipment" )
	void HotKeyPaint( TSubclassOf< class UFGCustomizationRecipe > customization );

	/** Instantly goes to build mode for blueprint with the given name. If already set we unequip the build gun */
	UFUNCTION( BlueprintCallable, Category = "Equipment" )
	void HotKeyBlueprint( const FString& blueprintName );

	/** Returns Mesh1P SubObject **/
	UFUNCTION( BlueprintPure, Category = "Mesh" )
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return GetMesh(); }

	/** Returns Mesh3P SubObject */
	virtual USkeletalMeshComponent* GetMesh3P() const override;

	/** Returns 1p or 3p mesh */
	virtual USkeletalMeshComponent* GetMainMesh() const override;

	/** Set vehicle that is pending client attach when joining */
	void SetWaitingClientAttachDrivable( class AFGDriveablePawn* drivablePawn ) { mWaitingClientAttachDrivable = drivablePawn; }

	/** Switches between camera modes */
	UFUNCTION()
	void ToggleCameraMode( bool force = false );

	/** Switches between "regular" camera and cinematic camera, enabled = true activates cinematic camera and deactivates regular camera and vice versa */
	UFUNCTION()
	void Photo_SetAdvancedPhotoMode( bool enabled );

	/** Switches between "regular" camera and cinematic camera */
	void Photo_ToggleAdvancedPhotoMode();

	/** Get current camera mode */
	UFUNCTION( BlueprintPure, Category = "Camera" )
	FORCEINLINE ECameraMode GetCameraMode() const { return mCurrentCameraMode; }

	/** Get the camera mode we are currently interpolating to (or have already interpolated to) */
	UFUNCTION( BlueprintPure, Category = "Camera" )
	FORCEINLINE ECameraMode GetTargetCameraMode() const { return mTargetCameraMode; }

	/** Set camera mode */
	UFUNCTION( BlueprintCallable, Category = "Camera" )
	void SetCameraMode( const ECameraMode newCameraMode );

	/** Updates the player visibility, and the visibility of the player equipments */
	UFUNCTION( BlueprintCallable, Category = "Camera" )
	void SetPlayerVisibility( bool bPlayerVisibility );

	/** Set camera mode with a smooth transition. That will not immediately cause the SetCameraMode call, but will instead start a transition that will last a few seconds. */
	UFUNCTION( BlueprintCallable, Category = "Camera" )
	void TransitionToCameraMode( const ECameraMode newCameraMode );

	/** Set the camera mode to the one specified in mPlayerPreferredCameraMode */
	UFUNCTION( BlueprintCallable, Category = "Camera" )
	void UsePreferredCameraMode();

	/** Are we in first person mode? */
	UFUNCTION( BlueprintPure, Category = "Camera" )
	bool IsFirstPerson() const;

	/** Makes this pawn a current view target of the first controller in the world */
	UFUNCTION( BlueprintCallable, Category = "Camera", CallInEditor )
	void SetAsCurrentViewTarget();

	/** Updates the camera with crouch settings */
	void TickCameraOffset( float dt );

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

	UFGGameUI* GetGameUI() const;

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

	/**
	 * Picks up a boom box. Only works as long as the player has a free hand slot, so the boombox gets equipped right away. 
	 */
	UFUNCTION( BlueprintCallable )
	void PickUpBoomBox( class AFGBoomBoxPlayer* boomBox );

	//** The target of a pickup, this is only set if the pickup has a collection time */
	void SetPickupToCollect( class AFGItemPickup* itemPickup );

	FORCEINLINE class AFGFoliagePickup* GetFoliagePickupProxy() const { return mFoliagePickupProxy; }
	
	/** @return This players inventory. */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	FORCEINLINE class UFGInventoryComponent* GetInventory() const { return mInventory; }

	/** @return This players trash inventory. */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	FORCEINLINE class UFGInventoryComponent* GetTrashSlot() const { return mTrashSlot; }

	/** @return This players upload inventory which is used to upload items to central storage */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	FORCEINLINE class UFGInventoryComponent* GetUploadInventory() const { return mUploadInventory; }

	/** @return This players resource scanner. */
	UFUNCTION( BlueprintPure, Category = "Equipment" )
	FORCEINLINE class AFGResourceScanner* GetResourceScanner() const { return mResourceScanner; }

	/** Returns the resource miner that can be used for mining resources by this player. */
	UFUNCTION( BlueprintPure, Category = "Equipment" )
	class AFGResourceMiner* GetActiveResourceMiner() const;

	UFUNCTION( BlueprintPure, Category = "FactoryGame|Character" )
	FORCEINLINE class USkeletalMeshComponent* Get3PMesh() const{ return mMesh3P; }

	/** @todo This should move to the replicator object... Toggles the switch on the server. */
	UFUNCTION( Reliable, Server, WithValidation )
	void Server_ToggleSwitchControl( class AFGBuildableRailroadSwitchControl* switchControl );

	/** Ticks drown damage. Tests drown interval and applies drown damage when appropriate */
	void TickDrownDamage( float delta );

	/** Ticks health regen */
	void TickHealthGeneration( float delta );

	/** returns the foliage pickup proxy, duh */
	class AFGFoliagePickup* GetFoliagePickupData() const { return mFoliagePickupProxy; }

	/** returns currently cached use state, duh */
	FUseState* GetCachedUseState() { return &mCachedUseState; }

	/** returns ladder we are currently on */
	UFUNCTION( BlueprintCallable, Category = "Movement" )
	class UFGLadderComponent* GetCurrentLadderComponent() const;

	/** Gets the camera bobbing animation we want to use when sprinting ( can vary with equipment ) */
	UFUNCTION( BlueprintCallable, Category = "Movement" )
	UCameraAnimationSequence* GetDesiredSprintHeadBobShake() const;

	/** Gets the camera bobbing animation we want to use when walking ( can vary with equipment ) */
	UFUNCTION( BlueprintCallable, Category = "Movement" )
	UCameraAnimationSequence* GetDesiredWalkHeadBobShake() const;

	/** Gets a PreCasted movement component. We should be able to optimize this by ensuring that this component is the right type when assigning it and then do a free cast here ans have it faster. So making this way of fetching it now. Even though it's not really faster atm, it can be optimized later.*/
	UFUNCTION( BlueprintPure )
	UFGCharacterMovementComponent* GetFGMovementComponent() const;

	UFUNCTION( BlueprintPure )
	class AFGPlayerController* GetFGPlayerController() const;

	/** Whether or not an interact widget is open. */
	UFUNCTION( BlueprintPure, Category = "UI" )
	bool IsInteractWidgetOpen() const { return mIsInteractWidgetOpen; }
	
	/** Called whenever an interact widget gets added or removed. */
    void OnInteractWidgetAddedOrRemoved( class UFGInteractWidget* widget, bool added );

	/** Setter for mWantsSprintBobbing */
	UFUNCTION( BlueprintCallable, Category = "Movement" ) 
	void SetWantSprintBobbing( const bool wantBobbing );

	/** Getter for mWantsSprintBobbing */
	UFUNCTION( BlueprintPure, Category = "Movement" ) 
	FORCEINLINE bool GetWantSprintBobbing() const { return mWantsSprintBobbing; }

	/** Getter for the world location of the Camera component */
	FVector GetCameraComponentWorldLocation() const;

	/** Getter for the world location of the Camera component */
	FVector GetCameraComponentForwardVector() const;

	/** Where to drop a inventory item if we drop one */
	FVector GetInventoryDropLocation() const;

	/** Adds or removes an amount of radiation */
	UFUNCTION( BlueprintCallable, Category = "Radiation" )
	void AddRadiationImmunity( const float toAdd );

	/** Sets an amount of radiation */
	UFUNCTION( BlueprintCallable, Category = "Radiation" )
	void SetRadiationImmunity( const float newImmunity );
	
	//Cheats
	virtual void ClientCheatWalk_Implementation() override;
	UFUNCTION( Server, Reliable )
	void Server_CheatWalk();
	virtual void ClientCheatFly_Implementation() override;
	UFUNCTION( Server, Reliable )
	void Server_CheatFly();
	void CheatSetGhostFly( bool ghostModeActive );
	UFUNCTION( Server, Reliable )
	void Server_CheatSetGhostFly( bool ghostModeActive );
	bool CheatToggleGhostFlyIsActive();
	bool CheatToggleFlyModeIsActive();
	UFUNCTION( Server, Reliable )
	void Server_CheatTeleport( FTransform newTransform );
	void CheatTeleport();
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
	void Client_HyperTubeStart( UFGPipeConnectionComponentBase* connectionEnteredThrough, float startTime, float pipeVelocity, float pipeProgress, float pipeAccumulatedTime );
	UFUNCTION( NetMulticast, Reliable, WithValidation, Category = "Hyper Tubes" )
	void Client_HyperTubeEnd( FVector point, FVector velocity, float startTime );

	UFUNCTION( NetMulticast, Reliable, Category = "Portal" )
	void Multicast_UpdatePortalState( const FFGPlayerPortalData& portalData );
	UFUNCTION( Server, Reliable, Category = "Portal" )
	void Server_NotifyPortalLevelStreamingComplete();

	/** Returns the Cinematic Camera SubObject used in PhotoMode **/
	UFUNCTION( BlueprintPure, Category = "Camera" )
	FORCEINLINE class UFGCineCameraComponent* GetCinematicCameraComponent() const { return mCinematicCameraComponent; }

	UFUNCTION( BlueprintCallable, Category = "Emote" )
	void PlayEmote( TSubclassOf<class UFGEmote> emote );
	UFUNCTION( Server, Reliable, Category = "Emote" )
	void Server_PlayEmote( TSubclassOf<class UFGEmote> emote, int32 randomInteger );
	UFUNCTION( NetMulticast, Reliable, Category = "Emote" )
	void Multicast_PlayEmote( TSubclassOf<class UFGEmote> emote, int32 randomInteger );
	UFUNCTION( BlueprintCallable, Category = "Emote" )
	void PlayEmoteSFX( class UAkAudioEvent* event );
	UFUNCTION( BlueprintPure, Category = "Emote" )
	class USkeletalMeshComponent* GetEmoteSkelMeshComp() const { return mEmoteSkelMeshComp; }
	UFUNCTION( BlueprintCallable, Category = "Emote" )
	void ClearEmoteSkelMeshComp( const float delay );
	UFUNCTION( BlueprintPure, Category = "Emote" )
	class UFGInteractWidget* GetEmoteMenu() const { return mEmoteMenuWidget; } 
	// Finds all light sources in the desired radius around the player and toggles them after the desired delay.
	UFUNCTION( Server, Reliable, BlueprintCallable, Category="Lights")
	void Server_ToggleLightsInRadius( float inRadius, float inDelay );

	/** Returns the info regarding the pending HyperTube junction */
	UFUNCTION(BlueprintPure, Category = "Hyper Tube" )
	FFGPendingHyperJunctionInfo GetPendingHyperJunctionInfo() const;

	/** Returns a total distance the player has  travelled in a HyperTube */
	UFUNCTION( BlueprintPure, Category = "Hyper Tube" )
	float GetTotalHyperTubeTravelDistance() const;
	
	/** The connection that has been picked on the pending junction through Server_UpdateHyperJunctionPath */
	UFUNCTION( BlueprintPure, Category = "Hyper Tube" )
	FORCEINLINE FFGPipeHyperConnectionHistoryEntry GetPendingHyperJunctionOutputConnection() const { return mPendingHyperJunctionOutputConnection; };

	/** Updates the output path on the next junction picked by the client */
	UFUNCTION( BlueprintCallable, Server, Reliable, WithValidation, Category = "Hyper Tube" )
	void Server_UpdateHyperJunctionOutputConnection( UFGPipeConnectionComponentBase* connectionEnteredThrough, UFGPipeConnectionComponentBase* newOutputConnection);

	/** Returns the last history entry for the provided junction actor */
	UFUNCTION( BlueprintPure, Category = "Hyper Tube" )
	UFGPipeConnectionComponentBase* GetHyperTubeJunctionOutputConnectionFromHistory( UFGPipeConnectionComponentBase* connectionEnteredThrough ) const;

	UFUNCTION( BlueprintPure, Category = "Player|CentralStorage" )
	bool IsUploadingToCentralStorage() const;
	UFUNCTION( BlueprintPure, Category = "Player|CentralStorage" )
	float GetCentralStorageUploadProgress() const;
	UFUNCTION( BlueprintPure, Category = "Player|CentralStorage" )
	bool IsUploadInventoryEmpty() const;
	
	/** Called when player switches the current REAL hyper tube being travelled, can be used for cosmetic effects */
	UFUNCTION(BlueprintImplementableEvent, Category = "Hyper Tube" )
	void OnNewTravelPipeSection();

	/** Returns true whenever this player character is driven by a cinematic */
	UFUNCTION( BlueprintPure, Category = "Cinematic" )
	bool IsCinematicControlled() const;

	/** Returns the cinematic driver that is currently controlling this player */
	UFUNCTION( BlueprintPure, Category = "Cinematic" )
	FORCEINLINE class UFGPlayerCinematicDriver* GetCinematicDriver() const { return mCinematicDriver; }

	/** Returns the cinematic player settings for this character. Only valid when the character is cinematic controlled. */
	FORCEINLINE FFGCinematicPlayerSettings GetCinematicPlayerSettings() const { return mCinematicPlayerSettings; }
	
	void SetIsFlyingToggleable( const bool canFlyingBeToggled );

	void OnPhotoModeToggled( bool enabled );

	UFUNCTION( BlueprintPure, Category = "Input" )
	int32 GetMappingContextPriority() const;

	/** Enables / disables specified mapping contexts. Can change multiple at the same time. */
	UFUNCTION( BlueprintCallable, Category = "Input" )
	void SetMappingContextEnabled( UPARAM( meta = ( Bitmask, BitmaskEnum = "EPlayerMappingContextCategory" ) )int32 contextMask, bool enabled );
	void SetMappingContextEnabled( EPlayerMappingContextCategory contextMask, bool enabled );
	
	void ClipboardCopy();
    void ClipboardPaste();

	// Begin bonk
	/* To bonk or not to bonk. */
	void UpdateBonk(FRotator viewRotation, FVector viewLocation);

	UPROPERTY(EditDefaultsOnly,Category = "Bonk")
	UAkAudioEvent* mBonkSound;

	UPROPERTY(EditDefaultsOnly, Category = "Bonk")
	TArray<TSubclassOf<AFGBuildable>> mBonkClasses;

	UPROPERTY(EditDefaultsOnly, Category = "Bonk")
	float mMinTimeBetweenBonk = 5.f;

	UPROPERTY(EditDefaultsOnly, Category = "Bonk")
	float mMinBonkVelocity = 10.f;
	
	float mTimeLastBonk = 0;
	bool bDidBonk = false;
	// End bonk
	
	/** Input Actions **/
	void Input_Jump( const FInputActionValue& actionValue );
	void Input_Use( const FInputActionValue& actionValue );
	
	void Input_CloseBuildGunMenu( const FInputActionValue& actionValue );
	
	void Input_ToggleBuildGunBuild( const FInputActionValue& actionValue );
	void Input_ToggleBuildGunDismantle( const FInputActionValue& actionValue );
	void Input_ToggleBuildGunPaint( const FInputActionValue& actionValue );
	
	void Input_MoveAxis( const FInputActionValue& actionValue );
	void Input_LookAxis( const FInputActionValue& actionValue );
	void Input_TurnAxis( const FInputActionValue& actionValue );

	// <FL> [KajtaziT] actions for radial menu direction
	// alternative actions to control radial menu direction
	// either using a gamepad stick or the mouse cursor
	void Input_RadialMenuDirectionAxis( const FInputActionValue& actionValue );
	void Input_RadialMenuDirectionCursor( const FInputActionValue& actionValue );	

	// switch gamepad mapping context on menu open/close
	UFUNCTION( BlueprintCallable )
	void SetMenuActive( bool IsActive, UUserWidget* MenuWidget );

	UPROPERTY( BlueprintAssignable, Category = "Input" )
	FFGOnActiveMenuUpdated mOnActiveMenuUpdated;
	
	// </FL>

	
	void Input_Sprint( const FInputActionValue& actionValue );

	void Input_Crouch( const FInputActionValue& actionValue );

	void Input_CycleNextEquipment(const FInputActionInstance& ActionInstance);
	void Input_CycleEquipmentAxis(const FInputActionValue& actionValue);
	void Input_Holster( const FInputActionValue& ActionValue );

	void Input_EmoteWheel( const FInputActionValue& actionValue );

	void Input_SampleBuilding( const FInputActionValue& actionValue );

	void Input_ToggleInventory( const FInputActionValue& actionValue );

	UFUNCTION( BlueprintImplementableEvent, Category = "Player", meta = (DisplayName = "OnToggleInventory") )
	void NotifyOnToggleInventory();

	void Input_ToggleCodex( const FInputActionValue& actionValue );

	UFUNCTION( BlueprintImplementableEvent, Category = "Player", meta = (DisplayName = "OnToggleCodex") )
	void NotifyOnToggleCodex();

	void Input_ToggleQuickSearch( const FInputActionValue& actionValue );

	UFUNCTION( BlueprintImplementableEvent, Category = "Player", meta = (DisplayName = "OnToggleQuickSearch") )
	void NotifyOnToggleQuickSearch();

	void Input_ToggleFlashlight( const FInputActionValue& actionValue );
	
	UFUNCTION( BlueprintImplementableEvent, Category = "Player", meta = (DisplayName = "OnToggleFlashlight") )
	void NotifyOnToggleFlashlight();
	
	void Input_ToggleFly( const FInputActionValue& actionValue );
	void Cheat_ToggleFly();

	void Input_ToggleGhostFly( const FInputActionValue& actionValue );

	void Input_Teleport( const FInputActionValue& actionValue );
	
	/**
	 * Binds the input context to the input subsystem owned by this local player
	 * Will also apply additional associated mapping contexts on top with lower priority
	 */
	UFUNCTION( BlueprintCallable, Category = "Input" )
	void SetMappingContextBound( UInputMappingContext* context, bool bind, int32 priority = 0 );

	/** Revives the current player with full health. Needs to be called on the authority side */
	UFUNCTION( BlueprintCallable, BlueprintAuthorityOnly, Category = "Player" )
	void RevivePlayerWithFullHealth();

	bool SetPlayerFlyingOnSpawn();

	/** Returns distance we want to be able to use stuff from */
	UFUNCTION( BlueprintPure, Category = "Use" )
	float GetUseDistance() const;

	bool GetIsInGasCloud() const;
	void SetIsInGasCloud( const bool isInGas );

	/** Called when the ziplining is started or ended by the FGCharacterMovementComponent. */
	void OnZiplineStarted();
	void OnZiplineEnded();

	/** Returns true if the player is currently playing intro sequence */
	UFUNCTION( BlueprintPure, Category = "Intro Sequence" )
	FORCEINLINE bool IsPlayingIntroSequence() const { return mIntroSequenceStartingPod != nullptr; }

	/** Returns the pod that is currently playing the intro sequence if we are playing one */
	UFUNCTION( BlueprintPure, Category = "Intro Sequence" )
	FORCEINLINE AFGStartingPod* GetIntroSequencePod() const { return mIntroSequenceStartingPod; }

	/** Applies the new player visibility to the player */
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "Character" )
	void UpdatePlayerVisibility();

	/** Updates the visibility of the equipments by calling ShouldShowEquipments for active equipments */
	UFUNCTION( BlueprintCallable, Category = "Equipment" )
	void UpdateEquipmentVisibility();

	/** Updates the movement mode based on whenever the player is currently respawning */
	void UpdateMovementModeOnRespawn( bool bIsRespawning );

	FORCEINLINE void Internal_SetIntroSequenceStartingPod( AFGStartingPod* newStartingPod ) { mIntroSequenceStartingPod = newStartingPod; } 
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent( class UInputComponent* inputComponent ) override;
	virtual void DestroyPlayerInputComponent() override;
	// End of APawn interface

	void BindActions( EActionsToBind actionsToBindMask = EActionsToBind::All );
	void UnbindActions();

	virtual void Native_OnLocallyPossessedChanged( bool isPossessed ) override;
	
	void SetupCinematicDriver();
	void DestroyCinematicDriver();

#if WITH_EDITOR
	/** Updates items in the inventory of the cinematic player */
	UFUNCTION( CallInEditor, Category = "Cinematic", DisplayName = "Update Inventory Items" )
	void EditorCinematic_UpdateInventoryItems();
#endif
	
	/** Called when we unlock more inventory slots */
	UFUNCTION()
	void OnInventorySlotsUnlocked( int32 newUnlockedSlots );

	/** Called when we unlock more arms slots */
	UFUNCTION()
	void OnArmsSlotsUnlocked( int32 newUnlockedSlots );
	
	/** Called when we unlock more upload slots */
	UFUNCTION()
	void OnUploadSlotsUnlocked();

	void CheckAndAddPositionToSafeList( FVector currentPos );
	void CheckForWaterVolumeOverlaps();

	// Begin AFGCharacterBase interface
	virtual float AdjustDamage( AActor* damagedActor, float damageAmount, const class UDamageType* damageType, class AController* instigatedBy, AActor* damageCauser ) override;
	virtual void DoRagdoll_Internal() override;
	// End AFGCharacterBase interface

	/** Blueprint accessor for when an item was picked up, called on client/server/remote */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, BlueprintCosmetic, Category = "Character" )
	void PlayPickupEffects();

	/** For playing 1P events */
	virtual class UAkAudioEvent* GetFootstepEvent( int32 footDown ) const override;

	UFUNCTION( BlueprintNativeEvent, Category = "Input" )
	void OnDisabledInputGateChanged( const FDisabledInputGate newValue);

	/**
	 * Initiates player teleportation from the source portal to the destination portal
	 */
	UFUNCTION( BlueprintCallable, BlueprintAuthorityOnly, Category = "Portal" )
	void StartPortal( AFGBuildablePortalBase* sourcePortal, AFGBuildablePortalBase* destPortal );
	
	/** Called when the state of our long-distance teleport changed from valid to not-valid or vice versa */
	UFUNCTION( BlueprintNativeEvent, Category = "Portal" )
	void OnPortalStateChanged( const FFGPlayerPortalData& newValue );

	/** Immediately snaps the player to the portal exit transform */
	void SnapPlayerToPortalExitLocation();

	/** SERVER ONLY: Drops the contents of the player on the ground */
	struct FInventoryToRespawnWith SpawnDeathCrate( const EPlayerKeepInventoryMode& keepInventoryMode, UFGInventoryComponent* inventory );
	
	UFUNCTION()
	void OnItemAddedToInventory( TSubclassOf< UFGItemDescriptor > itemClass, const int32 numAdded, UFGInventoryComponent* targetInventory = nullptr );

	UFUNCTION()
	void OnInventorySlotUpdated( const int32 Index );

	UFUNCTION()
	void OnCentralStorageItemAmountUpdated( const TSubclassOf<UFGItemDescriptor> itemClass, int32 newAmount );

	/** Hand out the starting resources. */
	void AddDefaultInventoryItems();

	/** Equip the existing equipment, useful when exiting a car, loading games a similar */
	void ReEquipExistingEquipment();

	/** Equip the existing equipment, useful when exiting a car, loading games a similar */
	void UnEquipAllEquipment();

	/** Check if we are allowed to trace for best usable actor. */
	bool CanPickBestUsableActor() const;

	/** Update which actor we can interact with at our location. */
	void UpdateBestUsableActor();

	/** Called on both server and client when we want to use something. */
	void OnUse();

	/** Called on both server and client when we want to use something. */
	void OnUseStop();

	/** Checks if what we hit can be picked up */
	bool CanBePickedUp( const FHitResult& hitResult ) const;

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

	/** Returns Camera SubObject **/
	UFUNCTION( BlueprintPure, Category = "Camera" )
	FORCEINLINE class UCameraComponent* GetCameraComponent() const { return mCameraComponent; }

	/** Returns spring arm SubObject **/
	UFUNCTION( BlueprintPure, Category = "Camera" )
	FORCEINLINE class USpringArmComponent* GetSpringArmComponent() const { return mSpringArmComponent; }

	/** Set the best usable actor */
	void SetBestUsableActor( class AActor* newBestUsableActor );

	/** snaps the camera spring arm to its desired location, so no interp */
	UFUNCTION( BlueprintImplementableEvent, Category = "Camera" )
	void SnapSpringArmToDesiredLocation();

	/** Callback for the revive timer */
	void OnReviveTimerComplete();

	/** returns the progress of reviving a player 0..1 */
	UFUNCTION( BlueprintPure, Category="Revive" )
	float GetReviveProgress() const;

	/** Takes care of client side stuff when revived (eg. Enabling player input) */
	UFUNCTION( Client, Reliable, Category = "Revive" )
	void Client_Revived();

	/** Called on client when we started to revive someone or someone started to revive us */
	UFUNCTION( Client, Reliable, Category = "Revive" )
	void Client_ReviveStarted();

	/** Called on client when we stopped to revive someone or someone stopped to revive us */
	UFUNCTION(Client, Reliable, Category = "Revive" )
	void Client_ReviveEnded();

	/** returns the progress of reviving a player 0..1 */
	UFUNCTION( BlueprintPure, Category = "Use" )
	float GetPickupProgress() const;

	/** Called when we start receiving radiation. */
	UFUNCTION( BlueprintImplementableEvent, Category = "Radiation" )
	void OnReceiveRadiationStart();

	/** Called when we stop receiving radiation. */
	UFUNCTION( BlueprintImplementableEvent, Category = "Radiation" )
	void OnReceiveRadiationStop();

	/** Fetches the color to use for this actors representation */
	UFUNCTION( BlueprintImplementableEvent, Category = "Representation" )
	FLinearColor GetDefaultRepresentationColor();

	UFUNCTION()
	void StartReceivingRadiation();

	UFUNCTION()
	void StopReceivingRadiation();

	/** Called when we respawn but did not get a death crate, so we can find our last death location. */
	UFUNCTION( BlueprintImplementableEvent, Category = "Death" )
	void OnSpawnDeathMarker();

	/** Returns accumulated normalized radiation intensity at the the players location **/
	UFUNCTION( BlueprintPure, Category = "Radiation" )
	FORCEINLINE float GetRadiationIntensity() const { return mRadiationIntensity; }

	/** Returns accumulated radiation immunity **/
	UFUNCTION( BlueprintPure, Category = "Radiation" )
	FORCEINLINE float GetRadiationImmunity() const { return mRadiationImmunity; }

	/** Returns the angle from the players view to the accumulated radiation damage **/
	UFUNCTION( BlueprintPure, Category = "Radiation" )
	FORCEINLINE float GetRadiationDamageAngle() const { return mRadiationDamageAngle; }

	UFUNCTION( BlueprintPure, Category = "Radiation" )
	FORCEINLINE bool IsInRadioActiveZone() const { return mInRadioactiveZone; }

	/** Start the pending removal of the character */
	virtual void TornOff() override;
	
	/** Called when some state changed so we can update name tag location */
	UFUNCTION( BlueprintImplementableEvent, Category = "Character" )
	void UpdatePlayerNameTagLocation();

	/** Called when the player customization data is updated and needs to be applied to the mesh */
	UFUNCTION( BlueprintImplementableEvent, Category = "Character" )
	void ApplyPlayerCustomizationData( const FPlayerCustomizationData& NewCustomizationData );

	/** Returns true if the given equipment should be visible under the current circumstances. Will only be called on equip, if you want to refresh the visibility call UpdateEquipmentVisibility() */
	UFUNCTION( BlueprintNativeEvent, Category = "Equipment" )
	bool ShouldShowEquipment( AFGEquipment* Equipment ) const;

	/** Returns true if the player mesh should currently be visible. Make sure to re-evaluate this by calling UpdatePlayerVisibility */
	UFUNCTION( BlueprintNativeEvent, Category = "Character" )
	bool ShouldShowPlayer() const;

	/** True if player is online. By online we mean this player or the driven vehicle has a player state and someone is controlling it */
	UFUNCTION( BlueprintPure, Category = "Radiation" )
	FORCEINLINE bool IsPlayerOnline() const { return mIsPlayerOnline.IsSet() ? mIsPlayerOnline.GetValue() : false; }

	UFUNCTION( BlueprintCallable )
	void ToggleFlashlight();
	
	/** Called when we update the best useable actor */
	UPROPERTY( BlueprintAssignable, Category = "UI"  )
	FOnBestUseableActorUpdated mOnBestUseableActorUpdated;

	/** Called to check if we can pick a usable actor */
	UPROPERTY( BlueprintReadWrite, Category = "UI" )
	TArray<FCanPickBestUsableActorDelegate> mCanPickBestUsableActorDelegate;

	/** Called when we started to revive someone or someone started to revive us */
	UPROPERTY( BlueprintAssignable, Category = "UI"  )
	FOnReviveStarted mOnReviveStarted;

	/** Called when we stopped to revive someone or someone stopped to revive us */
	UPROPERTY( BlueprintAssignable, Category = "UI"  )
	FOnReviveEnded mOnReviveEnded;

	/** Called when the state of the item we are trying to pickup changes */
	UPROPERTY( BlueprintAssignable, Category = "UI"  )
	FOnPickupToCollectStateUpdated mOnPickupToCollectStateUpdated;

	UPROPERTY( BlueprintAssignable, Category = "Equipment" )
	FOnActiveEquipmentChangedInSlot mOnActiveEquipmentChangedInSlot;

	float mFlyToggleTimeStamp = 0.0f;
	/* Time between pressing jump twice for the Flying Mode to toggle. */
	UPROPERTY( EditDefaultsOnly, Category = "Character Movement: Flying" )
	float mFlyToggleTime = 0.2f;

	UPROPERTY( BlueprintReadWrite, Replicated, SaveGame )
	bool mIsFlashlightOn = false;
	
	void DebugBuildablesInFrustum() const;
	void DebugVisualizeDropPods( int32 debugMode ) const;

public:
	// Callbacks used by the replication graph to build dependency lists
	/** Event for when equipment that is should always be replicated on the player is spawned */
	static FOnPersistentEquipmentActivated OnPersistentEquipmentActivated;
	
	/** Event on when new equipment has been equipped */
	static FOnEquipmentEquipped OnEquipmentEquipped;

	/** Event on when equipment has been unequipped */
	static FOnEquipmentUnequipped OnEquipmentUnequipped;

	/** Event when the foliage pickup proxy has spawned */
	static FOnFoliagePickupSpawned OnFoliagePickupSpawned;

	/** Event when player character input controller has been set up and vanilla actions have been bound */
	static FOnPlayerInputInitializedDelegate OnPlayerInputInitialized;
	static FSimpleCharacterPlayerDelegate OnPlayerInputDestroyed;

	/** Event when player has received the OnActorCreated call, which happens before save load and BeginPlay call */
	static FSimpleCharacterPlayerDelegate OnPlayerCreated;
	/** Event when player character has received the BeginPlay, which would be after construction and save load */
	static FSimpleCharacterPlayerDelegate OnPlayerBegunPlay;

	/** Called whenever an actor perception info is added. */
	UPROPERTY( BlueprintAssignable, Category = "UI" )
	FOnActorPerceptionInfoAdded mOnActorPerceptionInfoAdded;

	/** Called whenever an actor perception info is removed. */
	UPROPERTY( BlueprintAssignable, Category = "UI" )
	FOnActorPerceptionInfoRemoved mOnActorPerceptionInfoRemoved;

	/** Called whenever a creature which is perceiving us has a state change. */
	UPROPERTY( BlueprintAssignable, Category = "UI" )
	FOnCreaturePerceptionStateChanged mOnCreaturePerceptionStateChanged;

	/** Called whenever a pending junction info changes */
	UPROPERTY( BlueprintAssignable, Category = "UI" )
	FOnPendingJunctionStateChanged mOnPendingJunctionStateChanged;

	/** Called whenever a selected output connection on the pending junction changes */
	UPROPERTY( BlueprintAssignable, Category = "UI" )
	FOnPendingJunctionOutputChanged mOnPendingJunctionOutputChanged;

	/** Called when the player's camera mode changes to the new value */
	UPROPERTY( BlueprintAssignable, Category = "Camera" )
	FFGOnCameraModeModeChanged mOnPlayerCameraModeChanged;

	/** Event for when player death crate is about to be spawned. Gives you a chance to modify both dropped and retained items */
	UPROPERTY( BlueprintAssignable, Category = "Death" )
	FFGOnPlayerDeathCrateSpawned mOnDeathCrateSpawned;

	/** Event for when the player's portal state changes */
	UPROPERTY( BlueprintAssignable, Category = "Portal" )
	FFGOnPlayerPortalStateChanged mOnPlayerPortalStateChanged;

	UPROPERTY( BlueprintAssignable, DisplayName = "OnDeathNotify" )
	FDeathGameUIDelegate mOnDeathGameUIDelegate;
	
	/** Called just after a new equipment actor has been spawned, before it eventually gets equipped. */
	FOnEquipmentSpawned mOnEquipmentSpawned;

	/** Cached player start actor that was used to restart this player. If player pawn was loaded from the save game, this will be null */
	UPROPERTY()
	AActor* mPlayerStartActor;

	/** The best usable actor nearby. */
	UFUNCTION( BlueprintPure, Category = "Use" )
	FORCEINLINE	class AActor* GetBestUsableActor() const { return mBestUsableActor; }

	/** Triggers the OnBestUseableActorUpdated delegate with the cached best useable actor. Used to update UI when best useable actor changes */
	UFUNCTION( BlueprintCallable, Category = "Use" )
	void TriggerBestUsableActorDelegate();

	/** Update what crosshair to show */
	void UpdateHUDCrosshair();

	/** Gets sliding status */
	UFUNCTION( BlueprintPure, Category = "Use" )
	bool IsSliding() const;

	/** Gets mTryToUnSlide */
	inline bool IsTryingToUnslide() const { return mTryToUnSlide; }

	bool IsInPumpiMode() const;

	/** Update name and color on player name widget */
	UFUNCTION( BlueprintCallable, Category = "Player Name" )
	void UpdatePlayerNameWidget();

	/** Forcefully updates the player customization data from the correct place (either offline cache or player state) */
	void UpdatePlayerCustomizationData();

	/** Update the status of the player s we can update appearances and UI */
	void UpdatePlayerStatus();

	/** Gets the players state for this player. Either from this character or the driven vehicle */
    UFUNCTION( BlueprintPure, Category = "General" )
    class AFGPlayerState* GetControllingPlayerState() const;

	/** This function tells us if we should be able to interact with objects such as vehicles, foliage, ores, or use equipments. */
	bool CanInteractWithEnvironment() const;

	/** Returns the arm bone location offset we want to use depending on crouch/stand state **/
	UFUNCTION( BlueprintPure, Category = "Movement" )
	FORCEINLINE float GetArmBoneLocation() const { return mArmBoneLocation; }
	
	/** Registers dependencies between this pawn and replication of it's owned equipments and foliage pickup */
	void RegisterPersistentEquipmentReplicationDependencies();
private:
	/**
	 * Spawn a new equipment.
	 * @param equipmentClass Class to spawn.
	 * @param owner Optionally pass an owner, only use this in combination with persistent equipments.
	 */
	AFGEquipment* SpawnEquipment( const TSubclassOf< AFGEquipment > &equipmentClass, AActor* owner = nullptr );

	template< typename T >
	T* SpawnEquipment( const TSubclassOf< AFGEquipment > equipmentClass, AActor* owner = nullptr )
	{
		fgcheck( equipmentClass->IsChildOf( T::StaticClass() ) );
		return Cast<T>( SpawnEquipment( equipmentClass, owner ) );
	}
	
	/** Wrapper for updating actor perception info. Should return false if info should be removed. */
	bool UpdateActorPerceptionInfo( FFGActorPlayerPerceptionInfo& info ) const;
	
	/** Used to properly remove perception info for an actor */
	void RemoveActorPerceptionInfo( const FFGActorPlayerPerceptionInfo& info );

	/** Custom ticks */
	void UpdateHeadBob();

	void NotifyGameStatePlayerAdded();

	/** Update the UI with status if we are in radioactive zone or not*/
	void UpdateGameUIRadiationStatus();

	/** Update the UI with radiation intensity*/
	void UpdateGameUIRadiationIntensity() const;

	/** Resets the cached customization data on the character to the defaults from the player state */
	void SetupDefaultPlayerCustomizationData();

	UFUNCTION( BlueprintPure, Category = "General" )
	int32 GetTotalPlayerInventorySlots() const;

	UFUNCTION( BlueprintPure, Category = "General" )
	int32 GetTotalPlayerArmEquipmentSlots() const;

	/** Server function that are called from public clients of the same name */
	UFUNCTION( Reliable, Server, WithValidation )
	void Server_EquipEquipment( AFGEquipment* newEquipment );
	UFUNCTION( Reliable, Server, WithValidation )
	void Server_UnequipEquipment( AFGEquipment* newEquipment );
	UFUNCTION( Reliable, Server )
	void Server_ToggleEquipment();
	
	UFUNCTION( Server, Reliable, Category = "Revive" )
	void Server_RevivePlayer( AFGCharacterPlayer* playerToRevive );
	UFUNCTION( Reliable, Server, WithValidation, Category = "Use" )
	void Server_OnUse();
	UFUNCTION( Reliable, Server, WithValidation, Category = "Use" )
	void Server_OnUseReleased();
	UFUNCTION( Reliable, Server, WithValidation )
	void Server_PickUpItem( class AFGItemPickup* itemPickup );
	UFUNCTION( Reliable, Server )
	void Server_PickUpBoomBoxPlayer( class AFGBoomBoxPlayer* boomBox );
	UFUNCTION( Reliable, Server )
	void Server_UpdateFlySpeedMultiplier( float newFlySpeedMultiplier );

	UFUNCTION( Client, Reliable )
	void Client_OnPerceivingCreatureStateChange( AFGCreature* creature, ECreatureState newState );
	void OnPerceivingCreatureStateChange_Internal( AFGCreature* creature, ECreatureState newState ) const;
	
	/** Called when slide status changes so we can change capsule size accordingly */
	void OnSlideStatusUpdated();
	
	UFUNCTION()
	void MakeSlidingNoise();

	/** OnReps */
	UFUNCTION()
	void OnRep_ActiveEquipments();
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
	UFUNCTION()
	void OnRep_PendingHyperJunctionOutputConnection();
	UFUNCTION()
	void OnRep_CachedPlayerName();
	UFUNCTION()
	void OnRep_CachedPlayerCustomizationData();
	
	UFUNCTION()
	void OnRep_ActorPerceptionInfo( const TArray< FFGActorPlayerPerceptionInfo >& OldValues );

	/** Called to update the customization data when it updated the player state */
	UFUNCTION()
	void OnPlayerCustomizationDataChanged( const FPlayerCustomizationData& NewCustomizationData );
	
	/** Migrate number of inventory and arm equipment slots saved before BU3 to unlock subsystem */
	void MigrateNumSavedSlots();

	/** Check if we have items picked up that isn't registered as picked up. Fixes issues on old saves before we saved picked up items */
	void CheckItemPickedUp() const;
	
	virtual void OnRep_IsPossessed() override;
	virtual void OnRep_PlayerState() override;
	
	void SetOnlineState( const bool isPlayerOnline );

	/** Checks the player state if flying is toggleable */
	void UpdateFlyingIsToggleable();

	/** Tick the upload timer that tries to send items to central storage */
	void TickUploadTimer( float dt );
	/** Can we upload one item from the upload inventory */
	bool CanUploadItem();
	/** Try to upload one item from the upload inventory */
	bool TryUploadItem();
	/** Immediately applies the current camera mode to the player */
	void ApplyCurrentCameraMode();
	/** Sets what mesh is visible on us ( 1p or 3p ) */
	void SetMeshViewModeFirstPerson( const bool isFirstPerson );
	/** Applies first person settings to the player camera, does not change the camera mode or dispatch any events */
	void SetFirstPersonMode();
	/** Applies third person settings to the player camera, does not change the camera mode or dispatch any events */
	void SetThirdPersonMode();
	/** Applies the first person mode transition to the camera, but does not actually set it to the real first person mode */
	void SetFirstPersonTransition();
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

	UPROPERTY( BlueprintReadWrite )
	bool mIsCurrentlyTryingToEnterVehicle = false;

	/** Locally cached fly speed multiplier. Fetched from the options menu in cheat builds */
	float mFlySpeedMultiplier{1.0f};

	// <FL> [KajtaziT] decoupling radial menus from input
	UPROPERTY( DisplayName = "RadialMenuDirection" )
	FVector2f mRadialMenuDirection;
	
	// <FL> [KajtaziT] workaround to ignore held input when adding gamepad mappings context after leaving a menu
	UPROPERTY( DisplayName = "MenuWasDeactivatedTickDelay" )
	int mMenuWasDeactivatedTickDelay = 0;

	UFUNCTION( BlueprintPure, Category = "Map" )
	FORCEINLINE FVector2f GetRadialMenuDirection() const { return mRadialMenuDirection; }
	// </FL>

	/** Returns the cached player customization data. Note that unlike retrieving player state, this handles offline players correctly by remembering their customizations */
	FORCEINLINE FPlayerCustomizationData GetCachedPlayerCustomizationData() const { return mCachedPlayerCustomizationData; }
	
	FORCEINLINE float GetFloorIsLavaAchievementTimerDuration() const { return mFloorIsLavaAchievementTimerDuration; }
protected:
	/** Pawn mesh: 3rd person view */
	UPROPERTY( VisibleDefaultsOnly, BlueprintReadOnly, Category = Mesh )
	class USkeletalMeshComponent* mMesh3P;

	/** Helmet Mesh */
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = Mesh )
	TObjectPtr<UStaticMeshComponent> mHelmetMesh;

	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite )
	TObjectPtr<class USpotLightComponent> mFirstPersonFlashlight;
	
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite )
	TObjectPtr<USpotLightComponent> mThirdPersonFlashlight;

	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite )
	TObjectPtr<class UPostProcessComponent> mTakeDamagePostProcess;

	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite )
	TObjectPtr<class UMaterialInstanceDynamic> mRadiationNoise;
	
	/** Hat mesh used for the christmas hat */
	UPROPERTY( BlueprintReadWrite, Category = Mesh )
	TObjectPtr<UStaticMeshComponent> mHat;
	
	/** The widget component used to show the players name */
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = "Player Name" )
	class UWidgetComponent* mPlayerNameWidgetComponent;

	/** As we have no foliage actor to actually put pickup code in, we use this actor as a proxy */
	UPROPERTY( EditDefaultsOnly, Category = "Use" )
	TSubclassOf< class AFGFoliagePickup > mFoliagePickupProxyClass;

	/** Actor that's used when trying to pickup foliage */
	UPROPERTY( Replicated, BlueprintReadOnly, Category = "Use" )
	class AFGFoliagePickup* mFoliagePickupProxy;

	/* This is the infamous build gun. */
	UPROPERTY( SaveGame, BlueprintReadOnly, Replicated, Category = "Equipment" )
	class AFGBuildGun* mBuildGun;

	/*Reference to the resource scanner */
	UPROPERTY( SaveGame, Replicated )
	AFGResourceScanner* mResourceScanner;

	/* Reference to the resource miner */
	UPROPERTY( SaveGame, Replicated )
	class AFGResourceMiner* mResourceMiner;

	/** Reference to pending Vehicle (this is set when a client joins that left while in a game. This is used when the player joins so they can locally run their AttachDriver logic on the vehicle*/
	UPROPERTY( Replicated )
	class AFGDriveablePawn* mWaitingClientAttachDrivable;

	/** The best usable actor nearby. */
	UPROPERTY()
	class AActor* mBestUsableActor;

	/** Of the usable actor we are looking at, UPROPERTY to prevent the AdditionalData to be garbage collected */
	UPROPERTY( BlueprintReadOnly )
	FUseState mCachedUseState;

	UPROPERTY( BlueprintReadOnly )
	FUseState mPreviousCachedUseState;
	
	UPROPERTY( BlueprintReadOnly )
	FUseState mOldCachedUseState;
	
	/** Anim instance class to use in third person */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Character" )
	TSubclassOf< class UAnimInstance > mAnimInstanceClass;

	/** Anim instance class to use in first person */
	UPROPERTY( EditDefaultsOnly, Category = "Character" )
	TSubclassOf< class UAnimInstance > mAnimInstanceClass1P;

	/** time (in seconds) it takes to revive a fellow player */
	UPROPERTY( EditDefaultsOnly, Category = "Revive" )
	float mReviveDuration;

	/** @todo: This should not be specified for each pawn */
	UPROPERTY(EditDefaultsOnly, Instanced, Category= "Swimming")
	TArray< UFGDamageType* > mDrownDamageTypes;

	/** Time between each application of drowning damage (in seconds) */
	UPROPERTY( EditDefaultsOnly, Category = "Swimming" )
	float mDrownDamageInterval;

	/** The player that we are reviving */
	UPROPERTY( BlueprintReadOnly, Category = "Revive" )
	AFGCharacterPlayer* mPlayerToRevive;

	/** The pickup we are collecting */
	UPROPERTY( BlueprintReadOnly, Category = "Use" )
	class AFGItemPickup* mPickupToCollect;

	/** Default effects to play when a foot hits the ground when the material does not exist in m1PFootstepEffect */
	UPROPERTY( EditDefaultsOnly, Category = "Footstep" )
	FFootstepEffect m1PDefaultFootstepEffect;

	/** Effects to play when a foot hits the ground in first person */
	UPROPERTY( EditDefaultsOnly, Category = "Footstep" )
	TArray< FFootstepEffectSurface > m1PFootstepEffect;

	/** Effects to play when a foot hits the ground in first person */
	UPROPERTY( EditDefaultsOnly, Category = "Footstep" )
	TArray<class UAkAudioEvent*> m1PFootstepEvent;

	/** Info about creatures which currently perceive us. */
	UPROPERTY( BlueprintReadOnly, ReplicatedUsing = OnRep_ActorPerceptionInfo, Category = "UI" )
	TArray< FFGActorPlayerPerceptionInfo > mActorPerceptionInfo;
	
	/** latest safe ground location check timer */
	float mLastSafeGroundCheckTimer;

	static constexpr int32 MAX_SAFE_GROUND_POS_BUFFER_SIZE = 3;

	/** latest safe ground location positions */
	UPROPERTY( SaveGame )
	FVector mLastSafeGroundPositions[ MAX_SAFE_GROUND_POS_BUFFER_SIZE ];

	/** used for knowing which is the latest written safe ground position */
	UPROPERTY( SaveGame )
	int32 mLastSafeGroundPositionLoopHead = 0;

	/** The Hazmat suit does not exist as a native class so this member is here to identify it in code. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Default" )
	TSubclassOf< class UFGEquipmentDescriptor > mHazmatSuitClass;
	
	/** Mapping contexts for the player. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Input" )
	TArray< FPlayerMappingContext > mMappingContexts;	

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly)
	UMaterialInterface* mCompassMaterialInstance;

	/** Checks if this player has any holstered equipment */
	UFUNCTION( BlueprintCallable )
	bool HasHolsteredEquipment() const;

	/** Will return the index of the equipment holstered in the hand slot, of any. INDEX_NONE(-1) otherwise */
	UFUNCTION( BlueprintCallable )
	int32 GetHolsteredEquipmentIndex() const;

	UFUNCTION( BlueprintCallable, Server, Reliable )
	void Server_SetFlashlightState( const bool isFlashlightOn );

	UFUNCTION( BlueprintCallable )
	float GetHealthPercentage() const;

	UFUNCTION( BlueprintImplementableEvent )
	void StartPlayingWindAudio();

	UFUNCTION( BlueprintImplementableEvent )
	void StopPlayingWindAudio();

	UFUNCTION( BlueprintCallable )
	void ApplyDamagePostProcess();

	UFUNCTION()
	void AttemptToConnectCentralStorageDelegate();

	/** Used to start / stop the floor is lava timer. */
	void SetFloorIsLavaTimerActive( bool active );
	
private:
	/** Bound to mItemFilter to filter what items can be used in the inventory slots. */
	UFUNCTION()
	bool FilterInventoryClasses( TSubclassOf< UObject > object, int32 idx ) const;
	
	/** Function called whenever the floor is lava timer finishes. */
	UFUNCTION()
	void OnFloorIsLavaTimerFinished();

	bool IsValidMovementModeForFloorIsLava( EMovementMode movementMode, uint8 customMovementMode ) const;

	void InitializePreferredCameraMode();

	/** Character can unslide, no collision is blocking */
	void DoUnSlide();

	UFUNCTION()
	void OnUserSettingsUpdated();

	UFUNCTION( Client, Reliable )
	void Client_SetupHUD( AController* newController );
	
	UFUNCTION( Client, Reliable )
	void Client_RemoveHUD( AController* oldController );

	/** Interpolates the transition from 1p mode to 3p mode, and handles the camera offset to transition into and out of the head of the player. */
	UFUNCTION( BlueprintCallable, Category = "Camera" )
	void CameraTick( float deltaTime );

	void UpdateDamageIndicator( float deltaTime );

	void TickWindSpeedAudio();

	void HandleFlashlightToggle();

	void FadeDamageIndicator( float deltaTime );

	void TickFlashlight();

	void RadiationIntensityUpdated();

	bool IsPlayerInOrAboveWater( const FVector& hitPosition ) const;
	
protected:
	/** Player camera */
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	class UCameraComponent* mCameraComponent;
    
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "HUD" )
	TSoftClassPtr<UUserWidget> mPlayerHUDClass;

	/** Interpolation speed for the camera offset */
	UPROPERTY( BlueprintReadWrite, EditAnywhere, Category = "3rd Person Camera" )
	float mCameraOffsetInterpolationSpeed = 500.0f;

	/** Distance of camera from the player that we are interpolating to */
	UPROPERTY( BlueprintReadWrite, EditAnywhere, Category = "3rd Person Camera" )
	float mTargetCameraDistance = 300.0f;

	/** Camera offset from the player that we are interpolating to */
	UPROPERTY( BlueprintReadWrite, EditAnywhere, Category = "3rd Person Camera" )
	FVector mTargetCameraOffset;

	/** Camera FOV that we are interpolating to */
	UPROPERTY( BlueprintReadWrite, EditAnywhere, Category = "3rd Person Camera" )
	float mTargetCameraFOV = 90.0f;

	/** Interpolation speed for the FOV (in degrees/s) */
	UPROPERTY( EditAnywhere, Category = "3rd Person Camera" )
	float mCameraFOVInterpolationSpeed = 20.0f;

	/** Interpolation speed for the camera distance (units per second) */
	UPROPERTY( EditAnywhere, Category = "3rd Person Camera" )
	float mCameraDistanceInterpolationSpeed = 5.0f;

	/** Default FOV for the player */
	UPROPERTY( EditAnywhere, Category = "3rd Person Camera" )
	float mDefaultFOV = 90.0f;

	/** Target spring arm length when the player is in third person */
	UPROPERTY( EditAnywhere, Category = "3rd Person Camera" )
	float mCameraDistanceDefault3P = 300.0f;

	/** Camera distance to which the spring arm will be immediately snapped when transitioning from first person to third person to avoid clipping into the player's head */
	UPROPERTY( EditAnywhere, Category = "3rd Person Camera" )
	float mStartCameraDistance3PTransition{20.0f};

	/** Camera distance at which the transition to first person will snap the camera to the first person POV immediately */
	UPROPERTY( EditAnywhere, Category = "3rd Person Camera" )
	float mCutoffCameraDistance1PTransition{20.0f};

	/** Camera offset from the player when we are in third person */
	UPROPERTY( EditAnywhere, Category = "3rd Person Camera" )
	FVector mCameraOffset3P{0.0f, 40.0f, 0.0f};
	
	UPROPERTY( BlueprintReadWrite, EditAnywhere )
	float mLastDamageTime = -1.0;

	UPROPERTY( BlueprintReadWrite, EditAnywhere, Category = "TakeDamageFX" )
	float mCurrentDamageIndicator;

	UPROPERTY( BlueprintReadWrite, EditAnywhere, Category = "TakeDamageFX" )
	float mDesiredDamageIndicator;
	
	UPROPERTY( BlueprintReadWrite, EditAnywhere, Category = "TakeDamageFX" )
	float mDamageIndicatorSpeed = 5.0f;

	UPROPERTY( BlueprintReadWrite, EditAnywhere, Category = "TakeDamageFX" )
	float mMaxDamageIndicator = 2.0f;
	
private:
	UFUNCTION()
	void OnActiveEquipmentChangedInSlot( EEquipmentSlot slot );
	
	friend class AFGPlayerController;
	friend class UFGInventoryComponentEquipment;
	friend class AFGEquipment;

	/** Keeps track of the Flying Mode Setting. If this is true thee player can toggle Flying Mode on/off. */
	bool mFlyingIsToggleable = false;

	/** Basically just stores movement components bCheatFlying when we save the game so it can be applied when loading a game.
	 *	This is a pretty naive implementation but seems to work and has minimal effects on other systems.
	 *	DON'T RELY ON THIS AT RUNTIME. I don't feel its worth tracking this state during the whole session -K2 */
	// [ZolotukhinN:24/05/2024] This needs to be replicated to the client because we update the movement mode on both the client and the server
	UPROPERTY( SaveGame, Replicated )
	bool mIsCheatFlyingSaved = false;
	
	/** Tracks whether or not an interact widget is open. */
	bool mIsInteractWidgetOpen;
	
	/** The cinematic camera used in photo mode */
	UPROPERTY( Transient )
	class UFGCineCameraComponent* mCinematicCameraComponent;

	/** Spring arm for camera */
	UPROPERTY( EditAnywhere )
	class USpringArmComponent* mSpringArmComponent;

	/** This is the equipment we hold in our hands.*/
	UPROPERTY( ReplicatedUsing = OnRep_ActiveEquipments )
	TArray< class AFGEquipment* > mActiveEquipments;

	/** Simulated on the client so they know what to unequip. */
	UPROPERTY()
	TArray< class AFGEquipment* > mClientActiveEquipments;

	/** Current camera mode for the character */
	UPROPERTY()
	ECameraMode mCurrentCameraMode;

	/** Camera mode to which we are currently interpolating */
	UPROPERTY()
	ECameraMode mTargetCameraMode;

	/** What camera mode were we in before we opened the  */
	UPROPERTY( EditDefaultsOnly, Category = "Camera" )
	ECameraMode mPlayerPreferredCameraMode;

	UPROPERTY( SaveGame )
	UFGInventoryComponent* mInventory;
	
	bool mIsShoppingListDelegateBound = false;
	
	/** The players inventory that we use to upload items to central storage */
	UPROPERTY( SaveGame, EditDefaultsOnly )
	class UFGInventoryComponent* mUploadInventory;

	/** Arms equipment slot */
	UPROPERTY( SaveGame )
	UFGInventoryComponentEquipment* mArmsEquipmentSlot;

	/** Back equipment slot */
	UPROPERTY( SaveGame )
	UFGInventoryComponentEquipment* mBackEquipmentSlot;

	/** Legs equipment slot */
	UPROPERTY( SaveGame )
	UFGInventoryComponentEquipment* mLegsEquipmentSlot;

	/** Head equipment slot */
	UPROPERTY( SaveGame )
	UFGInventoryComponentEquipment* mHeadEquipmentSlot;

	/** Body equipment slot */
	UPROPERTY( SaveGame )
	UFGInventoryComponentEquipment* mBodyEquipmentSlot;

	/** The resource forms that are allowed in players inventory. */
	UPROPERTY( EditDefaultsOnly )
	TArray<EResourceForm> mAllowedResourceFormsInInventory;

	/** The players trash slot inventory. */
	UPROPERTY()
	UFGInventoryComponent* mTrashSlot;

	/** How long the player needs to stay off the ground for the floor is lava achievement. */
	UPROPERTY( EditDefaultsOnly, Category = "Achievement" )
	float mFloorIsLavaAchievementTimerDuration;

	/** Timer handle for the floor is lava achievement.*/
	FTimerHandle mFloorIsLavaTimerHandle;

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
	UPROPERTY()
	AFGCharacterPlayer* mReviver;

	/** Revive timer handle, started locally on revived clients to show progress */
	FTimerHandle mReviveTimerHandle;

	/** Cached walk head bob camera anim reference from the FGPlayerSettings */
	UPROPERTY( Transient )
	UCameraAnimationSequence* mDefaultWalkHeadBobCameraAnim;

	/** Cached sprint head bob camera anim reference from the FGPlayerSettings */
	UPROPERTY( Transient )
	UCameraAnimationSequence* mDefaultSprintHeadBobCameraAnim;

	/** Indicates if the player is sprinting and wants to use the sprint bobbing */
	bool mWantsSprintBobbing;

	/** Reference to the current head bob camera animation we should use */
	FCameraAnimationHandle mCurrentHeadBobCameraAnimHandle;

	/** Currently cached scale of the head bobbing animation, we re-start the montage if it changes */
	float mCurrentHeadBobScale{1.0f};

	/** Handle to the currently playing head bob animation */
	TWeakObjectPtr<class UCameraAnimationSequence> mCurrentHeadBobCameraAnim;

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

	/** How much time to wait after taking damage until health regeneration starts. */
	UPROPERTY( EditDefaultsOnly, Category = "HealthGeneration" )
	float mHealthGenerationWaitTime;

	/** Curve describing how much health should be regenerated over time based on the current health value.*/
	UPROPERTY( EditDefaultsOnly, Category = "HealthGeneration" )
	FRuntimeFloatCurve mHealthGenerationRateOverHealthAmount;

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

	/** The noise to make when sliding . */
	UPROPERTY( EditDefaultsOnly, Category = "FactoryGame|Movement|Slide" )
	TSubclassOf< class UFGNoise > mSlideNoise;
	
	/** How often to make the noise (in seconds) while sliding. */
	UPROPERTY( EditDefaultsOnly, Category = "FactoryGame|Movement|Slide" )
	float mSlideNoiseFrequency;

	FTimerHandle mSlideNoiseTimerHandle;

	/** New offset that we want to have */
	float mTargetCameraRelativeOffset;

	/* Old offset we are interpolating from */
	float mOldCameraRelativeOffset;

	float mSpringArmOffsetX; // Fetched during begin play from the spring arm, and used to be able to restore it's value later on.

	/** New offset that we want to have */
	float mCurrentCameraPipeOffset = 0;
	
	/** Representation of user setting */
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

	/** If enable the input vector will use the look direction as the forward vector */
	bool mIsUsingFull3DInput = false;

	/** How many enemies are engaged in combat with this character */
	UPROPERTY( Replicated )
	int32 mIncomingAttackers;

	FText mCachedLookAtDescription;

	UPROPERTY()
	class UFGEmote* mCurrentEmote;

	UPROPERTY()
	class UAkComponent* mCurrentEmoteSFX;

	UPROPERTY()
	UFGInteractWidget* mEmoteMenuWidget;

	UPROPERTY( VisibleDefaultsOnly, Category = Mesh )
	class USkeletalMeshComponent* mEmoteSkelMeshComp;

	FTimerHandle mEmoteSkelMeshTimer;
	
	EActionsToBind mBoundInputActionsMask;

	/** The timer we use to track upload of an item to central storage */
	UPROPERTY( SaveGame, Replicated ) 
	float mUploadTimer;
	
	// <FL> [PfaffN] Why are these variables public? Why nobody reviewed this code?
public:
	/** Whenever we should skip the next camera offset update */
	uint8 mSkipNextCameraOffsetUpdate : 1;
	/** Whenever we are partially submerged into the water volume and should not be allowed to crouch */
	uint8 mIsPartiallySubmergedInWater : 1;

	// <FL> [KajtaziT] temporary functions to allow to dynamically toggle bindings to aid design process
	UUserWidget* mActiveMenuWidget; // to determine if gamepad mapping context should be enbaled
	// </FL>

private:
	UPROPERTY( EditDefaultsOnly, Category = "Representation" )
	class UTexture2D* mActorRepresentationTexture;

	UPROPERTY( EditDefaultsOnly, Category = "Representation" )
	class UTexture2D* mActorRepresentationTextureDead;

	UPROPERTY( EditDefaultsOnly, Category = "Representation" )
	class UTexture2D* mActorRepresentationTextureOffline;

	/** This players actor representation */
	UPROPERTY( Transient )
	class UFGActorRepresentation* mCachedActorRepresentation;

	/** The indexed of the holstered hand equipment, if we have any. Replicated for UI use */
	UPROPERTY( SaveGame, Replicated )
	int32 mHolsteredEquipmentIndex = INDEX_NONE;

	TSet< EEquipmentSlot > mQueuedEquipmentChangedInSlotNotifies;

	/** The player name of the last logged in player that possessed this pawn */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_CachedPlayerName )
	FString mCachedPlayerName;

	/** Customization data for the player that has been cached the last time player was possessed by a player state */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_CachedPlayerCustomizationData )
	FPlayerCustomizationData mCachedPlayerCustomizationData;

	/** Default customization in case the player state is missing. */
	UPROPERTY( EditDefaultsOnly )
	FPlayerCustomizationData mDefaultPlayerCustomization;

	/** True if player is online. Update on both server and client By online we mean this player or the driven vehicle has a player state and someone is controlling it.
	 *	It does not care about platform logins */
	TOptional<bool> mIsPlayerOnline;
	
	UPROPERTY( ReplicatedUsing=OnRep_PendingHyperJunctionOutputConnection )
	FFGPipeHyperConnectionHistoryEntry mPendingHyperJunctionOutputConnection;

	/** The cache of all destinations picked by the player, used for network correction and movement simulation on other clients */
	UPROPERTY()
	TArray<FFGPipeHyperConnectionHistoryEntry> mPendingHyperJunctionOutputConnectionHistory;

	/** True if this character is controlled by the cinematic */
	UPROPERTY( EditAnywhere, Category = "Cinematic" )
	bool mCinematicControlled{false};

	/** Settings for the cinematic behavior of this character */
	UPROPERTY( EditAnywhere, Category = "Cinematic", meta = ( EditCondition = "mCinematicControlled", EditConditionHides ) )
	FFGCinematicPlayerSettings mCinematicPlayerSettings;
	
	/** Cinematic driver that is currently controlling this pawn. */
	UPROPERTY( VisibleInstanceOnly, Transient, Interp, BlueprintGetter = "GetCinematicDriver", Category = "Cinematic" )
	class UFGPlayerCinematicDriver* mCinematicDriver;

	UPROPERTY( SaveGame, Replicated )
	FFGPlayerPortalData mPortalData;

	/** Timer handle to snap the player to the portal exit transform */
	FTimerHandle mPortalSnapToExitTransformTimerHandle;

	/** True if we are currently simulating in editor, e.g. are in the active PIE session while being detached from the Player Controller. */
	bool mIsSimulatingInEditor{false};

	bool mShouldPlayWindSpeedAudio = false;

	/** True if the player is currently hidden and should not be visible */
	bool mPlayerVisibility{true};

	/** Set to the drop pod associated with the intro sequence if it is currently playing. That means they should be invincible, do not get aggro'd by the creatures, and not get saved into the save game */
	UPROPERTY( Transient )
	AFGStartingPod* mIntroSequenceStartingPod;
};
