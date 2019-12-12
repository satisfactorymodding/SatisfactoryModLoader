// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/CoreNet.h"
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

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
	// End AActor interface

	// Begin APawn interface
	virtual void PossessedBy( AController* newController ) override;
	virtual void UnPossessed() override;
	// End APawn interface

	// Begin ADriveablePawn/AFGVehicle interface
	virtual bool DriverEnter( class AFGCharacterPlayer* driver ) override;
	virtual bool DriverLeave( bool keepDriving = false ) override;
	virtual bool CanSelfDriverEnter( class AAIController* ai ) const override;
	virtual bool SelfDriverEnter( class AAIController* ai ) override;
	// End ADriveablePawn/AFGVehicle interface
		
	// Begin ARailroadVehicle interface
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

	//@todo Look over authority on the path functions BlueprintAuthorityOnly/if(HasAuthority())
	/**
	 * Clears the old path and sets a new one path from a pathfinding result.
	 * @param The path finding result to set the path from. If result is invalid, old path is cleared but no new path is set.
	 * @return true if the new path is valid; false otherwise.
	 */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Railroad|Locomotive" )
	bool SetPath( const FRailroadPathFindingResult& result );

	/**
	 * Clears the locomotives path.
	 */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Railroad|Locomotive" )
	void ClearPath();

	/**
	 * If this locomotive has a path, only checks if it has a path and not if the path still leads to the goal.
	 * @return true if path is set; false if path is not set.
	 */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Locomotive" )
	bool HasPath() const;

	/**
	 * Get the path ahead of this train.
	 * @param out_points Connections to follow, including switches, distance is the distance to the destination.
	 */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Railroad|Locomotive" )
	void GetPath( TArray< FRailroadPathPoint >& out_points );

	/**
	 * Get the target points ahead of this train.
	 * @param out_points Target points along the track ahead: connections, switches, signals, stops etc.
	 *                   Distance is the distance from the locomotive to the target point.
	 */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Railroad|Locomotive" )
	void GetTargetPoints( TArray< FRailroadPathPoint >& out_points );

	/** Check and update where along the path we are. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Railroad|Locomotive" )
	bool UpdatePathSegment();

	/** Update our awareness of connections, switches, signals ahead. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Railroad|Locomotive" )
	void UpdateTargetPoints( float maxDistance );

	/**
	 * Enable self driving on the train.
	 */
	UFUNCTION( BlueprintCallable, BlueprintAuthorityOnly, Category = "FactoryGame|Railroad|Locomotive" )
	void SetSelfDrivingEnabled( bool isEnabled );

	/**
	 * Enable self driving on the train.
	 */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Locomotive" )
	bool IsSelfDrivingEnabled() const;

	/**
	 * Report an error to be displayed for the self driving locomotive. This also applies the emergency brakes.
	 */
	UFUNCTION( BlueprintAuthorityOnly, BlueprintCallable, Category = "FactoryGame|Railroad|Locomotive" )
	void ReportSelfDrivingError( ESelfDrivingLocomotiveError error );

	/**
	 * Get the self driving error for this locomotive.
	 */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Locomotive" )
	ESelfDrivingLocomotiveError GetSelfDrivingError() const;

	/**
	 * Clear all errors for the self driving locomotive.
	 */
	UFUNCTION( BlueprintAuthorityOnly, BlueprintCallable, Category = "FactoryGame|Railroad|Locomotive" )
	void ClearSelfDrivingError();

	/** Get the power info about this train. If it runs on electricity. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Railroad|Locomotive" )
	UFGPowerInfoComponent* GetPowerInfo() const { return mPowerInfo; }

	/** Used by the movement component to control the power usage. */
	void SetPowerConsumption( float pct );
	void SetPowerRegeneration( float pct );

	/** Debug */
	virtual void DisplayDebug( class UCanvas* canvas, const class FDebugDisplayInfo& debugDisplay, float& YL, float& YPos ) override;

	/** Called when the name of the train this locomotive is part of has changed name */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "FactoryGame|Railroad|Locomotive" )
	void OnNameChanged();

private:
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
	UPROPERTY( EditDefaultsOnly, Category = "Power", meta = ( ClampMin = 0, UIMin = 0 ) )
	FFloatInterval mPowerConsumption;

	/** The sliding shoe making contact with the third rail. */
	UPROPERTY()
	class UFGPowerConnectionComponent* mSlidingShoe;

	/** The power info for this train, draw power from the circuit. */
	UPROPERTY( Replicated )
	class UFGPowerInfoComponent* mPowerInfo;

	//@todo Replace when proper physics simulations are done.
	UPROPERTY( ReplicatedUsing = OnRep_ReplicatedMovementTransform )
	FTransform mReplicatedMovementTransform;

	/** vehicle simulation component */
	UPROPERTY( VisibleDefaultsOnly, BlueprintReadOnly, Category = Vehicle, meta = ( AllowPrivateAccess = "true" ) )
	class UFGLocomotiveMovementComponent* mVehicleMovement;

	/** The path this locomotive follows. */
	FRailroadPathSharedPtr mPath;

	/** Index of the next path point ahead. */
	int32 mCurrentPathSegment;

	/**
	 * Extrapolated array of path points "target points" that we need to pass when moving forward.
	 * The path only specifies the connections (incl switches) and the stop.
	 * In addition this specifies signals, signs etc a given distance forward.
	 */
	TArray< FRailroadPathPoint > mTargetPoints;
};
