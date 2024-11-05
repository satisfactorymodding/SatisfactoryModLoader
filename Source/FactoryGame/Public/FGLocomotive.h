// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGRailroadVehicle.h"
#include "FGLocomotiveMovementComponent.h"
#include "FGTrain.h"
#include "FGLocomotive.generated.h"


UENUM( BlueprintType )
namespace ELocomotiveHeadlightsMode
{
	enum Type
	{
		LHM_Off			UMETA( DisplayName = "Off" ),
		LHM_On			UMETA( DisplayName = "On" ),
		LHM_Taillights	UMETA( DisplayName = "Taillights" ),
		LHM_MAX 		UMETA( Hidden )
	};
}

/** Small struct to contain the properties for the different headlight modes. */
USTRUCT( BlueprintType )
struct FHeadlightParams
{
	GENERATED_BODY()

	/** Should we show a visible beam for the light. */
	UPROPERTY( EditDefaultsOnly )
	bool ShowBeam = false;

	/** Color of the light. */
	UPROPERTY( EditDefaultsOnly )
	FLinearColor Color;

	/** Intensity for the light source, does not affect the beam. */
	UPROPERTY( EditDefaultsOnly )
	float Intensity = 0.f;
};


/**
 * Base class for locomotives, choo choo!
 */
UCLASS()
class FACTORYGAME_API AFGLocomotive : public AFGRailroadVehicle
{
	GENERATED_BODY()
public:
	/** Replication */
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	AFGLocomotive();

	// Begin Movement
	virtual class UPawnMovementComponent* GetMovementComponent() const override { return mVehicleMovement; }
	virtual class UFGRailroadVehicleMovementComponent* GetRailroadVehicleMovementComponent() const override { return mVehicleMovement; }
	
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Locomotive" )
	class UFGLocomotiveMovementComponent* GetLocomotiveMovementComponent() const { return mVehicleMovement; }
	// End Movement

	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void Tick( float dt ) override;
	virtual void PossessedBy( AController* newController ) override;
	virtual void UnPossessed() override;
	// End AActor interface

	// Begin ADriveablePawn/AFGVehicle interface
	virtual bool DriverEnter( class AFGCharacterPlayer* driver ) override;
	virtual bool DriverLeave( bool keepDriving = false ) override;
	virtual void AddInputBindings( UInputComponent* inputComponent ) override;
	virtual bool CanLeaveVehicle( AFGCharacterPlayer* character ) override;
	virtual void UpdatePlayerStatus() override;
	// End ADriveablePawn/AFGVehicle interface
		
	// Begin ARailroadVehicle interface
	virtual void UpdatePower() override;
	virtual class UFGPowerConnectionComponent* GetSlidingShoe() const override { return mSlidingShoe; }
	// End ARailroadVehicle interface
	
	//Begin IFGSignificanceInterface
	virtual void GainedSignificance_Implementation() override;
	//End IFGSignificanceInterface

	/**
	 * Get the role for this locomotive when MUing.
	 * @see EMultipleUnitControl.
	 */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Locomotive" )
	EMultipleUnitControl GetMultipleUnitRole() const;

	/**
	 * @return true if we can set the multiple unit master on locomotive without forcing; false if we cannot.
	 */
	UFUNCTION( BlueprintAuthorityOnly, BlueprintPure, Category = "FactoryGame|Railroad|Locomotive" )
	bool CanSetTrainMultipleUnitMaster() const;

	/**
	 * Set this vehicle as the MU master.
	 * This updates all other vehicles in the train accordingly.
	 * @param force Force this to be the master, sets any current master to slave.
	 * @return true on success; false if there is another master and this was not forced.
	 */
	UFUNCTION( BlueprintAuthorityOnly, BlueprintCallable, Category = "FactoryGame|Railroad|Locomotive" )
	bool SetMultipleUnitControlMaster( bool force );

	/**
	 * Clears this vehicle as the MU master.
	 * Returns the train to MU disabled until another one is set as master.
	 */
	UFUNCTION( BlueprintAuthorityOnly, BlueprintCallable, Category = "FactoryGame|Railroad|Locomotive" )
	void ClearMultipleUnitControlMaster();

	/** Get the power info about this train. If it runs on electricity. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Railroad|Locomotive" )
	class UFGPowerInfoComponent* GetPowerInfo() const { return mPowerInfo; }

	/** Debug */
	virtual void DisplayDebug( class UCanvas* canvas, const class FDebugDisplayInfo& debugDisplay, float& YL, float& YPos ) override;

