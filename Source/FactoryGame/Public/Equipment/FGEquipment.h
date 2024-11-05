// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CameraAnimationCameraModifier.h"
#include "Blueprint/UserWidget.h"
#include "CharacterAnimationTypes.h"
#include "FGDynamicStruct.h"
#include "FGHealthComponent.h"
#include "FGLegacyItemStateActorInterface.h"
#include "FGSaveInterface.h"
#include "GameFramework/Actor.h"
#include "InputMappingContext.h"
#include "ItemAmount.h"
#include "Replication/FGReplicationDependencyActorInterface.h"
#include "PlayerCustomizationData.h"
#include "FGEquipment.generated.h"

class UCameraAnimationSequence;
class UAnimMontage;
class UAkAudioEvent;

// [ZolotukhinN:14/03/2023] Moved here from FGCharacterPlayer.h because it's used here and FGCharacterPlayer.h includes this header, so we cannot include it here
UENUM( BlueprintType )
enum class ECameraMode : uint8
{
	ECM_None,
	ECM_FirstPerson,
	ECM_ThirdPerson,
};

//Equipments are equip on different slots on the player. One EQ per slot. These are the slots.
UENUM( BlueprintType )
enum class EEquipmentSlot :uint8
{
	ES_NONE			UMETA( DisplayName = "Please specify a slot." ),
	ES_ARMS			UMETA( DisplayName = "Arms" ),
	ES_BACK			UMETA( DisplayName = "Back" ),
	ES_LEGS			UMETA( DisplayName = "Legs" ),
	ES_HEAD			UMETA( DisplayName = "Head" ),
	ES_BODY			UMETA( DisplayName = "Body" ),
	ES_MAX			UMETA( Hidden )
};

/** A type of default equipment action. */
UENUM( BlueprintType, Meta = ( Bitflags, UseEnumValuesAsMaskValuesInEditor = "true" ) )
enum class EDefaultEquipmentAction : uint8
{
	None			= 0			UMETA( Hidden ),
	
	PrimaryFire		= 1 << 0	UMETA( DisplayName = "Primary Fire" ),
	SecondaryFire	= 1 << 1	UMETA( DisplayName = "Secondary Fire" ),

	MAX							UMETA( Hidden ),
	ALL				= 0xFF		UMETA( Hidden )
};

ENUM_CLASS_FLAGS( EDefaultEquipmentAction )

/** Events for the default equipment actions. */
UENUM( BlueprintType )
enum class EDefaultEquipmentActionEvent : uint8
{
	Pressed		UMETA( DisplayName = "Pressed" ),
	Released	UMETA( DisplayName = "Released" ),
};

/**
 * Helper struct to store a list of materials for a Map using the mesh name as key
 * This is used at runtime to swap materials on equipment to support Panini WPO for fov inversion	
 */
USTRUCT()
struct FFirstPersonMaterialArray
{
	GENERATED_BODY()

	// List of materials with matching indices
	UPROPERTY( EditDefaultsOnly )
	TArray< class UMaterialInterface* > FirstPersonMaterials;
};

/** Montage that plays when you un-equip the equipment */
USTRUCT()
struct FEquipmentUnEquipMontage
{
	GENERATED_BODY()
	
	/** Audio event to play *on the character* when un-equipping */
	UPROPERTY( EditAnywhere, Category = "Audio" )
	UAkAudioEvent* AudioEvent{};

	/** Whenever there is a separate 3P audio event that should be used instead of the main one */
	UPROPERTY( EditAnywhere, Category = "Audio" )
	bool bSeparate3PAudioEvent{false};

	/** Audio event to be used when the character is in third person, instead of the main audio event. */
	UPROPERTY( EditAnywhere, Category = "Audio", meta = ( EditCondition = "bSeparate3PAudioEvent", EditConditionHides ) )
	UAkAudioEvent* AudioEvent3P{};
};

/**
 * Equipment montage combines a perspective aware montage on the character with the equipment montage
 */
USTRUCT( BlueprintType )
struct FFGEquipmentMontage
{
	GENERATED_BODY()

	/** Montage to play on the character in 1P */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Character" )
	UAnimMontage* Montage_1P{};

