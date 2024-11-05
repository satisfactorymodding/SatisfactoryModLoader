// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGBuildableSpawnStrategy_Factory.h"
#include "FGBuildableSpawnStrategy_Manufacturer.generated.h"

// Spawn strategy for manufacturer buildings
UCLASS()
class FACTORYGAME_API UFGBuildableSpawnStrategy_Manufacturer : public UFGBuildableSpawnStrategy_Factory
{
	GENERATED_BODY()
public:
	UFGBuildableSpawnStrategy_Manufacturer();

	virtual void PostSpawnBuildable(AFGBuildable* buildable) override;
public:
	// Recipe to set on this manufacturer
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Buildable | Manufacturer", meta = ( ExposeOnSpawn ) )
	TSubclassOf<UFGRecipe> mRecipe;

	// Whenever this buildable must have it's inputs automatically saturated by the test manager.
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Buildable | Manufacturer", meta = ( ExposeOnSpawn ) )
	bool mAutoSaturateInputs;

	// Whenever this buildable must have it's outputs automatically consumed by the test manager.
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Buildable | Manufacturer", meta = ( ExposeOnSpawn ) )
	bool mAutoConsumeOutputs;
};
