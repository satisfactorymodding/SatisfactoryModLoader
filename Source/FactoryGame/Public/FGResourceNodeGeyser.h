// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Buildables/FGBuildableGeneratorGeoThermal.h"
#include "Resources/FGResourceNode.h"
#include "FGResourceNodeGeyser.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGResourceNodeGeyser : public AFGResourceNode
{
	GENERATED_BODY()

public:
	/** CTOR, who the hell is that? Some Star Wars robot? */
	AFGResourceNodeGeyser();

	virtual void BeginPlay() override;
	
	void NotifyNodeOfGeoThermal( class AFGBuildableGeneratorGeoThermal* geoThermal ) { mAttachedGeoThermals.AddUnique( geoThermal ); }
	
private:

	/**
	 * Tracks all thermal generators attached. In begin play if we have more than 1 we know people have either cheated
	 * (or likely abused the brief time during EXP blueprint release when this could be done via blueprints)
	 */
	UPROPERTY()
	TArray< class AFGBuildableGeneratorGeoThermal* > mAttachedGeoThermals;
};