	/** Montage to play on the character in 3P */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Character" )
	UAnimMontage* Montage_3P{};

	/** Montage to play on the equipment mesh */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Equipment" )
	UAnimMontage* Montage_Equipment;

	/** Audio event to play when playing the montage. Will be played on the equipment location. */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Equipment" )
	UAkAudioEvent* AudioEvent{};

	/** Whenever there is a separate 3P audio event that should be used instead of the main one */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Equipment" )
	bool bSeparate3PAudioEvent{false};
	
	/** Audio event to be used when the character is in third person, instead of the main audio event. */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Equipment", meta = ( EditCondition = "bSeparate3PAudioEvent", EditConditionHides ) )
	UAkAudioEvent* AudioEvent3P{};

	/** Camera animation to play in first person. */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Character" )
	UCameraAnimationSequence* CameraAnim{};
};

/**
 * Equipment montage with a weight attached to it, used for randomizing the animations
 */
USTRUCT( BlueprintType )
struct FFGWeightedEquipmentMontage : public FFGEquipmentMontage
{
	GENERATED_BODY()

	/** Weight of this montage among other montages */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Weight" )
	float Weight{1.0f};

	/** When true, this montage will be filtered based on the tag */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Weight" )
	bool Filter{false};

	/** Tag use as a filter for this montage. Owner equipment defines the available options. */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Weight", meta = ( EditCondition = "Filter", EditConditionHides, GetOptions = "GetAvailableMontageTags" ) )
	FName FilterMontageTag;

	/** When true, the filter montage tag condition is inverted */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Weight", meta = ( EditCondition = "Filter", EditConditionHides ) )
	bool InvertFilter{false};

	/** When true and this montage is not filtered out, it will have higher priority over other non-exclusive montages */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Weight", meta = ( EditCondition = "Filter", EditConditionHides ) )
	bool Exclusive{false};
};

/** Array of equipment montages with specified weights */
USTRUCT( BlueprintType )
struct FFGWeightedEquipmentMontageArray
{
	GENERATED_BODY()

	/** A collection of all montages */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Equipment Montages", meta = ( ShowOnlyInnerProperties ) )
	TArray<FFGWeightedEquipmentMontage> Montages;
};

/**
 * Base class for all kinds of equipment in the game.
 */
UCLASS( meta = (AutoJson = true) )
class FACTORYGAME_API AFGEquipment : public AActor, public IFGSaveInterface, public IFGReplicationDependencyActorInterface, public IFGLegacyItemStateActorInterface
{
	GENERATED_BODY()
public:
	AFGEquipment();

	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void PreReplication( IRepChangedPropertyTracker & ChangedPropertyTracker ) override;
	virtual void OnRep_AttachmentReplication() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	// End AActor interface

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface
	
	// Begin IFGLegacyItemStateActorInterface
	virtual FFGDynamicStruct ConvertToItemState( TSubclassOf<UFGItemDescriptor> itemDescriptor ) const override;
	// End IFGLegacyItemStateActorInterface

	/** Equips the equipment. */
	UFUNCTION( BlueprintCallable, Category = "Equipment" )
	virtual void Equip( class AFGCharacterPlayer* character );
	/** Put the equipment away. */
	UFUNCTION( BlueprintCallable, Category = "Equipment" )
	virtual void UnEquip();

	/** Called whenever the character changes movement mode. */
	virtual void OnCharacterMovementModeChanged( EMovementMode PreviousMovementMode, uint8 PreviousCustomMode, EMovementMode NewMovementMode, uint8 NewCustomMode );

	/* Updates primitive values on all UPrimitive components.*/
	void UpdatePrimitiveColors(FLinearColor Primary, FLinearColor Secondary, FLinearColor Detail);

	/** Updates materials based on the camera mode */
	UFUNCTION( BlueprintCallable, Category = "Equipment" )
	void UpdateMaterialsFromCameraMode();

	UFUNCTION( BlueprintCallable, Category= "Equipment" )
	virtual void DisableEquipment();

	UFUNCTION(BlueprintNativeEvent)
	void SetupTrinketMeshes(bool bIsLocalInstigator, USkeletalMesh* TrinketChainMesh, FName TrinketChainSocketName, UStaticMesh* TrinketMesh, FName TrinketSocketName);
	
