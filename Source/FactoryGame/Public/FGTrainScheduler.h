// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "FGRailroadSignalBlock.h"
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
	/**
	 * The train being tracked.
	 */
	TWeakObjectPtr< AFGTrain > Train = nullptr;
	
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
	 * The priority for this train when requests are handled.
	 *
	 * Higher number have higher priority.
	 */
	int32 Priority = -1;

	/** The overlaps that this this train have along its path. */
	ERailroadPathOverlap PathOverlaps = ERailroadPathOverlap::RPO_None;
};


/**
 * Class responsible for scheduling trains across signal blocks.
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
	/** Each tick we output details about the scheduling, and decrease this by one. Only valid in non-shipping builds. */
	int32 mDebugDumpNextTick;
	
private:
	//@todo-trains Split the master tick into manageable functions.
	
private:
	/** List of information for the tracked trains. */
	TArray< TSharedPtr< FTrainSchedulerInfo > > mSchedulerInfos;
};
