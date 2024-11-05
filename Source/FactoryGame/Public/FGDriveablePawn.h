// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "GameFramework/Pawn.h"
#include "FGSaveInterface.h"
#include "Replication/FGConditionalReplicationInterface.h"
#include "FGDriveablePawn.generated.h"


/**
 * Base class for pawns that can be driven by a player character, this includes vehicles, remote drones and passenger seats.
 */
UCLASS()
class FACTORYGAME_API AFGDriveablePawn : public APawn, public IFGSaveInterface, public IFGConditionalReplicationInterface
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

	// Begin IFGConditionalReplicationInterface
	virtual void GetConditionalReplicatedProps(TArray<FFGCondReplicatedProperty>& outProps) const override;
	virtual bool IsPropertyRelevantForConnection(UNetConnection* netConnection, const FProperty* property) const override;
	// End IFGConditionalReplicationInterface

	// Begin APawn interface
	virtual void PossessedBy( AController* newController ) override;
	virtual void UnPossessed() override;
	virtual void OnRep_PlayerState() override;
	virtual void CalcCamera(float DeltaTime, FMinimalViewInfo& OutResult) override;
	// End APawn interface

	// Begin AActor interface
	virtual void PreInitializeComponents()  override;
	// End AActor interface

	virtual void UpdatePlayerStatus();

	/** Gets the driving pawn. */
	UFUNCTION( BlueprintPure, Category = "Driveable" )
	FORCEINLINE class AFGCharacterPlayer* GetDriver() const { return mDriver; }

	/** Whether or not the vehicle has an active driver, will return false if there's a driver with no controller (offline player). */
	UFUNCTION( BlueprintPure, Category = "Driveable" )
	bool HasActiveDriver() const;

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
	
	UFUNCTION( BlueprintCallable, Server, Reliable )
	virtual void Server_DriverLeave();

	UFUNCTION( BlueprintPure, Category = "Driveable" )
	virtual bool CanLeaveVehicle( class AFGCharacterPlayer* character );

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

	/** Helpers */
	bool GetSafeExitLocation( class AFGCharacterPlayer* exitingCharacter, const FVector& exitOffset, FVector& out_location, FRotator& out_rotation ) const;

protected:
	/** When driving status changed for this vehicle. */
	virtual void OnDrivingStatusChanged();

	/** Add the bindings to vehicle and child-classes. */
	virtual void AddInputBindings( UInputComponent* inputComponent );

	/** Clear input bindings for the driveable pawn. */
	void ClearInputBindings( class AFGPlayerController* playerController );

	/** Called when the driver is about to leave (human or ai) */
	UFUNCTION( BlueprintImplementableEvent, meta = ( DisplayName = "OnDriverLeave" ) )
	void ReceiveOnDriverLeave();

	/** Places the driver at a valid location when they leave the vehicle. */
	UFUNCTION( BlueprintCallable, Category = "Vehicle" )
	void PlaceExitingDriver();

	/** Helpers */
	void SetDriving( bool isDriving );

	virtual void SetupPlayerInputComponent( UInputComponent* PlayerInputComponent ) override;
	
	/** Input Bindings */
	UFUNCTION()
	void Input_LeaveVehicle( const FInputActionValue& actionValue );

	class UFGGameUI* GetGameUI() const;
private:
	/** Rep notifies */
	UFUNCTION()
	void OnRep_IsDriving();
	
	UFUNCTION()
	void OnRep_Driver( AFGCharacterPlayer* previousDriver );

	virtual void LeavesVehicle() {}
	
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

	bool mIsDriverDirty = false;

	/** Whether or not this driveable pawn is possessed. */
	UPROPERTY( Replicated )
	bool mIsPossessed;
	
protected:
	/** Property replicator handling conditional replication of properties on this vehicle */
	UPROPERTY( Replicated, Transient, meta = ( FGPropertyReplicator ) )
	FFGConditionalPropertyReplicator mPropertyReplicator;
	
	/** Mapping context which is applied when entering. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category="Input" )
	TObjectPtr< class UInputMappingContext > mMappingContext;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category="Input" )
	int32 mMappingContextPriority = 0;

	/** Spring arm and camera components for the driver. */
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = "Driveable" )
	TSoftObjectPtr<class USpringArmComponent> mSpringArmComponent;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = "Driveable" )
	TSoftObjectPtr<class UCameraComponent> mCameraComponent;

	void ActivateCameraComponents();
	void DeactivateCameraComponents();
	
private:
	/** If another driver is about to enter this vehicle. Used to not shutdown/startup the */
	bool mHasPendingDriver;

	//@todo Verify if vehicle should be occupied when client leaves or not.
	/** The driver, not saved, pawns remember their last driven vehicle and enters it in begin play. */
	UPROPERTY( ReplicatedUsing = OnRep_Driver )
	class AFGCharacterPlayer* mDriver;

	/** Is this vehicle being driven. */
	UPROPERTY( ReplicatedUsing = OnRep_IsDriving )
	bool mIsDriving;
	
};
