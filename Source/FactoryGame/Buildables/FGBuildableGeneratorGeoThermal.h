// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "FGBuildableGenerator.h"
#include "FGBuildableGeneratorGeoThermal.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGBuildableGeneratorGeoThermal : public AFGBuildableGenerator
{
	GENERATED_BODY()
public:

	// Begin AActor interface
	virtual void Destroyed() override;
	// End AActor interface 
	
	/** Set the resource node for this generator */
	void SetResourceNode( class AFGResourceNode* resourceNode );

protected:
	// Begin AFGBuildableGenerator interface
	virtual bool CanStartPowerProduction_Implementation() const override;
	virtual void Factory_StartPowerProduction_Implementation() override;
	virtual void Factory_StopPowerProduction_Implementation() override;
	// End AFGBuildableGenerator interface

private:
	/** This is the geyser this generator is placed on */
	UPROPERTY( SaveGame )
	AFGResourceNode* mExtractResourceNode;
};
