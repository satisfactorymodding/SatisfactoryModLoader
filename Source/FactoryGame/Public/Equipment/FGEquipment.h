// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "GameFramework/Actor.h"
#include "ItemAmount.h"
#include "FGSaveInterface.h"
#include "CharacterAnimationTypes.h"
#include "Replication/FGReplicationDependencyActorInterface.h"
#include "FGEquipment.generated.h"

//Equipments are equip on different slots on the player. One EQ per slot. These are the slots.
UENUM( BlueprintType )
enum class EEquipmentSlot :uint8
{
	ES_NONE			UMETA( DisplayName = "Please specify a slot." ),
	ES_ARMS			UMETA( DisplayName = "Arms" ),
	ES_BACK			UMETA( DisplayName = "Body" ),
	ES_MAX			UMETA( Hidden )
};


/**
 * Base class for all kinds of equipment in the game.
 */
UCLASS( meta = (AutoJson = true) )
class FACTORYGAME_API AFGEquipment : public AActor, public IFGSaveInterface, public IFGReplicationDependencyActorInterface
{
	GENERATED_BODY()
public:
	AFGEquipment();

	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void PreReplication( IRepChangedPropertyTracker & ChangedPropertyTracker ) override;
	virtual void BeginPlay() override;
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

	/** Equips the equipment. */
	UFUNCTION( BlueprintCallable, Category = "Equipment" )
	virtual void Equip( class AFGCharacterPlayer* character );
	/** Put the equipment away. */
	UFUNCTION( BlueprintCallable, Category = "Equipment" )
	virtual void UnEquip();

	/** Called whenever the character changes movement mode. */
	virtual void OnCharacterMovementModeChanged( EMovementMode PreviousMovementMode, uint8 PreviousCustomMode, EMovementMode NewMovementMode, uint8 NewCustomMode );

	/** Called on the owner, client or server but not both. */
	void OnDefaultPrimaryFirePressed();

	/** Only server implementation of primary fire */
	UFUNCTION( Server, Reliable, WithValidation )
	void Server_DefaultPrimaryFire();

	/** BP hook for implementing what should actually happen when pressing fire */
	UFUNCTION( BlueprintImplementableEvent, Category = "Equipment" )
	void DoDefaultPrimaryFire();

	/** Plays effects when using default primary fire */
	UFUNCTION( BlueprintImplementableEvent, Category = "Equipment" )
	void DoDefaultPrimaryFireEffects();

	/** Native only function that does default stuff needed for the default primary fire event */
	UFUNCTION()
	virtual void DoDefaultPrimaryFire_Native();

	/** Native only function that does default stuff needed for the default primary fire event */
	UFUNCTION( BlueprintNativeEvent, Category = "Equipment" )
	bool CanDoDefaultPrimaryFire();

	UFUNCTION( BlueprintCallable, Category= "Equipment" )
	virtual void DisableEquipment();
	
	/**
	 * Is this equipment equipped.
	 * @return - true if equiped; otherwise false.
	 */
	UFUNCTION( BlueprintPure, Category = "Equipment" )
	FORCEINLINE bool IsEquipped() const { return GetInstigator() != nullptr; }

	/**
	 * Convenience blueprint function to return Instigator as a FGCharacterPlayer
	 * @return The instigator for this equipment; nullptr if not equipped or Instigator is not an FGCharacterPlayer.
	 */
	UFUNCTION( BlueprintPure, Category = "Equipment" )
	class AFGCharacterPlayer* GetInstigatorCharacter() const;

	/** 
	 * @return Is the instigator locally controlled; false if no instigator.
	 */
	UFUNCTION( BlueprintPure, Category = "Equipment" )
	bool IsLocalInstigator() const;

	/**
	 * If this equipment has a state that should be saved when unequipped.
	 * @todo Refine this for equipments that could have a null state, i.e. unloaded weapons can be discarded but loaded weapons need to be saved.
	 * @todo Expose to blurre for mods.
	 */
	virtual bool ShouldSaveState() const;