	/**
	 * Is this equipment equipped.
	 * @return - true if equipped; otherwise false.
	 */
	UFUNCTION( BlueprintPure, Category = "Equipment" )
	FORCEINLINE bool IsEquipped() const { return mPlayerCharacter != nullptr; }

	/**
	 * Convenience blueprint function to return Instigator as a FGCharacterPlayer
	 * @return The instigator for this equipment; nullptr if not equipped or Instigator is not an FGCharacterPlayer.
	 */
	UFUNCTION( BlueprintPure, Category = "Equipment" )
	class AFGCharacterPlayer* GetInstigatorCharacter() const;

	/** Applies player customization data to this piece of equipment. Automatically called when our customization data updates for equipped equipments. */
	void ApplyPlayerCustomizationData( const FPlayerCustomizationData& NewCustomizationData );
	
	/** 
	 * @return Is the instigator locally controlled; false if no instigator.
	 */
	UFUNCTION( BlueprintPure, Category = "Equipment" )
	bool IsLocalInstigator() const;

	/** Attempts to load the state of this equipment from the item state */
	UFUNCTION( BlueprintNativeEvent, Category = "Equipment" )
	void LoadFromItemState( const FFGDynamicStruct& itemState );

	/** Saves the state of this equipment to the item state */
	UFUNCTION( BlueprintNativeEvent, Category = "Equipment" )
	FFGDynamicStruct SaveToItemState() const;

	/** Flushes the current equipment state to the item associated with it */
	UFUNCTION( BlueprintCallable, Category = "Equipment" )
	void FlushItemState();
	
	/** Get the arms animation to play on the player */
	FORCEINLINE EArmEquipment GetArmsAnimation() const{ return mArmAnimation; }

	/** Get the back animation to play on the player */
	FORCEINLINE EBackEquipment GetBackAnimation() const{ return mBackAnimation; }
	
	/**
	 * Called whenever our owner is damaged and gives us a chance to adjust it
	 * SERVER ONLY
	 *
	 * @param damageAmount - how much damage we receive
	 * @param damageType - what damage type the damage is that we receive
	 * @param instigatedBy - who instigated the damage (Controller)
	 * @param damageCauser - the actor who damaged us
	 * @return the adjusted damage
	 **/
	UFUNCTION( BlueprintNativeEvent, CustomEventUsing = mHave_AdjustDamage, Category = "Damage" )
	float AdjustDamage( const float damageAmount, const class UDamageType* damageType, class AController* instigatedBy, AActor* damageCauser );

	/** When using this equipment, the character use distance will be increased to this amount. */
	UFUNCTION( BlueprintPure, Category = "Equipment" )
    virtual float GetCharacterUseDistanceOverride() const { return 0.0f; }

	/** When using this equipment, checks if the character is allowed to use things */
	UFUNCTION( BlueprintPure, BlueprintNativeEvent, Category = "Equipment" )
	bool CanPickBestUsableActor() const;

	/** Returns the enum for the equipment slot, ARMS, BACK etc. */
	UFUNCTION( BlueprintPure, Category = "Equipment" )
	static EEquipmentSlot GetEquipmentSlot( TSubclassOf< AFGEquipment > inClass );

	/** Called after the spawning of this equipment to spawn any child dependencies */
	void SpawnChildEquipment();

	/** Should we play stinger animation */
	UFUNCTION( BlueprintPure, Category = "Equipment" )
	bool ShouldShowStinger() const;

	/** Sets if this is the first time this was equipped */
	void SetFirstTimeEquipped( const bool firstTime ) { mFirstTimeEquipped = firstTime; }

	/** @return idle pose animation, can be NULL */
	UFUNCTION( BlueprintPure, Category = "Animation" )
	class UAnimSequence* GetIdlePoseAnimation() const { return mIdlePoseAnimation; }

	/** @return idle pose animation for 3p, can be NULL */
	UFUNCTION( BlueprintPure, Category = "Animation" )
	class UAnimSequence* GetIdlePoseAnimation3p() const { return mIdlePoseAnimation3p; }

