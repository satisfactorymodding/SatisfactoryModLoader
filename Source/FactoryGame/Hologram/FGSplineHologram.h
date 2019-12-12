// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "FGBuildableHologram.h"
#include "Components/SplineComponent.h"
#include "../FSplinePointData.h"
#include "FGSplineHologram.generated.h"

//@todo This is only used by the roads for now, use this for the conveyors/tracks as well.
/**
 * Base hologram for all spline type holograms.
 */
UCLASS()
class FACTORYGAME_API AFGSplineHologram : public AFGBuildableHologram
{
	GENERATED_BODY()
public:
	AFGSplineHologram();

	// Begin AActor Interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	// End AActor Interface

	// Begin AFGHologram Interface
	virtual TArray< FItemAmount > GetCost( bool includeChildren ) const override;
	// End AFGHologram Interface

protected:
	/** Update the spline on the client. */
	UFUNCTION()
	virtual void OnRep_SplineData();

	/** Override this to return how many segments to pay for. Defaults to 1. */
	virtual int32 GetNumCostSections() const;

protected:
	/** The spline component we're placing. */
	UPROPERTY( VisibleAnywhere, Category = "Spline" )
	class USplineComponent* mSplineComponent;

	/** This is the data needed to create the spline component (local space). */
	UPROPERTY( ReplicatedUsing = OnRep_SplineData )
	TArray< FSplinePointData > mSplineData;
};
