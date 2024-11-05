// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

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


/** Signal aspects used for signaling. */
UENUM( BlueprintType )
enum class ERailroadSignalAspect : uint8
{
	RSA_None			UMETA( DisplayName = "None" ),
	RSA_Clear			UMETA( DisplayName = "Clear" ),
	RSA_Stop			UMETA( DisplayName = "Stop" ),
	RSA_Dock			UMETA( DisplayName = "Dock" ) // Special aspect used at stations to tell the train that it should slow down and dock at the desired distance.
};


/**
 * How have this block been reserved.
 * Path: Only valid through path blocks.
 * Exclusive: Regular blocks and path blocks can be exclusively reserved.
 */
enum class ERailroadBlockReservationType : uint8
{
	RBRT_Exclusive,
	RBRT_Path
};

enum class ERailroadBlockReservationStatus : uint8
{
	RBRS_Pending,
	RBRS_Approved,
	RBRS_Cancelled
};

/**
 * Holds all relevant information about a reservation into a block.
 * The holder of a reservation is responsible for approving, updating and cancelling the reservation as needed.
 */
struct FACTORYGAME_API FFGRailroadBlockReservation
{
public:
	/**
	 * Approve reservation.
	 *
	 * Move this reservation to the approved list inside the block.
	 *
	 * Note: It is the callers responsibility to check for invalid approvals using the functions available for getting dependencies and overlapping reservation.
	 */
	void Approve();
	
	/**
	 * Cancels the reservation, after this the reservation is invalid.
	 */
	void Cancel();

	/**
	 * Call this if you changed the signals inside the reservation.
	 */
	void UpdateSignalAspects();
	
	/**
	 * Call this if you changed the remaining tracks.
	 */
	void UpdateRemainingTracks();

	/** The tracks that are reserved. */
	const TSet< class AFGBuildableRailroadTrack* >& Tracks() const;
	/** The tracks that overlap any reserved tracks. */
	const TSet< class AFGBuildableRailroadTrack* >& OverlappingTracks() const;

private:
	void InvalidateTrackCache();
	void FillTrackCache() const;
	
public:
	/** The block this reservation was made in. */
	TWeakPtr< struct FFGRailroadSignalBlock > Block;

	/** The train that made this reservation. */
	TWeakObjectPtr< class AFGTrain > Train;
	
	/** The type of this reservation. */
	ERailroadBlockReservationType Type = ERailroadBlockReservationType::RBRT_Exclusive;
	
	/**
	 * Status for this reservation.
     * Note: Cancelled reservations are not updated and might contain outdated information, avoid interacting with them.
	 */
	ERailroadBlockReservationStatus Status = ERailroadBlockReservationStatus::RBRS_Pending;
	
	/**
	 * The entry signal into the block.
	 * This is used to keep this signal green (valid entry).
	 * This is reset when the train enters the reserved block (signal passed).
	 */
	TWeakObjectPtr< class AFGBuildableRailroadSignal > EntrySignal;
	
	/**
	 * The exit signal out of the block.
	 * Used to traverse a chain of path signals.
	 * Null if this is not a path reservation.
	 */
	TWeakObjectPtr< class AFGBuildableRailroadSignal > ExitSignal;

	/**
	 * First path segment in this reservation.
	 * This is reset when the train enters the reserved block.
	 */
	int32 EntryPathSegment = INDEX_NONE;
	
	/**
	 * Last path segment in this reservation, only used for path reservations.
	 */
	int32 ExitPathSegment = INDEX_NONE;

	/**
	 * Keep track of where we are along the path so we can clear segments as we go.
	 * This is not valid to use before we are inside the block.
	 */
	int32 CurrentPathSegment = INDEX_NONE;
	
	/**
	 * Tracks in this reservation that the train still need to pass over, empty for exclusive reservations.
	 * This is also empty if the train is at the last segment in a path reservation.
	 * 
	 * Not a guarded pointer as the reservations are cleared if a track is dismantled.
	 */
	TArray< class AFGBuildableRailroadTrack* > RemainingTracks;

private:
	/**
	 * Cached tracks to use when approving reservations.
	 * The cache is invalidated when the reserved segments are updated.
	 * The cache is filled when it is accessed.
	 */
	mutable bool CachedTracksInvalidated = true;
	mutable TSet< class AFGBuildableRailroadTrack* > CachedTracks;
	mutable TSet< class AFGBuildableRailroadTrack* > CachedOverlappingTracks;
};


