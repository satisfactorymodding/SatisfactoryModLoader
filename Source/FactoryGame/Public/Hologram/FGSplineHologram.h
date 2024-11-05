// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SplineComponent.h"
#include "FGBuildableHologram.h"
#include "FGSplineHologram.generated.h"

UENUM()
enum class ESplineHologramBuildStep : uint8
{
	SHBS_FindStart,
	SHBS_AdjustStartingPole,
	SHBS_PlacePoleOrSnapEnding,
	SHBS_AdjustPole
};

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
	
	virtual bool CanNudgeHologram() const override;

	/** Checks if we have snapped to any connection */
	virtual bool IsConnectionSnapped( bool lastConnection );

	/** Returns reference to spline point data */
	void GetLastSplineData( FSplinePointData& data );

	virtual void ResetBuildSteps();

	FORCEINLINE ESplineHologramBuildStep GetCurrentBuildStep() { return mBuildStep; }
protected:
	FORCEINLINE TArray<FSplinePointData> GetSplineData() const { return mSplineData; }

	// Begin AFGHologram Interface
	virtual bool IsHologramIdenticalToActor( AActor* actor, const FVector& hologramLocationOffset ) const override;
	// End AFGHologram Interface
	
	/** Update the spline on the client. */
	UFUNCTION()
	virtual void OnRep_SplineData();


	/** Let children update their spline. */
	virtual void UpdateSplineComponent();

	virtual void UpdateClearanceData();

protected:
	/** The spline component we're placing. */
	UPROPERTY( VisibleAnywhere, Category = "Spline" )
	class USplineComponent* mSplineComponent;

	/** This is the data needed to create the spline component (local space). */
	UPROPERTY( ReplicatedUsing = OnRep_SplineData, CustomSerialization )
	TArray< FSplinePointData > mSplineData;

	UPROPERTY( Replicated )
	ESplineHologramBuildStep mBuildStep = ESplineHologramBuildStep::SHBS_FindStart;

	/** Index of the currently moved point. */
	int32 mActivePointIdx;
};
