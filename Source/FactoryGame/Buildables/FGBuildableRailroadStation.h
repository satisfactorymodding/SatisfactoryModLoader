// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "FGBuildableFactory.h"
#include "FGBuildableTrainPlatform.h"
#include "../FGTrainPlatformConnection.h"
#include "../FGRailroadInterface.h"
#include "FGBuildableRailroadTrack.h"
#include "FGBuildableRailroadStation.generated.h"

UENUM()
enum class EStationDockingStatus
{
	ESDS_NotDocked,
	ESDS_DockInProcess,
	ESDS_DockComplete
};

/**
 * Base class for rail road stations. Not to be confused railroad docking stations.
 */
UCLASS()
class FACTORYGAME_API AFGBuildableRailroadStation : public AFGBuildableTrainPlatform, public IFGRailroadInterface
{
	GENERATED_BODY()
public:
	AFGBuildableRailroadStation();

	// Begin Actor interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	// End Actor interface

	// Begin IFGDismantlableInterface
	virtual bool CanDismantle_Implementation() const override;
	// End IFGDismantlableInterface

	// Begin IFGRailroadInterface
	virtual void RegisteredOnTrack_Implementation( const FRailroadTrackPosition& position ) override;
	virtual void UnregisteredFromTrack_Implementation() override;
	virtual FRailroadTrackPosition GetTrackPosition_Implementation() const override;
	virtual int32 GetTrackGraphID_Implementation() const override;
	// End IFGRailroadInterface

	// Begin BuildableTrainPlatform Implementation
	virtual bool ShouldRegisterOnTrack() override;
	// End BuildableTrainPlatform Implementation

	// Begin Factory_ interface
	virtual void Factory_Tick( float dt ) override;
	// End Factory_ interface

	/** Get the station identifier for this station. Shared between server, client and used in time tables. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Station" )
	class AFGTrainStationIdentifier* GetStationIdentifier() const { return mStationIdentifier; }

	/** Notify of begin docking procedure */
	UFUNCTION( BlueprintNativeEvent, Category = "FactoryGame|Railroad|Station" )
	void OnLocomotiveDocked();

	/** Called by other platforms after a docking procedure to notify of their status */
	void NotifyPlatformDockingComplete( class AFGBuildableTrainPlatform* completedPlatform );

	/** Called by relevant docked platforms to get offset to use for position the arm claw */
	FORCEINLINE float GetDockedVehicleOfset() const { return mDockedPositionOffset; }

	/** Returns the component specified as an output (pointing away from the station to its children) */
	class UFGTrainPlatformConnection* GetStationOutputConnection();

	/** Called when the name of the station has changed. */
	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|Railroad|Station" )
	void OnNameChanged();

private:
	/** Temp: Function called when collider is overlaped to test for docking */
	UFUNCTION()
	void OnDockingColliderBeginOverlap( UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult );

	/** Temp: Function called when collider is unoverlapped to stop testing for docking */
	UFUNCTION()
	void OnDockingColliderEndOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex );

	/** Called by a timer to check if a train has docked */
	UFUNCTION()
	void PerformIsDockedCheck();

	/** Called when a docking sequence is complete to undock the locomotive and finalize the dock */
	virtual void FinishDockingSequence() override;


public:
	//@todotrains private
	/** Light weight representation about this station, the railroad subsystem is responsible for this. */
	UPROPERTY( Replicated )
	class AFGTrainStationIdentifier* mStationIdentifier;

protected:
	/** Enum tracking the status of a docking sequence */
	UPROPERTY( SaveGame, Replicated, BlueprintReadOnly, Category = "FactoryGame|Railroad|Station" )
	EStationDockingStatus mStationDockingStatus;

	/** When docked, this station will fill this array with every potential platform in its tail. 1 for each train segment */
	UPROPERTY( SaveGame )
	TArray< class AFGBuildableTrainPlatform* > mDockedPlatformList;

	/** Stores the distance from the perfect center of the platform that a docked loco has stopped. Used to position the claw arm when loading/unloading */
	float mDockedPositionOffset;

	/** When docked, a TTrainIterator is used to find all trailing (relevant) train carts matching the direction of this station on the track */
	UPROPERTY()
	TArray< TWeakObjectPtr< class AFGRailroadVehicle > > mRelevantDockedVehicles;



private:
	/** Collider, TEMP I hope, used for detecting overlap with train locomotives for docking */
	UPROPERTY(EditAnywhere)
	class UBoxComponent* mStationDockCollider;

	/** TimerHandle for checking the status of a docking sequence and updating it */
	UPROPERTY()
	FTimerHandle mUpdateDockingStatusTimer;

	/** Locomotive Docking Reference, presently set by a collider overlap */
	UPROPERTY( SaveGame )
	class AFGLocomotive* mDockingLocomotive;

	/** Max speed to consider locomotive docked (if traveling faster than this then locos cannot dock) */
	UPROPERTY( EditDefaultsOnly, Category = "FactoryGame|Railroad|Station" )
	float mMaxDockSpeed;

	/** Max offset from track center to allow a locomotive to be considered docked */
	UPROPERTY( EditDefaultsOnly, Category = "FactoryGame|Railroad|Station" )
	float mMaxDockDistanceFromCenter;

	/** Where on the track is this station located. */
	UPROPERTY( SaveGame, Meta = ( NoAutoJson = true ) )
	FRailroadTrackPosition mTrackPosition;

};