/**
 * Representing a signal block in the track graph.
 *
 * A block can be either a "regular" block or a path block.
 *
 * Regular Blocks:
 * Signals into these blocks are green by default and they turn red when one of the following conditions occur:
 * - A train enters the block.
 * - An exclusive reservation is put on the block (a train is soon about to enter) in which case only the entry signal is kept green.
 * Regular blocks are exclusive meaning only one train can be inside the block at any given moment.
 *
 * Path Blocks:
 * Signals into these blocks are red by default and only turn green when a train has been granted a path through the block in which case the entry signal turns green.
 * Multiple trains can be moving inside a path block at the same time as long as their paths don't intersect.
 * If a train is parked inside a path block other trains cannot reserve a path that intersects with the parked train.
 *
 * Responsibilities of this class:
 * Keep track of trains entering and exiting the block.
 * Provide the signal aspects for the signals associated with this block (includes block validation errors).
 * Providing information to the scheduler about dependencies between reservation and trains.
 * Store reservations through the block. The scheduler is responsible to keep these reservations up-to-date.
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
	 * See this block from the given signals perspective.
	 *
	 * For standard blocks, this reflects the occupancy of the block and any reservations from a trains brake distance.
	 * For path blocks, multiple inbound signals might be green at the same time.
	 *
	 * If no signal is given, this always returns stop.
	 */
	ERailroadSignalAspect GetAspectFor( class AFGBuildableRailroadSignal* signal ) const;
	
	/** @return If this block is occupied by vehicles. */
	bool IsOccupied() const;

	/** @return true if this block is occupied by the given train, otherwise false. */
	bool IsOccupiedBy( class AFGTrain* train ) const;

	/**
	 * Creates a reservation for a train into this block.
	 * Note that the reservation needs to be approved in a separate step for the train to be able to enter the block.
	 * This is only valid to call on a path block.
	 * 
	 * @param train The train that makes the reservation. Cannot be null.
	 * @param entrySignal The signal we will be entering from into this block. Cannot be null.
	 * @param entryPathSegment From which segment do we which to enter the path block. Must be a valid index.
	 * @param trainPath The trains current path. Must be valid.
	 *
	 * @return A reservation handle on success, otherwise null.
	 */
	TWeakPtr< FFGRailroadBlockReservation > CreatePathReservation( class AFGTrain* train, AFGBuildableRailroadSignal* entrySignal, int32 entryPathSegment, FRailroadPathSharedPtr trainPath );
	
	/**
	 * Same as above but this one is for making a path reservation from inside a path block.
	 * This is only valid to call on a path block.
	 * 
	 * @param train The train that makes the reservation. Cannot be null.
	 * @param currentPathSegment Where along the path we are right now. Must be a valid index.
	 * @param trainPath The trains current path. Must be valid.
	 *
	 * @return A reservation handle on success, otherwise null.
	 */
	TWeakPtr< FFGRailroadBlockReservation > CreatePathReservationFromInside( class AFGTrain* train, int32 currentPathSegment, FRailroadPathSharedPtr trainPath );
	
	/**
	 * Create a reservation for a train into this block.
	 * This is valid on any block, creates an exclusive reservation on path blocks.
	 * Follow up on this call with a call to ApproveReservation.
	 *
	 * @param train The train that makes the reservation.
	 * @param entrySignal The signal we will be entering from into this block.
	 *
	 * @return A reservation handle on success, otherwise null.
	 */
	TWeakPtr< FFGRailroadBlockReservation > CreateExclusiveReservation( class AFGTrain* train, AFGBuildableRailroadSignal* entrySignal, int32 entryPathSegment );

	/**
	 * Find all trains that overlap within the block.
	 * 
	 * @param reservation Reservation to check for overlaps against, must be a reservation made inside this block.
	 * @param out_overlaps Any overlaps found are added to this list.
	 */
	void FindOverlappingTrains( FFGRailroadBlockReservation* reservation, TSet< AFGTrain* >& out_overlaps ) const;
	bool HasOverlappingTrains( FFGRailroadBlockReservation* reservation ) const;
	
	/**
	 * Find all approved reservations that overlap within the block.
	 * 
	 * @param reservation Reservation to check for overlaps against, must be a reservation made inside this block.
	 * @param out_overlaps Any overlaps found are added to this list.
	 */
	void FindOverlappingApprovedReservations( FFGRailroadBlockReservation* reservation, TSet< AFGTrain* >& out_overlaps ) const;
	bool HasOverlappingApprovedReservations( FFGRailroadBlockReservation* reservation ) const;

	/**
	 * Are there any pending reservations for the given dependencies that overlap within the block.
	 * 
	 * @param reservation Reservation to check for overlaps against, must be a reservation made inside this block.
	 * @param dependencies Only check against reservations that have an owner inside this list.
	 *
	 * @return True if there are any overlaps.
	 */
	bool HasOverlappingPendingReservationsForDependencies( FFGRailroadBlockReservation* reservation, const TSet< TWeakObjectPtr< AFGTrain > >& dependencies ) const;
	
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
	/** Helper to update this blocks occupancy status. */
	void UpdateOccupancy();
	
	/** Called whenever reservations are updated so the signals leading into this block can update their shown aspect. */
	void OnReservationsUpdated();
	
	// Helpers, see block reservation class for more details, just don't pass a null reservation.
	void ApproveReservation( FFGRailroadBlockReservation* reservation );
	void CancelReservation( FFGRailroadBlockReservation* reservation );

	/** @return True if an unapproved reservation is overlapping an already approved one. False if there is no overlap. */
	bool AreReservationsOverlapping( const FFGRailroadBlockReservation* approved, const FFGRailroadBlockReservation* unapproved ) const;

	/** @return the tracks that go through this block for the given path, empty if the path does not go through the block. */
	TArray< class AFGBuildableRailroadTrack* > GetTracksThroughBlock( int32 startSegment, FRailroadPathSharedPtr path, TWeakObjectPtr< class AFGBuildableRailroadSignal >& out_exitSignal, int32& out_exitSegment );
	
public:
	/** Delegate for when changes happens to this block, it can be aspect, reservation or validation changes. */
	DECLARE_MULTICAST_DELEGATE( FOnBlockChanged )
	FOnBlockChanged OnBlockChanged;

	/** Stats for block validation, set by the subsystem when the block is created. */
	bool NoExitSignal = false;
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

	/** All reservations made for this block, path or whole block reservations. */
	TArray< TSharedPtr< FFGRailroadBlockReservation > > mPendingReservations;
	TArray< TSharedPtr< FFGRailroadBlockReservation > > mApprovedReservations;
};