	/** Called when the name of the train this locomotive is part of has changed name */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "FactoryGame|Railroad|Locomotive" )
	void OnNameChanged();

	/** Return the current state of HasPower replicated from Server to client */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Locomotive" )
	bool HasPower() const { return mHasPower; }
	
	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|Railroad|Locomotive" )
	bool IsPossessed();

	/** Called when the self driver notifies the player about something, e.g. leaving the station. (Called on server only) */
	UFUNCTION( BlueprintImplementableEvent )
    void HonkShort();

	/** Called when the self driver honks on a danger ahead, collision or player on track. (Called on server only) */
	UFUNCTION( BlueprintImplementableEvent )
    void HonkDanger();

	/**
	 * Called when a human driver takes control over this locomotive.
	 * This can be upon entering the locomotive or when disabling the self driver.
	 */
	void GiveHumanDriverControl();

	/** Update the headlights to correctly reflect the state of the train. I.e. direction, power etc. */
	void UpdateHeadlightsMode();

	/**
	 * @return true if the headlights are on, otherwise false.
	 */
	ELocomotiveHeadlightsMode::Type GetHeadlightsMode() const { return mHeadlightMode; }

	void OpenLocomotiveMenu();
	
protected:
	/** Called from tick if train is significant. */
	UFUNCTION( BlueprintImplementableEvent )
	void UpdateVFX();

	/** Called when the player presses the horn input. (Called on server and client) */
	UFUNCTION( BlueprintImplementableEvent )
    void OnHonkBegin();

	/** Called when the player releases the horn input. (Called on server and client) */
	UFUNCTION( BlueprintImplementableEvent )
    void OnHonkEnd();

	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Locomotive" )
	bool IsInputEnabled() const;

	/** Input Actions */
	UFUNCTION()
	void Input_ThrottleAxis_Started( const FInputActionValue& actionValue );
	
	UFUNCTION()
	void Input_ThrottleAxis( const FInputActionValue& actionValue );

	UFUNCTION()
	void Input_SteerAxis( const FInputActionValue& actionValue );
	
	UFUNCTION()
	void Input_Handbrake( const FInputActionValue& actionValue );

	UFUNCTION()
	void Input_Honk( const FInputActionValue& actionValue );
	
	UFUNCTION()
	void Input_OpenLocomotiveMenu( const FInputActionValue& actionValue );
	
private:
	/** Used by the movement component to control the power usage. */
	void SetPowerConsumption( float pct );
	void SetPowerRegeneration( float pct );

	/** Called when the power status changes for this locomotive. */
	void OnHasPowerChanged();

	/** Called whenever the headlight mode has been changed (both server and client) so the lights can be configured. */
	UFUNCTION()
	void OnRep_HeadlightMode();
public:
	/** Name of the VehicleMovement. Use this name if you want to use a different class (with ObjectInitializer.SetDefaultSubobjectClass). */
	static FName VehicleMovementComponentName;
	
	/** Delegates for the replication graph so it can setup dependencies. Only called on the server. */
	DECLARE_MULTICAST_DELEGATE_TwoParams( FOnLocomotivePossessedBy, AFGLocomotive*, AController* );
	DECLARE_MULTICAST_DELEGATE_TwoParams( FOnLocomotiveUnPossessed, AFGLocomotive*, AController* );
	
	static FOnLocomotivePossessedBy OnPossessedBy;
	static FOnLocomotiveUnPossessed OnUnPossessed;

private:
	/** The power consumption of this electric locomotive, min is idle power consumption and max is power consumption at maximum torque. */
	UPROPERTY( EditDefaultsOnly, Category = "Power", meta = ( ClampMin = 0, UIMin = 0, AddAutoJSON = true ) )
	FFloatInterval mPowerConsumption;

	/** The sliding shoe making contact with the third rail. */
	UPROPERTY( )
	class UFGPowerConnectionComponent* mSlidingShoe;

	/** The power info for this train, draw power from the circuit. */
	UPROPERTY()
	class UFGPowerInfoComponent* mPowerInfo;

	/** Has power. Used to keep clients in sync with circuit power state */
	UPROPERTY( Replicated )
	bool mHasPower;

	/** vehicle simulation component */
	UPROPERTY( VisibleDefaultsOnly, BlueprintReadOnly, Category = Vehicle, meta = ( AllowPrivateAccess = "true" ) )
	class UFGLocomotiveMovementComponent* mVehicleMovement;

	/** True if we're honking right now. */
	bool mIsHonking;

	/** Remember the state of the headlights, use the setter to set this so that the light and meshes gets updated. */
	UPROPERTY( ReplicatedUsing = OnRep_HeadlightMode )
	TEnumAsByte< ELocomotiveHeadlightsMode::Type > mHeadlightMode;

	/**
	 * Parameters for the different headlight modes.
	 */
	UPROPERTY( EditDefaultsOnly, Category = Vehicle )
	FHeadlightParams mHeadlightModes[ ELocomotiveHeadlightsMode::LHM_MAX ];

	/** The widget that is shown when player interact with the locomotive from inside the locomotive, Train scheduler etc. */
	UPROPERTY( EditDefaultsOnly, Category = Vehicle )
	TSoftClassPtr<UFGInteractWidget> mLocomotiveMenuWidgetClass;
};
