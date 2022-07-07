// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "RailroadNavigation.h"
#include "FGRailroadSignalBlock.generated.h"


/** Error enum for block validation. */
UENUM( BlueprintType )
enum class ERailroadBlockValidation : uint8
{
	RBV_Unvalidated 				UMETA( DisplayName = "Unvalidated" ),
	RBV_Valid 						UMETA( DisplayName = "Valid" ),
	RBV_NoExitSignals				UMETA( DisplayName = "No Exit Signal" ),
	RBV_ContainsLoop				UMETA( DisplayName = "Contains Loop" ),
	RBV_ContainsMixedEntrySignals	UMETA( DisplayName = "Contains Mixed Entry Signals" ),
	RBV_ContainsStation				UMETA( DisplayName = "Contain Station" ),
};


/** Status this block can have at a given entry signal. */
enum class ERailroadBlockOccupancy : uint8
{
	RBO_Clear,
	RBO_Occupied,
	RBO_ReservationNeeded,
	RBO_ReservationExclusive
};


/** How have this block been reserved. */
enum class ERailroadBlockReservationType : uint8
{
	RBRT_Exclusive,
	RBRT_Path,
	RBRT_PartialPath
};

/**
 * Helper to check against another reservation.
 *
 * Order is important, the more sever the higher the enum number, we find the most severe overlap and base decisions on that.
 */
enum class ERailroadPathOverlap : int8
{
	RPO_None						= 0x00,
	RPO_PathInSameDirection			= 0x01,
	RPO_PathInOppositeDirection		= 0x02,
	RPO_PathOnNeighboringTrack		= 0x04, //@todo-signals See comment about how to handle forks, is this higher or lower than RPO_PathInSameDirection? Higher, a train cannot start on the path (safer), lower and the train can potentially start the path if other segments are not opposing?
	RPO_OccupiedNeighboringTrack	= 0x08,
	RPO_OccupiedTrack				= 0x10,
	RPO_ExclusiveTrack				= 0x20,
	RPO_Max							= 0x40
};
inline ERailroadPathOverlap operator|( ERailroadPathOverlap a, ERailroadPathOverlap b ) { return static_cast< ERailroadPathOverlap >( static_cast< int8 >( a ) | static_cast< int8 >( b ) ); }
inline ERailroadPathOverlap& operator|=( ERailroadPathOverlap& a, ERailroadPathOverlap b ) { return reinterpret_cast< ERailroadPathOverlap& >( reinterpret_cast< int8& >( a ) |= static_cast< int8 >( b ) ); }
inline ERailroadPathOverlap operator&( ERailroadPathOverlap a, ERailroadPathOverlap b ) { return static_cast< ERailroadPathOverlap >( static_cast< int8 >( a ) & static_cast< int8 >( b ) ); }
inline ERailroadPathOverlap operator>=( ERailroadPathOverlap a, ERailroadPathOverlap b ) { return static_cast< ERailroadPathOverlap >( static_cast< int8 >( a ) >= static_cast< int8 >( b ) ); }
inline ERailroadPathOverlap operator>( ERailroadPathOverlap a, ERailroadPathOverlap b ) { return static_cast< ERailroadPathOverlap >( static_cast< int8 >( a ) >= static_cast< int8 >( b ) ); }
// For logging only.
FString RailroadPathOverlapToString( ERailroadPathOverlap flags );

/**
 * Lets us keep track of segments and their direction so we can allow reservations in the same direction but not in opposite directions, this is to avoid deadlock situations.
 */
struct FRailroadReservedSegment
{
	/**
	 * Track that is being reserved.
	 * Not a guarded pointer as the reservations are cleared if a track is dismantled.
	 */
	class AFGBuildableRailroadTrack* Track;

	/*
	 * Keep track of the direction of the reservation so we can avoid deadlocks by making reservations in opposing directions.
	 * 1: Forward
	 * -1: Backward
	 * 0: Unknown
	 **/
	int8 Direction = 0;
};


/**
 * Holds all relevant information about a reservation into a block.
 */
struct FACTORYGAME_API FFGRailroadBlockReservation
{
public:
	/** Update the info for the reservation, such as occupancy and overlaps. */
	void Update();
	/** Approve reservation. If successful the reservation is marked with approved. */
	void Approve();
	/** Cancels the given reservation, if the reservation is invalid, this does nothing. */
	void Cancel();
	/** Notify the reservation that the train has entered. Used to clear entry signals. */
	void NotifyEntered();
	/** Notify the exit condition for the signal block chain this is part of. */
	void NotifyExitCondition( bool isClear );
	/** @return true if the train has exited the reserved area. */
	bool HasExitedReservation( class AFGTrain* train );
	
public:
	/** The block this reservation was made in. */
	TWeakPtr< struct FFGRailroadSignalBlock > Block;

