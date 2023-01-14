// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "UObject/Interface.h"
#include "FGSplineBuildableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UFGSplineBuildableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Universal functions that we use to get data from different buildables to reconstruct their spline meshes (used by the blueprint hologram)
 */
class FACTORYGAME_API IFGSplineBuildableInterface
{
	GENERATED_BODY()

public:
	virtual TArray< FSplinePointData > GetSplinePointData() = 0;
	virtual float GetMeshLength() = 0;
	virtual FVector GetCollisionExtent() = 0;
	virtual float GetCollisionSpacing() = 0;
	virtual FVector GetCollisionOffset() = 0;
	virtual UStaticMesh* GetUsedSplineMesh() = 0;
};
