// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Buildables/FGBuildableFactoryBuilding.h"
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
	AFGBuildableCornerWall();
	
public:
	/** Size of the wall corner */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Wall" )
	float mSize;

	/** Height of the wall corner */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Wall" )
	float mHeight;
};