	/** Saved name for owner of this reservation, used for debugging purposes. */
	FString TrainName;
	
	/** The type of this reservation. */
	ERailroadBlockReservationType Type = ERailroadBlockReservationType::RBRT_Exclusive;

	/** Is this reservation on hold, meaning it has the lowest priority at the moment. */
	bool IsExitClear = false;
	
	/** true if the reservation is approved, meaning path is now clear; false if there is a train or reservation blocking. */
	bool IsApproved = false;

	/**
	 * Priority of this request compared to other requests in the same block.
	 * Higher number is higher priority.
	 * -1: Uninitialized, and lowest priority possible.
	 * 0: Is the lowest that should be set from outside code.
	 */
	int32 Priority = -1;

	/** Position of this reservation in the approval queue, lower number is served first. */
	int8 QueuePosition = INDEX_NONE;
	
	/** Information about the block from the last update. */
	ERailroadPathOverlap Overlap;
	
	/**
	 * The entry point into the block.
	 * This is used to keep this signal green (valid entry).
	 * This is reset when the train enters the reserved block.
	 */
	TWeakObjectPtr< class AFGBuildableRailroadSignal > EntrySignal;

	/**
	 * First path segment in this reservation.
	 * This is reset when the train enters the reserved block.
	 */
	int32 EntryPathSegment = INDEX_NONE;
	
	/**
	 * The exit point out of the block.
	 * Used to traverse chained signals.
	 * Can be null if it is either a non path reservation or if the destination is inside a path block.
	 */
	TWeakObjectPtr< class AFGBuildableRailroadSignal > ExitSignal;
	
	/**
	 * Last path segment in this reservation, only used for path reservations.
	 * When the lead engine passes this segment, the path reservation can be safely cleared.
	 */
	int32 ExitPathSegment = INDEX_NONE;
	
	/**
	 * Tracks in this reservation, if empty the whole block is reserved.
	 */
	TArray< FRailroadReservedSegment > Segments;

	/**
	 * Tracks that this reservation overlaps.
	 * Not a guarded pointer as the reservations are cleared if a track is dismantled.
	 */
	TSet< class AFGBuildableRailroadTrack* > OverlappingTracks;
};


/**
 * Representing a signal block in the track graph. Keeps track of blocks
 */
struct FACTORYGAME_API FFGRailroadSignalBlock : public TSharedFromThis< FFGRailroadSignalBlock >
{
public:
	/**
	 * Called bu the tracks when a vehicle enters and exits a section of track.
	 *
	 * The number of calls to enter and exit must match up in a way so that every enter have an exit.
	 */
	void BlockEntered( class AFGRailroadVehicle* byVehicle );
	void BlockExited( class AFGRailroadVehicle* byVehicle );

	/**
	 * See if this block is occupied from the given signals perspective.
	 *
	 * For standard blocks, this reflects the occupancy of the block and any reservations from a trains brake distance.
	 * For path blocks, multiple inbound signals might be green at the same time.
	 *
	 * If no signal is given, this always returns true.
	 */
	ERailroadBlockOccupancy GetOccupancyFor( class AFGBuildableRailroadSignal* signal ) const;
	
	/** @return If this block is occupied by vehicles. */
	bool IsOccupied() const;

	/** @return true if this block is occupied by the given train, otherwise false. */
	bool IsOccupiedBy( class AFGTrain* train ) const;

	/**
	 * Creates and queues a reservation for a train into this block.
	 * It is only valid to reserve a path inside a path block.
	 * Follow up on this call with a call to ApproveReservation.
	 * 
	 * @param train The train that makes the reservation. For debugging.
	 * @param entrySignal The signal we will be entering from into this block.
	 * @param trainPath The path we want to book.
	 * @param entryPathSegment Where along the path we are right now.
	 *
	 * @return A reservation handle on success, otherwise null.
	 */
	TWeakPtr< FFGRailroadBlockReservation > CreateReservation( class AFGTrain* train, AFGBuildableRailroadSignal* entrySignal, int32 entryPathSegment, FRailroadPathSharedPtr trainPath );
	
