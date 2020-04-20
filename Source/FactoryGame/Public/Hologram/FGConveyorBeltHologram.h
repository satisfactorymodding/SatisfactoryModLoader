// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Components/SplineMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Array.h"
#include "GameFramework/Actor.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "Hologram/FGSplineHologram.h"
#include "FGFactoryHologram.h"
#include "Components/SplineComponent.h"
#include "../FGFactoryConnectionComponent.h"
#include "FGConveyorBeltHologram.generated.h"

/**
 * Hologram for the conveyor belts, contains all the curve bending magic.
 */
UCLASS()
class FACTORYGAME_API AFGConveyorBeltHologram : public AFGSplineHologram
{
	GENERATED_BODY()
public:
	AFGConveyorBeltHologram();

	// Begin AActor Interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	// End AActor Interface

	// Begin AFGHologram Interface
	virtual bool TryUpgrade( const FHitResult& hitResult ) override;
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	virtual bool DoMultiStepPlacement(bool isInputFromARelease) override;
	virtual int32 GetBaseCostMultiplier() const override;
	virtual AActor* GetUpgradedActor() const override;
	virtual void OnInvalidHitResult() override;
	virtual void SpawnChildren( AActor* hologramOwner, FVector spawnLocation, APawn* hologramInstigator ) override;
	virtual bool IsValidHitResult( const FHitResult& hitResult ) const override;
	virtual void AdjustForGround( const FHitResult& hitResult, FVector& out_adjustedLocation, FRotator& out_adjustedRotation ) override;
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	virtual void Scroll( int32 delta ) override;
	virtual void GetSupportedScrollModes( TArray<EHologramScrollMode>* out_modes ) const override;
	virtual bool CanTakeNextBuildStep() const override;
	// End AFGHologram Interface

	// Begin FGConstructionMessageInterface
	virtual void SerializeConstructMessage( FArchive& ar, FNetConstructionID id ) override;
	virtual void ClientPreConstructMessageSerialization() override;
	virtual void ServerPostConstructMessageDeserialization() override;
	// End FGConstructionMessageInterface

	FORCEINLINE EFactoryConnectionDirection GetActiveConnectionDirection()
	{ return mSnappedConnectionComponents[0] && mBuildStep != ESplineHologramBuildStep::SHBS_FindStart ? mSnappedConnectionComponents[0]->GetDirection() : EFactoryConnectionDirection::FCD_ANY; }


	/** Returns any AFGBuildables that the ConveyorBeltHologram are currently snapping to */
	TArray<AFGBuildable*> GetAnyConnectedBuildables();

protected:
	// Begin AFGBuildableHologram Interface
	virtual void CheckValidFloor() override;
	virtual void CheckClearance() override;
	virtual void CheckValidPlacement() override;

	virtual void ConfigureActor( class AFGBuildable* inBuildable ) const override;
	virtual void ConfigureComponents( class AFGBuildable* inBuildable ) const override;
	//void ConfigureSnappedBuilding( class AFGBuildable* inBuildable ) const override;

	// End AFGBuildableHologram Interface

	/** Creates the clearance detector used with conveyor belts */
	void SetupConveyorClearanceDetector();

private:
	// Begin FGSplineHologram
	virtual void UpdateSplineComponent() override;
	// End FGSplineHologram

	/** Get the number of sections this conveyor has. Used for cost, max length etc. */
	int32 GetNumSections() const;

	/** Create connection arrow component on the client. */
	UFUNCTION()
	void OnRep_ConnectionArrowComponentDirection();

	/**
	 * This routes the spline to the new location. Inserting bends and straights.
	 */
	void AutoRouteSpline(
		const FVector& startConnectionPos,
		const FVector& startConnectionNormal,
		const FVector& endConnectionPos,
		const FVector& endConnectionNormal );

	bool ValidateIncline();
	bool ValidateMinLength();

private:
	bool mUsingCutstomPoleRotation = false;

	/**Used to redirect input and construct poles when needed*/
	UPROPERTY( Replicated )
	class AFGConveyorPoleHologram* mChildPoleHologram = nullptr;

	/** The two connection components for this conveyor. */
	UPROPERTY()
	class UFGFactoryConnectionComponent* mConnectionComponents[ 2 ];

	/** The connections we've made. */
	UPROPERTY( /*CustomSerialization*/ )
	class UFGFactoryConnectionComponent* mSnappedConnectionComponents[ 2 ];


	/** If we upgrade another conveyor belt this is the belt we replaces. */
	UPROPERTY()
	class AFGBuildableConveyorBelt* mUpgradedConveyorBelt;

	/** Class of conveyor pole to place at the end. */
	UPROPERTY( EditDefaultsOnly, Category = "Conveyor Belt" )
	TSubclassOf< class UFGRecipe > mDefaultConveyorPoleRecipe;

	/** What radius will the bends have. */
	UPROPERTY( EditDefaultsOnly, Category = "Conveyor Belt" )
	float mBendRadius;

	/** What is the maximum length of one segment. */
	UPROPERTY( EditDefaultsOnly, Category = "Conveyor Belt" )
	int32 mMaxLength;

	/** What is the maximum incline of the conveyor belt (degrees). */
	UPROPERTY( EditDefaultsOnly, Category = "Conveyor Belt" )
	float mMaxIncline;

	/** Used to replicate the direction arrow. */
	UPROPERTY( ReplicatedUsing = OnRep_ConnectionArrowComponentDirection )
	EFactoryConnectionDirection mConnectionArrowComponentDirection;

	/** Arrow to indicate the direction of the conveyor while placing it. */
	UPROPERTY()
	class UStaticMeshComponent* mConnectionArrowComponent;

	UPROPERTY( /*CustomSerialization*/ )
	FVector mConstructionPoleLocations[ 2 ];

	UPROPERTY(/*CustomSerialization*/)
	FRotator mConstructionPoleRotations[ 2 ];

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

public:
	FORCEINLINE ~AFGConveyorBeltHologram() = default;
};
