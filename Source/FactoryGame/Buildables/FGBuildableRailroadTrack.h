// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/StaticMesh.h"
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "FGBuildable.h"
#include "../FSplinePointData.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
//#include "FGInstancedSplineMeshComponent.h"
#include "FGBuildableRailroadTrack.generated.h"



/**
 * This is a way to represent a position on the railroad.
 */
USTRUCT(BlueprintType)
struct FRailroadTrackPosition
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

	/** Get the world location and direction of this track position. Does nothing if Track is not valid. */
	void GetWorldLocationAndDirection( FVector& out_location, FVector& out_direction ) const;

	/**
	 * Get the world location.
	 * @return World location if valid; otherwise a zero vector.
	 */ 
	FVector GetWorldLocation() const;

	/**
	 * Get the world direction.
	 * @return World direction if valid; otherwise a zero vector.
	 */
	FVector GetWorldDirection() const;

	/** @return Offset from the beginning of the track in the forward direction. It's up to the caller to check the validity of the track. */
	float GetForwardOffset() const;

	/** @return Offset from the end of the track in the reverse direction. It's up to the caller to check the validity of the track. */
	float GetReverseOffset() const;

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

	/** @todotrains The block id, for signals later, a long wagon can possibly be on 2 or more blocks at once. */
	//int32 Block;
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
	// End IFGDismantleInterface

	/** Get the spline for this track. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Track" )
	class USplineComponent* GetSplineComponent() const { return mSplineComponent; }

	/** Get the length of this track. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Track" )
	FORCEINLINE float GetLength() const { return mSplineComponent->GetSplineLength(); }

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

	/**
	 * Registers an object on the track, it can be a stop, signal, speed sign etc.
	 *
	 * @param object The object to register on this track.
	 */
	void RegisterRailroadInterface( UObject* object, const FRailroadTrackPosition& position );

	/**
	 * Unregisters an object from the track, it can be a stop, signal, speed sign etc.
	 *
	 * @param object The object to register on this track.
	 */
	void UnregisterRailroadInterface( UObject* object );

	/** @return The track graph this track belongs to. */
	FORCEINLINE int32 GetTrackGraphID() const { return mTrackGraphID; }

	//@todotrains This could be shared with conveyors later.
	template< typename MeshConstructor >
	static void BuildSplineMeshes(
		class USplineComponent* spline,
		UStaticMesh* mesh,
		float meshLength,
		TArray< USplineMeshComponent* >& meshPool,
		MeshConstructor meshConstructor );

	// MODDING EDIT
	//static void BuildSplineMeshes(
	//	class USplineComponent* spline,
	//	UStaticMesh* mesh,
	//	float meshLength,
	//	UFGInstancedSplineMeshComponent* splineInstances );

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
	
	// MODDING EDIT
	///** The spline meshes for this train track. */
	//UPROPERTY( VisibleAnywhere, Category = "Spline" )
	//class UFGInstancedSplineMeshComponent* mInstancedSplineComponent;

	/** Spline data saved in a compact form for saving and replicating. All the vectors are in local space. */
	UPROPERTY( SaveGame, Replicated, Meta = (NoAutoJson = true) )
	TArray< FSplinePointData > mSplineData;

	/** This tracks connection component. */
	UPROPERTY( SaveGame )
	class UFGRailroadTrackConnectionComponent* mConnections[ 2 ];

	/** Was this track created and is owned by a platform */
	UPROPERTY( SaveGame )
	bool mIsOwnedByPlatform;

	/** The graph this track belongs to. */
	int32 mTrackGraphID;

	/** Objects registered on this track in the order they're placed on the track beginning from the start, offset 0. */
	UPROPERTY()
	TArray< UObject* > mRailroadInterfaces;
};



/**
 * Templated function implementations.
 */
template< typename MeshConstructor >
void AFGBuildableRailroadTrack::BuildSplineMeshes(
	class USplineComponent* spline,
	UStaticMesh* mesh,
	float meshLength,
	TArray< USplineMeshComponent* >& meshPool,
	MeshConstructor meshConstructor )
{
	check( spline );

	const float splineLength = spline->GetSplineLength();
	const int32 numMeshes = FMath::Max( 1, FMath::RoundToInt( splineLength / meshLength ) + 1 );

	// Create more or remove the excess meshes.
	if( numMeshes < meshPool.Num() )
	{
		while( meshPool.Num() > numMeshes )
		{
			meshPool.Last()->DestroyComponent();
			meshPool.Pop();
		}
	}
	else if( numMeshes > meshPool.Num() )
	{
		while( meshPool.Num() < numMeshes )
		{
			meshPool.Push( meshConstructor( spline ) );
		}
	}

	// Put all pieces along the spline.
	for( int32 i = 0; i < meshPool.Num(); ++i )
	{
		const float segmentLength = splineLength / numMeshes;
		const float startDistance = ( float )i * segmentLength;
		const float endDistance = ( float )( i + 1 ) * segmentLength;
		const FVector startPos = spline->GetLocationAtDistanceAlongSpline( startDistance, ESplineCoordinateSpace::Local );
		const FVector startTangent = spline->GetTangentAtDistanceAlongSpline( startDistance, ESplineCoordinateSpace::Local ).GetSafeNormal() * segmentLength;
		const FVector endPos = spline->GetLocationAtDistanceAlongSpline( endDistance, ESplineCoordinateSpace::Local );
		const FVector endTangent = spline->GetTangentAtDistanceAlongSpline( endDistance, ESplineCoordinateSpace::Local ).GetSafeNormal() * segmentLength;

		meshPool[ i ]->SetStartAndEnd( startPos, startTangent, endPos, endTangent, true );
		meshPool[ i ]->SetStaticMesh( mesh );
	}

	// Register new meshes, needs to happen after the properties are set for static components.
	for( auto meshComp : meshPool )
	{
		if( !meshComp->IsRegistered() )
		{
			meshComp->RegisterComponent();
		}
	}
}
