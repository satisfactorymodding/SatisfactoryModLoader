// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "FGRailroadSignalBlock.h"
#include "FGTrainScheduler.generated.h"


struct FACTORYGAME_API FTrainAtcBlockReservation
{
public:
	/** True if the reservation has been successfully made, false if not. */
	bool IsReserved = false;
	
	/**
	* Reference to the block reserved.
	* This may become null if the block becomes invalid.
	*/
	TWeakPtr< FFGRailroadSignalBlock > Block = nullptr;
	
	/**
	* Reference to the reservation made.
	* This may become null if the block clears the reservation, train exits block, or if the block becomes invalid.
	*/
	TWeakPtr< FFGRailroadBlockReservation > Handle = nullptr;

	/** At which signal is this reservation starting, this is only used for partial reservations. */
	TWeakObjectPtr< AFGBuildableRailroadSignal > EntrySignal = nullptr;
	/** At which path segment is this reservation starting, this is only used for partial reservations. */
	int32 EntryPathSegment = INDEX_NONE;
};


/**
 * All information that is needed for the train scheduler to keep track of this train.
 */
struct FACTORYGAME_API FTrainSchedulerInfo
{
public:
	FTrainSchedulerInfo( class AFGTrain* train );
	~FTrainSchedulerInfo();
	
	/**
	 * Clear all the reservations we hold.
	 */
	void ClearBlockReservations();

public:
	/**
	 * The train being tracked.
	 */
	TWeakObjectPtr< AFGTrain > Train = nullptr;
	
	/**
	 * Path that was used to make reservations, keep track of it in case it changes.
	 * If the previous path is cleared, then we need to clean any reservation pertaining to that path.
	 */
	FRailroadPathWeakPtr Path = nullptr;
	
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
	TArray< FTrainAtcBlockReservation > BlockReservations;
};


/**
 * When making a reservation request this is the type of request, their priority is their order in the list, higher number is higher priority.
 */
enum class ETrackReservationRequestType
{
	TRRT_Invalid,
	TRRT_EntryPathSignal,
	TRRT_PlayerEntryPathSignal, //@todo-trains Add support
	TRRT_InsidePathBlock
};


/**
 * A block reservation request made by a train.
 */
struct FACTORYGAME_API FTrackReservationRequest
{
public:
	FTrackReservationRequest(
		TWeakPtr< FTrainSchedulerInfo > requesterInfo,
		ETrackReservationRequestType type,
		int32 pathSegment,
		TWeakPtr< FFGRailroadSignalBlock > block,
		class AFGBuildableRailroadSignal* signal );

	/** Checks if this request is valid. */
	bool IsValid() const;

public:
	/** Who made this request, might become null from the time of the request to the handling of the request. */
	TWeakPtr< FTrainSchedulerInfo > RequesterInfo = nullptr;
	
	/** Type of request, must be any other value that invalid. */
	ETrackReservationRequestType Type = ETrackReservationRequestType::TRRT_Invalid;
	
	/** Set to true by the system when this request have been handled. */
	bool Handled = false;
	
	/** Signal we're making this request in front of, can be null if reservation is made inside a block. */
	TWeakObjectPtr< class AFGBuildableRailroadSignal > Signal = nullptr;
	
	/**
	 * Segment which marks the start of the reservation, i.e. segment of the signal or segment we're at inside the block.
	 * Can be invalid if we are reserving the whole block.
	 */
	int32 PathSegment = INDEX_NONE;
	
	/** Block we are making the reservation request to. Cannot be null. */
	TWeakPtr< FFGRailroadSignalBlock > Block = nullptr;
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
	
private:
	/**
	 * Request access to the blocks along the path, signals will turn green when the reservation is successfully handled.
	 */
	void RequestReservation( const FTrackReservationRequest& request );
	
	/**
	 * Cancels all reservation requests that the given train have at the moment.
	 */
	void CancelAllReservationRequests( class AFGTrain* train );

	/**
	 * Tick all the reservation requests in the system.
	 */
	void TickReservationRequests();
	
	/**
	 * Called when the scheduler wants a train to handle it's reservation request.
	 */
	void HandleReservationRequest( FTrackReservationRequest& request );

	/**
	 * Update the block reservations for the given info.
	 */
	void TickBlockReservations( TSharedPtr< FTrainSchedulerInfo > info );
private:
	/** List of information for the tracked trains. */
	TArray< TSharedPtr< FTrainSchedulerInfo > > mSchedulerInfos;
	
	/** Reservation requests are put in this queue according to their priority and at the end of the frame the scheduler handles them in order. */
	TArray< FTrackReservationRequest > mReservationRequests;
};
