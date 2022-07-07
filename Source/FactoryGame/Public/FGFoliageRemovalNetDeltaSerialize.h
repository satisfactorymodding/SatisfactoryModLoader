// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "Engine/NetSerialization.h"

struct FFastNetRemovedInstanceArrayState : public FNetFastTArrayBaseState
{
	FFastNetRemovedInstanceArrayState() :
		FNetFastTArrayBaseState(),
		DoneIncremental( false )
	{
	}

	// true if we have sent everything incrementally
	int32 DoneIncremental : 1;
};

template< typename ArrayType >
int32 WriteToBuffer( typename ArrayType::ItemType* element, TMap< int32, int32 >& newMap, FNetDeltaSerializeInfo& deltaParams, FBitWriter& writer )
{
	newMap.Add( element->ReplicationID ) = element->ReplicationKey;

	ensure( element->ReplicationID < ArrayType::ItemType::MaxCount );

	// Dont pack this, want property to be byte aligned
	typename ArrayType::ItemType::IndexType ID = element->ReplicationID;

 	writer << ID;

	UE_LOG( LogNetFoliageRemoval, Log, TEXT( "   Changed ElementID: %d" ), ID );

	int32 preSerializeBits = writer.GetNumBits();

	FNetDeltaSerializeInfo deltaSerializeInfo;
	deltaSerializeInfo.Struct = ArrayType::ItemType::StaticStruct();
	deltaSerializeInfo.Writer = &writer;
	deltaSerializeInfo.Map = deltaParams.Map;
	deltaSerializeInfo.Data = element;
	deltaParams.NetSerializeCB->NetSerializeStruct( deltaSerializeInfo );
	
	return ( writer.GetNumBits() - preSerializeBits );
}

