// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "UObject/Class.h"

#include "FGEquipment.h"
#include "FGEquipmentAttachment.h"
#include "FGJetPack.generated.h"

UCLASS()
class FACTORYGAME_API AFGJetPack : public AFGEquipment
{
	GENERATED_BODY()

public:

	/** You know what this is */
	AFGJetPack();

	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Begin AFGEquipment interface
	virtual bool ShouldSaveState() const override;
	// End

	/** Simple set */
	void SetIsThrusting( bool newIsThrusting );

	FORCEINLINE bool GetIsThrusting() const { return mIsThrusting; }

	virtual void Equip( class AFGCharacterPlayer* character ) override;
	virtual void UnEquip() override;

	/** Player pressed thrust */
	void JetPackThrust();

	/** Player released thrust */
	void JetPackStopThrust();

	/** This function calculates our new velocity when we are thrusting */
	UFUNCTION( BlueprintImplementableEvent )
	FVector GetNewVelocityWhenThrusting( float delta );

	/** This function calculates our new velocity when we are thrusting */
	UFUNCTION( BlueprintImplementableEvent )
	bool CanThrust();

	/** Called when we start thrusting */
	UFUNCTION( BlueprintImplementableEvent )
	void OnStartThrusting();

	/** Called when we stop thrusting */
	UFUNCTION( BlueprintImplementableEvent )
	void OnStopThrusting();

	/** Returns the current amount of fuel for the jet pack. Please override. */
	UFUNCTION( BlueprintNativeEvent, BlueprintPure, Category = "JetPack" )
	float GetCurrentFuel() const;

	/** Returns the maximum amount of fuel for the jet pack. Please override. */
	UFUNCTION( BlueprintNativeEvent, BlueprintPure, Category = "JetPack" )
	float GetMaxFuel();

protected:
	/** @copydoc AFGEquipment::AddEquipmentActionBindings */
	virtual void AddEquipmentActionBindings() override;

public:
	
	/** The duration we've held down thrust this flight, only resets when Landed*/
	UPROPERTY( VisibleInstanceOnly, BlueprintReadOnly )
	float mJumpTimeStamp;

protected:
	/** If we are actually thrusting or not */
	UPROPERTY( VisibleInstanceOnly, BlueprintReadOnly )
	bool mIsThrusting;

private:

	/** The player is holding down the thrust key and wants to thrust */
	bool mWantsToThrust;

	/** A cached instance of the instigators movementcomponent */
	class UFGCharacterMovementComponent* mCachedMovementComponent;
};

UCLASS()
class FACTORYGAME_API AFGJetPackAttachment : public AFGEquipmentAttachment
{
	GENERATED_BODY()

public:

	/** Replication. */
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	/** Called when mIsThrusting is replicated */
	UFUNCTION()
	void OnRep_IsThrusting();

	/** Called when we start thrusting */
	UFUNCTION( BlueprintImplementableEvent )
	void OnStartThrusting();

	/** Called when we stop thrusting */
	UFUNCTION( BlueprintImplementableEvent )
	void OnStopThrusting();

	/** Simple set */
	void SetIsThrusting( bool newIsThrusting );

protected:
	UPROPERTY( ReplicatedUsing = OnRep_IsThrusting )
	bool mIsThrusting;

};