	/** @return crouch pose animation for 3p, can be NULL */
	UFUNCTION( BlueprintPure, Category = "Animation" )
    class UAnimSequence* GetCrouchPoseAnimation3p() const { return mCrouchPoseAnimation3p; }

	/** @return slide pose animation for 3p, can be NULL */
	UFUNCTION( BlueprintPure, Category = "Animation" )
    class UAnimSequence* GetSlidePoseAnimation3p() const { return mSlidePoseAnimation3p; }

	/** @return idle pose animation for 3p, can be NULL */
	UFUNCTION( BlueprintPure, Category = "Animation" )
    class UAimOffsetBlendSpace* GetAttachmentIdleAO() const { return mAttachmentIdleAO; }

	/** Called when the equipment was removed from it's equipment slot */
	UFUNCTION( BlueprintNativeEvent, Category = "Equipment" )
	void WasRemovedFromSlot();

	/** Called when the equipment was moved to it's equipment slot (this can happen without necessarily switching to that slot thus equipping the equipment) */
	UFUNCTION( BlueprintNativeEvent, Category = "Equipment" )
	void WasSlottedIn( class AFGCharacterPlayer* holder );

	UFUNCTION( BlueprintPure, Category = "Equipment" )
	virtual void GetSupportedConsumableTypes(TArray<TSubclassOf<UFGItemDescriptor>>& out_itemDescriptors) const;
	
	UFUNCTION( BlueprintPure, Category = "Equipment" )
	virtual TSubclassOf<UFGItemDescriptor> GetSelectedConsumableType() const;
	
	UFUNCTION( BlueprintCallable, Category = "Equipment" )
	virtual void SetSelectedConsumableType( const TSubclassOf<UFGItemDescriptor> selectedConsumableType );

	FORCEINLINE UInputMappingContext* GetMappingContext() const { return mMappingContext; }
	int32 GetMappingContextPriority() const;

	FORCEINLINE bool IsMappingContextApplied() const { return mIsMappingContextApplied; }

	/** Returns the current camera mode of the player the equipment is attached to. Will return ECM_None if not equipped */
	UFUNCTION( BlueprintPure, Category = "Equipment" )
	ECameraMode GetInstigatorCameraMode() const;

	/**
	 * Called when the camera mode of the player having the equipment changes to third or first person
	 * This is called before the character mesh visibility changes, so the anim instance of the old camera mode is still active.
	 */
	UFUNCTION( BlueprintNativeEvent, Category = "Equipment" )
	void OnCameraModeChanged( ECameraMode newCameraMode );

	/** Called to update the equipment visibility based on the external conditions such as player visibility and/or status (e.g. hand equipments are hidden inside of the hyper tube) */
	UFUNCTION( BlueprintNativeEvent, Category = "Equipment" )
	void SetEquipmentVisibility( bool bNewEquipmentVisible );

	/**
	 * Called after the camera mode has changed and the mesh visibility changes have been handled.
	 * Good place to re-apply data harvested from the old character mesh to the new character mesh.
	 */
	UFUNCTION( BlueprintNativeEvent, Category = "Equipment" )
	void OnPostCameraModeChanged( ECameraMode newCameraMode );

	const TArray< FItemAmount >& GetCostToUse() const { return mCostToUse; }

	FORCEINLINE FText GetEquipmentLookAtDescOverride() const { return mEquipmentLookAtDescOverride; }

	/** Called whenever an interact widget gets added or removed. */
    virtual void OnInteractWidgetAddedOrRemoved( class UFGInteractWidget* widget, bool added );

	/** Allows the equipment to intercept the shortcut pressed event. Return true if the event was handled by the equipment */
	virtual bool OnShortcutPressed( int32 shortcutIndex ) { return false; }

	/** Plays the specified montage on this equipment. Returns the length of the first played equipment montage */
	UFUNCTION( BlueprintCallable, Category = "Equipment" )
	void PlayEquipmentMontage( const FFGEquipmentMontage& equipmentMontage );

	/** Returns the character animation montage active for the current camera mode inside of the provided equipment montage */
	UFUNCTION( BlueprintPure, Category = "Equipment" )
	UAnimMontage* GetActiveCharacterAnimMontage( const FFGEquipmentMontage& equipmentMontage ) const;

