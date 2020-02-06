// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGSplineHologram.h"
#include "FGRailroadBridgeHologram.generated.h"


UCLASS()
class FACTORYGAME_API AFGRailroadBridgeHologram : public AFGSplineHologram
{
	GENERATED_BODY()
public:
	AFGRailroadBridgeHologram();

	// Begin AFGHologram interface
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	virtual bool MultiStepPlacement() override;
	// End AFGHologram interface

	// Begin AFGBuildableHologram interface
	virtual void ConfigureActor( class AFGBuildable* inBuildable ) const override;
	// End AFGBuildableHologram interface

private:
	/** Check for nearby snapping connections. */
	class AFGBuildableFoundation* FindOverlappingFoundation( const FVector& location, float radius ) const;

private:
	/** Index of the currently moved point. */
	int32 mCurrentConnection;

	/** Where we snapped. */
	UPROPERTY()
	class AFGBuildableFoundation* mSnappedFoundation[ 2 ];
	FTransform mSnappedTransform[ 2 ];
};
