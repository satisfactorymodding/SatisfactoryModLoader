// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGBuildableFactoryBuilding.h"
#include "FGBuildableCornerWall.generated.h"

/**
 * Woa this corner is so corner-y.
 * Assumes highest point of the corner is towards positive X and Y
 */
UCLASS()
class FACTORYGAME_API AFGBuildableCornerWall : public AFGBuildableFactoryBuilding
{
	GENERATED_BODY()
public:
	AFGBuildableCornerWall(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
public:
	/** Size of the wall corner */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Wall" )
	float mSize;

	/** Height of the wall corner */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Wall" )
	float mHeight;

	/** Whether or not this is an inverted corner. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Wall" )
	bool mIsInverted;
};

UCLASS( Abstract )
class FACTORYGAME_API AFGBuildableCornerWallLightweight : public AFGBuildableCornerWall
{
	GENERATED_BODY()
	AFGBuildableCornerWallLightweight(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
