// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Buildables/FGBuildableFactoryBuilding.h"
#include "FGBuildableStair.generated.h"

UENUM()
enum class EBuildableStairDirection : uint8
{
	EBSD_Right		UMETA( DisplayName = "Right" ),
	EBSD_Left		UMETA( DisplayName = "Left" ),
	EBSD_Straight	UMETA( DisplayName = "Straight" )
};

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGBuildableStair : public AFGBuildableFactoryBuilding
{
	GENERATED_BODY()
public:
	AFGBuildableStair();

	UPROPERTY( EditDefaultsOnly, Category = "Stair" )
	EBuildableStairDirection mStairDirection;

	/** Height of the staircase. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Stair" )
	float mHeight;

	/** Size of the staircase. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Stair" )
	float mSize;
};
