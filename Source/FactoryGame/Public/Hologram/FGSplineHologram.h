// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "FGBuildableHologram.h"
#include "Components/SplineComponent.h"
#include "FGSplineHologram.generated.h"

UENUM()
enum class ESplineHologramBuildStep : uint8
{
	SHBS_FindStart,
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

	// Begin FGConstructionMessageInterface
	virtual void SerializeConstructMessage( FArchive& ar, FNetConstructionID id ) override;
	virtual void ClientPreConstructMessageSerialization() override;
	virtual void ServerPostConstructMessageDeserialization() override;
	// End FGConstructionMessageInterface

	// Handles the pending hologram state copy
	virtual void OnPendingConstructionHologramCreated_Implementation( AFGHologram* fromHologram ) override;

	/** Set point index directly */
	//void SetActivePointIndex( int32 newIndex ){ mActivePointIdx = newIndex; }

	/** Checks if we have snapped to any connection */
	virtual bool IsConnectionSnapped( bool lastConnection );

	/** Returns reference to spline point data */
	void GetLastSplineData( FSplinePointData& data );

	virtual void ResetBuildSteps();

	FORCEINLINE ESplineHologramBuildStep GetCurrentBuildStep() { return mBuildStep; }

	//shape test used for spline hologram clerance tests
	bool CheckClearanceForShapeIgnoreStructure( FCollisionShape& shape, FTransform transform, ECollisionChannel chanel, const FComponentQueryParams& params /*= FComponentQueryParams::DefaultComponentQueryParams */ );
protected:
	FORCEINLINE TArray<FSplinePointData> GetSplineData() const { return mSplineData; }

	/** Update the spline on the client. */
	UFUNCTION()
	void OnRep_SplineData();


	/** Let children update their spline. */
	virtual void UpdateSplineComponent();

protected:
	/** The spline component we're placing. */
	UPROPERTY( VisibleAnywhere, Category = "Spline" )
	class USplineComponent* mSplineComponent;

	/** This is the data needed to create the spline component (local space). */
	UPROPERTY( ReplicatedUsing = OnRep_SplineData /*, CustomSerialization*/ )
	TArray< FSplinePointData > mSplineData;

	/** Used in the construction message to determine if this has snapped to an existing connection or not */
	UPROPERTY( /*CustomSerialization*/ )
	uint8 mIsConnectionSnappedOnConstruction;

	UPROPERTY( Replicated )
	ESplineHologramBuildStep mBuildStep = ESplineHologramBuildStep::SHBS_FindStart;

	/** Index of the currently moved point. */
	int32 mActivePointIdx;

public:
	FORCEINLINE ~AFGSplineHologram() = default;
};