	/** Sets the current attachment for this weapon */
	void SetAttachment( class AFGEquipmentAttachment* newAttachment );

	/** Sets the current attachment for this weapon */
	void SetSecondaryAttachment( class AFGEquipmentAttachment* newAttachment );

	/** Get the arms animation to play on the player */
	FORCEINLINE EArmEquipment GetArmsAnimation() const{ return mArmAnimation; }

	/** Get the back animation to play on the player */
	FORCEINLINE EBackEquipment GetBackAnimation() const{ return mBackAnimation; }

	/**
	 * Get the attachment for this equipment.
	 */
	UFUNCTION( BlueprintCallable, Category = "Equipment" )
	FORCEINLINE class AFGEquipmentAttachment* GetAttachment() const { return mAttachment; }

	UFUNCTION( BlueprintCallable, Category = "Equipment" )
	FORCEINLINE class AFGEquipmentAttachment* GetSecondaryAttachment() const { return mSecondaryAttachment; }

	/**
	 * Get the attachment for this equipment.
	 * @return - The attachment; nullptr if attachment is not a child of class C.
	 */
	template< class C >
	FORCEINLINE C* GetAttachment() const { return Cast< C >( mAttachment ); }
	
	/**
	* Get the secondary attachment for this equipment.
	* @return - The attachment; nullptr if attachment is not a child of class C.
	*/
	template< class C >
	FORCEINLINE C* GetSecondaryAttachment() const { return Cast< C >( mSecondaryAttachment ); }

	/**
	 * This is called to update the relevant attachments' use state so that animations can be played etc.
	 */
	UFUNCTION( BlueprintCallable, Server, Reliable, WithValidation, Category = "Equipment" )
	void Server_UpdateAttachmentUseState( int newUseState );

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
	float AdjustDamage( float damageAmount, const class UDamageType* damageType, class AController* instigatedBy, AActor* damageCauser );

	/** When using this equipment, the character use distance will be increased to this amount. */
	UFUNCTION( BlueprintPure, Category = "Equipment" )
    virtual float GetCharacterUseDistanceOverride() const { return 0.0f; }

	/** Returns the enum for the equipment slot, ARMS, BACK etc. */
	UFUNCTION( BlueprintPure, Category = "Equipment" )
	static EEquipmentSlot GetEquipmentSlot( TSubclassOf< AFGEquipment > inClass );

	/** Called after the spawning of this equipment to spawn any child dependencies */
	void SpawnChildEquipment();

	/** Should we play stinger animation */
	UFUNCTION( BlueprintPure, Category = "Equipment" )
	FORCEINLINE bool ShouldShowStinger() { return mFirstTimeEquipped; }

	/** Sets if this is the first time this was equipped */
	void SetFirstTimeEquipped( bool firstTime ) { mFirstTimeEquipped = firstTime; }

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
	
protected:
	/** Was the equipment equipped. */
	UFUNCTION( BlueprintNativeEvent, Category = "Equipment" )
	void WasEquipped();
	/** Was the equipment put away. */
	UFUNCTION( BlueprintNativeEvent, Category = "Equipment" )
	void WasUnEquipped();

	/** Add HUD that this equipment needs */
	void AddEquipmentHUD();
	/** Removes HUD for the equipment */
	void RemoveEquipmentHUD();

	/** Sets tick status for actor and all components */
	void SetEquipmentTicks( bool inTick );

	/** Helper for binding actions and setting their consume status */
	template< class UserClass >
	FORCEINLINE void BindActionHelper( const FName ActionName, const EInputEvent KeyEvent, UserClass* Object, typename FInputActionHandlerSignature::TUObjectMethodDelegate< UserClass >::FMethodPtr Func, bool consumeInput )
	{
		FInputActionBinding& inputAction = InputComponent->BindAction( ActionName, KeyEvent, Object, Func );

		inputAction.bConsumeInput = consumeInput;
	}

	/** Add custom bindings for this equipment */
	virtual void AddEquipmentActionBindings();
	/** Clear all action bindings for this equipment, meaning that we will remove all inputs we are listening for */
	void ClearEquipmentActionBindings();

