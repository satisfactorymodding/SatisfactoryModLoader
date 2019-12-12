// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/StaticMesh.h"
#include "Array.h"
#include "UObject/Class.h"

#include "FGSplineHologram.h"
#include "FGBuildableHologram.h"
#include "../FSplinePointData.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "FGRailroadTrackHologram.generated.h"


/**
 * Hologram used to place train tracks.
 */
UCLASS()
class FACTORYGAME_API AFGRailroadTrackHologram : public AFGSplineHologram
{
	GENERATED_BODY()
public:
	AFGRailroadTrackHologram();

	virtual void BeginPlay() override;

	// Begin AFGHologram interface
	virtual class USceneComponent* SetupComponent( USceneComponent* attachParent, UActorComponent* componentTemplate, const FName& componentName ) override;
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	virtual bool MultiStepPlacement() override;
	// End AFGHologram interface

	// Begin AFGBuildableHologram interface
	virtual void ConfigureActor( class AFGBuildable* inBuildable ) const override;
	virtual void ConfigureComponents( class AFGBuildable* inBuildable ) const override;
	// End AFGBuildableHologram interface

	/**
	 * Automatically create a hologram instance with the specified platform connections
	 * @note This is used when spawning this railroad segment as a child hologram for a train station or platform
	 */
	void SetLocationAndRotationFromPlatformConnections( class UFGTrainPlatformConnection* connectionOne, class UFGTrainPlatformConnection* connectionTwo );

protected:
	// Begin AFGBuildableHologram interface
	virtual void CheckValidPlacement() override;
	virtual void CheckValidFloor() override;
	virtual void CheckClearance() override;
	// End AFGBuildableHologram interface

	// Begin AFGSplineHologram interface
	virtual void OnRep_SplineData() override;
	virtual int32 GetNumCostSections() const override;
	// End AFGSplineHologram interface

private:
	bool ValidateGrade();
	bool ValidateCurvature();

	/** This routes the spline to the new location. Giving it a nice curvature. */
	void AutoRouteSpline(
		const FVector& startConnectionPos,
		const FVector& startConnectionNormal,
		const FVector& endConnectionPos,
		const FVector& endConnectionNormal );

private:
	/** Length restriction of the track. [cm] */
	UPROPERTY( EditDefaultsOnly, Category = "Tracks" )
	float mMinLength;
	/** Length restriction of the track. [cm] */
	UPROPERTY( EditDefaultsOnly, Category = "Tracks" )
	float mMaxLength;
	/** Turn radius restriction of the track. [cm] */
	UPROPERTY( EditDefaultsOnly, Category = "Tracks" )
	float mMinBendRadius;
	/** Grade restriction of the track. [degrees] */
	UPROPERTY( EditDefaultsOnly, Category = "Tracks" )
	float mMaxGrade;
	/** From how far away we should snap to another track. [cm] */
	UPROPERTY( EditDefaultsOnly, Category = "Tracks" )
	float mSnapDistance;

	/** Index of the currently moved point. */
	int32 mActivePointIdx;

	/** The track connections we have. */
	UPROPERTY()
	class UFGRailroadTrackConnectionComponent* mConnectionComponents[ 2 ];

	/** The track connection we snap when building the track. */
	UPROPERTY()
	class UFGRailroadTrackConnectionComponent* mSnappedConnectionComponents[ 2 ];

	/** All the generated spline meshes. */
	UPROPERTY()
	TArray< class USplineMeshComponent* > mSplineMeshes;

	/** This is an additional floor data for the spline data (local space). */
	TArray< FVector > mFloorData;

	/** Cached from the default buildable. */
	UPROPERTY()
	class UStaticMesh* mMesh;
	float mMeshLength;
};
