// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

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
	virtual bool IsNetRelevantFor( const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation ) const override;
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	virtual void Serialize( FArchive& ar ) override;
	virtual void Tick( float dt ) override;
	// End AActor interface

	//~ Begin IFGDismantleInterface
	virtual bool CanDismantle_Implementation() const override;
	//~ End IFGDismantleInterface

	// Train platform docking events
	// Does not utilize dockable interface as train platforms are not dockables and it confuses the situation to mix some of the interface calls with new functions
	virtual void DockedWithPlatform( class AFGBuildableTrainPlatform* dockedPlatform );
	virtual void UndockedWithPlatform();
	// End platform docking events 

	/** Update the animations for this vehicle, this is called after the whole train has been moved. */
	void UpdateAnimation();

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

	/** Get the sliding shoe if this  */

	/**
	 * @return The length of this vehicle.
	 */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Vehicle" )
	FORCEINLINE float GetLength() const { return mLength; }

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
	FORCEINLINE bool IsCoupledAt( ERailroadVehicleCoupler coupler ) const { return mCoupledVehicles[ ( uint8 )coupler ].IsValid(); }

	/**
	 * @param at Coupler, valid values are 0 (front) and 1 (back).
	 * @return the vehicle coupled at index.
	 */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Vehicle" )
	FORCEINLINE AFGRailroadVehicle* GetCoupledVehicleAt( ERailroadVehicleCoupler coupler ) const { return mCoupledVehicles[ ( uint8 )coupler ].Get(); }
	
	/**
	 * Get the track position for this vehicle.
	 */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Vehicle" )
	FORCEINLINE FRailroadTrackPosition GetTrackPosition() const { return mTrackPosition; }

	/** 
	 * Get the track id this vehicle is on; -1 if the track is invalid.
	 */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Vehicle" )
	FORCEINLINE int32 GetTrackGraphID() const { return mTrackPosition.IsValid() ? mTrackPosition.Track->GetTrackGraphID() : INDEX_NONE; }

	/**
	 * Set the track position for this vehicle, be careful cause the actor and any coupled vehicles will not get moved.
	 */
	FORCEINLINE void SetTrackPosition( const FRailroadTrackPosition& position ) { mTrackPosition = position; }

	/**	Get if this vehicle is currently docked with a train platform */
	FORCEINLINE bool GetIsDockedAtPlatform() const { return mDockedAtPlatform != nullptr; }

	/** Debug */
	virtual void DisplayDebug( class UCanvas* canvas, const class FDebugDisplayInfo& debugDisplay, float& YL, float& YPos ) override;

private:
	bool IsVehicleNetRelevantFor( const class AFGRailroadVehicle* vehicle, const FVector& SrcLocation ) const;

	/**
	 * @param at Coupler to connect to.
	 */
	void CoupleVehicleAt( AFGRailroadVehicle* vehicle, ERailroadVehicleCoupler coupler );

	/**
	 * @param at Coupler to connect to.
	 */
	void DecoupleVehicleAt( ERailroadVehicleCoupler coupler );

protected:
	/** The train this vehicle is part of, updated from the railroad subsystem */
	UPROPERTY( Replicated )
	class AFGTrain* mTrain;

	/** How long is this vehicle. */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	float mLength;

	/** Store the platform, if any, this train vehicle is docked at */
	UPROPERTY( Replicated )
	class AFGBuildableTrainPlatform* mDockedAtPlatform;

private:
	/** These need access to the vehicles internals. */
	friend class AFGRailroadSubsystem;
	friend class TTrainIterator;

	/**
	 * A train is a doubly linked list of AFGRailroadVehicles.
	 * Use TTrainIterator to iterate over a train (in any direction).
	 *
	 * Vehicles coupled to this vehicle.
	 * Use ERailroadVehicleCoupler to access this.
	 */
	UPROPERTY() // Saved in serialize.
	TWeakObjectPtr< AFGRailroadVehicle > mCoupledVehicles[ 2 ];

	/** If this vehicle is reversed in the train formation. */
	UPROPERTY( SaveGame )
	bool mIsOrientationReversed;

	/** Where along the track is the train. */
	UPROPERTY( SaveGame )
	FRailroadTrackPosition mTrackPosition;

};
