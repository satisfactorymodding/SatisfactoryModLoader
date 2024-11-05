// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGVehicle.h"
#include "Buildables/FGBuildableRailroadTrack.h"
#include "FGRailroadVehicle.generated.h"


/**
 * Type of connections in the game.
 */
UENUM()
enum class ERailroadVehicleCoupler : uint8
{
	RVC_FRONT = 0	UMETA( DisplayName = "Front" ),
	RVC_BACK = 1	UMETA( DisplayName = "Back" )
};

/**
 * Vehicle is derailed and can be re-railed                                                                    
 */
UCLASS()
class FACTORYGAME_API UFGUseState_VehicleDerailed : public UFGUseState
{
	GENERATED_BODY()
public:
	UFGUseState_VehicleDerailed() { mIsUsableState = true; }
};

/**
 * Base vehicle for all railroad vehicles. E.g. locomotives, wagons etc.
 */
UCLASS()
class FACTORYGAME_API AFGRailroadVehicle : public AFGVehicle
{
	GENERATED_BODY()
public:
	AFGRailroadVehicle();

	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	virtual void Serialize( FArchive& ar ) override;
	virtual void Tick( float dt ) override;
	// End AActor interface

	//~ Begin IFGDismantleInterface
	virtual bool CanDismantle_Implementation() const override;
	virtual bool SupportsDismantleDisqualifiers_Implementation() const override { return true; }
	virtual void GetDismantleDisqualifiers_Implementation(TArray<TSubclassOf<UFGConstructDisqualifier>>& out_dismantleDisqualifiers, const TArray<AActor*>& allSelectedActors) const override;
	//~ End IFGDismantleInterface

	//Begin IFGSignificanceInterface
	virtual void GainedSignificance_Implementation() override;
	virtual	void LostSignificance_Implementation() override;
	//End IFGSignificanceInterface

	//~ Begin IFGUseableInterface
	virtual void UpdateUseState_Implementation( class AFGCharacterPlayer* byCharacter, const FVector& atLocation, class UPrimitiveComponent* componentHit, FUseState& out_useState ) override;
	virtual void OnUse_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual void OnUseStop_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual bool IsUseable_Implementation() const override;
	virtual void StartIsLookedAt_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state  ) override;
	virtual void StopIsLookedAt_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual FText GetLookAtDecription_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) const override;
	virtual void RegisterInteractingPlayer_Implementation( class AFGCharacterPlayer* player ) override;
	virtual void UnregisterInteractingPlayer_Implementation( class AFGCharacterPlayer* player ) override;
	//~ End IFGUseableInterface

	/** Update the power usage and info for this railroad vehicle. */
	virtual void UpdatePower();

	/** Get the railroad movement for this vehicle. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Vehicle" )
	virtual class UFGRailroadVehicleMovementComponent* GetRailroadVehicleMovementComponent() const;

	/**
	 * Get the train this vehicle is part of.
	 */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Vehicle" )
	FORCEINLINE class AFGTrain* GetTrain() const { return mTrain; }

	/** Get the sliding shoe if this vehicle consumes power. */
	virtual class UFGPowerConnectionComponent* GetSlidingShoe() const { return nullptr; }

	/**
	 * @return The length of this vehicle.
	 */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Vehicle" )
	FORCEINLINE float GetLength() const { return mLength; }

	/** Is this vehicle docked to a station. */
	bool IsDocked() const;

	/** Is this vehicle derailed? */
	bool IsDerailed() const { return mIsDerailed; }

	/**
	 * If this vehicles orientation is reversed in the train formation.
	 * @return true if forward for this vehicle is not the same as the trains forward.
	 */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Vehicle" )
	FORCEINLINE bool IsOrientationReversed() const { return mIsOrientationReversed; }

	/**
	 * @param at Coupler, valid values are 0 (front) and 1 (back).
	 * @return the vehicle coupled at index.
	 */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Vehicle" )
	FORCEINLINE bool IsCoupledAt( ERailroadVehicleCoupler coupler ) const { return IsValid( coupler == ERailroadVehicleCoupler::RVC_FRONT ? mCoupledVehicleFront : mCoupledVehicleBack ); }

	/**
	 * @param at Coupler, valid values are 0 (front) and 1 (back).
	 * @return the vehicle coupled at index.
	 */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Vehicle" )
	FORCEINLINE AFGRailroadVehicle* GetCoupledVehicleAt( ERailroadVehicleCoupler coupler ) const { return coupler == ERailroadVehicleCoupler::RVC_FRONT ? mCoupledVehicleFront : mCoupledVehicleBack; }
	
	/**
	 * Get the track position for this vehicle.
	 */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Vehicle" )
	FORCEINLINE FRailroadTrackPosition const& GetTrackPosition() const { return mTrackPosition; }

	/** 
	 * Get the track id this vehicle is on; -1 if the track is invalid.
	 */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Vehicle" )
	FORCEINLINE int32 GetTrackGraphID() const { return mTrackPosition.IsValid() ? mTrackPosition.Track->GetTrackGraphID() : INDEX_NONE; }

	/**
	 * Set the track position for this vehicle, be careful cause the actor and any coupled vehicles will not get moved.
	 */
	void SetTrackPosition( const FRailroadTrackPosition& position );

	/** Called when this vehicle is derailed. */
	virtual void OnDerail( const FVector& velocity );

	/** Called when this vehicle is derailed. */
	UFUNCTION( BlueprintImplementableEvent, meta = ( DisplayName = "OnDerail" ) )
	void ReceiveOnDerail();

	/** Called when this vehicle is re-railed. */
	virtual void OnRerail();

	/** Called when this vehicle is re-railed. */
	UFUNCTION( BlueprintImplementableEvent, meta = ( DisplayName = "OnRerail" ) )
	void ReceiveOnRerail();

	/** Show/hide the derail hologram. */
	void ShowDerailHologram();
	void HideDerailHologram();

	/** Debug */
	virtual void DisplayDebug( class UCanvas* canvas, const class FDebugDisplayInfo& debugDisplay, float& YL, float& YPos ) override;

