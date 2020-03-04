// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "FGBuildableTrainPlatform.h"
#include "FGBuildableFactory.h"
#include "FGBuildableTrainPlatform.h"
#include "../FGTrainPlatformConnection.h"
#include "FGBuildableRailroadTrack.h"
#include "FGBuildableRailroadStation.generated.h"


//@todotrains Rename to TrainPlatformStation
/**
 * Base class for rail road stations. Not to be confused railroad docking stations.
 */
UCLASS()
class FACTORYGAME_API AFGBuildableRailroadStation : public AFGBuildableTrainPlatform
{
	GENERATED_BODY()
public:
	AFGBuildableRailroadStation();

	// Begin Actor interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	// End Actor interface

	// Begin save interface
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	// End save interface

	// Begin IFGDismantlableInterface
	virtual bool CanDismantle_Implementation() const override;
	// End IFGDismantlableInterface

	/** Get the station identifier for this station. Shared between server, client and used in time tables. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Station" )
	class AFGTrainStationIdentifier* GetStationIdentifier() const { return mStationIdentifier; }

	/** Called when the name of the station has changed. */
	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|Railroad|Station" )
	void OnNameChanged();

	/** Returns the component specified as an output (pointing away from the station to its children) */
	class UFGTrainPlatformConnection* GetStationOutputConnection();

	/** @return true if the given locomotive is valid for docking. */
	bool CanDock( class AFGLocomotive* locomotive );

	/**
	 * Start the docking sequence for the given locomotive.
	 * If docked the station is responsible for releasing the trains when docking is finished.
	 *
	 * @return true if we docked; false if we did not, e.g. no freight cars to dock.
	 */
	bool StartDocking( class AFGLocomotive* locomotive, float offset );

	/** Called by other platforms after a docking procedure to notify of their status */
	void NotifyPlatformDockingComplete( class AFGBuildableTrainPlatform* completedPlatform );

	/** Called by relevant docked platforms to get offset to use for position the arm claw */
	FORCEINLINE float GetDockedVehicleOffset() const { return mDockedPositionOffset; }

protected:
	// Begin AFGBuildableTrainPlatform
	virtual void SetupRailroadTrack() override;
	// End AFGBuildableTrainPlatform

private:
	/** Tries to dock each vehicle in the train to a platform */
	bool DockVehiclesToPlatforms( class AFGLocomotive* locomotive );

	/** Called when a docking sequence is complete to undock the locomotive and finalize the dock */
	virtual void FinishDockingSequence() override;

public:
	//@todotrains private
	/** Light weight representation about this station, the railroad subsystem is responsible for this. */
	UPROPERTY( Replicated )
	class AFGTrainStationIdentifier* mStationIdentifier;

private:
	/** When docked, this station will fill this array with every potential platform in its tail. 1 for each train segment */
	UPROPERTY( SaveGame )
	TArray< class AFGBuildableTrainPlatform* > mDockedPlatformList;

	/** Reference to the docked locomotive. */
	UPROPERTY( SaveGame )
	class AFGLocomotive* mDockingLocomotive;

	/** Stores the distance from the perfect center of the platform that a docked loco has stopped. Used to position the claw arm when loading/unloading. */
	float mDockedPositionOffset;

public:
	FORCEINLINE ~AFGBuildableRailroadStation() = default;
};
