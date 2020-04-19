// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/StaticMesh.h"
#include "Array.h"
#include "GameFramework/Actor.h"
#include "Components/SplineMeshComponent.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "HologramHelpers.h"
#include "Hologram/FGSplineHologram.h"
#include "Components/SplineComponent.h"
#include "FGPipelineHologram.generated.h"

/**
 * Hologram for constructing pipelines.
 */
UCLASS()
class FACTORYGAME_API AFGPipelineHologram : public AFGSplineHologram
{
	GENERATED_BODY()
public:
	AFGPipelineHologram();

	// Begin AActor Interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	// End AActor Interface

	// Begin AFGHologram Interface
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;

	void RouteSelectedSplineMode( FVector startLocation, FVector startNormal, FVector endLocation, FVector endNormal );

	virtual bool DoMultiStepPlacement( bool isInputFromARelease )  override;
	virtual int32 GetBaseCostMultiplier() const override;
	virtual void SpawnChildren( AActor* hologramOwner, FVector spawnLocation, APawn* hologramInstigator ) override;
	virtual void GetSupportedScrollModes( TArray< EHologramScrollMode >* out_modes ) const override;
	virtual void GetSupportedSplineModes_Implementation( TArray< EHologramSplinePathMode >& out_splineModes ) const override;
	bool IsValidHitResult( const FHitResult& hitResult ) const override;
	void AdjustForGround( const FHitResult& hitResult, FVector& out_adjustedLocation, FRotator& out_adjustedRotation ) override;
	bool TrySnapToActor( const FHitResult& hitResult ) override;
	void OnInvalidHitResult() override;
	void Scroll( int32 delta ) override;
	virtual bool CanTakeNextBuildStep() const override;
	// End AFGHologram Interface

	// Begin FGConstructionMessageInterface
	virtual void SerializeConstructMessage( FArchive& ar, FNetConstructionID id ) override;
	virtual void ClientPreConstructMessageSerialization() override;
	virtual void ServerPostConstructMessageDeserialization() override;
	// End FGConstructionMessageInterface

	virtual void OnPendingConstructionHologramCreated_Implementation( AFGHologram* fromHologram ) override;

	//[DavalliusA:Fri/13-12-2019]  Not here anymore. Set the build step instead with the EPipeHologramBuildStep
	/** Set point index directly */
	//void SetActivePointIndex( int32 newIndex ){ mActivePointIdx = newIndex; }

	virtual void ResetBuildSteps() override;

	/** Returns reference to spline point data */
	void GetLastSplineData( FSplinePointData &data );

	/** Checks if we have snapped to any connection */
	virtual bool IsConnectionSnapped( bool lastConnection ) override;

	void SetSnapToGuideLines( bool isEnabled ) override;

protected:
	// Begin AFGBuildableHologram Interface
	virtual void ConfigureActor( class AFGBuildable* inBuildable ) const override;
	virtual void ConfigureComponents( class AFGBuildable* inBuildable ) const override;
	virtual void CheckValidFloor() override;
	virtual void CheckClearance() override;
	virtual void CheckValidPlacement() override;
	// End AFGBuildableHologram Interface

	/** Creates the clearance detector used with Pipelines */
	void SetupPipeClearanceDetector();

	FORCEINLINE class AFGPipelineSupportHologram* GetChildPoleHologram() const { return mChildPoleHologram; }

private:
	/** Get the number of sections this conveyor has. Used for cost, max length etc. */
	int32 GetNumSections() const;

	/** Update the spline on the client. */
	UFUNCTION()
	void UpdateSplineComponent();

	void UpdateConnectionComponentsFromSplineData();

	void UpdateSplineCompFromSplineData();

	/**
	* This routes the spline to the new location. Inserting bends and straights.
	*/
	void AutoRouteSpline(
		const FVector& startConnectionPos,
		const FVector& startConnectionNormal,
		const FVector& endConnectionPos,
		const FVector& endConnectionNormal );
	/**
	* This routes the spline to the new location. Inserting bends and straights.
	*/
	void Auto2DRouteSpline(
		const FVector& startConnectionPos,
		const FVector& startConnectionNormal,
		const FVector& endConnectionPos,
		const FVector& endConnectionNormal );

