// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Buildables/FGBuildableRailroadTrack.h"
#include "RailroadNavigation.h"
#include "FGRailroadFunctionLibrary.generated.h"


/**
 * Function library for railroad related functions.
 */
UCLASS()
class FACTORYGAME_API UFGRailroadFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/***************************************************************************
	 * Debug.
	 */

	/** Draw a railroad path. */
	static void DrawDebugRailroadPath( FRailroadPathSharedPtr path, int32 currentSegment = INDEX_NONE, bool isPersistentLines = false );

	/** Draw a track segment. */
	static void DrawDebugTrack( AFGBuildableRailroadTrack* track, float startOffset, float endOffset, const FColor& color, bool isPersistentLines = false );

	/** Draw a railroad position. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Railroad|Debug" )
	static void DrawDebugTrackPosition( const FRailroadTrackPosition& position, const FColor& color, bool isPersistentLines = false );


	/***************************************************************************
	 * TrackPosition.
	 */
	
	/** @return Is this a valid track position. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|TrackPosition" )
	static bool IsValid( const struct FRailroadTrackPosition& position );

	/**
	 * The track segment this position is on.
	 * @return Track if valid position; otherwise null.
	 */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|TrackPosition" )
	static class AFGBuildableRailroadTrack* GetTrack( const struct FRailroadTrackPosition& position );

	/** Get the world location and direction of this track position. Zero vectors if the track is not valid. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|TrackPosition" )
	static void GetWorldLocationAndDirection( const struct FRailroadTrackPosition& position, FVector& out_location, FVector& out_direction );

public:
	FORCEINLINE ~UFGRailroadFunctionLibrary() = default;
};
