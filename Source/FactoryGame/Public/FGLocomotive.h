// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGRailroadVehicle.h"
#include "FGLocomotiveMovementComponent.h"
#include "RailroadNavigation.h"
#include "FGTrain.h"
#include "FGLocomotive.generated.h"


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
	virtual void PreReplication( IRepChangedPropertyTracker & ChangedPropertyTracker ) override;

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
	// End AActor interface

	// Begin ADriveablePawn/AFGVehicle interface
	virtual bool DriverEnter( class AFGCharacterPlayer* driver ) override;
	virtual bool DriverLeave( bool keepDriving = false ) override;
	// End ADriveablePawn/AFGVehicle interface
		
	// Begin ARailroadVehicle interface
	virtual void UpdatePower() override;
	virtual class UFGPowerConnectionComponent* GetSlidingShoe() const override { return mSlidingShoe; }
	// End ARailroadVehicle interface

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
	UFGPowerInfoComponent* GetPowerInfo() const { return mPowerInfo; }

	/** Debug */
	virtual void DisplayDebug( class UCanvas* canvas, const class FDebugDisplayInfo& debugDisplay, float& YL, float& YPos ) override;

	/** Called when the name of the train this locomotive is part of has changed name */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "FactoryGame|Railroad|Locomotive" )
	void OnNameChanged();

	/** Return the current state of HasPower replicated from Server to client */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Locomotive" )
	bool HasPower() const { return mHasPower; }

protected:
	UFUNCTION( BlueprintImplementableEvent )
	void UpdateVFX();
	
private:
	/** Used by the movement component to control the power usage. */
	void SetPowerConsumption( float pct );
	void SetPowerRegeneration( float pct );
	
	UFUNCTION()
	void OnRep_ReplicatedMovementTransform()
	{
		RootComponent->SetWorldTransform( mReplicatedMovementTransform );
	}

public:
	/** Name of the VehicleMovement. Use this name if you want to use a different class (with ObjectInitializer.SetDefaultSubobjectClass). */
	static FName VehicleMovementComponentName;

private:
	/** The power consumption of this electric locomotive, min is idle power consumption and max is power consumption at maximum torque. */
	UPROPERTY( EditDefaultsOnly, Category = "Power", meta = ( ClampMin = 0, UIMin = 0, AddAutoJSON = true ) )
	FFloatInterval mPowerConsumption;

	/** The sliding shoe making contact with the third rail. */
	UPROPERTY( )
	class UFGPowerConnectionComponent* mSlidingShoe;

	/** The power info for this train, draw power from the circuit. */
	UPROPERTY( Replicated )
	class UFGPowerInfoComponent* mPowerInfo;

	//@todo Replace when proper physics simulations are done.
	UPROPERTY( ReplicatedUsing = OnRep_ReplicatedMovementTransform )
	FTransform mReplicatedMovementTransform;

	/** Has power. Used to keep clients in sync with circuit power state */
	UPROPERTY( Replicated )
	uint8 mHasPower : 1;

	/** vehicle simulation component */
	UPROPERTY( VisibleDefaultsOnly, BlueprintReadOnly, Category = Vehicle, meta = ( AllowPrivateAccess = "true" ) )
	class UFGLocomotiveMovementComponent* mVehicleMovement;
};
