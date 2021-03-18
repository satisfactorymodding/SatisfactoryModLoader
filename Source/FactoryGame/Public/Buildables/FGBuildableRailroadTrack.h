// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Buildables/FGBuildable.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "FGInstancedSplineMeshComponent.h"
#include "FGBuildableRailroadTrack.generated.h"


//@todotrains Move this to separate header, so many use the track position but not the track itself.
/**
 * This is a way to represent a position on the railroad.
 */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FRailroadTrackPosition
{
	GENERATED_BODY()
public:
	/** A null track position. */
	static const FRailroadTrackPosition InvalidTrackPosition;

	FRailroadTrackPosition();
	FRailroadTrackPosition( class AFGBuildableRailroadTrack* track, float offset, float forward );
	FRailroadTrackPosition( const FRailroadTrackPosition& position );
	~FRailroadTrackPosition();

	/** Function called when serializing this struct to a FArchive. */
	bool Serialize( FArchive& ar );
	friend FArchive& operator<<( FArchive& ar, FRailroadTrackPosition& item );

	/** Is this a valid track position. */
	FORCEINLINE bool IsValid() const { return Track.IsValid(); }

	/** Get the world location and direction of this track position; zero if invalid. */
	void GetWorldLocationAndDirection( FVector& out_location, FVector& out_direction ) const;

	/** @return Offset from the beginning/end of the track in the forward direction if valid; otherwise zero. */
	float GetForwardOffset() const;
	float GetReverseOffset() const;

	/** @return The next track connection in the forward direction if valid; otherwise a nullptr. */
	class UFGRailroadTrackConnectionComponent* GetForwardConnection() const;
	class UFGRailroadTrackConnectionComponent* GetReverseConnection() const;

public:
	/**
	 * This is the track segment this position is on.
	 * If null then this is not a valid position.
	 */
	UPROPERTY()
	TWeakObjectPtr< class AFGBuildableRailroadTrack > Track;

	/** Offset along the track. */
	UPROPERTY()
	float Offset;

	/**
	 * How are we rotated on this segment.
	 *  1: We travel forward by increasing the offset (Along the spline).
	 * -1: We travel forward by decreasing the offset (Against the spine).
	 */
	UPROPERTY()
	float Forward;
};

/** Enable custom serialization of FRailroadTrackPosition */
template<>
struct TStructOpsTypeTraits< FRailroadTrackPosition > : public TStructOpsTypeTraitsBase2< FRailroadTrackPosition >
{
	enum
	{
		WithSerializer = true
	};
};



/**
 * A piece of train track, it has a spline and to ends.
 */
UCLASS( Abstract )
class FACTORYGAME_API AFGBuildableRailroadTrack : public AFGBuildable
{
	GENERATED_BODY()
public:
	AFGBuildableRailroadTrack();

	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	// End AActor interface

	// Begin IFGDismantleInterface
	virtual void Dismantle_Implementation() override;
	virtual bool CanDismantle_Implementation() const override;
	// End IFGDismantleInterface

	// Begin Buildable interface
	virtual int32 GetDismantleRefundReturnsMultiplier() const override;
	// End Buildable interface

	/** Get the spline for this track. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Track" )
	class USplineComponent* GetSplineComponent() const { return mSplineComponent; }

	/** Get the length of this track. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Track" )
	FORCEINLINE float GetLength() const { return mLength; }

	/** Flag the track as being owned by a platform */
	void SetIsOwnedByPlatform( bool isOwned ) { mIsOwnedByPlatform = isOwned; }

	/** Get whether a platform takes ownership of this track */
	bool GetIsOwnedByPlatform() const { return mIsOwnedByPlatform; }

	/**
	 * Get the track location closest to the given world location.
	 */
	FRailroadTrackPosition FindTrackPositionClosestToWorldLocation( const FVector& worldLocation );

	/**
	 * Get a location and rotation given a train position.
	 */
	void GetWorldLocationAndDirectionAtPosition( const struct FRailroadTrackPosition& position, FVector& out_location, FVector& out_direction ) const;

	/**
	 * Get the connection at offset.
	 *
	 * @param offset     May have the following values:
	 *                   0: Beginning of track, spline offset 0.
	 *                   1: End of the track segment.
	 *
	 * @return The connection; nullptr if offset is invalid.
	 */
	FORCEINLINE class UFGRailroadTrackConnectionComponent* GetConnection( int32 offset ) const
	{
		check( offset == 0 || offset == 1 );
		return mConnections[ offset ];
	}

	/** @return The track graph this track belongs to. */
	FORCEINLINE int32 GetTrackGraphID() const { return mTrackGraphID; }

	/**
	 * Get the third rail power connection for this track.
	 * The third rail is not unique per track segment but is the same for all tracks in a graph.
	 * 
	 * @note Only valid on server.
	 * 
	 * @return The third rail, nullptr if client or track is not connected to a valid graph.
	 */
	class UFGPowerConnectionComponent* GetThirdRail() const;

private:
	void SetTrackGraphID( int32 trackGraphID );

protected:
	/** Mesh to use for his track. */
	UPROPERTY( EditDefaultsOnly, Category = "Track" )
	class UStaticMesh* mMesh;

	/** Length of the mesh to use for this track */
	UPROPERTY( EditDefaultsOnly, Category = "Track" )
	float mMeshLength;

private:
	friend class AFGRailroadTrackHologram;
	friend class AFGRailroadSubsystem;

	/** The spline component for this train track. */
	UPROPERTY( VisibleAnywhere, Category = "Spline" )
	class USplineComponent* mSplineComponent;

	/** The spline meshes for this train track. */
	UPROPERTY( VisibleAnywhere, Category = "Spline" )
	class UFGInstancedSplineMeshComponent* mInstancedSplineComponent;

	/** Spline data saved in a compact form for saving and replicating. All the vectors are in local space. */
	UPROPERTY( SaveGame, Replicated, Meta = (NoAutoJson = true) )
	TArray< FSplinePointData > mSplineData;

	//@todo 2020-07-06 G2: Tracks built during play does not replicate the inner data for the second component in this array.
	//                     Index 0 replicates fine, index 1 does not, if the client reconnects the data is replicated on initial,
	//                     but during play... nothing. mConnectedComponents stays empty for index 1 for some unknown reason.
	/** This tracks connection components. Created locally with net stable naming. */
	UPROPERTY()
	TArray< class UFGRailroadTrackConnectionComponent* > mConnections;

	/** Was this track created and is owned by a platform. */
	UPROPERTY( EditDefaultsOnly, Category = "Track" )
	bool mIsOwnedByPlatform;

	/** The graph this track belongs to. */
	int32 mTrackGraphID;

	/** Length of this track. [cm] */
	float mLength;
};
