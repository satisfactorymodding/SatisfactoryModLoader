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
	RBV_ContainsMixedEntrySignals	UMETA( DisplayName = "Contains Mixed Entry Signals" )
};


/** Status this block can have at a given entry signal. */
enum class ERailroadBlockOccupancy : uint8
{
	RBO_Clear,
	RBO_Occupied,
	RBO_ReservationNeeded,
	RBO_ReservationExclusive
};


/**
 * Holds all relevant information about a reservation into a block.
 */
struct FACTORYGAME_API FFGRailroadBlockReservation
{
public:
	/** Who made the reservation. */
    TWeakObjectPtr< class AFGTrain > Train = nullptr;

	/** true if this is a path reservation; false if this is a whole block reservation. */
	bool IsPathReservation = false;
	
	/**
	 * The reservations entry point into the block.
	 * This is used to keep this signal green (valid entry).
	 * As soon as the train enters the block, this signal is nulled to turn it red.
	 */
	TWeakObjectPtr< class AFGBuildableRailroadSignal > EntrySignal;

	/** First path segment in this reservation. */
	int32 EntryPathSegment = INDEX_NONE;
	
	/**
	* Last path segment in this reservation.
	* When the lead engine passes this segment, the reservation can be safely cleared.
	*/
	int32 ExitPathSegment = INDEX_NONE;
	
	/**
	 * Tracks in this reservation, if empty the whole block is reserved.
	 * Not a guarded pointer as the reservations are cleared if a track is dismantled.
	 */
	TSet< class AFGBuildableRailroadTrack* > Tracks;

	/**
	 * Tracks that this reservation overlaps.
	 * Not a guarded pointer as the reservations are cleared if a track is dismantled.
	 */
	TSet< class AFGBuildableRailroadTrack* > OverlappingTracks;
};


/**
 * Representing a signal block in the track graph. Keeps track of blocks
 */
struct FACTORYGAME_API FFGRailroadSignalBlock
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

	/**
	 * Make a reservation for the given train into this block before entering it.
	 * It is only valid to reserve a path inside a path block.
	 *
	 * @param train The train that makes the reservation, if an existing reservation is present that one is cleared.
	 * @param path The path we want to book.
	 * @param progress Where along the path we are right now.
	 * @param entry The signal we will be entering from into this block.
	 *
	 * @return true if the reservation was successful, false if not.
	 */
	TWeakPtr< FFGRailroadBlockReservation > MakeReservation( class AFGTrain* train, FRailroadPathSharedPtr path, int32 progress, AFGBuildableRailroadSignal* entry );
	
	/**
	 * Make a reservation for the given train into this block before entering it.
	 * This is valid on any block.
	 *
	 * @param train The train that makes the reservation, if an existing reservation is present that one is cleared.
	 * @param entry The signal we will be entering from into this block.
	 *
	 * @return true if the reservation was successful, false if not.
	 */
	TWeakPtr< FFGRailroadBlockReservation > MakeReservation( class AFGTrain* train, AFGBuildableRailroadSignal* entry );
	
	/** Clear any reservations made by the given train. */
	void ClearReservation( class AFGTrain* train );
	
	/** @return If this block have any reservations */
	bool HaveReservations() const { return mReservations.Num() > 0; }
	
	/** @return All the tracks that are reserved inside the block. */
	TArray< class AFGBuildableRailroadTrack* > GetReservedTracks() const;

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
	void ClearInvalidReservations();
	void UpdateOccupancy();
	void OnReservationsUpdated();

public:
	/** Delegate for when changes happens to this block, it can be aspect, reservation or validation changes. */
	DECLARE_MULTICAST_DELEGATE( FOnBlockChanged )
	FOnBlockChanged OnBlockChanged;

	/** Stats for block validation, set by the subsystem when the block is created. */
	bool HasEntrySignal = false;
	bool HasExitSignal = false;
	bool ContainsLoop = false;
	bool ContainsMixedEntrySignals = false;

	/** Unique id for this block. Unique per track graph and not globally. */
	int32 ID = INDEX_NONE;

private:
	/** Vehicles currently occupying this block. */
	TArray< TWeakObjectPtr< AFGRailroadVehicle > > mOccupiedBy;

	/** True if this block is considered occupied. */
	bool mIsOccupied = false;
	
	/** If this is a path block. */
	bool mIsPathBlock = false;

	/** Allow multiple reservations as long as the paths do not intersect. */
	bool mAllowMultipleReservations = true;

	/** All reservations made for this block, path or whole block reservations. */
	TArray< TSharedPtr< FFGRailroadBlockReservation > > mReservations;
};
