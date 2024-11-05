// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGCharacterPlayer.h"
#include "FGPlayerCinematicProxy.generated.h"

/** Class that handles the cinematic state for the player character controlled by the cinematic */
UCLASS( Blueprintable, Within = FGCharacterPlayer )
class FACTORYGAME_API UFGPlayerCinematicDriver : public UObject
{
	GENERATED_BODY()
public:
	UFGPlayerCinematicDriver();

	// Begin UObject interface
	virtual UWorld* GetWorld() const override;
	// End UObject interface
	
	/** Called to attach this instance to the new owner. Will be called during PostInitializeComponents */
	virtual void AttachToOwner();

	/** Called when the owner had it's BeginPlay called */
	virtual void OwnerBeginPlay();

	/** Will be called each frame to update the cinematic proxy */
	virtual void UpdateCinematicDriver( float deltaTime );

	/** Called when the cinematic driver is about to be destroyed */
	virtual void DestroyCinematicDriver();

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void PostEditChangeCinematicPlayerSettings(FPropertyChangedEvent& PropertyChangedEvent);
#endif

	/**
	 * Returns the rotation currently desired by the controller
	 * Called from the movement component to override the rotation when we are not possessed by the controller
	 */
	FRotator GetDesiredRotation( FRotator currentRotation ) const;

	/** Returns the character owning this cinematic driver */
	UFUNCTION( BlueprintPure, Category = "Cinematic" )
	FORCEINLINE AFGCharacterPlayer* GetOwner() const { return GetOuterAFGCharacterPlayer(); }

	/** Equips the equipment item from the inventory to the relevant slot */
	UFUNCTION( BlueprintCallable, Category = "Cinematic | Inventory" )
	void EquipItemFromInventory( TSubclassOf<UFGEquipmentDescriptor> equipmentDescriptor, bool makeIndexActive = true );
	
	/** Makes the character play the specified emote */
	UFUNCTION( BlueprintCallable, Category = "Cinematic | Emote" )
	void PlayEmote( TSubclassOf<class UFGEmote> emote );

	/** Makes the character holster the currently selected equipment */
	UFUNCTION( BlueprintCallable, Category = "Cinematic | Equipment" )
	void ToggleEquipmentHolster();

	/** Sets the active arms equipment slot index */
	UFUNCTION( BlueprintCallable, Category = "Cinematic | Equipment" )
	void SetSelectedEquipmentIndex( int32 newSelectedArmsIndex );

	/** Executes the primary fire on the currently selected hands equipment, optionally holds it for the given amount of time */
	UFUNCTION( BlueprintCallable, Category = "Cinematic | Equipment" )
	void EquipmentPrimaryFire( float holdDuration = -1.0f );

	/** Executes the secondary fire on the currently selected hands equipment, optionally holds it for the given amount of time */
	UFUNCTION( BlueprintCallable, Category = "Cinematic | Equipment" )
	void EquipmentSecondaryFire( float holdDuration = -1.0f );

	/** Forces the currently loaded equipment to reload, if it is a weapon */
	UFUNCTION( BlueprintCallable, Category = "Cinematic | Equipment | Weapon" )
	void EquipmentReload();

	/** Forces the currently selected equipment to switch the equipped ammo type, if it is a weapon */
	UFUNCTION( BlueprintCallable, Category = "Cinematic | Equipment | Weapon" )
	void EquipmentChangeAmmoType( TSubclassOf< UFGAmmoType > newDesiredAmmoClass );

	void Internal_RefreshInventoryItems();
protected:
	void EquipItemsFromInventory();
	void UpdateDefaultInventoryItems() const;
	
	/** Called when we are attached to the character */
	UFUNCTION( BlueprintImplementableEvent, Category = "Cinematic Driver", DisplayName = "OnAttachToCharacter" )
	void K2_OnAttachToCharacter();

	/** Called when the character begun playing */
	UFUNCTION( BlueprintImplementableEvent, Category = "Cinematic Driver", DisplayName = "OnCharacterBegunPlay" )
	void K2_OnCharacterBegunPlay();

	/** Called every frame to update cinematic driver */
	UFUNCTION( BlueprintImplementableEvent, Category = "Cinematic Driver", DisplayName = "UpdateCinematicDriver" )
	void K2_UpdateCinematicDriver( float deltaTime );
private:

	/** The view rotation the player should have when controlled by the cinematic */
	UPROPERTY( EditAnywhere, Interp, Category = "Cinematic | Movement" )
	FRotator mViewRotation;
	
	/** Whenever the character should be sprinting right now */
	UPROPERTY( EditAnywhere, Interp, Category = "Cinematic | Movement" )
	bool mWantsToSprint;

	/** Whenever the character should be crouching right now */
	UPROPERTY( EditAnywhere, Interp, Category = "Cinematic | Movement" )
	bool mWantsToCrouch;

	/** Whenever the character should be jumping right now */
	UPROPERTY( EditAnywhere, Interp, Category = "Cinematic | Movement" )
	bool mWantsToJump;

	/** Amount of time left until we emit the primary fire release event */
	UPROPERTY( VisibleInstanceOnly, Transient, Category = "Cinematic" )
	float mPrimaryFireTimeLeft;

	/** Amount of time left until we emit the primary fire release event */
	UPROPERTY( VisibleInstanceOnly, Transient, Category = "Cinematic" )
	float mSecondaryFireTimeLeft;

	/** The location of the actor that we have cached last frame */
	UPROPERTY( VisibleInstanceOnly, Transient, Category = "Cinematic" )
	FVector mLastActorLocation;

	UPROPERTY( VisibleInstanceOnly, Transient, Category = "Cinematic" )
	AFGPlayerState* mCinematicPlayerState;
};