	/** Returns the active character animation montage for the weighted montage provided */
	UFUNCTION( BlueprintPure, Category = "Equipment" )
	UAnimMontage* GetActiveCharacterAnimMontageWeighted( const FFGWeightedEquipmentMontage& equipmentMontage ) const;

	/** Returns true if the filters for the provided montage match the current state of the equipment */
	UFUNCTION( BlueprintPure, Category = "Equipment" )
	bool IsEquipmentMontageAllowed( const FFGWeightedEquipmentMontage& montage ) const;

	/** Gives the equipment an opportunity to filter the weighted montages based on their tag */
	UFUNCTION( BlueprintNativeEvent, Category = "Equipment" )
	bool IsEquipmentMontageTagAllowed( FName montageTag ) const;

	/** Functions used to get a list of available montage tags for filtering */
	UFUNCTION( BlueprintNativeEvent, Category = "Equipment" )
	TArray<FString> GetAvailableMontageTags() const;
	
	/** Plays one of the montages from the weighted montages collection, returns the montage length and the tag of the montage that was played */
	UFUNCTION( BlueprintCallable, Category = "Equipment" )
	void PlayWeightedEquipmentMontage( const FFGWeightedEquipmentMontageArray& montageArray, FFGWeightedEquipmentMontage& out_pickedMontage );
	
	/** Plays camera animation sequence for the local player in 1P, otherwise does nothing */
	UFUNCTION( BlueprintCallable, Category = "Equipment" )
	void PlayCameraAnimation( class UCameraAnimationSequence* cameraAnimationSequence );
	
	/** Plays the un-equip montage and sound */
	void PlayUnEquipMontage() const;

	/** Returns the currently active arm equipment animation */
	UFUNCTION( BlueprintPure, Category = "Equipment" )
	EArmEquipment GetCurrentArmEquipmentAnimation() const;

	/** Returns the equip montage that we played when the equipment was equipped */
	UFUNCTION( BlueprintPure, Category = "Equipment" )
	FFGWeightedEquipmentMontage GetPlayedEquipMontage() const;

	/** Stops the currently running equipment montage (both on the equipment and on the player character), and also stops all currently playing equipment sounds */
	UFUNCTION( BlueprintCallable, Category = "Equipment" )
	void StopCurrentEquipmentMontage( bool bStopSounds = true );

	/** Used to trigger a default equipment action. */
	void TriggerDefaultEquipmentActionEvent( EDefaultEquipmentAction action, EDefaultEquipmentActionEvent actionEvent );

	/** Called when the equipment is spawned to initialize it with the owner */
	void OnEquipmentSpawned( AFGCharacterPlayer* equipmentOwner );
protected:
	UFUNCTION( Server, Reliable )
	void Server_TriggerDefaultEquipmentActionEvent( EDefaultEquipmentAction action, EDefaultEquipmentActionEvent actionEvent );
	
	/** Native handler for a default action event for an equipment. Gets called on both Server and Client. */
	virtual void HandleDefaultEquipmentActionEvent( EDefaultEquipmentAction action, EDefaultEquipmentActionEvent actionEvent );

	/** Blueprint handler for a default action event for an equipment. Gets called on both Server and Client. */
	UFUNCTION( BlueprintImplementableEvent, Category = "Equipment" )
	void DoHandleDefaultEquipmentActionEvent( EDefaultEquipmentAction action, EDefaultEquipmentActionEvent actionEvent );
	
	/** Was the equipment equipped. */
	UFUNCTION( BlueprintNativeEvent, Category = "Equipment" )
	void WasEquipped();
	/** Was the equipment put away. */
	UFUNCTION( BlueprintNativeEvent, Category = "Equipment" )
	void WasUnEquipped();

	UFUNCTION()
    virtual void OnCharacterRagdollStateChanged( bool isRagdolled );
	
	/** Sets tick status for actor and all components */
	void SetEquipmentTicks( bool inTick );

	/** Add custom bindings for this equipment */
	virtual void AddEquipmentActionBindings();
	/** Clear all action bindings for this equipment, meaning that we will remove all inputs we are listening for */
	void ClearEquipmentActionBindings();

