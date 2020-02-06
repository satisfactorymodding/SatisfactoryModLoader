// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "FGBuildableFactoryBuilding.h"
#include "FGBuildableWall.generated.h"

/**
 * A wall that can be build on foundations, floors and other walls.
 */
UCLASS( Abstract )
class FACTORYGAME_API AFGBuildableWall : public AFGBuildableFactoryBuilding
{
	GENERATED_BODY()
public:
	AFGBuildableWall();

public:
	/** Width of the wall */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Wall" )
	float mWidth;

	/** Height of the wall */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Wall" )
	float mHeight;
};
