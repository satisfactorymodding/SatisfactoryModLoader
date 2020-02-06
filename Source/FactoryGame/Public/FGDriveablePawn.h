// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "UObject/Class.h"

#include "GameFramework/Pawn.h"
#include "FGSaveInterface.h"
#include "FGDriveablePawn.generated.h"


/**
 * Base class for pawns that can be driven by a player character, this includes vehicles, remote drones and passenger seats.
 */
UCLASS()
class FACTORYGAME_API AFGDriveablePawn : public APawn, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	AFGDriveablePawn();

	/** Decide on what properties to replicate. */
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	// Begin APawn interface
	virtual void PossessedBy( AController* newController ) override;
	virtual void UnPossessed() override;
	// End APawn interface

	/** Gets the driving pawn. */
	UFUNCTION( BlueprintPure, Category = "Driveable" )
	FORCEINLINE class AFGCharacterPlayer* GetDriver() const { return mDriver; }

	/** Can we drive this. (server and locally controlled client) */
	UFUNCTION( BlueprintPure, Category = "Driveable" )
	virtual bool CanDriverEnter( class AFGCharacterPlayer* character );

	/**
	 * Make player the new driver of this vehicle.
	 * @note Call this on server only.
	 */
	UFUNCTION( BlueprintCallable, BlueprintAuthorityOnly, Category = "Driveable" )
	virtual bool DriverEnter( class AFGCharacterPlayer* driver );

	/**
	 * Called when player wants to get out.
	 * @note Call this on server only.
	 *
	 * @param keepDriving    True if we want to leave the without setting IsDriving to false (turn off the vehicle).
	 */
	UFUNCTION( BlueprintCallable, BlueprintAuthorityOnly, Category = "Driveable" )
	virtual bool DriverLeave( bool keepDriving = false );

	/**
	 * Attach/detach driver to vehicle.
	 * Use this to attach the driver to the seat and setup animations, collision on pawn etc.
	 * Called from AFGCharacter on server and client.
	 */
	virtual void AttachDriver( class AFGCharacterPlayer* driver );

	/** @return true if the driver should be attached. */
	UFUNCTION( BlueprintPure, Category = "Driveable" )
	bool ShouldAttachDriver() const { return mShouldAttachDriver; }

	/** @return true if the driver should be visible. */
	UFUNCTION( BlueprintPure, Category = "Driveable" )
	bool IsDriverVisible() const { return mIsDriverVisible; }

	/** @return socket to attach the driver to; none if no socket set. */
	UFUNCTION( BlueprintPure, Category = "Driveable" )
	FName GetDriverSeatSocket() const { return mDriverSeatSocket; }

	/** @return animation to set on the driver; null if no animation set. */
	UFUNCTION( BlueprintPure, Category = "Driveable" )
	class UAnimSequence* GetDriverSeatAnimation() const { return mDriverSeatAnimation; }

	/** @return exit offset to try to place the driver at (local space). */
	UFUNCTION( BlueprintPure, Category = "Driveable" )
	FVector GetDriverExitOffset() const { return mDriverExitOffset; }

	/** @return true if this vehicle is being driven. */
	UFUNCTION( BlueprintPure, Category = "Driveable" )
	bool IsDriving() const { return mIsDriving; }

	/** @return true if another driver is about to enter. */
	UFUNCTION( BlueprintPure, Category = "Driveable" )
	bool HasPendingDriver() const { return mHasPendingDriver; }

protected:
	/** When driving status changed for this vehicle. */
	virtual void OnDrivingStatusChanged();

	/** Called when the driver has entered (human or ai) */
	UFUNCTION( BlueprintImplementableEvent, meta = ( DisplayName = "OnDriverEnter" ) )
	void ReceiveOnDriverEnter();

	/** Called when the driver is about to leave (human or ai) */
	UFUNCTION( BlueprintImplementableEvent, meta = ( DisplayName = "OnDriverLeave" ) )
	void ReceiveOnDriverLeave();

	/** Places the driver at a valid location when they leave the vehicle. */
	UFUNCTION( BlueprintCallable, Category = "Vehicle" )
	void PlaceExitingDriver();

	/** Helpers */
	void SetDriving( bool isDriving );

private:
	/** Helpers */
	bool GetSafeExitLocation( class AFGCharacterPlayer* exitingCharacter, const FVector& exitOffset, FVector& out_location, FRotator& out_rotation ) const;

	/** Rep notifies */
	UFUNCTION()
	void OnRep_IsDriving();

public:
	/** True if the driver should be attached, false if this is a "remote controlled" pawn. */
	UPROPERTY( EditDefaultsOnly, Category = "Driveable" )
	bool mShouldAttachDriver;

	/** True if the driver should be visible, set from FVehicleSeat */
	UPROPERTY( EditDefaultsOnly, Category = "Driveable" )
	bool mIsDriverVisible;

	/** Socket to attach the driver to, if mShouldAttachDriver is true, set from FVehicleSeat */
	UPROPERTY( EditDefaultsOnly, Category = "Driveable" )
	FName mDriverSeatSocket;

	/** Animation to play on the character player when in the driver seat, set from FVehicleSeat */
	UPROPERTY( EditDefaultsOnly, Category = "Driveable" )
	class UAnimSequence* mDriverSeatAnimation;

	/** Where to place the driver upon exiting (local space), set from FVehicleSeat */
	UPROPERTY( EditDefaultsOnly, Category = "Driveable" )
	FVector mDriverExitOffset;

private:
	/** If another driver is about to enter this vehicle. Used to not shutdown/startup the */
	bool mHasPendingDriver;

	//@todo Verify if vehicle should be occupied when client leaves or not.
	/** The driver, not saved, pawns remember their last driven vehicle and enters it in begin play. */
	UPROPERTY( Replicated )
	class AFGCharacterPlayer* mDriver;

	/** Is this vehicle being driven. */
	UPROPERTY( ReplicatedUsing = OnRep_IsDriving )
	bool mIsDriving;
};