	/**
	 * Create a reservation for a train into this block.
	 * This is valid on any block, creates an exclusive reservation on path blocks.
	 * Follow up on this call with a call to ApproveReservation.
	 *
	 * @param train The train that makes the reservation. For debugging.
	 * @param entrySignal The signal we will be entering from into this block.
	 *
	 * @return A reservation handle on success, otherwise null.
	 */
	TWeakPtr< FFGRailroadBlockReservation > CreateReservation( class AFGTrain* train, AFGBuildableRailroadSignal* entrySignal, int32 entryPathSegment );
	
	/** @return If this block have any reservations */
	bool HaveReservations() const { return mApprovedReservations.Num() > 0; }

	/** @return true if this is a path block. */
	bool IsPathBlock() const { return mIsPathBlock; }
	/**
	 * Set if this is a path block or not.
	 * If set while trains are traversing the block, there might be collisions.
	 */
	void SetIsPathBlock( bool isPathBlock );
	
	/** Get the validation status for this block. */
	ERailroadBlockValidation GetBlockValidation() const;

private:
	bool CanCreateReservation() const { return mQueuedReservations.Num() + mApprovedReservations.Num() < mMaxMultipleReservations; }
	void UpdateOccupancy();
	void OnReservationsUpdated();

	// Helpers, see block reservation class for more details, just don't pass a null reservation.
	void UpdateReservation( FFGRailroadBlockReservation* reservation );
	void ApproveReservation( FFGRailroadBlockReservation* reservation );
	void CancelReservation( FFGRailroadBlockReservation* reservation );
	void NotifyEnteredReservation( FFGRailroadBlockReservation* reservation );

public:
	/** Delegate for when changes happens to this block, it can be aspect, reservation or validation changes. */
	DECLARE_MULTICAST_DELEGATE( FOnBlockChanged )
	FOnBlockChanged OnBlockChanged;

	/** Stats for block validation, set by the subsystem when the block is created. */
	bool HasEntrySignal = false;
	bool HasExitSignal = false;
	bool ContainsLoop = false;
	bool ContainsMixedEntrySignals = false;
	bool ContainsStation = false;

	/** Unique id for this block. Unique per track graph and not globally. */
	int32 ID = INDEX_NONE;

private:
	friend struct FFGRailroadBlockReservation; // Access to the helper functions.
	friend class AFGRailroadSubsystem; // Show debug command.
	
	/** Vehicles currently occupying this block. */
	TArray< TWeakObjectPtr< AFGRailroadVehicle > > mOccupiedBy;

	/** True if this block is considered occupied. */
	bool mIsOccupied = false;
	
	/** If this is a path block. */
	bool mIsPathBlock = false;

	/** How many reservations can be queued inside this block, including approved and pending. */
	int8 mMaxMultipleReservations = 100;

	/** All reservations made for this block, path or whole block reservations. */
	TArray< TSharedPtr< FFGRailroadBlockReservation > > mQueuedReservations;
	TArray< TSharedPtr< FFGRailroadBlockReservation > > mApprovedReservations;
};

inline FString RailroadPathOverlapToString( ERailroadPathOverlap flags )
{
	FString result;

	if( ( flags & ERailroadPathOverlap::RPO_PathInSameDirection ) != ERailroadPathOverlap::RPO_None )
	{
		result += TEXT( "PathInSameDirection, " );
	}
	if( ( flags & ERailroadPathOverlap::RPO_PathInOppositeDirection ) != ERailroadPathOverlap::RPO_None )
	{
		result += TEXT( "PathInOppositeDirection, " );
	}
	if( ( flags & ERailroadPathOverlap::RPO_PathOnNeighboringTrack ) != ERailroadPathOverlap::RPO_None )
	{
		result += TEXT( "PathOnNeighboringTrack, " );
	}
	if( ( flags & ERailroadPathOverlap::RPO_OccupiedNeighboringTrack ) != ERailroadPathOverlap::RPO_None )
	{
		result += TEXT( "OccupiedNeighboringTrack, " );
	}
	if( ( flags & ERailroadPathOverlap::RPO_OccupiedTrack ) != ERailroadPathOverlap::RPO_None )
	{
		result += TEXT( "OccupiedTrack, " );
	}
	if( ( flags & ERailroadPathOverlap::RPO_ExclusiveTrack ) != ERailroadPathOverlap::RPO_None )
	{
		result += TEXT( "ExclusiveTrack, " );
	}

	result.RemoveFromEnd( TEXT( ", " ) );

	if( result.IsEmpty() )
	{
		result = TEXT( "None" );
	}
	
	return result;
}