	/** True if we can afford the cost of using this equipment */
	UFUNCTION( BlueprintCallable, Category = "Equipment" )
	bool CanAffordUse() const;

	/** Called if we could not afford to use the equipment */
	UFUNCTION( BlueprintNativeEvent, Category = "Equipment" )
	void DidNotAffordUse();

	/** Consumes the cost of using this equipment, will call Server_ChargeForUse if we don't have authority */
	UFUNCTION( BlueprintCallable, Category = "Equipment" )
	void ChargeForUse();

	/** Will call ChargeForUse_Internal on server */
	UFUNCTION( Server, Reliable, WithValidation )
	void Server_ChargeForUse();

	/** Does the actual charging of cost on both server and client */
	void ChargeForUse_Internal();

	UFUNCTION()
	void OnChildEquipmentReplicated();
	
	/** Used to apply / remove the mapping context for this equipment. */
	void SetMappingContextApplied( bool applied );

	/** Input Actions */
	void Input_DefaultPrimaryFire( const FInputActionValue& actionValue );
	void Input_DefaultSecondaryFire( const FInputActionValue& actionValue );

	/** Adds an entry into the first person component to material map. This is used for equipments (decorations) that don't know there mesh until runtime */
	UFUNCTION( BlueprintCallable, Category="Equipment" )
	void AddFirstPersonComponentAndMaterialsEntry( FName compName, TArray< class UMaterialInterface* > firstPersonMaterials );

public:
	/** To what slot is this limited to? */
	UPROPERTY( EditDefaultsOnly, Category = "Equipment" )
	EEquipmentSlot mEquipmentSlot;

	/** Camera shake to play when sprinting */
	UPROPERTY( EditDefaultsOnly, Category = "Equipment" )
	UCameraAnimationSequence* mSprintHeadBobCameraAnim;

	/** Montages to play when the equipment is equipped */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Equipment|Animation" )
	FFGWeightedEquipmentMontageArray mEquipMontage;

	/** True if this equipment has a separate stinger montage that can be played */
	UPROPERTY( EditDefaultsOnly, Category = "Equipment|Animation" )
	bool mHasStingerMontage{false};
	
	/** Montage to play when equipping the equipment for the first time */
	UPROPERTY( EditDefaultsOnly, Category = "Equipment|Animation", meta = ( EditCondition = "mHasStingerMontage", EditConditionHides ) )
	FFGWeightedEquipmentMontageArray mStingerMontage;
	
	/** Montages to play when the equipment is un-equipped. Will also stop all other montages started before. */
	UPROPERTY( EditDefaultsOnly, Category = "Equipment|Animation" )
	FEquipmentUnEquipMontage mUnEquipMontage;
	
	/** Holds a reference to the child equipment that may be spawned with this */
	UPROPERTY( Replicated, ReplicatedUsing=OnChildEquipmentReplicated )
	class AFGEquipmentChild* mChildEquipment;

	UPROPERTY(EditDefaultsOnly)
	float mMontageBlendOutTime = 0.f;

protected:
	/** Needed for validating the data */
	friend class UFGEquipmentValidator;

	/** The AnimBlueprint class to use for the 1p anim for our pawn, specifying none here means that the pawn default 1p anim will be used */
	UPROPERTY( EditDefaultsOnly, Category = "Equipment|Animation|Pose" )
	TSubclassOf< class UAnimInstance > m1PAnimClass;

	/** If this equipment should attach to a socket, this is the socket. */
	UPROPERTY( EditDefaultsOnly, Category = "Equipment" )
	FName mAttachSocket;

	/** Each Mesh Component should have an entry here to remap its materials to the First person material (one with the panini switch enabled) */
	UPROPERTY( EditDefaultsOnly, Category = "Equipment")
	TMap< FName, FFirstPersonMaterialArray > mComponentNameToFirstPersonMaterials;

	// TODO: Get rid of child equipment logic
	/** The class (if any) to use to spawn a child equipment */
	UPROPERTY( EditDefaultsOnly, Category = "Equipment" )
	TSubclassOf< class AFGEquipmentChild > mChildEquipmentClass;

	/** Whether or not this equipment needs the default equipment mapping context. */
	UPROPERTY( EditDefaultsOnly, Category = "Equipment" )
	bool mNeedsDefaultEquipmentMappingContext;
	
