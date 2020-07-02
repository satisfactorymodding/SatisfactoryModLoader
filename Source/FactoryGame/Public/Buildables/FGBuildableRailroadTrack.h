// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/StaticMesh.h"
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "FGBuildable.h"
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
	FORCEINLINE FRailroadTrackPosition( class AFGBuildableRailroadTrack* track, float offset, float forward );
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
struct FACTORYGAME_API TStructOpsTypeTraits< FRailroadTrackPosition > : public TStructOpsTypeTraitsBase2< FRailroadTrackPosition >
{
	enum
	{
		WithSerializer = true
	};

public:
	FORCEINLINE ~TStructOpsTypeTraits< FRailroadTrackPosition >() = default;
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

	//@todoconveyor This could be shared with conveyors later.
	template< typename MeshConstructor >
	static void BuildSplineMeshes(
		class USplineComponent* spline,
		UStaticMesh* mesh,
		float meshLength,
		TArray< USplineMeshComponent* >& meshPool,
		MeshConstructor meshConstructor );

	static void BuildSplineMeshes(
		class USplineComponent* spline,
        UStaticMesh* mesh,
		float meshLength,
		UFGInstancedSplineMeshComponent* splineInstances );

	static void BuildSplineCollisions(
		class USplineComponent* spline,
		const FVector& collisionExtent,
		float collisionSpacing,
		const FVector& collisionOffset,
		FName collisionProfile );

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

	/** This tracks connection component. */
	UPROPERTY( SaveGame )
	class UFGRailroadTrackConnectionComponent* mConnections[ 2 ];

	/** Was this track created and is owned by a platform. */
	UPROPERTY( EditDefaultsOnly, Category = "Track" )
	bool mIsOwnedByPlatform;

	/** The graph this track belongs to. */
	int32 mTrackGraphID;

	/** Length of this track. [cm] */
	float mLength;

public:
	FORCEINLINE ~AFGBuildableRailroadTrack() = default;
};
