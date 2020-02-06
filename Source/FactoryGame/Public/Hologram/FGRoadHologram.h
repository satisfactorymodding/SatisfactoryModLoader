// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "FGSplineHologram.h"
#include "FGRoadHologram.generated.h"

//@todonow Broke this when making the lifts
/**
 * Hologram for spline roads.
 */
UCLASS()
class FACTORYGAME_API AFGRoadHologram : public AFGSplineHologram
{
	GENERATED_BODY()
public:
	/** Ctor */
	AFGRoadHologram();

	// Begin AActor interface
	virtual void BeginPlay() override;
	// Begin AActor interface

	// Begin AFGHologram interface
	virtual class USceneComponent* SetupComponent( USceneComponent* attachParent, UActorComponent* componentTemplate, const FName& componentName ) override;
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	virtual bool MultiStepPlacement() override;
	// End AFGHologram interface

	// Begin AFGBuildableHologram interface
	virtual void ConfigureActor( class AFGBuildable* inBuildable ) const override;
	virtual void ConfigureComponents( class AFGBuildable* inBuildable ) const override;
	// End AFGBuildableHologram interface

protected:
	// Begin AFGBuildableHologram interface
	virtual void CheckValidFloor() override;
	virtual void CheckClearance() override;
	// End AFGBuildableHologram interface

private:
	/** Check for nearby snapping connections. */
	class UFGRoadConnectionComponent* FindOverlappingConnectionComponent( const FVector& location, float radius, class UFGRoadConnectionComponent* ignoredConnection, bool ignoreIsConnected ) const;

private:
	/** This is an additional floor data for the spline data (local space). */
	TArray< FVector > mFloorData;

	/** Index of the currently moved point. */
	int32 mCurrentConnection;

	/** The connections we have. */
	UPROPERTY()
	class UFGRoadConnectionComponent* mConnectionComponents[ 2 ];

	/** The connection we snapped to. */
	UPROPERTY()
	class UFGRoadConnectionComponent* mSnappedConnectionComponents[ 2 ];
};