	void AutoRouteNoodleSpline( const FVector& startConnectionPos, const FVector& startConnectionNormal, const FVector& endConnectionPos, const FVector& endConnectionNormal );

	/**
	* This routes the spline adding a potential 90 degree vertical rise before reaching the end if the height difference is large enough
	*/
	void HorizontalAndVerticalRouteSpline(
		bool horizontalFirst,
		const FVector& startConnectionPos,
		const FVector& startConnectionNormal,
		const FVector& endConnectionPos,
		const FVector& endConnectionNormal );
	void HorizontalAndVerticalRouteSplineNew(
		bool horizontalFirst,
		const FVector& startConnectionPos,
		const FVector& startConnectionNormal,
		const FVector& endConnectionPos,
		const FVector& endConnectionNormal );

	/**
	* Path finding route of a spline from start to end location.
	*/
	void PathFindingRouteSpline(
		TArray< struct FHologramAStarNode >& pathNodes,
		const FVector& startConnectionPos,
		const FVector& startConnectionNormal,
		const FVector& endConnectionPos,
		const FVector& endConnectionNormal );


	bool ValidateMinLength();

	
	/** ValidateCurvatureAndReturnFaultyPosition
	 * checks the curvature of the spline component against the min bend radius and returns the position of the violation 
	 * 
	 * @return	float - distance along the spline the problem was detected. If 0 or negative, there were no problems
	 */
	float ValidateCurvatureAndReturnFaultyPosition();


	/**
	* Validates any fluid Pipeline specific requirements for allowing placement
	*/
	bool ValidateFluidRequirements();

public:
	static constexpr float MINIMUM_PIPE_CLEARANCE = FHologramPathingGrid::PATH_GRID_CELL_SIZE;
	static constexpr float MINIMUM_HOLOGRAM_LENGTH = FHologramPathingGrid::PATH_GRID_CELL_SIZE * 2.f;


private:



	bool mUsingCutstomPoleRotation = false;

	/**Used to redirect input and construct poles when needed*/
	UPROPERTY( Replicated )
	class AFGPipelineSupportHologram* mChildPoleHologram = nullptr;

	/** The two connection components for this pipeline. */
	UPROPERTY()
	class UFGPipeConnectionComponentBase* mConnectionComponents[ 2 ];

	/** The connections we've made. */
	UPROPERTY()
	class UFGPipeConnectionComponentBase* mSnappedConnectionComponents[ 2 ];

	/** Class of conveyor pole to place at the end. */
	UPROPERTY( EditDefaultsOnly, Category = "Pipeline" )
	TSubclassOf< class UFGRecipe > mDefaultPipelineSupportRecipe;

	/** What radius will the bends have. */
	UPROPERTY( EditDefaultsOnly, Category = "Pipeline" )
	float mBendRadius;

	/** What radius will the bends have in the 2D mode AKA conveyor mode. Should be in sync with conveyors. */
	UPROPERTY( EditDefaultsOnly, Category = "Pipeline" )
	float mBendRadius2D = 199.0; //@TODO:[DavalliusA:Sun/08-12-2019] should we make something here that can check itself against conveyors to let designers know?

	/** The minimum allowed bend radius before the shape get's invalid */
	UPROPERTY( EditDefaultsOnly, Category = "Pipeline" )
	float mMinBendRadius = 75;

	/** Maximum number of meshes per pipe */
	UPROPERTY( EditDefaultsOnly, Category = "Pipeline" )
	int32 mMaxLength;

	/** Arrow to indicate the direction of the conveyor while placing it. */
	UPROPERTY()
	class UStaticMeshComponent* mConnectionArrowComponent;

	/** Struct for generating smart pathing between two connections */
	struct FHologramPathingGrid* mPathingGrid;

	/** Is path finding possible with the given points? */
	bool mCanPerformPathing;

	/** All the generated spline meshes. */
	UPROPERTY()
	TArray< class USplineMeshComponent* > mSplineMeshes;

	/** All the generated collision meshes. */
	UPROPERTY()
	TArray< class UShapeComponent* > mCollisionMeshes;

	/** Cached from the default buildable. */
	UPROPERTY()
	class UStaticMesh* mMesh;
	float mMeshLength;

	bool mPoleSnappedToActor = false;

public:
	FORCEINLINE ~AFGPipelineHologram() = default;
};