protected:
	/** See below */
	UFUNCTION( Unreliable, NetMulticast )
	void OnCollided( AFGRailroadVehicle* withVehicle, float impactVelocity, bool isPrimaryEvent, bool isDerailed );

	/**
	 * Called on all clients when the trains collide, only called if the vehicle is significant.
	 * This event is unreliable and should only be used for effects.
	 * 
	 * @param withVehicle Vehicle we collided with.
	 * @param impactVelocity Our vehicles velocity.
	 * @param isPrimaryEvent Is this the primary collision event, meaning we caused the collision.
	 * @param isDerailed Is the train derailed from the collision.
	 */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCosmetic, meta = ( DisplayName = "OnCollided" ) )
	void ReceiveOnCollided( AFGRailroadVehicle* withVehicle, float impactVelocity, bool isPrimaryEvent, bool isDerailed );

	/** Get the mesh to spawn for the derail hologram actor. */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCosmetic )
	UStaticMesh* GetDerailHologramMesh();

	/** Helpers for the derail physics. */
	void EnableDerailPhysics( const FVector& velocity );
	void FreezeDerailPhysics();
	void DisableDerailPhysics();
	
private:
	/** Updates the vehicles settings depending on if it should be simulated or "real" */
	virtual void OnIsSimulatedChanged();

	/** Couple a vehicle at the given coupler, the new vehicle must be valid. */
	void CoupleVehicleAt( AFGRailroadVehicle* vehicle, ERailroadVehicleCoupler coupler );

	/** Decouple the vehicle at the given coupler. */
	void DecoupleVehicleAt( ERailroadVehicleCoupler coupler );

	/** On reps */
	UFUNCTION()
	void OnRep_IsOrientationReversed();
	UFUNCTION()
	void OnRep_IsDerailed();
protected:
	// About 1/5 of the distance to the world bounds and about the same as distance to the KillZ in the sky from sea level.
	static constexpr float MAX_DERAIL_DISTANCE = 200000.f;
	
	/** The train this vehicle is part of, updated from the railroad subsystem */
	UPROPERTY( Replicated, VisibleAnywhere, Category = "Vehicle" )
	class AFGTrain* mTrain;

	/** How long is this vehicle. */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	float mLength;

private:
	/** These need access to the vehicles internals. */
	friend class AFGRailroadSubsystem;
	friend class AFGTrain;
	friend class TTrainIterator;

	/**
	 * Vehicles coupled to this vehicle.
	 * 
	 * A train is a doubly linked list of AFGRailroadVehicles.
	 * Use TTrainIterator to iterate over a train (in any direction).
	 *
	 * Saved in serialize.
	 */
	UPROPERTY( Replicated )
	AFGRailroadVehicle* mCoupledVehicleFront;
	UPROPERTY( Replicated )
	AFGRailroadVehicle* mCoupledVehicleBack;

	/** If this vehicle is reversed in the train formation. */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_IsOrientationReversed )
	bool mIsOrientationReversed;

	/** Where along the track is the train. */
	UPROPERTY( SaveGame, Replicated )
	FRailroadTrackPosition mTrackPosition;

	/** If this vehicle is derailed, handles the derailment on client. */
	UPROPERTY( ReplicatedUsing = OnRep_IsDerailed, VisibleAnywhere )
	bool mIsDerailed;
	UPROPERTY( VisibleAnywhere )
	bool mIsMaxDerailDistanceReached;

	/** If we have derailed and are far enough from the location of the derailing, this is the hologram shown in place of the train. */
	TWeakObjectPtr< class AFGRailroadVehicleRerailHologram > mDerailHologram;
};
