// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Buildables/FGBuildable.h"
#include "Components/SplineComponent.h"
#include "FGSplineComponent.h"
#include "FGBuildableRailroadBridge.generated.h"

/**
 * A spline based bridge for rail roads, it can be built between 2 existing foundations, bridge and track is built separately.
 */
UCLASS()
class FACTORYGAME_API AFGBuildableRailroadBridge : public AFGBuildable
{
	GENERATED_BODY()
public:
	AFGBuildableRailroadBridge();

	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	/** Get the length of the bridge */
	UFUNCTION( BlueprintPure, Category = "Railroad|Bridge" )
	FORCEINLINE float GetLength() const { return mSplineComponent->GetSplineLength(); }

protected:
	virtual void BeginPlay() override;

private:
	/** The hologram configures this actor. */
	friend class AFGRailroadBridgeHologram;

	/** The spline component for this bridge. */
	UPROPERTY( VisibleAnywhere, Category = "Spline" )
	class UFGSplineComponent* mSplineComponent;

	/** Spline data saved in a compact form for saving and replicating. All the vectors are in local space. */
	UPROPERTY( SaveGame, Replicated, Meta = (NoAutoJson = true) )
	TArray< FSplinePointData > mSplineData;
};
