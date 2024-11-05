// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "Algo/Accumulate.h"


/**
 * A black box can record state in the form of logs and then output it on demand, e.g. when a fault condition arise.
 * The block box only records state changes so you can spam the same state into the recorder every frame and let it filter out the changes.
 *
 * It supports two ways of operation, both described below.
 * Recording Mode (default):
 * Each state is saved in the black box's history, the full history can be logged on demand.
 *
 * Direct Output Mode:
 * No history is kept and the commits are logged directly to the games output log, useful to output a log only when the state changes.
 *
 * Usage (record mode):
 * // Initialize the black box to keep the 100 last states in its history.
 * box-Reset( 100 );
 * 
 * // Append state for frame 1:
 * box->Append( "Train: Quartz, Priority: 5" );
 * box->Append( "Train: Bauxite, Priority: 2" );
 * box->Commit(); // Outputs "Black Box Commit [0]" to the output log.
 *
 * // Append state for frame 2:
 * box->Append( "Train: Quartz, Priority: 5" );
 * box->Append( "Train: Bauxite, Priority: 2" );
 * box->Commit(); // Outputs nothing to the output log, the state has not changed since last frame and is therefore ignored.
 * 
 * // Append state for frame 3:
 * box->Append( "Train: Quartz, Priority: 4" );
 * box->Append( "Train: Bauxite, Priority: 2" );
 * box->Commit(); // Outputs "Black Box Commit [1]" to the output log, the priority of the Quartz train was changed.
 * 
 * // Fault condition arises, dump the recorded states to the log.
 * box->Dump();
 *
 * Output:
 * Black Box Commit [0]
 * ... game logs other stuff ...
 * Black Box Commit [1]
 * ... game logs other stuff ...
 * =========== Black Box Commit Start [0] ===============
 * Train: Quartz, Priority: 5
 * Train: Bauxite, Priority: 2
 * =========== Black Box Commit End [0] ===============
 * =========== Black Box Commit Start [1] ===============
 * Train: Quartz, Priority: 4
 * Train: Bauxite, Priority: 2
 * =========== Black Box Commit End [1] ===============
 */
struct FBlackBoxRecorder
{
	/** Append a log to the current state. */
	void Append( const FString& log ) { UncommittedState.Add( log ); }
	/** Reverts any uncommitted state. */
	void Revert() { UncommittedState.Empty(); }

	/**
	 * Tires to commit the current state to the history. If it is unchanged compared to the last known state, nothing is committed.
	 *
	 * Outputs a log on a successful commit.
	 * This is the full commit message if the history length is 0 (direct output mode).
	 * Otherwise this is just a short message with a unique commit number.
	 */
	void Commit()
	{
		const uint32 hash = Algo::Accumulate( UncommittedState, 0, []( uint32 result, const FString& line ){ return HashCombine( result, GetTypeHash( line ) ); } );
		
		if( hash != LastCommittedHash )
		{
			CommitId++;
			
			LastCommittedHash = hash;
			
			UncommittedState.Insert( FString::Printf( TEXT( "=========== Black Box Commit Start [%i] ===============" ), CommitId ), 0 );
			UncommittedState.Add( FString::Printf( TEXT( "=========== Black Box Commit End [%i] ===============" ), CommitId ) );
			
			if( HistoryLength == 0 )
			{
				// Direct output.
				while( UncommittedState.Num() > 0 )
				{
					UE_LOG( LogBlackBox, Log, TEXT( "%s" ), *UncommittedState[ 0 ] );

					UncommittedState.RemoveAt( 0 );
				}
			}
			else
			{
				UE_LOG( LogBlackBox, Log, TEXT( "Black Box Commit [%i]" ), CommitId );
				
				// Save history.
				History.Add( UncommittedState );
			
				while( History.Num() > HistoryLength )
				{
					History.RemoveAt( 0 );
				}
			}
		}
		
		UncommittedState.Empty();
	}

	/**
	 * Dump the state of the block box to the log.
	 *
	 * Note: This does not reset the recorder.
	 */
	void Dump()
	{
		for( auto commit : History )
		{
			for( auto log : commit )
			{
				UE_LOG( LogBlackBox, Log, TEXT( "%s" ), *log );
			}
		}
	}

	/**
	 * Reset (initialize) the recorder.
	 * 
	 *@param numRecordsToKeep How many records do we keep in the history.
	 *                        If 0, then no history is kept and a log is made every time a state is successfully committed (direct output mode).
	 *                        If >0, then history is kept and can be logged using the Dump() function (record mode).
	 */
	void Reset( int32 numRecordsToKeep )
	{
		HistoryLength = numRecordsToKeep;
		
		Reset();
	}

	/**
	 * Same as above but leaves the history length unchanged.
	 */
	void Reset()
	{
		History.Reset( HistoryLength );
		
		CommitId = 0;
		LastCommittedHash = 0;
	}
private:
	/** How many records do we keep. If 0, then no history is kept and a log is made every time a state is successfully committed. */
	int32 HistoryLength = 100;

	/** List of log lines for the current state. */
	TArray< FString > UncommittedState;
	
	/** We keep a hash for the last committed hash so we only record unique points in time. */
	uint32 LastCommittedHash = 0;
	
	/** Recorded history, keep the n last states. */
	TArray< TArray< FString > > History;
		
	/** Counter to identify committed entries for the user. */
	int32 CommitId = 0;
};
