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

	// Begin Save Interface
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	// End Save Interface

	/** Set the extractable resource interface for this generator */
	void SetExtractableResource( TScriptInterface< class IFGExtractableResourceInterface > extractableResource );

protected:
	// Begin AFGBuildableGenerator interface
	virtual bool CanStartPowerProduction_Implementation() const override;
	virtual void Factory_StartPowerProduction_Implementation() override;
	virtual void Factory_StopPowerProduction_Implementation() override;
	// End AFGBuildableGenerator interface

private:
	/** DEPRICATED - Use mExtractableResource instead. This exists for save functionality
	*	This is the geyser this generator is placed on
	*/
	UPROPERTY( SaveGame )
	class AFGResourceNode* mExtractResourceNode;

	/** Saved interface to the object we are extracting resrouces from */
	UPROPERTY( SaveGame )
	TScriptInterface< class IFGExtractableResourceInterface > mExtractableResource;

public:
	FORCEINLINE ~AFGBuildableGeneratorGeoThermal() = default;
};
