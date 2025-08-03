// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "FGBuildable.h"
#include "FGSplineBuildableInterface.h"
#include "FGBuildableSplineSnappedBase.generated.h"

/**
 * Base class for buildables that are placed using the SplineSnapHologram. Tex. ConveyorMonitor
 */
UCLASS(Abstract)
class FACTORYGAME_API AFGBuildableSplineSnappedBase : public AFGBuildable
{
	GENERATED_BODY()
public:

	UFUNCTION( BlueprintCallable, Category="SplineSnappedBase" )
	virtual void SetSnappedSplineBuildable( AFGBuildable* buildable )
	{
		fgcheck( buildable->Implements< UFGSplineBuildableInterface>() )

		mSnappedSplineBuildable = buildable;
	};

	UFUNCTION( BlueprintPure, Category="SplineSnappedBase" )
	AFGBuildable* GetSnappedSplineBuildable() const { return mSnappedSplineBuildable; }
	
protected:
	UPROPERTY( SaveGame )
	TObjectPtr< AFGBuildable > mSnappedSplineBuildable = nullptr;
};

