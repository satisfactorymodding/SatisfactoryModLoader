// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "FGEquipment.h"
#include "FGHookshot.generated.h"

UCLASS()
class FACTORYGAME_API AFGHookshot : public AFGEquipment
{
	GENERATED_BODY()
public:
	AFGHookshot();

	virtual void BeginPlay() override;

	/** Called locally */
	void OnPrimaryFirePressed();
	void OnSecondaryFirePressed();

	// AFGEquipment interface
	virtual void Equip( class AFGCharacterPlayer* character ) override;
	virtual void UnEquip();
	// AFGEquipment interface

	virtual void Tick( float deltaTime );

	/** Called whenever the wire is detached */
	UFUNCTION( BlueprintImplementableEvent, Category = "Equipment" )
	void OnWireDetach();

	/** Called locally when a player shoots the hookshot */
	UFUNCTION(BlueprintImplementableEvent, Category="Equipment")
	void OnFire( bool attachedToSomething, const FHitResult& hitResult );

	/** Wire gets detached */
	void WireDetach();
protected:
	/** @copydoc AFGEquipment::AddEquipmentActionBindings */
	virtual void AddEquipmentActionBindings() override;

	/** Move the audio in fron of the player */
	UFUNCTION(BlueprintCallable,Category="Equipment")
	void MoveAudioSourceInFrontOfPlayer();

	/** Stop updating position in front of the player */
	UFUNCTION( BlueprintCallable, Category = "Equipment" )
	void RestoreAudioSourceToOriginalLocation();
	/** Called whenever the actor we are attached to landed */
	UFUNCTION(BlueprintImplementableEvent,Category="Equipment")
	void OwnerLanded( const FHitResult& Hit );
public:
	/** How far we will trace to try and find something to attach to */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	float mMaxHookDistance;

	/** How fast do we accellerate toward the grappled target. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	float mAccelRate;

	/** Accel bonus added when we are moving away from the grappled target. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	float mBrakeAccelRate;

	/** A cached instance of the instigators movementcomponent */
	class UFGCharacterMovementComponent* mCachedMovementComponent;
protected:
	/** Component handling our hookshot sounds */
	UPROPERTY(VisibleDefaultsOnly,BlueprintReadOnly,Category="Equipment")
	class UAkComponent* mHookshotAudio;
private:
	/** Distance from player when attached, caluclated from mHookshotAudio */
	float mAttachDistance;

public:
	FORCEINLINE ~AFGHookshot() = default;
};
