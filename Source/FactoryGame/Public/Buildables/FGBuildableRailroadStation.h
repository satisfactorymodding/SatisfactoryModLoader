// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "Buildables/FGBuildableTrainPlatform.h"
#include "FGActorRepresentationInterface.h"
#include "FGTrainDockingRules.h"
#include "FGBuildableRailroadStation.generated.h"


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

	// Begin Factory_ interface
	virtual void Factory_Tick( float dt ) override;
	// End Factory_ interface

	// Begin AFGBuildableFactory interface
	virtual bool CanProduce_Implementation() const override;
	// End AFGBuildableFactory interface

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

	/** Fetches the texture to use for this actors representation */
	class UTexture2D* GetDefaultRepresentationTexture() { return mActorRepresentationTexture; }
	
	/** Fetches the color to use for this actors representation */
	UFUNCTION( BlueprintImplementableEvent, Category = "Representation" )
	FLinearColor GetDefaultRepresentationColor();

	/** Fetches the color to use for this actors representation */
	UFUNCTION( BlueprintImplementableEvent, Category = "Representation" )
	void SetRepresentationText( const FText& text );

	/** Fetches the color to use for this actors representation */
	UFUNCTION( BlueprintImplementableEvent, Category = "Representation" )
	FText GetRepresentationText();

	/** Overrides the current rule sets wait time, can be used to change the time duration rule for the currently docked train. 
	 *	@note - This does not update the timetable rule set. It only temporarily changes it. Useful for fixing a duration that is too long
	 */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|RailRoad|Station" )
	void ClearRuleSetTimeRequirement() { mCurrentDockedWithRuleSet.DockForDuration = 0.f; }

	/** Gets the duration a train has been docked at the station for */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|RailRoad|Station" )
	FORCEINLINE float GetCurrentDockForDuration() const { return mCurrentDockForDuration; }

	/** Returns the active rule set for the currently docked train */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|RailRoad|Station" )
	FORCEINLINE FTrainDockingRuleSet GetDockedTrainRuleSet() const { return mCurrentDockedWithRuleSet; }

	/** Cancel the current dock. This will notify all platforms in the docked platform list */
	virtual void CancelDockingSequence() override;

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
	/** If this is a cheat station that the train should teleport to. Functionality stripped in public builds. */
	UPROPERTY( EditDefaultsOnly )
	bool mShouldTeleportHere;
	
	//@todo-trains private
	/** Light weight representation about this station, the railroad subsystem is responsible for this. */
	UPROPERTY( Replicated )
	class AFGTrainStationIdentifier* mStationIdentifier;

private:
	/** When docked, this station will fill this array with every potential platform in its tail. 1 for each train segment */
	UPROPERTY( SaveGame )
	TArray< class AFGBuildableTrainPlatform* > mDockedPlatformList;

	UPROPERTY( SaveGame )
	FTrainDockingRuleSet mCurrentDockedWithRuleSet;

	/** Reference to the docked locomotive. */
	UPROPERTY( SaveGame )
	class AFGLocomotive* mDockingLocomotive;

	/** How long has the current train been docked for at this station? */
	UPROPERTY( SaveGame )
	float mCurrentDockForDuration;

	/** Stores the distance from the perfect center of the platform that a docked loco has stopped. Used to position the claw arm when loading/unloading. */
	float mDockedPositionOffset;

	UPROPERTY( EditDefaultsOnly, Category = "Representation" )
	class UTexture2D* mActorRepresentationTexture;
};
