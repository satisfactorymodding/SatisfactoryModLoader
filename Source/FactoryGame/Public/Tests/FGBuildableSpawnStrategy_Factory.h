// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGBuildableSpawnStrategy.h"
#include "FGBuildableSpawnStrategy_Factory.generated.h"

class UFGPowerShardDescriptor;
class UFGPowerConnectionComponent;

// Spawn strategy specifically for factory buildables (e.g. the ones inheriting from FGBuildableFactory)
UCLASS()
class FACTORYGAME_API UFGBuildableSpawnStrategy_Factory : public UFGBuildableSpawnStrategy
{
	GENERATED_BODY()
public:
	UFGBuildableSpawnStrategy_Factory();

	virtual bool IsCompatibleWith(AFGBuildable* buildable) const override;
	virtual void PostSpawnBuildable(AFGBuildable* buildable) override;
protected:
	virtual UFGPowerConnectionComponent* GetAutoSupplyPowerConnection() const;
public:
	// Power shard class to use for potential override. Needs to be valid.
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Buildable | Factory" )
	TSubclassOf<UFGPowerShardDescriptor> mPotentialPowerShardClass;
	
	// Allows overriding the potential (overclock) of the machine. Will automatically put enough shards to achieve the provided level.
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Buildable | Factory" )
	float mPotentialOverride;

	// Whenever the buildable should be automatically connected to the infinite power grid hosted by the test manager.
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Buildable | Factory", meta = ( ExposeOnSpawn ) )
	bool mAutoSupplyPower;

	// Allows pausing the production in the buildable by default
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Buildable | Factory" )
	bool mPauseProduction;
};