	/** True if we can afford the cost of using this equipment */
	UFUNCTION( BlueprintCallable, Category = "Equipment" )
	bool CanAffordUse() const;

	/** Called if we couldn't afford to use the equipment */
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

public:
	/** This is the attachment for this class */
	UPROPERTY( EditDefaultsOnly, Category = "Equipment" )
	TSubclassOf< class AFGEquipmentAttachment > mAttachmentClass;

	/** This is the secondary attachment for this class */
	UPROPERTY( EditDefaultsOnly, Category = "Equipment" )
	TSubclassOf< class AFGEquipmentAttachment > mSecondaryAttachmentClass;

	/** To what slot is this limited to? */
	UPROPERTY( EditDefaultsOnly, Category = "Equipment" )
	EEquipmentSlot mEquipmentSlot;

	/** Camera shake to play when sprinting */
	UPROPERTY( EditDefaultsOnly, Category = "Equipment" )
	TSubclassOf< class UMatineeCameraShake > mSprintHeadBobShake;

	//@todo Are these used by Joel or legacy?
	/** Sound played when equipping */
	UPROPERTY( EditDefaultsOnly, Category = "Sound" )
	class UAkAudioEvent* mEquipSound;

	/** Sound played when unequipping */
	UPROPERTY( EditDefaultsOnly, Category = "Sound" )
	class UAkAudioEvent* mUnequipSound;

	/** Class of widget to add when equipping this equipment */
	UPROPERTY( EditDefaultsOnly, Category = "UI" )
	TSubclassOf< UUserWidget > mEquipmentWidget;

	/** Holds a reference to the child equipment that may be spawned with this */
	UPROPERTY( Replicated, ReplicatedUsing=OnChildEquipmentReplicated )
	class AFGEquipmentChild* mChildEquipment;

protected:
	/** The AnimBlueprint class to use for the 1p anim for our pawn, specifying none here means that the pawn default 1p anim will be used */
	UPROPERTY( EditDefaultsOnly, Category = "Equipment" )
	TSubclassOf< class UAnimInstance > m1PAnimClass;

	/** If this equipment should attach to a socket, this is the socket. */
	UPROPERTY( EditDefaultsOnly, Category = "Equipment" )
	FName mAttachSocket;

	/** The class (if any) to use to spawn a child equipment */
	UPROPERTY( EditDefaultsOnly, Category = "Equipment" )
	TSubclassOf< class AFGEquipmentChild > mChildEquipmentClass;

	//@todo FIXUP Remove BlueprintReadOnly
	/** The cost of using this equipment */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Equipment" )
	TArray< FItemAmount > mCostToUse;

	/** Arms animation this should play on the when the equipment is equipped (only used if mEquipmentSlot == ES_ARMS) */
	UPROPERTY( EditDefaultsOnly, Category = "Equipment|Animation" )
	EArmEquipment mArmAnimation;

	/** Arms animation this should play on the when the equipment is equipped (only used if mEquipmentSlot == ES_BACK) */
	UPROPERTY( EditDefaultsOnly, Category = "Equipment|Animation" )
	EBackEquipment mBackAnimation;

	/** If the owner is persistent throughout the lifetime of this equipment */
	UPROPERTY( EditDefaultsOnly, Category = "Equipment", AdvancedDisplay )
	bool mHasPersistentOwner;

private:
	/** This is the attachment of this equipment */
	UPROPERTY()
	class AFGEquipmentAttachment* mAttachment;

	/** This is a potential secondary attachment */
	UPROPERTY()
	class AFGEquipmentAttachment* mSecondaryAttachment;

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

	/** Should we use the default primary fire implementation */
	UPROPERTY( EditDefaultsOnly, Category = "Equipment" )
	bool mUseDefaultPrimaryFire;

	/** Aim offset to override with */
	UPROPERTY( EditDefaultsOnly, Category = "Equipment|Animation" )
	class UAimOffsetBlendSpace* mAttachmentIdleAO;
};
