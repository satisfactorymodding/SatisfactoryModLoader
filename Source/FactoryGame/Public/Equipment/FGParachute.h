// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "UObject/Class.h"

#include "FGEquipment.h"
#include "FGEquipmentAttachment.h"
#include "Camera/CameraShake.h"
#include "FGParachute.generated.h"


UCLASS()
class FACTORYGAME_API UFGParachuteCameraShake : public UCameraShake
{
	GENERATED_BODY()
	public:
		UFGParachuteCameraShake();

public:
	FORCEINLINE ~UFGParachuteCameraShake() = default;
};

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGParachute : public AFGEquipment
{
	GENERATED_BODY()
public:
	AFGParachute();
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void Tick( float DeltaSeconds ) override;
	virtual void Equip( class AFGCharacterPlayer* character ) override;
	virtual void UnEquip() override;

	/** Player pressed deploy */
	void Deploy();

	/** Only the server handles the building. */
	UFUNCTION( Server, Reliable, WithValidation )
	void Server_Deploy();
	
	/** This function calculates our new velocity when we are deployed */
	UFUNCTION( BlueprintNativeEvent )
	FVector ModifyVelocity( float deltaTime, const FVector& oldVelocity );

	/** Is the parachute deployed or not */
	UFUNCTION( BlueprintPure )
	FORCEINLINE bool IsDeployed() const { return mIsDeployed; }

protected:
	virtual void AddEquipmentActionBindings() override;

	/** Called when we start deploying */
	UFUNCTION( BlueprintImplementableEvent )
	void OnDeployed();

	/** Called when we stop deploying */
	UFUNCTION( BlueprintImplementableEvent )
	void OnDeployStop();


protected:
	/** The velocity we fall at using the parachute. */
	UPROPERTY( EditDefaultsOnly, Category = "Parachute" )
	float mTerminalVelocityZ;

private:
	/** If we are actually deployed or not */
	UPROPERTY( Replicated )
	bool mIsDeployed;

	/** A cached instance of the instigators movement */
	UPROPERTY()
	class UFGCharacterMovementComponent* mCachedMovementComponent;

public:
	FORCEINLINE ~AFGParachute() = default;
};


UCLASS()
class FACTORYGAME_API AFGParachuteAttachment : public AFGEquipmentAttachment
{
	GENERATED_BODY()

public:

	/** Replication. */
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	/** Simple set */
	void SetIsDeployed( bool newIsDeployed );

protected:
	/** Called when we start thrusting */
	UFUNCTION( BlueprintImplementableEvent )
	void OnDeployed();

	/** Called when we start thrusting */
	UFUNCTION( BlueprintImplementableEvent )
	void OnDeployStop();

	/** Called when mIsDeployed is replicated */
	UFUNCTION()
	void OnRep_IsDeployed();

private:
	UPROPERTY( ReplicatedUsing = OnRep_IsDeployed )
	bool mIsDeployed;


public:
	FORCEINLINE ~AFGParachuteAttachment() = default;
};