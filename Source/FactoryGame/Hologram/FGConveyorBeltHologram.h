// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/StaticMesh.h"
#include "Array.h"
#include "GameFramework/Actor.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "FGFactoryHologram.h"
#include "Components/SplineComponent.h"
#include "../FSplinePointData.h"
#include "../FGFactoryConnectionComponent.h"
#include "FGConveyorBeltHologram.generated.h"

#define NUM_CONNECTIONS 2

/**
 * Hologram for the conveyor belts, contains all the curve bending magic.
 */
UCLASS()
class FACTORYGAME_API AFGConveyorBeltHologram : public AFGBuildableHologram
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
	virtual bool MultiStepPlacement() override;
	virtual TArray< FItemAmount > GetCost( bool includeChildren ) const override;
	virtual AActor* GetUpgradedActor() const override;
	virtual void SpawnChildren( class UFGBuildGunStateBuild* state ) override;
	// End AFGHologram Interface

	FORCEINLINE EFactoryConnectionDirection GetActiveConnectionDirection() { return mSnappedConnectionComponents[0] && mActivePointIdx != 0 ? mSnappedConnectionComponents[0]->GetDirection() : EFactoryConnectionDirection::FCD_ANY; }

	/** Returns any AFGBuildables that the ConveyorBeltHologram are currently snapping to */
	TArray<AFGBuildable*> GetAnyConnectedBuildables();

protected:
	// Begin AFGBuildableHologram Interface
	virtual void ConfigureActor( class AFGBuildable* inBuildable ) const override;
	virtual void ConfigureComponents( class AFGBuildable* inBuildable ) const override;
	virtual void CheckValidFloor() override;
	virtual void CheckClearance() override;
	virtual void CheckValidPlacement() override;
	// End AFGBuildableHologram Interface

	// Begin AFGHologram Interface
	virtual void SetMaterial( class UMaterialInterface* material ) override;
	// End AFGHologram Interface

	/** Creates the clearance detector used with conveyor belts */
	void SetupClearanceDetector();

private:
	/** Get the number of sections this conveyor has. Used for cost, max length etc. */
	int32 GetNumSections() const;

	/** Update the spline on the client. */
	UFUNCTION()
	void OnRep_SplineData();

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
	bool ValidateLength();

private:
	/** The spline component we're placing. */
	UPROPERTY()
	class UFGSplineComponent* mSplineComponent;

	/** This is the data needed to create the spline component (local space). */
	UPROPERTY( ReplicatedUsing = OnRep_SplineData )
	TArray< FSplinePointData > mSplineData;

	/** Index of the currently moved point. */
	int32 mActivePointIdx;

	/** The two connection components for this conveyor. */
	UPROPERTY()
	class UFGFactoryConnectionComponent* mConnectionComponents[ NUM_CONNECTIONS ];

	/** The connections we've made. */
	UPROPERTY()
	class UFGFactoryConnectionComponent* mSnappedConnectionComponents[ NUM_CONNECTIONS ];

	/** The poles we may place automatically. */
	UPROPERTY( Replicated )
	class AFGConveyorPoleHologram* mConveyorPoles[ 2 ];

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
};
