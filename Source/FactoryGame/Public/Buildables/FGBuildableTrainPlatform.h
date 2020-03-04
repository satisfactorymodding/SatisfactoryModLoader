// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Buildables/FGBuildableFactory.h"
#include "FGBuildableRailroadTrack.h"
#include "FGBuildableFactory.h"
#include "FGBuildableTrainPlatform.generated.h"


UENUM( BlueprintType )
enum class ETrainPlatformDockingStatus : uint8
{
	ETPDS_None					UMETA( DisplayName = "None" ),
	ETPDS_WaitingToStart		UMETA( DisplayName = "WaitingToStart" ),
	ETPDS_Loading				UMETA( DisplayName = "Loading" ),
	ETPDS_Unloading				UMETA( DisplayName = "Unloading" ), 
	ETPDS_WaitingForTransfer	UMETA( DisplayName = "WaitingTransfer" ),
	ETPDS_Complete				UMETA( DisplayName = "Complete" )
};

/**
 *	Base class for any train platform (station, cargo loading, empty etc. )
 */
UCLASS( )
class FACTORYGAME_API AFGBuildableTrainPlatform : public AFGBuildableFactory
{
	GENERATED_BODY()
public:
	AFGBuildableTrainPlatform();

	// Begin Actor interface
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	// End Actor interface

	// Begin save interface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	// End save interface

	// Begin IFGDismantlableInterface
	virtual bool CanDismantle_Implementation() const override;
	virtual void Dismantle_Implementation() override;
	virtual void GetDismantleRefund_Implementation( TArray< FInventoryStack >& out_refund ) const override;
	// End IFGDismantlableInterface

	//~ Begin IFGUseableInterface
	virtual bool IsUseable_Implementation() const override;
	//~ End IFGUseableInterface

	//@todotrains Get rid of the dependency on track position in platforms.
	FRailroadTrackPosition GetTrackPosition() const;
	int32 GetTrackGraphID() const;

	/** Get the platform that precedes this platform
	*	@param direction - 0 or 1 
	*	@info this can be null if the platform in the specified direction does not exist
	*/
	AFGBuildableTrainPlatform* GetConnectedPlatformInDirectionOf( uint8 direction );

	/** When a locomotive docks it will call this on relevant children in the direction of its output. It is up to the platform to decide how to act */
	virtual void NotifyTrainDocked( class AFGRailroadVehicle* railroadVehicle, class AFGBuildableRailroadStation* initiatedByStation );

	/** Is this platform reversed? */
	FORCEINLINE bool IsOrientationReversed() const { return mIsOrientationReversed; }

	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Platform" )
	ETrainPlatformDockingStatus GetDockingStatus() const { return mPlatformDockingStatus; }

	/** Timer Sequence Function to progress and handle all logic for docking
	 *	When a platform is docked, a timer handle is created that updates the dock sequence until its completion that calls this function each step
	 */
	virtual	void UpdateDockingSequence();

protected:
	/** his needs to happed from the hologram and from begin play */
	virtual void SetupRailroadTrack();

	/** Call to clear all docking related properties, overrides should always call super */
	virtual void FinishDockingSequence();

	/** Update the docking status of Clients */
	UFUNCTION()
	virtual void OnRep_UpdateDockingStatus();

private:
	/** Used by the hologram to configure this platform. */
	void ReverseConnectionDirections();
	void AssignRailroadTrack( class AFGBuildableRailroadTrack* track );

protected:
	UPROPERTY( SaveGame )
	class AFGBuildableRailroadTrack* mRailroadTrack;

	/** Each platform should have exactly 2 FGTrainPlatformConnectionComponents (Not a uproperty as it just holds refs to the below connections)
	*	They are individual components so that they appear correctly in the blueprint editor. If anyone sees this and knows a way to make containers
	*	of components be editable when inherited @me (dylan)
	*/
	UPROPERTY()
	TArray< class UFGTrainPlatformConnection* > mPlatformConnections;
	
	UPROPERTY( EditAnywhere )
	class UFGTrainPlatformConnection* mPlatformConnection0;

	UPROPERTY( EditAnywhere )
	class UFGTrainPlatformConnection* mPlatformConnection1;

	UPROPERTY( Replicated, SaveGame )
	class AFGRailroadVehicle* mDockedRailroadVehicle;

	/** Stores a reference to the station that initiated a docking sequence. Used to notify the station that we have completed */
	UPROPERTY( SaveGame )
	class AFGBuildableRailroadStation* mStationDockingMaster;

	// Is this platform reversed from its attached station?
	UPROPERTY( SaveGame )
	bool mIsOrientationReversed;

	// Where are we in the docking status. Updated by the mDockingSequenceTimer which is set by NotifyTrainDocked
	UPROPERTY( ReplicatedUsing = OnRep_UpdateDockingStatus )
	ETrainPlatformDockingStatus mPlatformDockingStatus;

	// The save state value to write for the stations docking status. It is modified in presave to force a docking reset if saved part way through.
	// However since it also drives the anim blueprint undesired anim starts are triggered if we save / modify the actually used mPlatformDockingStatus
	UPROPERTY( SaveGame )
	ETrainPlatformDockingStatus mSavedDockingStatus;

	// Timer handle that is set and retriggered over the course of a docking sequence
	UPROPERTY()
	FTimerHandle mDockingSequenceTimerHandle;

private:
	friend class AFGTrainPlatformHologram; //@todotrains use this instead of setters and getters for everything.

public:
	FORCEINLINE ~AFGBuildableTrainPlatform() = default;
};