	//@todo FIXUP Remove BlueprintReadOnly
	/** The cost of using this equipment */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Equipment" )
	TArray< FItemAmount > mCostToUse;

	/** Arms animation this should play on the when the equipment is equipped (only used if mEquipmentSlot == ES_ARMS) */
	UPROPERTY( EditDefaultsOnly, Category = "Equipment", meta = ( EditCondition = "mEquipmentSlot == EEquipmentSlot::ES_ARMS", EditConditionHides, DisplayPriority = 1 ) )
	EArmEquipment mArmAnimation;

	/** Arms animation this should play on the when the equipment is equipped (only used if mEquipmentSlot == ES_BACK) */
	UPROPERTY( EditDefaultsOnly, Category = "Equipment", meta = ( EditCondition = "mEquipmentSlot == EEquipmentSlot::ES_BACK", EditConditionHides, DisplayPriority = 1 ) )
	EBackEquipment mBackAnimation;
	
	/** The equipment's input mapping context which gets applied when equipping it. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Input" )
	TObjectPtr<UInputMappingContext> mMappingContext;

	/** What default equipment actions to enable. */
	UPROPERTY( EditDefaultsOnly, meta = ( Bitmask, BitmaskEnum = "EDefaultEquipmentAction" ), Category = "Equipment" )
	uint8 mDefaultEquipmentActions;

	/** The equip montage that was played when the equipment was equipped */
	UPROPERTY( VisibleInstanceOnly, Category = "Equipment", Transient )
	FFGWeightedEquipmentMontage mPickedEquipMontage;
private:
	/** True if we have a blueprint version of some functions */
	uint8 mHave_AdjustDamage : 1;

	/** Was this the first time equipping this */
	uint8 mFirstTimeEquipped : 1;

	/** Idle animation to play when equipped. Can be null if we don't want to play any special animation */
	UPROPERTY( EditDefaultsOnly, Category = "Equipment|Animation" )
	class UAnimSequence* mIdlePoseAnimation;

	/** Idle animation to play when equipped in 3p. Can be null if we don't want to play any special animation */
	UPROPERTY( EditDefaultsOnly, Category = "Equipment|Animation" )
	class UAnimSequence* mIdlePoseAnimation3p;

	/** Crouch animation to play when equipped in 3p. Can be null if we don't want to play any special animation */
	UPROPERTY( EditDefaultsOnly, Category = "Equipment|Animation" )
	class UAnimSequence* mCrouchPoseAnimation3p;

	/** Slide animation to play when equipped in 3p. Can be null if we don't want to play any special animation */
	UPROPERTY( EditDefaultsOnly, Category = "Equipment|Animation" )
	class UAnimSequence* mSlidePoseAnimation3p;

	/** Aim offset to override with */
	UPROPERTY( EditDefaultsOnly, Category = "Equipment|Animation" )
	class UAimOffsetBlendSpace* mAttachmentIdleAO;

	/** List of damages modifiers that this equipment applies upon equip (and removes once unequipped).
	 *Used to modify the amount of damages inbound from specific types of damages. */
	UPROPERTY(EditDefaultsOnly, Category= "Equipment" )
	TArray<FDamageModifier> mReceivedDamageModifiers;

	/** Materials that were swapped out during the change of the POV to first person */
	UPROPERTY( VisibleInstanceOnly, Category = "Equipment" )
	TMap<FName, FFirstPersonMaterialArray> mSwappedOutThirdPersonMaterials;

	/** The character that equipped us. */
	UPROPERTY()
	AFGCharacterPlayer* mPlayerCharacter;

	FCameraAnimationHandle CameraAnimationHandle;
	
	/** Used if we want to override the GetLookAtDescription for resource nodes with this equipment. Added for the AFGPortableMinerDispenser
	 * but figured we could use it for other equipment as well so put it here. {Ore}. {Purity} are relevant format specifiers for this text */
	UPROPERTY( EditDefaultsOnly, Category = "Equipment" )
	FText mEquipmentLookAtDescOverride;
	
	/** Whether or not the mapping contexts for this equipment are applied. */
	bool mIsMappingContextApplied;
};
