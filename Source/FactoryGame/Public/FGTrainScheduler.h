// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "FGRailroadSignalBlock.h"
#include "Debug/FBlackBoxRecorder.h"
#include "FGTrainScheduler.generated.h"


/**
 * All information that is needed for the train scheduler to keep track of this train.
 */
struct FACTORYGAME_API FTrainSchedulerInfo
{
public:
	FTrainSchedulerInfo( class AFGTrain* train );
	~FTrainSchedulerInfo();

	/** Add a reservation to the list. */
	void AddReservation( TWeakPtr< FFGRailroadBlockReservation >& handle );
	/** Cancel all the reservations we hold. */
	void CancelReservations();
	/** @return true if we have a reservation for the given block already. */
	bool HaveReservation( TWeakPtr< FFGRailroadSignalBlock > block );
	
public:
	/** Train for this info. */
	class AFGTrain* Train = nullptr;
	
	/**
	 * Path that was used to make reservations, keep track of it in case it changes.
	 * If the previous path is cleared, then we need to clean any reservation pertaining to that path.
	 */
	FRailroadPathSharedPtr Path = nullptr;
	
	/**
	 * All our active block reservations.
	 * 
	 * A reservation is placed when:
	 *  1. Train is approaching a path signal that is red.
	 *  2. Is withing the braking distance of a block signal.
	 *
	 * Reservations in the array is in the order they occur along the path. Meaning higher indices are further ahead.
	 *
	 * The number of reservations in this list may vary depending on the length of the path signal chain reserved.
	 */
	TArray< TWeakPtr< FFGRailroadBlockReservation > > BlockReservations;

	/**
	 * Does this train need any approvals.
	 */
	bool NeedApproval = false;

	/**
	 * This is the result from a topological sort done on all the trains.
	 *
	 * The numbers mean:
	 *        -1: Invalid.
	 *         0: No dependencies on other trains.
	 *        >0: We are part of a dependency chain and this is our position in this chain.
	 * Num Infos: We are part of a circular dependency chain.
	 */
	int32 DependencyLevel = -1;
	
	/**
	 * When a chain of reservations are made, this is updated with a reservation number.
	 * This is weighted into the priorities to provide fairness and avoid starvation in the scheduler.
	 */
	uint32 ReservationNumber = 0;

	/**
	 * The priority for this train when requests are handled.
	 *
	 * Lower number mean higher priority.
	 */
	int32 Priority = 0;

	/** All the trains we depend on. */
	TSet< TWeakObjectPtr< class AFGTrain > > TrainDependencies;
};


/**
 * Class responsible for scheduling trains moving across the rail network.
 * A self driving train will always drive forward when a signal is green and stop for a red signal so way this class can control the
 * movement of a train is through reservations into the blocks. Reservations are the primary way to turn path signals green and block signals red.
 *
 * The responsibilities of this class:
 * Creating and approving reservations for trains into path blocks (or exclusive reservations into regular blocks).
 * Updating progress of active reservations and remove them when not needed anymore.
 * Prioritize the trains' reservations to avoid deadlocks but also to be fair and avoid starvation.
 *
 * If you want to dive into the code I recommend starting in the TickScheduler function which is the entry point into the core logic.
 */
UCLASS()
class FACTORYGAME_API AFGTrainScheduler : public AInfo
{
	GENERATED_BODY()
public:
	AFGTrainScheduler();

	// Begin AActor
	virtual void DisplayDebug( class UCanvas* canvas, const class FDebugDisplayInfo& debugDisplay, float& YL, float& YPos ) override;
	// End AActor
	
	/** Add a train to be tracked by the scheduler. */
	void AddTrain( class AFGTrain* train );

	/** Remove a train from scheduler tracking. */
	void RemoveTrain( class AFGTrain* train );

	/** Ticks the scheduler and makes reservation on behalf of the tracked trains. */
	void TickScheduler();

public:
	/**
	 * Enable the black box, it will tick and directly outputs state to the log or records the history and outputs to the log when the dump function is called.
	 * @param isEnabled If the black box is enabled or not.
	 * @param numRecordsToKeep If 0, directly output to the log, otherwise store n records in history until Dump is called.
	 */
	void Debug_EnableBlackBox( bool isEnabled, int32 numRecordsToKeep );
	/** Dumps the content of the black box. */
	void Debug_DumpBlackBox();
	
private:
	/** "Tickers" to manage reservations throughout their lifetime. See cpp for details. */
	void UpdateReservations();
	void MakeNewReservations();
	void UpdateDependencies();
	void UpdatePrioritiesAndSort();
	void ApproveReservations();

	void ApproveReservation( FFGRailroadBlockReservation* reservation );
	void ApproveReservation( FFGRailroadBlockReservation* reservation, const TSet< TWeakObjectPtr< AFGTrain > >& dependencies );
	void UpdateApprovedReservation( FFGRailroadBlockReservation* reservation );

	/** See FTrainSchedulerInfo */
	uint32 GetReservationNumber() const;
	uint32 GetNextReservationNumber();

	/** Dump the internal state. */
	void Debug_UpdateBlackBox();
	
	/**
	 * Checks for a deadlocks in the scheduling.
	 * 
	 * This only checks for direct deadlocks (2 trains) and not indirect deadlocks (3+ trains).
	 * This checks all trains against all other trains so operation might be expensive.
	 * 
	 * @return Returns the two trains that are deadlocked.
	 */
	TTuple< class AFGTrain*, class AFGTrain* > Debug_CheckForDeadlock() const;
	
	/**
	 * Check if there are any trains that have derailed.
	 *
	 * @return an empty list if everything is fine.
	 */
	TArray< class AFGTrain* > Debug_CheckForDerailments() const;
	
private:
	/** Scheduling information for the tracked trains. */
	TMap< class AFGTrain*, TUniquePtr< FTrainSchedulerInfo > > mSchedulerInfos;

	/** Counter for giving out reservation numbers. */
	int32 mReservationCounter = 0;
	/** At which number the reservation counter rolls over to 0. This number must be a power of 10. */
	int32 mReservationCounterRolloverAt = 100000;
	
	/** Black box recorder used to track down issues leading to crashes or deadlocks. */
	bool mDebugEnableBlackBox = false;
	FBlackBoxRecorder mDebugBlackBox;
};
