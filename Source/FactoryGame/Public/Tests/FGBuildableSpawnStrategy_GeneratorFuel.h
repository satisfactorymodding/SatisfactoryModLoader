// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGBuildableSpawnStrategy_Factory.h"
#include "FGBuildableSpawnStrategy_GeneratorFuel.generated.h"

class UFGItemDescriptor;

// Spawn strategy for generator buildings
UCLASS()
class FACTORYGAME_API UFGBuildableSpawnStrategy_GeneratorFuel : public UFGBuildableSpawnStrategy_Factory
{
	GENERATED_BODY()
public:
	UFGBuildableSpawnStrategy_GeneratorFuel();

	virtual void PostSpawnBuildable(AFGBuildable* buildable) override;
	virtual UFGPowerConnectionComponent* GetAutoSupplyPowerConnection() const override;
public:
	// When set to a valid item descriptor, the test manager will automatically saturate the fuel slot with the given item
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Buildable | Generator", meta = ( ExposeOnSpawn ) )
	TSubclassOf<UFGItemDescriptor> mAutoSaturatedFuel;
	
	// Whenever this generator should have it's supplemental resource automatically saturated by the test manager
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Buildable | Manufacturer", meta = ( ExposeOnSpawn ) )
	bool mAutoSaturateSupplementalResource;

	// Whenever this generator must have it's outputs automatically consumed by the test manager. Only used for generators that give off a byproduct (e.g. nuclear power plants)
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Buildable | Manufacturer", meta = ( ExposeOnSpawn ) )
	bool mAutoConsumeOutputs;
};
