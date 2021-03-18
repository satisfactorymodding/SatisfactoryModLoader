// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Hologram/FGSplineHologram.h"
#include "Components/SplineComponent.h"
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

	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	// End AActor interface

	// Begin AFGHologram interface
	virtual class USceneComponent* SetupComponent( USceneComponent* attachParent, UActorComponent* componentTemplate, const FName& componentName ) override;
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	virtual int32 GetBaseCostMultiplier() const override;
	virtual void SpawnChildren( AActor* hologramOwner, FVector spawnLocation, APawn* hologramInstigator ) override;
	virtual bool DoMultiStepPlacement(bool isInputFromARelease) override;
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

	/** Get a reference to the stored snapped connection references (excludes null snapped components) */
	TArray< class UFGRailroadTrackConnectionComponent* > GetSnappedConnectionComponents();

protected:
	// Begin AFGBuildableHologram interface
	virtual void CheckValidPlacement() override;
	virtual void CheckValidFloor() override;
	virtual void CheckClearance() override;
	// End AFGBuildableHologram interface

	// Begin AFGSplineHologram interface
	virtual void UpdateSplineComponent() override;
	// End AFGSplineHologram interface

private:
	void TryFindAndSnapToOverlappingConnection( int32 forConnectionIndex, FVector& inout_newLocation, FVector& inout_newTangent );
	void TryPlaceSwitchControl( int32 forConnectionIndex );

	bool ValidateGrade();
	bool ValidateCurvature();

	/** This routes the spline to the new location. Giving it a nice curvature. */
	void AutoRouteSpline(
		const FVector& startConnectionPos,
		const FVector& startConnectionNormal,
		const FVector& endConnectionPos,
		const FVector& endConnectionNormal );

private:
	/** If we drag out a turnout, this is the switch control to spawn. */
	UPROPERTY( EditDefaultsOnly, Category = "Tracks" )
	TSubclassOf<class UFGRecipe> mDefaultSwitchControlRecipe;

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

	/** Optional child hologram to build if we are dragging out a turnout */
	UPROPERTY( Replicated )
	class AFGRailroadSwitchControlHologram* mSwitchControls[ 2 ];
};