template< typename ArrayType >
bool FoliageRemovalNetDeltaSerialize( FNetDeltaSerializeInfo& deltaParams, ArrayType& fastArray )
{
	SCOPE_CYCLE_COUNTER( STAT_NetIncrementalArray );
	class UScriptStruct* innerStruct = ArrayType::ItemType::StaticStruct();

	if( deltaParams.bUpdateUnmappedObjects || deltaParams.Writer == NULL )
	{
		//---------------
		// Build ItemMap if necessary. This maps ReplicationID to our local index into the Items array.
		//---------------
		if( fastArray.ItemMap.Num() != fastArray.Items.Num() )
		{
			SCOPE_CYCLE_COUNTER( STAT_NetIncrementalArray_BuildMap );
			UE_LOG( LogNetFoliageRemoval, Log, TEXT( "FastArrayDeltaSerialize: Recreating Items map. Struct: %s, Items.Num: %d Map.Num: %d" ), *innerStruct->GetOwnerStruct()->GetName(), fastArray.Items.Num(), fastArray.ItemMap.Num() );

			fastArray.ItemMap.Empty();
			for( int32 i = 0; i < fastArray.Items.Num(); ++i )
			{
				if( fastArray.Items[ i ].ReplicationID == INDEX_NONE )
				{
					if( deltaParams.Writer )
					{
						UE_LOG( LogNetFoliageRemoval, Warning, TEXT( "FastArrayDeltaSerialize: Item with uninitialized ReplicationID. Struct: %s, ItemIndex: %i" ), *innerStruct->GetOwnerStruct()->GetName(), i );
					}
					else
					{
						// This is benign for clients, they may add things to their local array without assigning a ReplicationID
						continue;
					}
				}
				fastArray.ItemMap.Add( fastArray.Items[ i ].ReplicationID, i );
			}
		}
	}

	if( deltaParams.GatherGuidReferences )
	{
		//@note We do not track any guids as we don't support object references.
		// Let the caller know we handled this.
		return true;
	}

	if( deltaParams.MoveGuidToUnmapped )
	{
		// Let the caller know we did not find the guid, as we do not track guids this code should not be called.
		return false;
	}

	if( deltaParams.bUpdateUnmappedObjects )
	{
		// We don't care about unmapped objects
		return true;
	}

	if( deltaParams.Writer )
	{
		//-----------------------------
		// Saving
		//-----------------------------	
		fgcheck( deltaParams.Struct );
		FBitWriter& writer = *deltaParams.Writer;

		// Create a new map from the current state of the array		
		FFastNetRemovedInstanceArrayState* newState = new FFastNetRemovedInstanceArrayState();
		fgcheck( deltaParams.NewState );
		*deltaParams.NewState = TSharedPtr<INetDeltaBaseState>( newState );
		TMap< int32, int32 >& newMap = newState->IDToCLMap;
		newState->ArrayReplicationKey = fastArray.ArrayReplicationKey;

		// Get the old map if its there
		FFastNetRemovedInstanceArrayState* oldState = ( FFastNetRemovedInstanceArrayState* )deltaParams.OldState;
		TMap< int32, int32 > * oldMap = oldState ? &oldState->IDToCLMap : NULL;
		int32 baseReplicationKey = oldState ? oldState->ArrayReplicationKey : -1;

		const bool calculatingInitialState = oldState == nullptr;

		// See if the array changed at all. If the ArrayReplicationKey matches we can skip checking individual items
		if( oldState && fastArray.ArrayReplicationKey == baseReplicationKey )
		{
			newState->DoneIncremental = oldState->DoneIncremental;
			if( oldState->DoneIncremental )
			{
				// Double check the old map is valid and that we will consider writing the same number of elements that are in the old map.
				if( ensureMsgf( oldMap, TEXT( "Invalid OldMap" ) ) )
				{
					// If the keys didn't change, only update the item count caches if necessary.
					if( fastArray.CachedNumItems == INDEX_NONE ||
						fastArray.CachedNumItems != fastArray.Items.Num() ||
						fastArray.CachedNumItemsToConsiderForWriting == INDEX_NONE )
					{
						fastArray.CachedNumItems = fastArray.Items.Num();
						fastArray.CachedNumItemsToConsiderForWriting = 0;

						// Count the number of items in the current array that may be written. On clients, items that were predicted will be skipped.
						for( const typename ArrayType::ItemType& Item : fastArray.Items )
						{
							if( fastArray.template ShouldWriteFastArrayItem< typename ArrayType::ItemType, ArrayType >( Item, deltaParams.bIsWritingOnClient ) )
							{
								fastArray.CachedNumItemsToConsiderForWriting++;
							}
						}
					}

					//ensureMsgf( ( oldMap->Num() == CachedNumItemsToConsiderForWriting ), TEXT( "OldMap size (%d) does not match item count (%d)" ), oldMap->Num(), CachedNumItemsToConsiderForWriting );
				}

				return false;
			}
		}

		int32 deleteCount = ( oldMap ? oldMap->Num() : 0 ) - fastArray.Items.Num(); // Note: this is incremented when we add new items below.
		UE_LOG( LogNetFoliageRemoval, Log, TEXT( "[%s] NetIncrementalArray: [%s]. DeleteCount: %d" ), *VarToFString( fastArray.FoliageRemoval ), *deltaParams.DebugName, deleteCount );

		// Log out entire state of current/base state
		if( UE_LOG_ACTIVE( LogNetFoliageRemoval, Log ) )
		{
			FString currentState = FString::Printf( TEXT( "Current: %d " ), fastArray.ArrayReplicationKey );
			for( int32 i = 0; i < fastArray.Items.Num(); ++i )
			{
				currentState += FString::Printf( TEXT( "[%d/%d], " ), fastArray.Items[ i ].ReplicationID, fastArray.Items[ i ].ReplicationKey );
			}
			UE_LOG( LogNetFoliageRemoval, Log, TEXT( "%s" ), *currentState );


			FString clientStateStr = FString::Printf( TEXT( "Client: %d " ), deltaParams.OldState ? ( ( FFastNetRemovedInstanceArrayState* )deltaParams.OldState )->ArrayReplicationKey : 0 );
			if( oldMap )
			{
				for( TMap< int32, int32 >::TIterator It = oldMap->CreateIterator(); It; ++It )
				{
					clientStateStr += FString::Printf( TEXT( "[%d/%d], " ), It.Key(), It.Value() );
				}
			}
			UE_LOG( LogNetFoliageRemoval, Log, TEXT( "%s" ), *clientStateStr );
		}

		//const int32 DESIRED_PACKET_BITS = 2047; //[DavalliusA:Thu/20-06-2019] made it even smaller just to see how it affect things. ( MAX_PACKET_SIZE * 8 ); //byte to bit //[DavalliusA:Wed/19-06-2019] added /2 to minimize load/chance of buffer bloat. Should probably find a better/variable value here later.
		const int32 DESIRED_PACKET_BITS = MAX_PACKET_SIZE * 8;

		// @optimize: We could calculate how big each FVector_NetQuantize is to pack more data each frame, just look at WritePackedVector in NetSerialization.h
		const int32 STATIC_SIZE_OVERHEAD = ( sizeof( fastArray.ArrayReplicationKey ) + sizeof( baseReplicationKey ) + sizeof( uint32 ) /* num deleted items */ + sizeof( uint32 ) /* num changed items */ ) * 8;
		//const int32 MAX_CHANGED_ITEM_SIZE = sizeof( uint32 ) * 8/** Item ID */ + 24 /** max of FVector_NetQuantize10 */ * 3 /** 3 float in a vector */;
		const int32 MAX_CHANGED_ITEM_SIZE = ArrayType::ItemType::BitCount /** Item ID */ + ArrayType::ItemType::BitCount /** Index size */;
		const int32 DELETED_ITEM_SIZE = ArrayType::ItemType::BitCount;

		int32 calculatedPacketSize = STATIC_SIZE_OVERHEAD;

		bool done = true;

		//--------------------------------------------
		// Find out what is new or what has changed
		//--------------------------------------------

		// Mark where the array replication key is now, so we can change it when we are done
		FBitWriterMark arrayReplicationKeyMark( writer );
		writer << fastArray.ArrayReplicationKey;
		writer << baseReplicationKey;

		// Mark where in the writer we have the number of delete elements
		FBitWriterMark numDeletedMark( writer );
		uint32 numDeletedElements = 0;
		writer << numDeletedElements;

		// Mark where in the writer we have the number of changed elements elements
		FBitWriterMark numChangedMark( writer );
		int32 numChangedElements = 0;
		writer << numChangedElements;


		//[DavalliusA:Wed/19-06-2019] loop thorugh all items, but will not write items after DESIRED_PACKET_BITS is met. Will hoever not break, but continue due to other state updates.
		for( int32 i = 0; i < fastArray.Items.Num(); ++i )
		{
			UE_LOG( LogNetFoliageRemoval, Log, TEXT( "    Array[%d] - ID %d. CL %d." ), i, fastArray.Items[ i ].ReplicationID, fastArray.Items[ i ].ReplicationKey );
			if( !fastArray.template ShouldWriteFastArrayItem< typename ArrayType::ItemType, ArrayType >( fastArray.Items[ i ], deltaParams.bIsWritingOnClient ) )
			{
				// On clients, this will skip items that were added predictively.
				continue;
			}
			if( fastArray.Items[ i ].ReplicationID == INDEX_NONE )
			{
				fastArray.MarkItemDirty( fastArray.Items[ i ] );
			}

			int32* oldValuePtr = oldMap ? oldMap->Find( fastArray.Items[ i ].ReplicationID ) : NULL;
			if( oldValuePtr )
			{
				if( *oldValuePtr == fastArray.Items[ i ].ReplicationKey )
				{
					UE_LOG( LogNetFoliageRemoval, Log, TEXT( "       Stayed The Same - Skipping" ) );
					newMap.Add( fastArray.Items[ i ].ReplicationID, fastArray.Items[ i ].ReplicationKey );

					// Stayed the same, it might have moved but we don't care
					continue;
				}
				else
				{
					// Changed
					UE_LOG( LogNetFoliageRemoval, Log, TEXT( "       Changed! Was: %d. Element ID: %d" ), *oldValuePtr, fastArray.Items[ i ].ReplicationID );

					if( !calculatingInitialState && calculatedPacketSize + MAX_CHANGED_ITEM_SIZE > DESIRED_PACKET_BITS )
					{
						done = false;
						// Need continue here so that we can properly populate the newMap
						continue;
					}

					calculatedPacketSize += WriteToBuffer< ArrayType >( &fastArray.Items[ i ], newMap, deltaParams, writer );

					numChangedElements++;
				}
			}
			else
			{
				// New item
				UE_LOG( LogNetFoliageRemoval, Log, TEXT( "       New! Element ID: %d" ), fastArray.Items[ i ].ReplicationID );

				if( !calculatingInitialState && calculatedPacketSize + MAX_CHANGED_ITEM_SIZE > DESIRED_PACKET_BITS )
				{
					done = false;
					// Need continue here so that we can properly populate the newMap
					continue;
				}
				calculatedPacketSize += WriteToBuffer< ArrayType >( &fastArray.Items[ i ], newMap, deltaParams, writer );

				numChangedElements++;
				deleteCount++; // We added something new, so our initial DeleteCount value must be incremented.
			}
		}

		// Find out what was deleted
		if( deleteCount > 0 && oldMap )
		{
			for( auto it = oldMap->CreateIterator(); it; ++it )
			{
				if( !newMap.Contains( it.Key() ) )
				{
					if( !calculatingInitialState && calculatedPacketSize + DELETED_ITEM_SIZE > DESIRED_PACKET_BITS )
					{
						done = false;
						// Here we can break, as we don't update things in the loop
						break;
					}
					calculatedPacketSize += DELETED_ITEM_SIZE;

					typename ArrayType::ItemType::IndexType ID = it.Key();
					writer << ID;

					UE_LOG( LogNetFoliageRemoval, Log, TEXT( "   Deleted ElementID: %d" ), ID );
					--numDeletedElements;

					if( --deleteCount <= 0 )
						break;
				}
			}
		}

		// Note: we used to early return false here if nothing had changed, but we still need to send
		// a bunch with the array key / base key, so that clients can look for implicit deletes.

		// The array replication key may have changed while adding new elemnts (in the call to MarkItemDirty above)
		newState->ArrayReplicationKey = fastArray.ArrayReplicationKey;
		newState->DoneIncremental = done;

		// Mark where we are now so, that if something else uses this writer, it will write at the correct location of it
		FBitWriterMark endOfPacketMark( writer );

		// Jump back and write the array replication key
		arrayReplicationKeyMark.PopWithoutClear( writer );
		writer << fastArray.ArrayReplicationKey;

		// Jump back and writer the number of delete elements
		numDeletedMark.PopWithoutClear( writer );
		writer << numDeletedElements;

		// Jump back and writer the number of changed elements
		numChangedMark.PopWithoutClear( writer );
		writer << numChangedElements;

		// Restor writer to end of packet
		endOfPacketMark.PopWithoutClear( writer );

		UE_LOG( LogNetFoliageRemoval, Log, TEXT( "   Writing Bunch. NumChange: %d. NumDel: %d [%d/%d] Done: [%s]" ), numChangedElements, numDeletedElements, fastArray.ArrayReplicationKey, baseReplicationKey, *VarToFString( done ) );
	}
	else
	{
		//-----------------------------
		// Loading
		//-----------------------------	
		fgcheck( deltaParams.Reader );
		FBitReader& reader = *deltaParams.Reader;

		//[Gafgar:Wed/23-09-2020] renamed these variables due to warning C4458: declaration of 'MAX_NUM_DELETED' hides class member. As there are variables with the same name in the base class.
		//And I assume we want to use our own values here.. even if our values atm is the same.
		//@TODO:[Gafgar:Wed/23-09-2020] verify this is what we want.. though we are to probably rewrite most of this system, so might not be an issue.
		static constexpr  int32 FG_FR_MAX_NUM_CHANGED = 2048; //[DavalliusA:Wed/19-06-2019] value estimated and assumed from package size limits and replication size above. Should be larger than it can write.
		static constexpr  int32 FG_FR_MAX_NUM_DELETED = 2048;

		//---------------
		// Read header
		//---------------

		int32 receivedArrayReplicationKey;
		reader << receivedArrayReplicationKey;

		int32 baseReplicationKey;
		reader << baseReplicationKey;

		uint32 numDeletes;
		reader << numDeletes;

		UE_LOG( LogNetFoliageRemoval, Log, TEXT( "[%s] Received [%d/%d]." ), *VarToFString( fastArray.FoliageRemoval ), receivedArrayReplicationKey, baseReplicationKey );

		if( numDeletes > FG_FR_MAX_NUM_DELETED )
		{
			UE_LOG( LogNetFoliageRemoval, Warning, TEXT( "NumDeletes > FG_FR_MAX_NUM_DELETED: %d." ), numDeletes );
			reader.SetError();
			return false;;
		}

		uint32 numChanged;
		reader << numChanged;

		if( numChanged > FG_FR_MAX_NUM_CHANGED )
		{
			UE_LOG( LogNetFoliageRemoval, Warning, TEXT( "NumChanged > FG_FR_MAX_NUM_CHANGED: %d." ), numChanged );
			reader.SetError();
			return false;;
		}

		UE_LOG( LogNetFoliageRemoval, Log, TEXT( "Read NumChanged: %d NumDeletes: %d." ), numChanged, numDeletes );

		// Increment keys so that a client can re-serialize the array if needed, such as for client replay recording
		if( numDeletes > 0 || numChanged > 0 )
		{
			fastArray.IncrementArrayReplicationKey();
		}

		TArray< int32, TInlineAllocator< 8 > > deleteIndices;
		TArray< int32, TInlineAllocator< 8 > > addedIndices;
		TArray< int32, TInlineAllocator< 8 > > changedIndices;

		//---------------
		// Read deleted elements
		//---------------
		if( numDeletes > 0 )
		{
			for( uint32 i = 0; i < numDeletes; ++i )
			{
				typename ArrayType::ItemType::IndexType elementID;
				reader << elementID;

				fastArray.GuidReferencesMap.Remove( elementID );

				int32* elementIndexPtr = fastArray.ItemMap.Find( elementID );
				if( elementIndexPtr )
				{
					int32 DeleteIndex = *elementIndexPtr;
					deleteIndices.Add( DeleteIndex );
					UE_LOG( LogNetFoliageRemoval, Log, TEXT( "   Adding ElementID: %d for deletion" ), elementID );
				}
				else
				{
					UE_LOG( LogNetFoliageRemoval, Log, TEXT( "   Couldn't find ElementID: %d for deletion!" ), elementID );
				}
			}
		}

		//---------------
		// Read Changed/New elements
		//---------------
		for( uint32 i = 0; i < numChanged; ++i )
		{
			typename ArrayType::ItemType::IndexType elementID;
			reader << elementID;

			int32* elementIndexPtr = fastArray.ItemMap.Find( elementID );
			int32 elementIndex = 0;
			typename ArrayType::ItemType* thisElement = nullptr;

			if( !elementIndexPtr )
			{
				UE_LOG( LogNetFoliageRemoval, Log, TEXT( "   New. ID: %d. New Element!" ), elementID );

				thisElement = &fastArray.Items.Emplace_GetRef();
				thisElement->ReplicationID = elementID;

				elementIndex = fastArray.Items.Num() - 1;
				fastArray.ItemMap.Add( elementID, elementIndex );

				addedIndices.Add( elementIndex );
			}
			else
			{
				UE_LOG( LogNetFoliageRemoval, Log, TEXT( "   Changed. ID: %d -> Idx: %d" ), elementID, *elementIndexPtr );
				elementIndex = *elementIndexPtr;
				thisElement = &fastArray.Items[ elementIndex ];
				changedIndices.Add( elementIndex );
			}

			// Update this element's most recent array replication key
			thisElement->MostRecentArrayReplicationKey = receivedArrayReplicationKey;

			// Update this element's replication key so that a client can re-serialize the array for client replay recording
			thisElement->ReplicationKey++;

			// Remember where we started reading from, so that if we have unmapped properties, we can re-deserialize from this data later
			FBitReaderMark mark( reader );

#if DEBUG_FOLIAGE_REMOVAL_SUBSYSTEM
			typename ArrayType::ItemType::IndexType oldIndex = 0;
			if( elementIndexPtr )
			{
				oldIndex = thisElement->Index;
			}
#endif
			
			FNetDeltaSerializeInfo deltaSerializeInfo;
			deltaSerializeInfo.Struct = innerStruct;
			deltaSerializeInfo.Reader = &reader;
			deltaSerializeInfo.Map = deltaParams.Map;
			deltaSerializeInfo.Data = thisElement;
			deltaParams.NetSerializeCB->NetSerializeStruct( deltaSerializeInfo );

#if DEBUG_FOLIAGE_REMOVAL_SUBSYSTEM
			if( elementIndexPtr )
			{
				// A change should never trigger a new value of the ID
				fgcheck( oldIndex == thisElement->Index );
			}
#endif

			if( reader.IsError() )
			{
				UE_LOG( LogNetFoliageRemoval, Warning, TEXT( "Parms.NetSerializeCB->NetSerializeStruct: Reader.IsError() == true" ) );
				return false;
			}
		}

		// ---------------------------------------------------------
		// Look for implicit deletes that would happen due to Naks
		// ---------------------------------------------------------

		for( int32 idx = 0; idx < fastArray.Items.Num(); ++idx )
		{
			typename ArrayType::ItemType& item = fastArray.Items[ idx ];
			if( item.MostRecentArrayReplicationKey < receivedArrayReplicationKey && item.MostRecentArrayReplicationKey > baseReplicationKey )
			{
				// Make sure this wasn't an explicit delete in this bunch (otherwise we end up deleting an extra element!)
				if( deleteIndices.Contains( idx ) == false )
				{
					// This will happen in normal conditions in network replays.
					UE_LOG( LogNetFoliageRemoval, Log, TEXT( "Adding implicit delete for ElementID: %d. MostRecentArrayReplicationKey: %d. Current Payload: [%d/%d]" ), item.ReplicationID, item.MostRecentArrayReplicationKey, fastArray.ArrayReplicationKey, baseReplicationKey );

					deleteIndices.Add( idx );
				}
			}
		}

		// ---------------------------------------------------------
		// Invoke all callbacks: removed -> added -> changed
		// ---------------------------------------------------------
		fgcheck( fastArray.FoliageRemoval );

		int32 preRemoveSize = fastArray.Items.Num();
		for( int32 idx : deleteIndices )
		{
			if( fastArray.Items.IsValidIndex( idx ) )
			{
				// Call the delete callbacks now, actually remove them at the end
				fastArray.FoliageRemoval->RemovedInstances_ItemRemoved( idx );
			}
		}
		if( preRemoveSize != fastArray.Items.Num() )
		{
			UE_LOG( LogNetFoliageRemoval, Error, TEXT( "Item size changed after PreReplicatedRemove! PremoveSize: %d  Item.Num: %d" ), preRemoveSize, fastArray.Items.Num() );
		}

		for( int32 idx : addedIndices )
		{
			if( idx < fastArray.Items.Num() )
			{
				fastArray.FoliageRemoval->RemovedInstances_ItemAdded( fastArray.Items[ idx ].Index );
			}
		}

		// @todo: We should be able to disable this to save performance, should just happen when we get duplicated packages (and then we don't want to do anything)
		for( int32 idx : changedIndices )
		{
			fastArray.FoliageRemoval->RemovedInstances_ItemChanged( idx );
		}

		fastArray.FoliageRemoval->RemovedInstances_ReplicationFrameDone();

		if( preRemoveSize != fastArray.Items.Num() )
		{
			UE_LOG( LogNetFoliageRemoval, Error, TEXT( "Item size changed after PostReplicatedAdd/PostReplicatedChange! PremoveSize: %d  Item.Num: %d" ), preRemoveSize, fastArray.Items.Num() );
		}

		if( deleteIndices.Num() > 0 )
		{
			deleteIndices.Sort();
			for( int32 i = deleteIndices.Num() - 1; i >= 0; --i )
			{
				int32 deleteIndex = deleteIndices[ i ];
				if( fastArray.Items.IsValidIndex( deleteIndex ) )
				{
					fastArray.Items.RemoveAtSwap( deleteIndex, 1, false );

					UE_LOG( LogNetFoliageRemoval, Log, TEXT( "   Deleting: %d" ), deleteIndex );
				}
			}

			// Clear the map now that the indices are all shifted around. This kind of sucks, we could use slightly better data structures here I think.
			// This will force the ItemMap to be rebuilt for the current Items array
			fastArray.ItemMap.Empty();
		}
	}

	return true;
}
