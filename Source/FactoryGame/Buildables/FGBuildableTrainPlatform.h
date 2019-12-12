// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
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
	//ctor
	AFGBuildableTrainPlatform();

	// Replication
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

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

	/** Get the platform that preceeds this platform
	*	@param direction - 0 or 1 
	*	@info this can be null if the platform in the specified direction does not exist
	*/
	AFGBuildableTrainPlatform* GetConnectedPlatformInDirectionOf( uint8 direction );

	/** Notify the platform of its child track that is constucted by the train platform to be used for dismantling */
	void AssignChildTrackBuildable( class AFGBuildableRailroadTrack* railroadTrack );

	/** Get the Buildable Track that was constructed from the buildable hologram */
	class AFGBuildableRailroadTrack* GetChildTrackBuildable();

	/** Returns all the connection components */
	TArray<class UFGTrainPlatformConnection*> GetPlatformConnectionComponents();

	/** Should this register? Does the subsystem really need to know I exist */
	virtual bool ShouldRegisterOnTrack();

	/** Reverse the direction of the connection components in this platform */
	virtual void ReverseConnectionDirections();

	/** When a locomotive docks it will call this on relevant children in the direction of its output. It is up to the platform to decide how to act */
	virtual void NotifyTrainDocked( class AFGRailroadVehicle* railroadVehicle, class AFGBuildableRailroadStation* initiaedByStation );

	/** Set the orientation in regards to the track. Is it reversed? */
	void SetIsOrientationReversed( bool isReversed ) { mIsOrientationReversed = isReversed; }

	/** Is this platform reversed? */
	FORCEINLINE bool GetIsOrientationReversed() const { return mIsOrientationReversed; }

	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Platform" )
	ETrainPlatformDockingStatus GetDockingStatus() const { return mPlatformDockingStatus; }

protected:
	/** Timer Sequence Function to progress and handle all logic for docking
	*	When a platform is docked, a timer handle is created that updates the dock sequence until its completion that calls this function each step
	*/
	virtual	void UpdateDockingSequence();

	/** Call to clear all docking related properties, overrides should always call super */
	virtual void FinishDockingSequence();

	/** Update the docking status of Clients */
	UFUNCTION()
	virtual void OnRep_UpdateDockingStatus();

protected:
	UPROPERTY( SaveGame )
	class AFGBuildableRailroadTrack* mRailroadTrack;

	/** Each platform should have exactly 2 FGTrainPlatformConnectionComponents (Not a uproperty as it just holds refs to the below connections)
	*	They are individual components so that they appear correctly in the blueprint editor. If anyone sees this and knows a way to make containers
	*	of components be editable when inherited @me (dylan)
	*/
	TArray<class UFGTrainPlatformConnection*> mPlatformConnections;
	
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
	UPROPERTY( ReplicatedUsing=OnRep_UpdateDockingStatus )
	ETrainPlatformDockingStatus mPlatformDockingStatus;

	// The save state value to write for the stations docking status. It is modified in presave to force a docking reset if saved part way through.
	// However since it also drives the anim blueprint undesired anim starts are triggered if we save / modify the actually used mPlatformDockingStatus
	UPROPERTY( SaveGame )
	ETrainPlatformDockingStatus mSavedDockingStatus;

	// Timer handle that is set and retriggered over the course of a docking sequence
	UPROPERTY()
	FTimerHandle mDockingSequenceTimerHandle;

};
