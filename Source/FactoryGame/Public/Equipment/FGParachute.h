// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGEquipment.h"
#include "FGParachute.generated.h"

class UFGCharacterMovementComponent;

/** Parachute settings used for defining it's behavior */
UCLASS()
class FACTORYGAME_API UFGParachuteSettings : public UDataAsset
{
	GENERATED_BODY()
public:
	/** Minimum vertical velocity the player should have to deploy the parachute */
	UPROPERTY( EditAnywhere, Category = "Parachute | Deploy" )
	float mMinimumVelocityForDeploy = -1500.0f;

	/** Multiplier applied to the character's terminal velocity when the parachute is deployed */
	UPROPERTY( EditAnywhere, Category = "Parachute | Fall Speed", meta = (ClampMin = "0.01", ClampMax = "1.0", UIMin = "0.01", UIMax = "1.0") )
	float mTerminalVelocityMultiplier = 0.33f;

	/** % of the lateral velocity converted into the fall speed. That means, the faster the player is moving, the faster they will be falling */
	UPROPERTY( EditAnywhere, Category = "Parachute | Fall Speed", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0") )
	float mLateralToTerminalConversionRatio = 0.33f;

	/** Max speed that the character can have while strafing */
	UPROPERTY( EditAnywhere, Category = "Parachute | Strafing", meta = (ClampMin = "0.0", UIMin = "0.0") )
	float mStrafeMaxSpeed = 1000.0f;

	/** Max speed that the character can have while holding shift when strafing */
	UPROPERTY( EditAnywhere, Category = "Parachute | Strafing", meta = (ClampMin = "0.0", UIMin = "0.0") )
	float mShiftStrafeMaxSpeed = 1500.0f;

	/** The deceleration applied to the player velocity when he is not giving active horizontal input */
	UPROPERTY( EditAnywhere, Category = "Parachute | Slow down", meta = (ClampMin = "0.0", UIMin = "0.0") )
	float mBrakingDeceleration = 100.0f;
	
	/** The exponent applied to the player velocity when he is actively braking with space */
	UPROPERTY( EditAnywhere, Category = "Parachute | Slow down", meta = (ClampMin = "0.0", UIMin = "0.0") )
	float mBrakingExponent = 2.4f;
};

UCLASS()
class FACTORYGAME_API AFGParachute : public AFGEquipment 
{
	GENERATED_BODY()
public:
	AFGParachute();
	
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void Tick( float DeltaSeconds ) override;
	virtual void UnEquip() override;

	/** Input Actions */
	void Input_Deploy( const FInputActionValue& actionValue );
	void Input_UnDeploy( const FInputActionValue& actionValue );

	/** Deploys the parachute, can be called both on the client and the authority side */
	void Deploy();
	/** Stops deploying the parachute, can be called both on the client and the authority side */
	void StopDeploy();
	
	/** Is the parachute deployed or not */
	UFUNCTION( BlueprintPure )
	FORCEINLINE bool IsDeployed() const { return mIsDeployed; }
protected:
	virtual void AddEquipmentActionBindings() override;
	virtual float GetCharacterUseDistanceOverride() const override;

	UFUNCTION( Server, Reliable )
	void Server_Deploy();
	UFUNCTION( Server, Reliable )
	void Server_StopDeploy();
	UFUNCTION( Client, Reliable )
	void Client_NotifyDeployFailed();

	/** Called when we start deploying */
	UFUNCTION( BlueprintImplementableEvent )
	void OnDeployed();

	/** Called when we stop deploying */
	UFUNCTION( BlueprintImplementableEvent )
	void OnDeployStop();

	/** Attempts to deploy the parachute locally, returns true if successfully deployed */
	bool AttemptDeployLocal();
	/** Locally stops deploying the parachute, always works */
	void StopDeployLocal();
	
	void Authority_SetDeployed( bool isDeployedNow );
	
	UFUNCTION()
	void OnRep_IsDeployed();
public:
	/** Parachute settings to apply to the character using the parachute */
	UPROPERTY( EditDefaultsOnly, Category = "Parachute" )
	UFGParachuteSettings* mParachuteSettings;

	/** The use distance override when the parachute is equipped  if not zero */
	UPROPERTY( EditDefaultsOnly, Category = "Parachute" )
	float mUseDistanceOverride;
private:
	/** If we are actually deployed or not */
	UPROPERTY( ReplicatedUsing = OnRep_IsDeployed )
	bool mIsDeployed;
	/** Timestamp at which the parachute has been deployed last time. Used to prevent glitches with constantly equipping and unequipping it */
	float mDeployTimestamp;
};
